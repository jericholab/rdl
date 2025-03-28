#jericholab rdl - continuous RDL data logging with python script

#!/usr/bin/env python3
import serial
from datetime import datetime, timedelta
import schedule
import time
import shutil
import json
import os  # library to interact with the operating system

#Jam length threshold for reset
jam_threshold = 2 #minutes
#jam_threshold = 15 #minutes

# Load the configuration file
with open('config.json', 'r') as config_file:
    config = json.load(config_file)
    print(json.dumps(config, indent=4))  # Print the config file

os.chdir(os.path.dirname(os.path.abspath(__file__)))  #change working directory to the directory containing the script


print("RDL-python-logging...")
DEVICE_NAME = "USB0"
#ser=serial.Serial('/dev/ttyUSB0', 57600) #change the port and baud rate as needed
ser = serial.Serial('/dev/ttyUSB0', 57600, timeout=30)  # X-second timeout /// TEMP TEST
time.sleep(2)  #test #During initialization of the arduino, the arduino may send random noise.

# Clear input buffer  (this is an attempt to avoid the initial gibberish)
ser.reset_input_buffer()   #method 1
ser.write(b'reset\r')
time.sleep(2)

#initializing
now = datetime.now()
dailyFolderNow = datetime.now()

last_data_time = datetime.now()  # Timer to track the last time data was received    //NEW
timeout_duration = timedelta(minutes=jam_threshold)  # 1-minute timeout for no data received     //NEW

# if (now != then):
if (config['RDL_FILEFORMAT_ACTIVE'] == 'hourly'):
    formatExpected = "%Y-%m-%d_%H"  #create a new file every hour
    formatDailyFolder = "%Y-%m-%d"  #create a new folder every day
    
else:
    formatExpected = "%Y-%m-%d"  #create a new file every day
    formatDailyFolder = "%Y-%m"  #create a new folder every month
    
#print({config['RDL_FILEFORMAT_ACTIVE']})
#formatExpected = "%Y-%m-%d"  #create a new file every day
#formatExpected = "%Y-%m-%d_%H"  #create a new file every hour
#formatExpected = "%Y-%m-%d_%H_%M"  #create a new file every minute
now = now.strftime(formatExpected)
then = now

dailyFolderNow = dailyFolderNow.strftime(formatDailyFolder)

def createFolder(folder_name):
    if not os.path.exists(folder_name):
        os.mkdir(folder_name)
        print("Folder created: ", folder_name)
    else:
        print("Folder already exists: ", folder_name)

def setUpFolders1():
    level1 = "./logging-folder"
    level2 = level1 + "/1_inprogress"
    level3 = level2 + "/RDL/"
    folder_name = level3 + DEVICE_NAME
    createFolder(level1)
    createFolder(level2)
    createFolder(level3)
    createFolder(folder_name)
    return folder_name

def setUpFolders2():
    level1 = "./logging-folder"
    level2 = level1 + "/2_tosync"
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
        if ser.in_waiting > 0:   #this is a new test to avoid blocking call (ser.readline())
#             log_entry = f"Im in the ser.inwaiting() loop"    
#             file.write(log_entry)
#             print(log_entry)
            try:
#                 log_entry = f"Im in the try loop"    
#                 file.write(log_entry)
#                 print(log_entry)
                data = ser.readline().decode('ascii')
                last_data_time = datetime.now()  # Reset timer when data is received   //NEW
            except UnicodeDecodeError:  #handle potential errors
                data = 'x'   #if data corrupted, substitute with 'x' character
            except serial.SerialTimeoutException:
                print("Timeout occurred while reading from the serial port.")
            # Get the current timestamp from the PC
            timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')     
            # Format the data with the timestamp
            log_entry = f"{timestamp} {data}"    
            file.write(log_entry)
            print(log_entry)
        
        # Check if the Arduino has not spoken for 1 minutes   //NEW
        if datetime.now() - last_data_time > timeout_duration:
            log_entry = f"\nNo data received for {jam_threshold} minutes. Exiting to trigger service restart."    
            file.write(log_entry)
            file.flush()
            print(log_entry)
            time.sleep(1)
            break  # Exit the loop to stop the script and let systemd restart it
        

            
    #time.sleep(0.1) #to avoid super fast looping
    #time.sleep(0.1) #to avoid super fast looping
    then = now
