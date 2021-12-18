import string
ALPHABET = string.ascii_lowercase


s = "abba"

signatures={}

for start in range(len(s)):
	for finish in range(start,len(s)):
		signature = [0 for _ in ALPHABET]
		for letter in s[start:finish+1]:
			signature[ord(letter) - ord(ALPHABET[0])]+=1
		signature=tuple(signature)
		signatures[signature]=signatures.get(signature,0)+1
res=0
for count in signatures.values():
	res+=count*(count-1)/2

print(res)