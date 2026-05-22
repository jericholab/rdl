# sendgrid_getlatestfiles.py
# Copyright (C) 2025 Jericho Laboratory Inc.

import os
import shutil
import datetime
import time

def get_latest_file_recursive(directory, filetype):
    latest_file = None
    latest_mtime = -1
    print("Running scheduled job at", datetime.datetime.now())
    
    # Walk through all subdirectories.
    for root, dirs, files in os.walk(directory):
        for f in files:
            # Check if the file ends with the given filetype (case insensitive).
            if f.lower().endswith(filetype):
                file_path = os.path.join(root, f)
                try:
                    mtime = os.path.getmtime(file_path)
                    if mtime > latest_mtime:
                        latest_mtime = mtime
                        latest_file = file_path
                except OSError:
                    # Skip files that might be inaccessible.
                    continue

    return latest_file

def higher_function():

    # Define the file types to search for.
    file_types = ('.jpg', '.jpeg', '.txt')
    directory_path = './logging-folder/4_synced/'

    # Store results in a dictionary.
    latest_files = {}
    for filetype in file_types:
        latest_files[filetype] = get_latest_file_recursive(directory_path, filetype)

    # Now you can access each result from the dictionary.
    for filetype, latest in latest_files.items():
        if latest:  # Check if a file was found.
            print(f"Most recent synced {filetype} file: {latest}")
        else:
            print(f"No {filetype} file found in the directory.")
            
    # Assume latest_files['.txt'] contains the path to the most recent .txt file
    txt_file_path = latest_files.get('.txt')

    if txt_file_path:
        print(f"Printing the first 10 lines of {txt_file_path}:\n")
        try:
            with open(txt_file_path, 'r', encoding='utf-8') as file:
                # Enumerate over the file lines, starting from 0
                for i, line in enumerate(file):
                    if i >= 10:  # Stop after printing 10 lines
                        break
                    print(line.rstrip())  # rstrip() to remove trailing newline characters
        except Exception as e:
            print(f"An error occurred while reading the file: {e}")
    else:
        print("No text file found to display.")
    
    return latest_files


if __name__ == '__main__':
    # Run the task every hour on the XXth minute.
    higher_function()

