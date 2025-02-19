# sendgrid-orchestrator.py
# Copyright (C) 2025 Jericho Laboratory Inc.


import datetime
import time
from sendgrid_getlatestfiles import get_latest_file_recursive, higher_function
from sendgrid_sendemail import sendemail


def run_weekly_at(target_weekday, target_hour, target_minute):
    """
    Schedules the task to run weekly at a specified day (0=Monday, 1=Tuesday, etc.), hour, and minute.
    In our case, use target_weekday=1 (Tuesday), target_hour=16, target_minute=0 for Tuesday 4:00 PM.
    """
    while True:
        now = datetime.datetime.now()
        # Set next_run to today at target_hour:target_minute
        next_run = now.replace(hour=target_hour, minute=target_minute, second=0, microsecond=0)
        
        # Calculate how many days until the target weekday
        days_ahead = target_weekday - now.weekday()
        if days_ahead < 0:
            days_ahead += 7  # Target day is in the next week
        
        # If today is the target day but the time has passed, schedule for next week
        if days_ahead == 0 and next_run <= now:
            days_ahead = 7
        
        # Add the days ahead to next_run
        next_run = next_run + datetime.timedelta(days=days_ahead)
        
        sleep_seconds = (next_run - now).total_seconds()
        print(f"Sleeping for {sleep_seconds:.2f} seconds until next run at {next_run}")
        time.sleep(sleep_seconds)
        
        # When it's time, get the latest files and send the email
        files_dict = higher_function()
        print(files_dict)
        sendemail(files_dict)


#hourly function is not used anymore
def run_hourly_at(minute):
    while True:
        now = datetime.datetime.now()
        # Compute the next run time at the specified minute of the current or next hour.
        next_run = now.replace(minute=minute, second=0, microsecond=0)
        if next_run <= now:
            next_run += datetime.timedelta(hours=1)
        sleep_seconds = (next_run - now).total_seconds()
        print(f"Sleeping for {sleep_seconds:.2f} seconds until next run at {next_run}")
        time.sleep(sleep_seconds)
        #find_latest_files()
        files_dict = higher_function()
        print(files_dict)
        #pass the created dictionnary over to sendemail function and execute
        sendemail(files_dict)

if __name__ == '__main__':
    # Run the task every hour on the XXth minute.
    #run_hourly_at(00)
    # Run the task once a week at specified day (Monday is day 0) and time
    run_weekly_at(target_weekday=1, target_hour=18, target_minute=5)
    