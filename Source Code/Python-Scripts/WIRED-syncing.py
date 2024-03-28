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

# Load the configuration file
with open('config.json', 'r') as config_file:
    config = json.load(config_file)






os.chdir(os.path.dirname(os.path.abspath(__file__)))  #change working directory to the directory containing the script

#configure the logging module
logging.basicConfig(filename="log_internal.txt", filemode="w", level=logging.DEBUG)
logging.info("This message will be logged to the file")


print("RDL-python-syncing to Dropbox script...")

source_path = "./logging-folder/tosync/"  #relative path"
transit_path = "./logging-folder/transit/"  #relative path"
#destination_path = "./logging-folder/synced/"
destination_path = "/media/orangepi/SD_CARD1/"

def syncToDropbox():
    print("move from /tosync to /transit folder")
    sync(source_path, transit_path)    #copy the files from local folders "/tosync" to "/transit"
    
    print("syncToDropbox")
    print("   ")
    from subprocess import call
    localSide1 = "./logging-folder/transit/RDL"
    cloudSide1 = f"Professional/WIRED/{config['SITE']}/RDL"
    localSide2 = "./logging-folder/transit/cameras"
    cloudSide2 = f"Professional/WIRED/{config['SITE']}/cameras"
    Upload = "/home/orangepi/Dropbox-Uploader/dropbox_uploader.sh -s upload" + " " + localSide1 +" " + cloudSide1
    call ([Upload], shell=True)
    Upload2 = "/home/orangepi/Dropbox-Uploader/dropbox_uploader.sh -s upload" + " " + localSide2 +" " + cloudSide2
    call ([Upload2], shell=True)
    
    print("move from /transit to /synced folder")
    sync(transit_path, destination_path)    #copy the files from local folders "/transit" to "/synced" 
    
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
            # Else (if the item is a file), copy it then remove it 
            if not os.path.exists(d) or os.stat(s).st_mtime - os.stat(d).st_mtime > 1:
                shutil.copy2(s, d) #copy
                os.remove(s)  #delete
                time.sleep(1) #to avoid error due to fast looping
   
    
schedule.every(10).seconds.do(syncToDropbox)
#schedule.every(1).minutes.do(syncToDropbox)


while True:
    print("running...")
    schedule.run_pending()
    time.sleep(10) #to avoid super fast looping


    
    
