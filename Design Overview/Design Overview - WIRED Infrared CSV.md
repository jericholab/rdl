# Seek Thermal Data Logging Script

## Overview

This script is designed for capturing thermographic data from Seek Thermal cameras. It continuously monitors the camera for new frames and logs the temperature data to dynamically named CSV files based on the date and time. The script is suitable for continuous monitoring and logging applications in industrial, environmental, and scientific research settings.

## Features

- **Dynamic Configuration**: Uses global variables to manage file naming based on the exact time of data capture.
- **Continuous Monitoring**: Monitors a connected Seek Thermal camera and logs each frame received to a CSV file.
- **Event-Driven Architecture**: Responds to camera events such as connection, disconnection, and error states.
- **Error Handling**: Robust error management to ensure continuous operation despite potential issues with file access or camera connectivity.

## Prerequisites

- Python 3.x
- Libraries: `cv2` (OpenCV), `numpy`, `PIL`, `os`, `glob`, `pathlib`, `datetime`
- Seek Thermal camera and associated SDK/library
- Adequate permissions to access connected USB devices

## Configuration

### Script Settings

- **`CAMERA_NAME`**: Specifies the identifier for the camera to aid in directory structuring and file naming.
- **File Naming Convention**: Files are named dynamically based on the camera ID and the timestamp, ensuring that each frame's data is logged without overwriting previous data.

### config.json

Currently, the script does not use a `config.json` but relies on hardcoded parameters and assumptions about directory structure and camera settings.

## File Structure

- **Data Directories**:
  - `./logging-folder/`: Base directory for all logging activities.
  - `./logging-folder/tosync/`: Contains newly logged data waiting to be synchronized or processed.
  - `./logging-folder/tosync/cameras/`: Subdirectory specific to camera data.
  - `./logging-folder/tosync/cameras/infrared1/`: Example directory for `infrared1` camera data.

The Syncing Python script will read the data found in this file structure and transfer it to both the Cloud and the local permanent backup (e.g. SD Card).

## Usage

Ensure the camera is connected and recognized by the system. Run the script in a Python environment where all dependencies have been installed:

```bash
python3 path_to_script.py
```

The script operates indefinitely, capturing frames and logging them as specified until manually stopped or in case of an error or camera disconnection.

The script can also be run automatically by the associated Daemon (service).

## Function Descriptions

- **`on_frame(camera, camera_frame, file)`**: Callback function that handles new frame data, logging it to a CSV file formatted to include the timestamp and camera ID.
- **`on_event(camera, event_type, event_status, _user_data)`**: Handles various camera events, ensuring robust operation through different states like connect, disconnect, and errors.
- **`createFolder(folder_name)`**: Ensures the existence of necessary directories for file storage and calls setUpFolders() if required.
- **`setUpFolders()`**: Initializes the directory structure for data logging.

## Scheduling

This script does not use scheduling but runs a continuous loop that handles events and frame data as they occur. The script's operation is bound by the event callbacks triggered by the camera's state and data availability. A delay was added in the continuous loop to imitate scheduling.
