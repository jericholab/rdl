#Jericho Lab - Internet Access Logging Script (Draft created by GPT)

import requests
import time
from datetime import datetime

def internet_on():
    try:
        # Attempt to request the Google homepage
        response = requests.get('http://www.google.com', timeout=5)
        # If the request succeeds, the internet is considered to be on.
        return response.status_code == 200
    except requests.ConnectionError:
        # If a connection error occurs, the internet is considered to be off.
        return False

def log_internet_status():
    with open('internet_status_log.txt', 'a') as file:
        # Check internet connectivity
        if internet_on():
            status = "Internet Access: Yes"
        else:
            status = "Internet Access: No"
        # Get the current time and format it
        current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        # Write the status and time to the log file
        file.write(f"{current_time} - {status}\n")
        # Print to terminal window
        print(f"{current_time} - {status}\n")


def main():
    # runnable entry point (only when executed as a script)
    interval = 60  # seconds
    while True:
        log_internet_status()
        time.sleep(interval)

if __name__ == "__main__":
    main()
