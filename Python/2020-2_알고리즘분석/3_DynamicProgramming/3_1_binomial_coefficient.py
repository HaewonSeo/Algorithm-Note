# Divide and Conquer
def bin(n, k):
	if k == 0 or n == k:
		return 1
	else:
		return bin(n-1, k-1) + bin(n-1, k)

# Dynamic Programming
def bin2(n, k):
	# (k+1) * (k+1) matrix
	B = [[0 for cols in range(0, k+1)] for rows in range(0, n+1)]

	for i in range(0, n+1):
		for j in range(0, min(i,k)+1):
			if j == 0 or j == i:
				B[i][j] = 1
			else:
				B[i][j] = B[i-1][j-1] + B[i-1][j]
	return B[n][k]

import time

stime = time.time()
print("bin : %d %10.5f" % (bin(10,5), time.time() - stime))

stime = time.time()
print("bin2 : %d %10.5f" % (bin(10,5), time.time() - stime))
