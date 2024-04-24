# WIRED Reolink Camera Image Capture Script


**Table of Contents**


  1. [Overview](#overview)
  2 [Features](#features)
  3. [Prerequisites](#prerequisites)
  4. [Configuration](#configuration)
     - [Script Settings](#script-settings)
     - [Dynamic Scheduling](#dynamic-scheduling)
  5. [File Structure](#file-structure)
  6. [Usage](#usage)
  7. [Function Descriptions](#function-descriptions)
  8. [Scheduling](#scheduling)

## Overview

This Python script is specifically designed to interface with Reolink RLC-520a cameras to capture images periodically based on a specified time interval. The images are saved in a structured directory system with timestamps to ensure easy tracking and retrieval. This script is ideal for surveillance, monitoring, or data collection scenarios where periodic visual data capture is required.

## Features

- **HTTP Communication**: Interacts with Reolink cameras over HTTP to capture snapshots.
- **Time-based Capturing**: Images are captured based on the defined schedule (hourly or minutely).
- **Automated Folder Management**: Automatically creates and manages folders based on the camera name and the date-time of the capture.
- **Dynamic File Naming**: Utilizes timestamps to uniquely name and save image files to prevent overwriting.

## Prerequisites

- Python 3.x
- Libraries: `datetime`, `schedule`, `time`, `shutil`, `requests`, `os`
- Network access to the Reolink camera's HTTP interface.
- Camera must have HTTP enabled, as HTTPS is not supported by the script.

## Configuration

### Script Settings

- **`CAMERA_NAME`**: Identifier for the camera, used in directory structuring and file naming.
- **`CAMERA_IP`**: IP address of the camera (pre-configured in the camera).
- **`USERNAME` and `PASSWORD`**: Credentials for accessing the camera (pre-configured in the camera).

### Dynamic Scheduling

- The script can be configured to capture images either hourly or minutely, adjustable by the `formatExpected` variable.

## File Structure

- **Data Directories**:
  - `./logging-folder/`: Root directory for logging.
  - `./logging-folder/tosync/`: Contains data pending further processing or synchronization.
  - `./logging-folder/tosync/cameras/`: Subdirectory for camera-specific data.
  - `./logging-folder/tosync/cameras/reolink1/`: Directory for `reolink1` camera images.

The Syncing Python script will read the data found in this file structure and transfer it to both the Cloud and the local permanent backup (e.g. SD Card).

## Usage

To run the script, ensure that all prerequisites are met, and execute it in a Python environment where all dependencies have been installed:

```bash
python3 path_to_script.py
```

The script will continuously operate, capturing and saving images at defined intervals until manually stopped.

The script can also be run automatically by the associated Daemon (service).

## Function Descriptions

- **`createFolder(folder_name)`**: Checks if a directory exists for the current data; if not, it creates it with setUpFolders().
- **`setUpFolders()`**: Initializes the directory structure required for storing the camera images.
- **`takePicture()`**: Handles the capture of an image from the camera and saves it to the designated file path using timestamp-based naming.

## Scheduling

- The script utilizes a continuous loop with a time check to trigger image capture when the minute or hour changes.
- To minimize resource consumption and avoid extremely frequent checks, a sleep interval of 5 seconds is used.
