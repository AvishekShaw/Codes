str1="afteosp"
str2="wmslwpqero"

from collections import defaultdict
dict1=defaultdict(int)
dict2=defaultdict(int)

for i in str1:
	dict1[i]+=1
for j in str2:
	dict2[j]+=1

set1=set(dict1.keys())
set2=set(dict2.keys())
print(len(list(set2 & set1)))