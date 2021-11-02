import utility

inf = 1000
w=[[0,  1,  3,inf, inf],
   [1,  0,  3,6,   inf],
   [3,  3,  0,4,   2],
   [inf,6,  4,0,   5],
   [inf,inf,2,5,   0]]

F = set()
utility.printMatrix(w)			# v0 ~ v4
n = len(w)						# len = 5
nearest = n*[0]
distance = n*[0]

for i in range(1, n):			# Initializing nearest[i] & distance[i]
	nearest[i] = 0
	distance[i] = w[0][i]

for i in range(1, n):			# repeat n-1 times
	min = inf
	for j in range(1, n):
		if (0 <= distance[j] < min):
			min = distance[j]			# update the min
			vnear = j					# find a vnear

	e = (nearest[i], vnear)
	F.add(e)
	distance[vnear] = -1	# 찾은 노드가 다시 검사되는 것을 방지(찾은 노드를 Y에 추가한다)

	for k in range(1, n):	# Y에서 X-Y로의 최단거리 및 가장 가까운 노드를 갱신
		if (w[k][vnear] < distance[k]):
			distance[k] = w[k][vnear]
			nearest[k] = vnear

print()
print(F)
