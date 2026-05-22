import os

def remove_empty_folders(path):
    # Traverse the directory tree from the bottom up
    for root, dirs, files in os.walk(path, topdown=False):
        for dir_name in dirs:
            dir_path = os.path.join(root, dir_name)
            try:
                # If the directory is empty, remove it
                if not os.listdir(dir_path):
                    os.rmdir(dir_path)
                    print(f"Removed empty folder: {dir_path}")
            except OSError as e:
                print(f"Error removing {dir_path}: {e}")

if __name__ == "__main__":
    # Set the current working directory
    current_directory = os.getcwd()
    
    # Call the function to remove empty folders
    remove_empty_folders(current_directory)
