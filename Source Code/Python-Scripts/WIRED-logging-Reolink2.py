#jericholab WIRED - test script to output reolink camera image at fixed interval

#import serial
from datetime import datetime
import schedule
import time
import shutil
import requests
import os  # library to interact with the operating system

print("Reolink logging python script...")

os.chdir(os.path.dirname(os.path.abspath(__file__)))  #change working directory to the directory containing the script

#HTTP is deactivated by default on each camera. This script requires HTTP, not HTTPS.

# Set the camera's IP address and login credentials
CAMERA_NAME = "reolink2"
CAMERA_IP = "192.168.0.196"
USERNAME = "admin"
PASSWORD = "password177"

# Build the URL for taking a snapshot
url = f"http://{CAMERA_IP}/cgi-bin/api.cgi?cmd=Snap&channel=0&rs=wuuPhkmUCeI9WG7F&user={USERNAME}&password={PASSWORD}"

#initializing
now = datetime.now()
dailyFolderNow = datetime.now()
#formatExpected = "%Y-%m-%d_%H"  #log once every hour
formatExpected = "%Y-%m-%d_%H_%M"  #log once every minute
now = now.strftime(formatExpected)
then = now
#formatDailyFolder = "%Y-%m-%d_%H_%M"  #daily folder (temporarily a minute folder for testing)
formatDailyFolder = "%Y-%m-%d"  #daily folder
dailyFolderNow = dailyFolderNow.strftime(formatDailyFolder)

def createFolder(folder_name):
    if not os.path.exists(folder_name):
        os.mkdir(folder_name)
        print("Folder created: ", folder_name)
    else:
        print("Folder already exists: ", folder_name)
        
def setUpFolders():
    level1 = "./logging-folder"
    level2 = level1 + "/2_tosync"
    level3 = level2 + "/cameras/"
    level4 = level3 + CAMERA_NAME
    folder_name = level4 + "/" + dailyFolderNow
    createFolder(level1)
    createFolder(level2)
    createFolder(level3)
    createFolder(level4)
    createFolder(folder_name)
    return folder_name

def takePicture():
    folder_name = setUpFolders() #rerun the function to create the daily folder, if applicable
    file_name= folder_name + '/' + now + '.jpg'  #where we save the data as it accumulates (include name and extension)

    # Send an HTTP request to the camera's web interface and download the image data
    response = requests.get(url)
    if response.status_code == 200:
        #with open('snapshot.jpg', 'wb') as f:
        with open(file_name, 'wb') as f:
            f.write(response.content)
            print(f'Snapshot saved to {file_name}')
    else:
        print('Error retrieving snapshot')

folder_name = setUpFolders()  # Run once at startup
print('Take initial picture')            
takePicture()

while True:
    now = datetime.now()
    now = now.strftime(formatExpected)  
    dailyFolderNow = datetime.now()
    dailyFolderNow = dailyFolderNow.strftime(formatDailyFolder) #update the dailyFolder

    if (now != then):
        takePicture()     
    
    #time.sleep(10) #to avoid super fast looping (in seconds)
    time.sleep(900) #force a 15-min interval
    then = now
   
    
   
