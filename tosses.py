import numpy as np
tosses=[]
toss_counts=[]
for i in range(500):
	for tries in range(10000):
		tosses.append(np.random.randint(0,2))
	toss_counts.append(np.sum(tosses))
	del tosses
	tosses=[]
print(np.mean(toss_counts),np.var(toss_counts))