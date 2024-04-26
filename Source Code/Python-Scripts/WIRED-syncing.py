#jericholab - syncing RDL data with cloud
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
logging.basicConfig(filename="log_internal.txt", filemode="w", level=logging.DEBUG)
logging.info("This message will be logged to the file")


print("RDL-python-syncing to Dropbox script...")

source_path = "./logging-folder/tosync/"  #relative path"
transit_path = "./logging-folder/transit/"  #relative path"
#destination_path = "./logging-folder/synced/"
#destination_path = "/media/orangepi/SD_CARD1/"
destination_path = f"/media/orangepi/{config['SD_CARD_NAME']}/"

def thermography_plot(csv_filename):
    # Check if the file exists
    if not os.path.exists(csv_filename):
        raise FileNotFoundError("File does not exist.")

    # Check the file extension
    _, file_extension = os.path.splitext(csv_filename)
    
    # Set a new default save format, for example to 'jpeg'
    plt.rcParams['savefig.format'] = 'jpeg'

    if file_extension.lower() in ['.csv']:
        # If it's a CSV file, proceed with reading and plotting
        data = np.loadtxt(csv_filename, delimiter=' ')

        # Create the graphic using imshow for better control over aspect ratio
        plt.imshow(data, cmap='jet', aspect='auto')
        plt.colorbar()  # Add a color bar to indicate the temperature scale

        # Additional options for better visualization
        plt.title('Infrared Thermography Temperature Map')
        plt.xlabel('Column Index')
        plt.ylabel('Row Index')

        # Define the output directory
        output_directory = './logging-folder/tosync/cameras/infrared1/'
        if not os.path.exists(output_directory):
            os.makedirs(output_directory)  # Create the directory if it doesn't exist

        # Split the file path into the file name and extension
        filename_with_extension = os.path.basename(csv_filename)
        filename_without_extension, _ = os.path.splitext(filename_with_extension)
        print(filename_without_extension)

        # Save the figure as an image file
        #output_filepath = os.path.join(output_directory, 'thermography_temperature_map.png')
        output_filepath = os.path.join(output_directory, filename_without_extension)
        plt.savefig(output_filepath)
        plt.close()  # Close the plot to free up memory

    elif file_extension.lower() in ['.jpg', '.jpeg', '.png']:
        # Handle images files differently (no conversion required)
        print(f"CSV-to-IMG: Skipping JPEG file: {csv_filename}")

    else:
        # Optionally handle other file types or raise an exception
        print(f"CSV-to-IMG: Unsupported file type: {csv_filename}")
    
def syncToDropbox():
    print("move from /tosync to /transit folder")
    sync(source_path, transit_path)    #copy the files from local folders "/tosync" to "/transit"
    
    print("syncToDropbox")
    print("   ")
    from subprocess import call
    localSide1 = "./logging-folder/transit/RDL"
    cloudSide1 = f"Professional/WIRED/{config['SITE']}"
    localSide2 = "./logging-folder/transit/cameras"
    cloudSide2 = f"Professional/WIRED/{config['SITE']}"
    Upload = "/home/orangepi/Dropbox-Uploader/dropbox_uploader.sh -s upload" + " " + localSide1 +" " + cloudSide1
    call ([Upload], shell=True)
    Upload2 = "/home/orangepi/Dropbox-Uploader/dropbox_uploader.sh -s upload" + " " + localSide2 +" " + cloudSide2
    call ([Upload2], shell=True)
    print("move from /transit to backup folder (e.g. SD Card)")
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
            # Else (if the item is a file), copy it then remove it ca
            if not os.path.exists(d) or os.stat(s).st_mtime - os.stat(d).st_mtime > 1:
                print(s)
                thermography_plot(s)
                shutil.copy2(s, d) #copy
                os.remove(s)  #delete
                time.sleep(1) #to avoid error due to fast looping
   
    
schedule.every(10).seconds.do(syncToDropbox)
#schedule.every(1).minutes.do(syncToDropbox)


while True:
    print("running...")
    schedule.run_pending()
    time.sleep(10) #to avoid super fast looping


    
    

