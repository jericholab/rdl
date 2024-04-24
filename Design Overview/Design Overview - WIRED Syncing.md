
# JerichoLab RDL - Python Syncing Script


**Table of Contents**


  1. [Overview](#overview)
  2. [Features](#features)
  3. [Prerequisites](#prerequisites)
  4. [Configuration File](#configuration-file)
  5. [File Structure](#file-structure)
  6. [Usage](#usage)
  7. [Function Description](#function-description)
  8. [Scheduling](#scheduling)

## Overview

This Python script is designed for use in Jericho Laboratory's data logging system. It handles the automatic continuous synchronization of data files from the local system to Dropbox. The script utilizes configuration settings from a JSON file to manage paths and some of the synchronization behaviors.

## Features

- **Configuration Driven**: Utilizes a JSON file for manageable and dynamic configuration.
- **Logging**: Records operational logs to help trace the activity and troubleshoot issues (WIP).
- **Scheduled Syncing**: Executes file synchronization tasks at regular intervals.
- **Directory Management**: Ensures that all necessary directories exist and handles the file transfer between directories.

## Prerequisites

- Python 3.x
- `serial`, `datetime`, `schedule`, `time`, `shutil`, `os`, `logging`, `json` libraries (Most are standard with Python except `schedule` which can be installed via pip).
- `config.json`: A configuration file storing parameters like SD card name and site-specific settings.
- Dropbox Uploader script setup on the system for interfacing with Dropbox.

## Configuration File

`config.json` should contain the following keys:

```json
{
    "SD_CARD_NAME": "Name_of_the_SD_Card",
    "SITE": "Your_Site_Name"
}
```

- `SD_CARD_NAME`: Name of the SD card where backup files are stored.
- `SITE`: The site identifier used to categorize and store files correctly in Dropbox.

## File Structure

- **`log_internal.txt`**: Stores logs from the script's execution.
- **Data Directories**:
  - `./logging-folder/tosync/`: Initial directory where new data files are stored.
  - `./logging-folder/transit/`: Temporary transit location for files before syncing to Dropbox.
  - `./media/orangepi/$SD_CARD_NAME/`: The SD CARD is the typical final destination for the files (configured in the JSON file).

## Usage

Run the script in a Python environment where all dependencies have been satisfied. Ensure the Dropbox Uploader script is configured and accessible:

```bash
python3 path_to_script.py
```

The script will automatically handle file transfers and synchronization based on the set interval (currently every 10 seconds for demonstration purposes).

The script can also be run automatically by the associated Daemon (service).

## Function Description

- **`syncToDropbox()`**: Manages the process flow from moving files to syncing them with Dropbox, and finally to the backup storage.
- **`sync(src, dest)`**: Recursive function to copy files from the source to the destination, handle directory creation, and manage file deletions post-transfer.

## Scheduling

The script uses the `schedule` library to run the syncing process every 10 seconds. This interval can be adjusted to fit more practical operational needs, such as every hour or once daily.
