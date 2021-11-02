import utility

def order(p,i,j):
	if i == j:
		print("A%d"%i, end="")
	else:
		k = p[i][j]
		print("(", end="")
		order(p, i, k)
		order(p, k+1, j)
		print(")", end="")

d = [5,2,3,4,6,7,8]			# d0~d6
n = len(d) - 1				# A1~A6, n=6

m = [[0 for j in range(1,n+2)] for i in range(1,n+2)]		# 7x7 matrix
p = [[0 for j in range(1,n+2)] for i in range(1,n+2)]		# 0행/열~6행/열

def minmult(d, n, m, p):
	# Initialize diagonal0 to zero
	for i in range(1, n+1):
		m[i][i] = 0

	# diagonal : 1~5
	for diagonal in range(1, n):
		# 동일 diagonal 위의 값들을 순차적으로 계산
		for i in range(1, n-diagonal+1):
			j = i + diagonal
			# Initialize m&p matrix, m[i][j] = 9999으로 아래 두줄을 대체 가능
			m[i][j] = m[i][i] + m[i+1][j] + d[i-1]*d[i]*d[j]
			p[i][j] = i
			for k in range(i,j):
				if (m[i][k] + m[k+1][j] + d[i-1]*d[k]*d[j]) < m[i][j]:
					m[i][j] = m[i][k] + m[k+1][j] + d[i-1]*d[k]*d[j]
					p[i][j] = k
	return m[1][n]

minmult(d, n, m, p)

print("(1) Matrix-chain multiplication")
print("matrix m")
utility.printMatrix(m)
print("\n matrix p")
utility.printMatrix(p)
print("\nOptimal Order : ", end="")
order(p,1,6)
