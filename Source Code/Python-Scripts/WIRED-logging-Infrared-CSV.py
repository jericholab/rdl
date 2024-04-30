#!/usr/bin/env python3
# Copyright 2021 Seek Thermal Inc.
#
# Original author: Michael S. Mead <mmead@thermal.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


CAMERA_NAME = "infrared1"
import cv2   #opencv
import numpy   
import PIL.Image   #pillow library allows to play with images (load, save, cropping, filtering, etc)
import os  # library to interact with the operating system
import glob  #library provides a way to find paths in the system. it recognizes characters like '*' that means 'every'.
from PIL import Image, ImageFont, ImageDraw
from pathlib import Path
from time import sleep
from datetime import datetime
import json
import numpy as np
import matplotlib.pyplot as plt

from seekcamera import (
    SeekCameraIOType,
    SeekCameraManager,
    SeekCameraManagerEvent,
    SeekCameraFrameFormat,
)

os.chdir(os.path.dirname(os.path.abspath(__file__)))  #change working directory to the directory containing the script


def on_frame(camera, camera_frame, file):
    """Async callback fired whenever a new frame is available.

    Parameters
    ----------
    camera: SeekCamera
        Reference to the camera for which the new frame is available.
    camera_frame: SeekCameraFrame
        Reference to the class encapsulating the new frame (potentially
        in multiple formats).
    file: TextIOWrapper
        User defined data passed to the callback. This can be anything
        but in this case it is a reference to the open CSV file to which
        to log data.
    """
    while True:
        now = datetime.now()
        now = now.strftime(formatExpected)
        dailyFolderNow = datetime.now()
        dailyFolderNow = dailyFolderNow.strftime(formatDailyFolder)
        folder_name = setUpFolders() #rerun the function to create the daily folder, if applicable
        
        try:
            csvName = Path('./' + folder_name + '/' + camera.chipid +'-'+ str(now)).with_suffix('.csv')
            file = open(csvName, "w")  # Open a new CSV file with the unique camera chip ID embedded.

        except OSError as e:
            print("Failed to open file: %s" % str(e))
            return
            
        frame = camera_frame.thermography_float

        print(
            "frame available: {cid} (size: {w}x{h})".format(
                cid=camera.chipid, w=frame.width, h=frame.height
            )
        )

        # Append the frame to the CSV file.
        np.savetxt(file, frame.data, fmt="%.1f")
        s = os.path.join('./', csvName)
        print(s)
        thermography_plot(s)
        # Wait ten seconds in between frames
        sleep(10.0)
        #sleep(60.0)



def on_event(camera, event_type, event_status, _user_data):
    """Async callback fired whenever a camera event occurs.

    Parameters
    ----------
    camera: SeekCamera
        Reference to the camera on which an event occurred.
    event_type: SeekCameraManagerEvent
        Enumerated type indicating the type of event that occurred.
    event_status: Optional[SeekCameraError]
        Optional exception type. It will be a non-None derived instance of
        SeekCameraError if the event_type is SeekCameraManagerEvent.ERROR.
    _user_data: None
        User defined data passed to the callback. This can be anything
        but in this case it is None.
    """
    print("{}: {}".format(str(event_type), camera.chipid))

    if event_type == SeekCameraManagerEvent.CONNECT:


        # Start streaming data and provide a custom callback to be called
        # every time a new frame is received.
        #camera.register_frame_available_callback(on_frame, file)  #file is not created at this step anymore.
        camera.register_frame_available_callback(on_frame)
        camera.capture_session_start(SeekCameraFrameFormat.THERMOGRAPHY_FLOAT)

    elif event_type == SeekCameraManagerEvent.DISCONNECT:
        camera.capture_session_stop()

    elif event_type == SeekCameraManagerEvent.ERROR:
        print("{}: {}".format(str(event_status), camera.chipid))

    elif event_type == SeekCameraManagerEvent.READY_TO_PAIR:
        return

def createFolder(folder_name):
    if not os.path.exists(folder_name):
        os.mkdir(folder_name)
        print("Folder created: ", folder_name)
    else:
        print("Folder already exists: ", folder_name)
        
def setUpFolders():
    now = datetime.now()
    now = now.strftime(formatExpected)
    dailyFolderNow = datetime.now()
    dailyFolderNow = dailyFolderNow.strftime(formatDailyFolder)
    level1 = "./logging-folder"
    level2 = level1 + "/tosync"
    level3 = level2 + "/cameras/"
    level4 = level3 + CAMERA_NAME
    folder_name = level4 + "/" + dailyFolderNow
    createFolder(level1)
    createFolder(level2)
    createFolder(level3)
    createFolder(level4)
    createFolder(folder_name)
    return folder_name

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
        folder_path = os.path.dirname(csv_filename)
        #print(folder_path)
        #print(filename_without_extension)

        # Save the figure as an image file
        #output_filepath = os.path.join(output_directory, filename_without_extension)
        output_filepath = os.path.join(folder_path, filename_without_extension)
        plt.savefig(output_filepath)
        #print(folder_name)
        #plt.savefig(folder_name) #testxxxxxxxxxxxxx
        plt.close()  # Close the plot to free up memory

    elif file_extension.lower() in ['.jpg', '.jpeg']:
        # Handle JPEG files differently, or simply print a message
        print(f"CSV-to-JPEG: Skipping JPEG file: {csv_filename}")

    else:
        # Optionally handle other file types or raise an exception
        print(f"CSV-to-JPEG: Unsupported file type: {csv_filename}")

def main():

    #initializing
    global formatExpected
    global dailyFolderNow
    global formatDailyFolder
    global folder_name
    #formatExpected = "%Y-%m-%d"  #log into different file every day
    #formatExpected = "%Y-%m-%d_%H"  #log into different file every hour
    #formatExpected = "-%Y-%m-%d_%H%M"  #log into different file every minute
    formatExpected = "%Y-%m-%d_%H%M%S"  #log into different file every second
    dailyFolderNow = datetime.now()
    #formatDailyFolder = "%Y-%m-%d_%H_%M"  #daily folder (temporarily a minute folder for testing)
    formatDailyFolder = "%Y-%m-%d"  #daily folder
    dailyFolderNow = dailyFolderNow.strftime(formatDailyFolder)
    folder_name = setUpFolders()  # Run once
    
    # Create a context structure responsible for managing all connected USB cameras.
    # Cameras with other IO types can be managed by using a bitwise or of the
    # SeekCameraIOType enum cases.
    with SeekCameraManager(SeekCameraIOType.USB) as manager:
        # Start listening for events.
        manager.register_event_callback(on_event)

        while True:
            
            sleep(1.0)



if __name__ == "__main__":
    main()
