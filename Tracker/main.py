from datetime import datetime
from datetime import date

def print_timestamp(msg:str):
    dt_string = datetime.now().strftime("%Y/%m/%d, %H:%M:%S")
    print(msg + " : " + dt_string)

if __name__ == "__main__":

    print("Which category would you like to input expense of:")
    categories = ["transport","food","books"]
    for idx,category in enumerate(categories):
        print(str(idx) + " " + category)
    j = input()

    date = date.today()

    now = datetime.now()
    hour = now.strftime("%H")
    minute =  now.strftime("%M")
    seconds = now.strftime("%S")

    # print(time)
    print(hour + " "+ minute+" "+seconds)
    print(date)
print("success")