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

from threading import Condition   #a thread is a separate flow of execution within a program. you can have simultaneous threads.

import cv2   #opencv
import numpy   
import PIL.Image   #pillow library allows to play with images (load, save, cropping, filtering, etc)
import os  # library to interact with the operating system
import glob  #library provides a way to find paths in the system. it recognizes characters like '*' that means 'every'.
import time
from datetime import datetime

from PIL import Image, ImageFont, ImageDraw

from seekcamera import (
    SeekCameraIOType,
    SeekCameraColorPalette,
    SeekCameraManager,
    SeekCameraManagerEvent,
    SeekCameraFrameFormat,
    SeekCameraShutterMode,
    SeekCamera,
    SeekFrame,
)

os.chdir(os.path.dirname(os.path.abspath(__file__)))  #change working directory to the directory containing the script


class Renderer:
    """Contains camera and image data required to render images to the screen."""

    def __init__(self):
        self.busy = False
        self.frame = SeekFrame()
        self.camera = SeekCamera()
        self.frame_condition = Condition()
        self.first_frame = True


def on_frame(_camera, camera_frame, renderer):
    """Async callback fired whenever a new frame is available.

    Parameters
    ----------
    _camera: SeekCamera
        Reference to the camera for which the new frame is available.
    camera_frame: SeekCameraFrame
        Reference to the class encapsulating the new frame (potentially
        in multiple formats).
    renderer: Renderer
        User defined data passed to the callback. This can be anything
        but in this case it is a reference to the renderer object.
    """

    # Acquire the condition variable and notify the main thread
    # that a new frame is ready to render. This is required since
    # all rendering done by OpenCV needs to happen on the main thread.
    with renderer.frame_condition:
        renderer.frame = camera_frame.color_argb8888
        renderer.frame_condition.notify()


def on_event(camera, event_type, event_status, renderer):
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
    renderer: Renderer
        User defined data passed to the callback. This can be anything
        but in this case it is a reference to the Renderer object.
    """
    print("{}: {}".format(str(event_type), camera.chipid))
    
    global chip
    chip = str(camera.chipid)   #added by FC

    if event_type == SeekCameraManagerEvent.CONNECT:
        if renderer.busy:
            return

        # Claim the renderer.
        # This is required in case of multiple cameras.
        renderer.busy = True
        renderer.camera = camera

        # Indicate the first frame has not come in yet.
        # This is required to properly resize the rendering window.
        renderer.first_frame = True

        # Set a custom color palette.
        # Other options can set in a similar fashion.
        camera.color_palette = SeekCameraColorPalette.TYRIAN

        # Start imaging and provide a custom callback to be called
        # every time a new frame is received.
        camera.register_frame_available_callback(on_frame, renderer)
        camera.capture_session_start(SeekCameraFrameFormat.COLOR_ARGB8888)

    elif event_type == SeekCameraManagerEvent.DISCONNECT:
        # Check that the camera disconnecting is one actually associated with
        # the renderer. This is required in case of multiple cameras.
        if renderer.camera == camera:
            # Stop imaging and reset all the renderer state.
            camera.capture_session_stop()
            renderer.camera = None
            renderer.frame = None
            renderer.busy = False

    elif event_type == SeekCameraManagerEvent.ERROR:
        print("{}: {}".format(str(event_status), camera.chipid))

    elif event_type == SeekCameraManagerEvent.READY_TO_PAIR:
        return

def bgra2rgb( bgra ):    #i think this is a section added by Tom at Seek Thermal for the record tutorial.
    row, col, ch = bgra.shape

    assert ch == 4, 'ARGB image has 4 channels.'

    rgb = numpy.zeros( (row, col, 3), dtype='uint8' )  #creates an empty array of zeros with values between 0 and 255 (uint8)
    # convert to rgb expected to generate the jpeg image
    rgb[:,:,0] = bgra[:,:,2]
    rgb[:,:,1] = bgra[:,:,1]
    rgb[:,:,2] = bgra[:,:,0]

    return rgb

def createFolder(folder_name):
    if not os.path.exists(folder_name):
        os.mkdir(folder_name)
        print("Folder created: ", folder_name)
    else:
        print("Folder already exists: ", folder_name)
        
def setUpFolders():
    level1 = "./logging-folder"
    level2 = level1 + "/tosync"
    level3 = level2 + "/cameras/"
    folder_name = level3 + CAMERA_NAME
    createFolder(level1)
    createFolder(level2)
    createFolder(level3)
    createFolder(folder_name)
    return folder_name

def main():       # this section was added by Tom at Seek Thermal for the record tutorial.
    #window_name = "Seek Thermal - Python OpenCV Sample"  #######temporary deactivation
    #  cv2.namedWindow(window_name, cv2.WINDOW_NORMAL)     #######temporary deactivation

   #initializing
    #formatExpected = "%Y-%m-%d"  #log into different file every day
    #formatExpected = "%Y-%m-%d_%H"  #log into different file every hour
    formatExpected = "%Y-%m-%d_%H%M"  #log into different file every minute
    #formatExpected = "%Y-%m-%d_%H%M%S"  #log into different file every second
    now = datetime.now()
    now = now.strftime(formatExpected)
    then = now
    
    
    folder_name = setUpFolders()  # Run once 
   
#     folder_name = "./logging-folder/sync/SeekRun_" + now 
#     if not os.path.exists(folder_name):
#         os.mkdir(folder_name)
#         print("Folder created: ", folder_name)
#     else:
#         print("Folder already exists: ", folder_name)

    from PIL import Image # a bit weird that he imports Image again
    from pathlib import Path
  
    # Create a context structure responsible for managing all connected USB cameras.
    # Cameras with other IO types can be managed by using a bitwise or of the
    # SeekCameraIOType enum cases.
    with SeekCameraManager(SeekCameraIOType.USB) as manager:
        # Start listening for events.
        renderer = Renderer()   
        manager.register_event_callback(on_event, renderer)
        capture = True  #setting the value to true will launch the capture
        
        

        while True:
            
            #we constantly update variable NOW
            now = datetime.now()
            now = now.strftime(formatExpected)
            
            #pseudo code: if time has passed (now is not then), capture becomes True
            if now != then:
                capture = True  #setting the value to true will launch the capture
                print("It is time to capture")
            
            # Wait a maximum of 150ms for each frame to be received.
            # A condition variable is used to synchronize the access to the renderer;
            # it will be notified by the user defined frame available callback thread.
            with renderer.frame_condition:
                if renderer.frame_condition.wait(150.0 / 1000.0):
                    img = renderer.frame.data 

                    # if capture or recording, convert the frame image
                    # to RGB and generate the file.
                    # Currently counter is a big number to allow easy ordering
                    # of frames when recording.
                    if capture:
                        rgbimg = bgra2rgb(img) #convert to rgb format
                        im = Image.fromarray(rgbimg).convert('RGB')
                        #jpgName = Path('.', fileName + str(counter)).with_suffix('.jpg')  # '.' means we will write to current dir?
                        #jpgName = Path('./'+folder_name + '/', fileName + str(counter)).with_suffix('.jpg')  # '.' means we will write to current dir?
                        #jpgName = Path('./'+folder_name + '/', 'image_' + str(now)).with_suffix('.jpg')
                        jpgName = Path('./'+folder_name + '/', chip + '_' + str(now)).with_suffix('.jpg')
                        im.save(jpgName)   #we save the image with the filename built
                        print("\n Capture taken")
                        #print("\n",now)
                        #print(then)
                        capture = False
                        then = now
                        time.sleep(1)
                        
                time.sleep(1)
        time.sleep(2)

    cv2.destroyWindow(window_name)
        
if __name__ == "__main__":
    main()
