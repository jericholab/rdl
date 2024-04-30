#jericholab rdl - continuous RDL data logging with python script

#!/usr/bin/env python3
import serial
from datetime import datetime
import schedule
import time
import shutil
import os  # library to interact with the operating system

os.chdir(os.path.dirname(os.path.abspath(__file__)))  #change working directory to the directory containing the script


print("RDL-python-logging...")
DEVICE_NAME = "USB0"
ser=serial.Serial('/dev/ttyUSB0', 57600) #change the port and baud rate as needed

time.sleep(2)  #test #During initialization of the arduino, the arduino may send random noise.



# Clear input buffer  (this is an attempt to avoid the initial gibberish)
ser.reset_input_buffer()   #method 1
#ser.flushInput()      #method 2 
#ser.flushOutput()      #method 2
#time.sleep(2)
#ser.write(b'quantity\r')
ser.write(b'reset\r')
time.sleep(2)

#initializing
now = datetime.now()
dailyFolderNow = datetime.now()
formatExpected = "%Y-%m-%d_%H"  #create a new file every hour
#formatExpected = "%Y-%m-%d_%H_%M"  #create a new file every minute
now = now.strftime(formatExpected)
then = now
#formatDailyFolder = "%Y-%m-%d_%H_%M"  #daily folder 
formatDailyFolder = "%Y-%m-%d"  #create a new folder every hour
dailyFolderNow = dailyFolderNow.strftime(formatDailyFolder)

def createFolder(folder_name):
    if not os.path.exists(folder_name):
        os.mkdir(folder_name)
        print("Folder created: ", folder_name)
    else:
        print("Folder already exists: ", folder_name)

def setUpFolders1():
    level1 = "./logging-folder"
    level2 = level1 + "/inprogress"
    level3 = level2 + "/RDL/"
    folder_name = level3 + DEVICE_NAME
    createFolder(level1)
    createFolder(level2)
    createFolder(level3)
    createFolder(folder_name)
    return folder_name

def setUpFolders2():
    level1 = "./logging-folder"
    level2 = level1 + "/tosync"
    level3 = level2 + "/RDL/"
    level4 = level3 + DEVICE_NAME
    folder_name = level4 + "/" + dailyFolderNow
    createFolder(level1)
    createFolder(level2)
    createFolder(level3)
    createFolder(level4)
    createFolder(folder_name)
    return folder_name

folder_name1 = setUpFolders1()  # Run once to create the "inprogress" folder
folder_name2 = setUpFolders2()  # Run once to create the "readytosync" folder
destination_path = folder_name2  #where we send the file when it is complete and ready to sync (relative path)

while True:
    now = datetime.now()
    now = now.strftime(formatExpected)  
    if (now != then):
      folder_name2 = setUpFolders2()  #create the daily sync folder with 'old' date
      dailyFolderNow = datetime.now() #update current time
      dailyFolderNow = dailyFolderNow.strftime(formatDailyFolder) #update the dailyFolder
      destination_path= folder_name2 #update the destination daily folder (after file moved)
      shutil.move(file_name, destination_path) #move file_name to the /sync_folder


    file_name= folder_name1 + "/RDL_" + now + "_" + DEVICE_NAME + ".txt"  #where we save the data as it accumulates (include name and extension) (relative path)
    
    with open(file_name, 'a') as file:
        try:
            #data = ser.readline().decode()
            data = ser.readline().decode('ascii')
        except UnicodeDecodeError:  #handle potential errors
            data = 'x'   #if data corrupted, substitute with 'x' character
        file.write(data)
        print(data)
    
    #time.sleep(1) #to avoid super fast looping
    then = now
