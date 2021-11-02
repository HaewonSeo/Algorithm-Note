import sys

def promising(i, col):
	k = 0
	switch = True
	while (k < i and switch == True):	# i행까지의 유망성을 검사한다.
		if (col[i] == col[k] or abs(col[i]-col[k]) == i-k):	# 같은 열 또는 같은 대각선에 있는지 검사
			switch = False
		k += 1
	return switch

def queens(n, i, col):
	if promising(i, col):				# 유망한지를 검사
		if i == n-1:					# 모든 행이 다 유망하다면(=solution)
			print(col)					# 출력
			global count_sol
			count_sol += 1
		else:
			for j in range(n):			# DFS
				col[i+1] = j			# 다음 행의 모든 가능성을 검사한다.
				queens(n, i+1, col)		# 재귀

def queens_first_solution(n, i, col):
	if promising(i, col):
		if i == n-1:
			print(col)
			sys.exit()					# 첫번째 솔루션만 출력하고 종료
		else:
			for j in range(n):
				col[i+1] = j
				queens_first_solution(n, i+1, col)

n = 7
col = n * [0]							# col[i] : i 번째 queen이 위치한 column값
count_sol = 0
print("7-Queens Problem")
queens(n, -1, col)						# i=-1이므로, 첫행(i=0)의 모든 가능성을 검사할 수 있다.
print("Number of Solutions : ", count_sol)
print("First Solution : ", end='')
queens_first_solution(n, -1, col)

