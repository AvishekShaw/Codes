import math
import os
import random
import re
import sys

# Complete the minimumSwaps function below.

def index_checker(arr):
    correct_index=[]
    for i in range(len(arr)):
        if arr[i]==i+1:
            correct_index.append(i)
    return(correct_index)



def minimumSwaps(arr):
    n=len(arr)
    index_list=[]
    i=0
    for i in range(n):
        index_list.append(i)

    correct_index=[]
    correct_index=index_checker(arr)
    swap=0
    while(len(correct_index)<n-1):
        i=0
        num=0
        temp=0
        diff_list=[x for x in index_list if x not in correct_index]
        for i in diff_list:
            num=arr[i]
            if(arr[num-1]<num):
                temp=arr[i]
                arr[i]=arr[num-1]
                arr[num-1]=temp
                swap+=1
                correct_index.append(num-1)
            
        # correct_index=index_checker(arr)    
    return(swap)


if __name__ == '__main__':
    

    arr=[1,3,5,2,4,6,7]
    print(minimumSwaps(arr))
