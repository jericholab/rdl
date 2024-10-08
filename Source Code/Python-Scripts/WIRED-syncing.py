#jericholab rdl - test script with python with daily file 
#!/usr/bin/env python3
import serial
from datetime import datetime
import schedule
import time
import shutil
import os   
import logging
import json
import numpy as np
import matplotlib.pyplot as plt

# Load the configuration file
with open('config.json', 'r') as config_file:
    config = json.load(config_file)
    print(json.dumps(config, indent=4))  # Print the config file
    
os.chdir(os.path.dirname(os.path.abspath(__file__)))  #change working directory to the directory containing the script

#configure the logging module
#logging.basicConfig(filename="log_internal.txt", filemode="w", level=logging.DEBUG)
#logging.info("This message will be logged to the file")


print("RDL-python-syncing to Dropbox script...")

source_path = "./logging-folder/2_tosync/"  #relative path"
transit_path = "./logging-folder/3_transit/"  #relative path"
destination_path = "./logging-folder/4_synced/"
#destination_path = "/media/orangepi/SD_CARD1/"
#destination_path = f"/media/orangepi/{config['SD_CARD_NAME']}/"
     
def syncToDropbox():
    
    remove_empty_dirs(source_path)  #remove any empty folders created before sync
    
    print("move from /tosync to /transit folder")
    sync(source_path, transit_path)    #copy the files from local folders "/tosync" to "/transit"
    
    print("syncToDropbox")
    print("   ")
    from subprocess import call
    #localSide1 = "./logging-folder/transit/RDL"
    localSide1 = transit_path + "/RDL"
    cloudSide1 = f"Professional/WIRED/{config['SITE']}"
    #localSide2 = "./logging-folder/transit/cameras"
    localSide2 = transit_path + "/cameras"
    cloudSide2 = f"Professional/WIRED/{config['SITE']}"
    #localSide3 = "./logging-folder/transit/internet"
    localSide3 = transit_path + "/internet"
    cloudSide3 = f"Professional/WIRED/{config['SITE']}"
    Upload = "/home/pi/Dropbox-Uploader/dropbox_uploader.sh -s upload" + " " + localSide1 +" " + cloudSide1
    #Upload = "/home/orangepi/Dropbox-Uploader/dropbox_uploader.sh -s upload" + " " + localSide1 +" " + cloudSide1
    call ([Upload], shell=True)
    #Upload2 = "/home/orangepi/Dropbox-Uploader/dropbox_uploader.sh -s upload" + " " + localSide2 +" " + cloudSide2
    Upload2 = "/home/pi/Dropbox-Uploader/dropbox_uploader.sh -s upload" + " " + localSide2 +" " + cloudSide2
    call ([Upload2], shell=True)
    Upload3 = "/home/pi/Dropbox-Uploader/dropbox_uploader.sh -s upload" + " " + localSide3 +" " + cloudSide3
    call ([Upload3], shell=True)    
    
    print("move from /transit to /synced")
    sync(transit_path, destination_path)    #copy the files from local folders "/transit" to "/synced"
    remove_empty_dirs(transit_path)  #remove any transit folder that became empty
    
def sync(src, dest):
    # If the destination directory doesn't exist, create it.
    if not os.path.exists(dest):
        os.makedirs(dest)

    # Walk through all files and directories in the source directory.
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dest, item)

        # If item is a directory, recurse into it
        if os.path.isdir(s):
            sync(s, d)
        else:
            # Else (if the item is a file), copy it then remove it ca
            if not os.path.exists(d) or os.stat(s).st_mtime - os.stat(d).st_mtime > 1:
                print(s)
                shutil.copy2(s, d) #copy
                os.remove(s)  #delete
                time.sleep(1) #to avoid error due to fast looping

def remove_empty_dirs(path):
    # Walk through the directory, bottom-up (to delete nested empty folders first)
    for root, dirs, files in os.walk(path, topdown=False):
        for dir_ in dirs:
            dir_path = os.path.join(root, dir_)
            # If the directory is empty, remove it
            if not os.listdir(dir_path):
                print(f"Removing empty folder: {dir_path}")
                os.rmdir(dir_path)
    
schedule.every(10).seconds.do(syncToDropbox)
#schedule.every(1).minutes.do(syncToDropbox)


while True:
    print("running...")
    schedule.run_pending()
    time.sleep(10) #to avoid super fast looping


    
    

