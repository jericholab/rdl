# jericholab rdl - per-file Dropbox sync with round-trip verification (no batch folders)
#!/usr/bin/env python3
import os
import json
import time
import shutil
import logging
import sys
import hashlib
import random
import subprocess
from datetime import datetime
import schedule

# ---- external: your lightweight connectivity probe ----
from internetAccess import internet_on  # must NOT execute loops at import

# =============================
# Config & working directory
# =============================
os.chdir(os.path.dirname(os.path.abspath(__file__)))
with open('config.json', 'r') as config_file:
    config = json.load(config_file)
    print(json.dumps(config, indent=4))

print("RDL-python-syncing to Dropbox script (per-file, hardened)...")

# ---- paths (unchanged) ----
SOURCE  = "./logging-folder/2_tosync/"
TRANSIT = "./logging-folder/3_transit/"
SYNCED  = "./logging-folder/4_synced/"

CLOUD_BASE  = f"Professional/WIRED/{config['SITE']}"
CLOUD_FINAL = f"{CLOUD_BASE}"  # final destination in Dropbox
UPLOADER    = "/home/pi/Dropbox-Uploader/dropbox_uploader.sh"
LOG_FILE  = "logging-folder/sync.log"
MAX_BYTES = 10 * 1024 * 1024  # 10 MiB MAX FOR LOG FILE

#---- logging (file optional) ----
logging.basicConfig(
    filename=LOG_FILE,
    filemode="a",
    level=logging.INFO,
    format="%(asctime)s %(levelname)s: %(message)s"
)

# logging.basicConfig(
#     level=logging.INFO,
#     handlers=[logging.StreamHandler(sys.stdout)],
#     format="%(asctime)s %(levelname)s: %(message)s"
# )


# =============================
# Utilities
# =============================

def run_uploader(args):
    """Run dropbox_uploader.sh with args list; return (ok, stdout, stderr)."""
    cmd = [UPLOADER, "-s"] + args
    p = subprocess.run(cmd, capture_output=True, text=True)
    logging.info("CMD %s\nOUT:\n%s\nERR:\n%s", " ".join(cmd), p.stdout, p.stderr)
    return (p.returncode == 0, p.stdout, p.stderr)

def files_in_tree(root):
    """Yield (abs_path, rel_path_under_root) for all files under root."""
    for r, _, files in os.walk(root):
        for f in files:
            fp = os.path.join(r, f)
            rel = os.path.relpath(fp, root).replace("\\", "/")
            yield fp, rel

def sha256_file(path, buf=1<<20):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        while True:
            b = f.read(buf)
            if not b:
                break
            h.update(b)
    return h.hexdigest()

def remove_empty_dirs(path):
    """Delete empty directories under path (bottom-up)."""
    for root, dirs, files in os.walk(path, topdown=False):
        for d in dirs:
            p = os.path.join(root, d)
            try:
                if not os.listdir(p):
                    os.rmdir(p)
                    print(f"Removing empty folder: {p}")
            except Exception as e:
                logging.warning("Failed to remove dir %s: %s", p, e)

def move_all(src, dest):
    """Move all entries from src into dest (preserves subtrees)."""
    os.makedirs(dest, exist_ok=True)
    for name in os.listdir(src):
        shutil.move(os.path.join(src, name), os.path.join(dest, name))

def prune_log_if_big(path=LOG_FILE, max_bytes=MAX_BYTES):
    """Truncate the log file to zero bytes if it exceeds max_bytes."""
    try:
        if os.path.exists(path) and os.path.getsize(path) > max_bytes:
            # Truncate in-place; safe even if a FileHandler has the file open.
            open(path, "w").close()
    except Exception:
        pass  # per your request: no extra checks / failures ignored


# =============================
# Cloud helpers (Dropbox-Uploader)
# =============================

def cloud_mkdir(path):
    """Idempotent: create folder on Dropbox (ignore 'already exists')."""
    run_uploader(["mkdir", path])
    return True

def ensure_cloud_parents(dst_path):
    """
    Ensure parent directories for a Dropbox destination path exist.
    Example: ensure parents for '.../RDL/USB0/foo/bar.txt' creates .../RDL and .../RDL/USB0/foo
    """
    parts = dst_path.strip("/").split("/")
    if len(parts) <= 1:
        return
    acc = ""
    for part in parts[:-1]:  # up to the parent
        acc = f"{acc}/{part}" if acc else part
        cloud_mkdir(acc)

def cloud_download(src_cloud_path, dest_local_path):
    ok, _, err = run_uploader(["download", src_cloud_path, dest_local_path])
    if not ok:
        logging.error("Download failed: %s -> %s (%s)", src_cloud_path, dest_local_path, err)
    return ok

def cloud_move_with_parents(src, dst):
    """
    Move src -> dst on Dropbox. If it fails (e.g., missing parent), create parents and retry once.
    """
    ok, _, err = run_uploader(["move", src, dst])
    if ok:
        return True
    ensure_cloud_parents(dst)
    ok2, _, err2 = run_uploader(["move", src, dst])
    if not ok2:
        logging.error("Move failed: %s -> %s\nERR1:%s\nERR2:%s", src, dst, err, err2)
    return ok2

# =============================
# Per-file pipeline
# =============================

def upload_one_file(src_abs, relpath, retries=3, drop_sha_sidecar=True):
    """
    Per-file pipeline (no batch folders):
      1) Upload local file to a temp path on Dropbox: /<relpath>.tmp_<rand>
      2) Round-trip download and SHA-256 verify against local
      3) Server-side rename temp -> final (/<relpath>) [atomic exposure to consumers]
      4) Optionally upload a .sha256 sidecar
    Returns True on success; False on failure (caller will retry next run).
    """
    # Compute local hash once
    expected_sha = sha256_file(src_abs)

    # Build cloud paths
    rel_dir  = os.path.dirname(relpath).replace("\\", "/")
    base     = os.path.basename(relpath)
    tmp_name = base + f".tmp_{random.randint(1000,9999)}"

    # Final and temporary destinations on Dropbox
    dst_final = f"{CLOUD_FINAL}/{relpath}".replace("\\", "/")
    dst_tmp   = f"{CLOUD_FINAL}/{rel_dir}/{tmp_name}".rstrip("/")

    for attempt in range(1, retries + 1):
        try:
            # Ensure parent folders (for tmp path)
            ensure_cloud_parents(dst_tmp)

            # Upload to temp destination
            ok, _, err = run_uploader(["upload", src_abs, dst_tmp])
            if not ok:
                logging.error("[attempt %d] upload failed: %s -> %s (%s)", attempt, src_abs, dst_tmp, err)
                time.sleep(1.0)
                continue

            # Round-trip verify: download the just-uploaded temp object and compare hash
            tmp_local = src_abs + ".roundtrip"
            try:
                if not cloud_download(dst_tmp, tmp_local):
                    time.sleep(1.0)
                    continue
                got_sha = sha256_file(tmp_local)
            finally:
                try:
                    os.remove(tmp_local)
                except:
                    pass

            if got_sha.lower() != expected_sha.lower():
                logging.error("[attempt %d] hash mismatch for %s (got %s expected %s)",
                              attempt, relpath, got_sha, expected_sha)
                # clean temp object to avoid litter
                run_uploader(["delete", dst_tmp])
                time.sleep(1.0)
                continue

            # Commit: rename temp -> final (atomic exposure)
            if not cloud_move_with_parents(dst_tmp, dst_final):
                # if commit fails, try cleaning temp for safety
                run_uploader(["delete", dst_tmp])
                time.sleep(1.0)
                continue

            # Optional: upload .sha256 sidecar (helps downstream consumers)
            if drop_sha_sidecar:
                sha_text  = expected_sha + "  " + base + "\n"
                sha_local = src_abs + ".sha256"
                with open(sha_local, "w") as sf:
                    sf.write(sha_text)
                try:
                    sha_dest = dst_final + ".sha256"
                    ensure_cloud_parents(sha_dest)
                    ok_sha, _, err_sha = run_uploader(["upload", sha_local, sha_dest])
                    if not ok_sha:
                        logging.warning("sidecar upload failed: %s -> %s (%s)", sha_local, sha_dest, err_sha)
                finally:
                    try:
                        os.remove(sha_local)
                    except:
                        pass

            return True

        except Exception as e:
            logging.exception("[attempt %d] unexpected error on %s: %s", attempt, relpath, e)
            time.sleep(1.0)

    return False

# =============================
# Core sync
# =============================

def syncToDropbox():
    # ---- lock: prevent overlaps ----
    lock = "/home/pi/SHELF3/rdl_sync.lock"
    if os.path.exists(lock):
        logging.warning("Another sync run is active; skipping.")
        return
    open(lock, "w").close()

    try:
        # Housekeeping on local trees
        remove_empty_dirs(SOURCE)

        # ---- pre-flight internet ----
        if not internet_on():
            print("Offline. Will retry in 60 sec.")
            logging.warning("Offline pre-check. Aborting this run.")
            time.sleep(60)
            return

        # ---- stage new files: /2_tosync -> /3_transit (additive) ----
        if any(os.scandir(SOURCE)):
            print("Move from /tosync to /transit")
            move_all(SOURCE, TRANSIT)
        else:
            # nothing new; also tidy transit if empty dirs remain
            remove_empty_dirs(TRANSIT)

        if not any(os.scandir(TRANSIT)):
            print("Nothing to sync.")
            return

        # ---- per-file upload directly into /root with verification ----
        files_ok = 0
        files_fail = 0
        bytes_ok = 0

        # Walk files in TRANSIT (preserve hierarchy in relpath)
        to_move_local = []  # (src_abs, dest_abs_in_synced, size)

        for absf, rel in files_in_tree(TRANSIT):
            # Skip any temporary or sidecar artifacts inadvertently left behind
            if rel.endswith(".roundtrip") or rel.endswith(".tmp") or rel.endswith(".sha256"):
                continue

            ok = upload_one_file(absf, rel, retries=3, drop_sha_sidecar=False)
            if ok:
                st = os.stat(absf)
                dest_abs = os.path.join(SYNCED, rel)
                to_move_local.append((absf, dest_abs, st.st_size))
                files_ok += 1
                bytes_ok += st.st_size
            else:
                files_fail += 1

        # ---- local promotion: move only successfully-uploaded files ----
        for src_abs, dst_abs, _size in to_move_local:
            os.makedirs(os.path.dirname(dst_abs), exist_ok=True)
            shutil.copy2(src_abs, dst_abs)
            os.remove(src_abs)

        remove_empty_dirs(TRANSIT)

        # Metrics
        logging.info("Per-file sync round completed. ok=%d fail=%d bytes_ok=%d", files_ok, files_fail, bytes_ok)
        print(f"Sync round: ok={files_ok} fail={files_fail} MB_ok={bytes_ok/1e6:.2f}")

    finally:
        try:
            os.remove(lock)
        except:
            pass

# =============================
# Scheduler
# =============================
# Run every 30 seconds (your earlier cadence)
schedule.every(30).seconds.do(syncToDropbox)

while True:
    print("running...")
    schedule.run_pending()
    prune_log_if_big()
    time.sleep(15)


