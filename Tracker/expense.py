from cmath import exp
import sys
from meta_expense import meta_expense
from datetime import datetime
import csv

def print_with_enumerate(obj):
    """
    Prints the keys/elements of dict/list along with the index nos.
    
    Parameters:
    -----------
    obj (list or dict): for dict print its keys, for list print its elements
    """
    for idx,key in enumerate(obj):
        print(str(idx)+ " " +key)

def check_if_index_in_object(obj,index):
    """
    Checks if an index position is present in an object

    Parameters:
    -----------
    obj (list or dict): or dict it checks the len(dict.keys()), for list it checks the len(list)
    
    """

    if index not in list(range(len(obj))):
        print("invalid option. Exiting")
        sys.exit()

user_date_response=["yes","no"]

# First print the categories and check if the input is correct 
print("category?")
print_with_enumerate(meta_expense)
index = int(input())
check_if_index_in_object(meta_expense,index)

# decide the category according to the index input. Python 3.6 and above stores ordered dict keys
categories = list(meta_expense.keys())
category = categories[index] 

# Print the subcategories and check if input is correct
print("subcategory?")
print_with_enumerate(meta_expense[category])
index = int(input())
check_if_index_in_object(meta_expense[category],index)

# Assign the subcategory and date,month,year
subcat = meta_expense[category][index]

# Read the expense
print("expense?")
expense = int(input())
print(expense)

# check if user wants to input date and check the input
print("do you want to enter date manually?")
print_with_enumerate(user_date_response)
index = int(input())
check_if_index_in_object(user_date_response,index)

if index == 0:
    print("enter [DD] [MM] [YYYY]")
    date = input().split()
    day = int(date[0])
    month = int(date[1])
    year = int(date[2])
    print(day,month,year)

elif index == 1:
    now = datetime.now()
    day = now.day
    month = now.month
    year = now.year

fields = ["category","subcategory","expense","day","month","year"]

row = [category,subcat,expense,day,month,year]
print(row)
    
file_path = "/home/avishek/Documents/expense_tracker.csv"
with open(file_path,"a") as f:
    csvwriter = csv.writer(f)
    csvwriter.writerow(row)
