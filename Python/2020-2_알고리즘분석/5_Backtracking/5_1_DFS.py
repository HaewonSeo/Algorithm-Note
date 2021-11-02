import utility

e = {0:[1,2,3], 1:[2,5], 2:[3,4,5,6], 3:[4,6],4:[6,7]}
n = 8
a = [ [0 for j in range(0,n)] for i in range(0,n)]

for i in range(0,n-1):
	for j in range(i+1,n):
		if i in e:
			if j in e[i]:
				a[i][j] = 1
				a[j][i] = 1

utility.printMatrix(a)

visited = n * [0]

def DFS(a,v):
	print(visited[v])								# root 노드 출력
	for i in range(v, n):
		if a[v][i] == 1 and visited[i] == 0:		# 연결되어있고, 방문하지 않았다면
			visited[i] = i							# i 노드를 방문했다고 표시하고
			DFS(a, i)								# i 노드를 root로 하여 재귀 수행

DFS(a,0)
