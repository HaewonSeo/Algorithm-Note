from utility import *

def allShortestPath(g,n):
	# node number는 1부터 n
	P = [[0 for cols in range(n)] for rows in range(n)]
	# copy g to D
	D = g[:]

	for k in range(n):
		for i in range(n):
			for j in range(n):
				# Floyd Alg2
				if D[i][k]+D[k][j] < D[i][j]:
					P[i][j] = k + 1 			#노드는 1부터 시작.
					D[i][j] = D[i][k]+D[k][j]
	return D, P

# for k in range(n-1, -1, -1):
# 위처럼 k를 오름차순이 아닌 내림차순으로 했을 경우 D의 결과는 같은데, P의 결과가 다르다.
# 그 이유는 i부터 j까지의 경로 중간에 노드를 2 개 거쳐갈 경우
# 반복문 안에서 앞서 나오는 노드가 늦게 나온 노드로 덮여쓰여지기 때문이다.


# 중간 노드 출력
def _path(p, q, r):
	if p[q][r] != 0:
		_path(p, q, p[q][r] - 1) # index = (행렬 P 내부의 값) - 1
		print("v%d" %p[q][r], end=" ") # 경유한 정점을 출력
		_path(p, p[q][r] - 1, r)

# wrapper 함수 : 시작노드, 끝노드 출력기능만 수행
def path(p, q, r):
    print("v%d"% q, end=" ")
    _path(p, q - 1, r - 1)		# path에서 index가 0부터 시작하므로 -1 하였다.
    print("v%d"% r, end=" ")



# 중간 노드만을 출력
def path2(p, q, r):
	if p[q-1][r-1] != 0:					#P는 인덱스 0부터 시작하고, 정점은 1부터 시작한다.
		path2(p, q, p[q-1][r-1])
		print("v%d" %p[q-1][r-1], end=" ")	#경유한 정점을 출력
		path2(p, p[q-1][r-1], r)


inf=1000
g=[[0,1,inf, 1,5],
   [9,0,3,2,inf],
   [inf,inf,0,4,inf],
   [inf,inf,2,0,3],
   [3,inf,inf,inf,0]]
d, p = allShortestPath(g,5)
print("\nmatrix d")
printMatrix(d)
print("\nmatrix p")
printMatrix(p)

print("\npath")
path(p, 5, 3)
print()
path2(p, 5, 3)
