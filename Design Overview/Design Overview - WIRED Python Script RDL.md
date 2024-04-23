# WIRED - RDL Data Logging Script

## Overview

This script is designed to capture data continuously from a USB-connected RDL device. It logs data received via serial communication into timestamped text files, facilitating real-time data acquisition and storage. The script is particularly useful in settings requiring regular monitoring of serial data, such as in laboratory experiments or industrial data collection.

The script is currently hardcoded for a single RDL connected via port USB0.

## Features

- **Serial Communication**: Handles data communication over USB using the `serial` library.
- **Dynamic File Management**: Creates files dynamically based on the date and time, ensuring data is segmented and easy to manage.
- **Robust Folder Structure**: Maintains a structured approach to data storage, using a multi-level directory system to manage ongoing and ready-to-sync data.
- **Error Handling**: Implements basic error management to cope with potential data decoding issues during transmission.

## Prerequisites

- Python 3.x
- Libraries: `serial`, `datetime`, `time`, `shutil`, `os`
- A device connected via USB capable of sending data in a readable format.
- Properly configured device settings to ensure data is sent over USB.

## Configuration

### Script Settings

- **`DEVICE_NAME`**: "USB0" - Identifier used to name directories and files.

## File Structure

- **`./logging-folder/inprogress/RDL/USB0/`**: Directory where data is initially logged and stored.
- **`./logging-folder/tosync/RDL/USB0/`**: Directory where data is moved once it is ready to be synchronized or processed further.

## Usage

Before running the script, ensure the connected USB device is configured to transmit data at the expected baud rate (57600) and format. Execute the script within a Python environment where all dependencies are installed:

```bash
python3 path_to_script.py
```

The script will operate indefinitely, logging incoming data into timestamped files until manually stopped.

The Syncing Python script will read the data found in this file structure and transfer it to both the Cloud and the local permanent backup (e.g. SD Card).

## Function Descriptions

- **`createFolder(folder_name)`**: Ensures necessary directories exist; creates them if they don't, using setUpFoldersX().
- **`setUpFolders1()` and `setUpFolders2()`**: Set up directories for initial data capture and for data ready to be synced.
- **Data Capturing Loop**: Continuously checks for new data, logs it to files, and moves files to a sync directory based on the timestamp.

## Scheduling

- The script uses a continuous loop with a timing mechanism based on the system clock. It checks for a change in time (hourly or minutely) to manage file transitions and creation.
- Files are moved from the 'inprogress' to the 'tosync' directory based on the timestamp change, facilitating organized data flow and storage management.
