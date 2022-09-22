from datetime import datetime
from datetime import date
import sys
from main import print_timestamp
import csv

def extract_date_time_info(now):
    """extracts the datetime info from a datetime.now object
    Parameters:
    -----------
    now(datetime.now()): the object holding the information for date and time
    """
    
    return (now.hour, now.minute, now.second, now.day, now.month, now.year)

if __name__ == "__main__":
        
    print_timestamp("starting to track book at")

    now = datetime.now()
    H,M,S,D,M,Y = extract_date_time_info(now)
    
    print("press any button to end the book tracking session")
    input()
    print_timestamp("ending the book tracking at")

    now = datetime.now()
    h,m,s,d,m,y = extract_date_time_info(now)

    print("enter [Book Name] [Start Page] [End Page]")
    info = input().split()
    book_name = info[0]
    start_page = info[1]
    end_page = info[2]
    
    fields = ["book_name","start_page","end_page",\
        "start_hour","start_minute","start_sec","start_day","start_month","start_year",\
        "end_hour","end_minute","end_sec","end_day","end_month","end_year"]

    row = [book_name,start_page,end_page,H,M,S,D,M,Y,h,m,s,d,m,y]
    
    file_path = "/home/avishek/Documents/book_tracker.csv"
    with open(file_path,"a") as f:
        csvwriter = csv.writer(f)
        csvwriter.writerow(row)

