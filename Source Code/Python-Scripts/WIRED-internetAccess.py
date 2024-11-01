#Jericho Lab - Internet Access Logging Script

import requests
import time
from datetime import datetime
import json
import subprocess
import re
import psutil
import shutil
import schedule
import os  # library to interact with the operating system

# Load the configuration file
with open('config.json', 'r') as config_file:
    config = json.load(config_file)

def createFolder(folder_name):    #sub function for creating a folder
    if not os.path.exists(folder_name):
        os.mkdir(folder_name)
        print("Folder created: ", folder_name)
    else:
        print("Folder already exists: ", folder_name)

def setUpFolders1():  #set up the "in progress" subfolder
    level1 = "./logging-folder"
    level2 = level1 + "/1_inprogress"
    folder_name = level2 + "/internet/"
    #level3 = level2 + "/Internet/"
    #folder_name = level3 + DEVICE_NAME
    createFolder(level1)
    createFolder(level2)
    #createFolder(level3)
    createFolder(folder_name)
    return folder_name

def setUpFolders2():   #set up the "to sync" subfolder
    level1 = "./logging-folder"
    level2 = level1 + "/2_tosync"
    folder_name = level2 + "/internet/"
    #level4 = level3 + DEVICE_NAME
    #folder_name = level3 + "/" + dailyFolderNow
    createFolder(level1)
    createFolder(level2)
    #createFolder(level3)
    #createFolder(level4)
    createFolder(folder_name)
    return folder_name

folder_name1 = setUpFolders1()  # Run once to create the "inprogress" folder
folder_name2 = setUpFolders2()  # Run once to create the "tosync" folder
destination_path = folder_name2  #where we send the file when it is complete and ready to sync (relative path)
filename_format = "%Y-%m-%d"  #define log file as one per day
now = datetime.now()   #define present time
now = now.strftime(filename_format) #adjust time format
then = now  #initialize "then" as being equal to "now"
filename = folder_name1 + "InternetLog-Montreal-" + now +".txt"  #create file name with path

def internet_on():  #verify internet access
    try:
        # Attempt to request the Google homepage
        response = requests.get('http://www.google.com', timeout=5)
        # If the request succeeds, the internet is considered to be on.
        return response.status_code == 200
    except requests.ConnectionError:
        # If a connection error occurs, the internet is considered to be off.
        return False

def get_signal_strength():  #verify wifi signal strength
    # Run iwconfig wlan0 and capture the output
    result = subprocess.run(['iwconfig', 'wlan0'], capture_output=True, text=True)

    # Extract the signal strength using regex
    match = re.search(r'Signal level=(-\d+ dBm)', result.stdout)
    
    if match:
        return match.group(1)
    else:
        return "000 dBm"
        #return "Signal strength not found."

def print_cpu_usage():  # Function to print the CPU usage
    # psutil.cpu_percent() gives the CPU usage percentage
    cpu_usage = psutil.cpu_percent(interval=1)
    #print(f"Current CPU usage: {cpu_usage}%")
    return cpu_usage

def get_cpu_temperature():  # Function to read CPU temperature
    with open("/sys/class/thermal/thermal_zone0/temp", "r") as temp_file:
        # Read the temperature in millidegrees Celsius, convert it to degrees Celsius
        temp = float(temp_file.read()) / 1000.0
        return temp

# Initialize the counter for internet disconnections
disconnection_counter = 0
reboot_threshold = 48  #Set to 48*15min (12hr) periods without internet access

def log_internet_status():  #main function to verify all status and write to log file
    global disconnection_counter
    global reboot_threshold
    #with open('internet_status_log.txt', 'a') as file:
    with open(filename, 'a') as file:
        # Check internet connectivity
        if internet_on():
            status = "Internet_Access, Yes, 1"
            disconnection_counter = 0  # Reset counter if the internet is on
        else:
            status = "Internet_Access, No, 0"
            disconnection_counter += 1  # Increment counter if the internet is off
  #      # Check if the threshold for disconnections has been reached
  #      if disconnection_counter >= reboot_threshold:
  #          print("Rebooting due to prolonged internet disconnection.")
  #          subprocess.run(["sudo", "reboot"])
        # Check if the threshold for disconnections has been reached
        if disconnection_counter >= reboot_threshold:
            # Check the auto_reboot setting before rebooting
            if config.get("AUTO_REBOOT_NO_WIFI", "false") == "true":
                print("Rebooting due to prolonged internet disconnection.")
                file.write(f"Rebooting due to prolonged internet disconnection \n")
                file.flush()
                time.sleep(10)  #10sec delay will allow writing to logfile
                subprocess.run(["sudo", "reboot"])
            else:
                print("Auto-reboot is disabled. Internet is down, but the system will not reboot.")
                file.write(f"Auto-reboot is disabled. Internet is down, but the system will not reboot \n")
                file.flush()


        # Get the current time and format it
        current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        # Get the current signal strength
        signal_strength = get_signal_strength()
        # Get the CPU usage
        cpu_use = print_cpu_usage()
        # Get the CPU temperature
        cpu_temp=get_cpu_temperature()
        # Write the status and time to the log file
        file.write(f"{current_time} , {config['SITE']} , {status} , Signal_strength, {signal_strength}, CPU_Usage, {cpu_use}% , CPU_Temp, {cpu_temp}, C \n")
        # Print to terminal window
        print(f"{current_time} , {config['SITE']} , {status} , Signal_strength, {signal_strength}, CPU_Usage, {cpu_use}% , CPU_Temp, {cpu_temp}, C \n")

# Set the interval for checks (900 seconds = 15 minutes)
interval = 900 #900

#main loop
while True:
    now = datetime.now()   #update "now" time
    now = now.strftime(filename_format)  #modify time format

    if (now != then):  #if enough time has passed
      #folder_name2 = setUpFolders2()  #create the daily sync folder with 'old' date
      #dailyFolderNow = datetime.now() #update current time
      #dailyFolderNow = dailyFolderNow.strftime(filename_format) #update the dailyFolder
      #destination_path= folder_name2 #update the destination daily folder
      setUpFolders2()   #rerun the folder creation in case the system cleaned it (empty folder)
      shutil.move(filename, destination_path) #move file name to the /sync_folder
      print("Moving filename to destination path")
      filename = folder_name1 + "InternetLog-Montreal-" + now + ".txt"  #update file name
      then = now

    log_internet_status()
    
    # Wait for some interval before the next check
    time.sleep(interval)


