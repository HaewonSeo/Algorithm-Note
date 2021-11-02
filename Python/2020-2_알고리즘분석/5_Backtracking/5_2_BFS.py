import utility
import queue

e = {0:[1,2,3], 1:[2,5], 2:[3,4,5,6], 3:[4,6],4:[6,7]}
n = 8
a = [[0 for j in range(0,n)] for i in range(0,n)]		# n*n matrix

for i in range(0,n-1):
	for j in range(i+1,n):
		if i in e:
			if j in e[i]:
				a[i][j] = 1			# i,j node가 연결되어 있음을 의미
				a[j][i] = 1			# a matrix는 대칭행렬이다.

utility.printMatrix(a)

visited = n * [0]					# 노드의 방문여부를 저장하는 배열 초기화

def BFS(a,v):
	q = queue.Queue()				# queue 생성
	q.put(v)						# root를 queue에 추가
	for i in range(v, n):			# a의 주대각선 위쪽 부분만 검사한다.
		for j in range(i, n):
			if a[i][j] == 1 and visited[j] == 0:	# 연결되어있고, 방문하지 않았을 시
				visited[j] = j						# 방문했음을 표시하고
				q.put(j)							# queue에 추가한다.

	for i in range(0, q.qsize()):					# queue를 순서대로 출력한다.
		print(q.get())

BFS(a,0)
