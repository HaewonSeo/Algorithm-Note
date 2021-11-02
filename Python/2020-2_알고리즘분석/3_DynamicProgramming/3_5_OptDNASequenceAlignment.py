import utility

a = ['A','A','C','A','G','T','T','A','C','C']
b = ['T','A','A','G','G','T','C','A']

# 이 경우 손해 정의 : 틈(2), 불일치(1)
def optDNA_table_and_sequence(a,b):
	m = len(a)	# 10
	n = len(b)	# 8
	table = [[0 for j in range(0, n+1)] for i in range(0, m+1)]			# 11*9
	minindex = [[(0, 0) for j in range(0, n+1)] for i in range(0, m+1)]	# 11*9

	# 틈 행 채우기
	for j in range(n-1, -1, -1):
		table[m][j] = table[m][j+1] + 2

	# 틈 열 채우기
	for i in range(m-1, -1, -1):
		table[i][n] = table[i+1][n] + 2

	# table
	for i in range(m-1, -1, -1):
		for j in range(n-1, -1, -1):
			if a[i] == b[j]:
				penalty = 0			# 일치시 손해는 0
			else:
				penalty = 1			# 불일치시 손해는 1
			table[i][j] = min(table[i+1][j+1]+penalty, table[i+1][j]+2, table[i][j+1]+2)	# 틈 발생시 손해는 2

	# minindex
	for i in range(0, m):
		for j in range(0, n):
			if table[i][j] == table[i+1][j]+2:
				minindex[i][j] = (i+1, j)
			elif table[i][j] == table[i][j+1]+2:
				minindex[i][j] = (i, j+1)
			else:
				minindex[i][j] = (i+1, j+1)

	utility.printMatrix(table)

	x = 0
	y = 0
	while (x < m and y < n):
		tx, ty = x, y
		print(minindex[x][y])
		(x, y) = minindex[x][y]			# 다음 opt(i,j) 갱신
		if x == tx+1 and y == ty+1:		# 좌상에서 온 경우, 좌상염기 출력
			print(a[tx], " ",  b[ty])
		elif x == tx and y == ty+1:		# 좌에서 온 경우, x서열에 틈을 넣는다.
			print(" - ", " ", b[ty])
		else:							# 상에서 온 경우, y서열에 틈을 넣는다.
			print(a[tx], " " , "-")

optDNA_table_and_sequence(a,b)
