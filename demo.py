import numpy as np

file1=open("myfile.txt","w")
for i in range(10):
	for j in range(10):
		file1.write(str(j)+",")
	file1.write("\n")