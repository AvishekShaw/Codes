import itertools

r=3
res=0
stuff = [1, 3, 9, 9, 27, 81]
for subset in itertools.combinations(stuff, 3):
    subset=sorted(list(subset))
    if (subset[0]*r == subset[1] and subset[1]*r == subset[2]):
    	res+=1
print(res)