def solve(A, B):
        left=0
        right=-1
        sum=0
        # while(abs(left)+abs(right)<=len(A)):
        for i in range(B):
                if A[left]>=A[right]:
                    # print(A[left])
                    sum+=A[left]
                    left=left+1
                else:
                    # print(A[right])
                    sum+=A[right]
                    right=right-1
        return(sum)

A=[ -533, -666, -500, 169, 724, 478, 358, -38, -536, 705, -855, 281, -173, 961, -509, -5, 942, -173, 436, -609, -396, 902, -847, -708, -618, 421, -284, 718, 895, 447, 726, -229, 538, 869, 912, 667, -701, 35, 894, -297, 811, 322, -667, 673, -336, 141, 711, -747, -132, 547, 644, -338, -243, -963, -141, -277, 741, 529, -222, -684, 35 ]
B = 48
print(len(A))
# A=[5, -2, 3 , 1, 2]
print(solve(A,B))