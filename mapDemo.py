def to_upper_case(s):
	return str(s).upper()
	
def print_iterator(it):
	for x in it:
		print(x)
	#print(' ')

map_iterator = map(to_upper_case, 'abc')
print(type(map_iterator))
print_iterator(map_iterator)

map1_iterator = map(to_upper_case, (1, 'abc','a'))
print_iterator(map1_iterator)
import random
print(random.randint(16,3340909))
