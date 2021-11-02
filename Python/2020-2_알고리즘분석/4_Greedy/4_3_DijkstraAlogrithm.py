inf = 1000
w = [[0,7,4,6,1],
	[inf,0,inf,inf,inf],
	[inf,2,0,5,inf],
	[inf,3,inf,0,inf],
	[inf,inf,inf,1,0]]

n = len(w)						# 그래프의 크기와 관계없이 계산이 가능하도록 수정
f = set()
touch = n * [0]
length = n * [0]
save_length = n * [0]			# 각 노드별 최단 거리를 저장하는 배열

for i in range(1, n):			# touch[], length[] 를 초기화
	touch[i] = 0
	length[i] = w[0][i]

for _ in range(1, n):
	min = inf
	for i in range(1, n):
		if (0 <= length[i] < min):
			min = length[i]		# update the min
			vnear = i			# find a vnear

	e = (touch[vnear], vnear)	# v0~vnear의 최단경로 상의 마지막 edge
	f.add(e)					# 해당 edge를 f에 추가
	print(e)					# f에 추가되는 edge를 출력

	for j in range(1, n):							# 최단 경로 갱신 및 거치는 노드 갱신
		if (length[vnear] + w[vnear][j]) < length[j]:
			length[j] = length[vnear] + w[vnear][j]
			touch[j] = vnear

	save_length[vnear] = length[vnear]		# 최단경로 저장
	length[vnear] = -1		# 찾은 노드가 다시 검사되는 것을 방지(찾은 노드를 Y에 추가한다)
							# Prim과 다른점은 length[vnear]를 최단거리 계산에 사용한 이후 -1로 만든다.

print("f : ",  f)
print("v0에서 각 노드로 도달하는 최단거리 : ", save_length)

# 최대 횟수(NoC)는 (총 아크 수) - (출발점에 연결된 아크수)
max_update = 0					# length[]를 update하는 최대 횟수
for i in range(len(w)):
	for j in range(len(w[i])):
		if w[i][j] != inf and w[i][j] != 0:
			max_update += 1

for i in range(len(w)):
	if w[0][i] != 0 and w[0][i] != inf:
		max_update -= 1
print("length[]를 update해야 하는 최대 횟수 :", max_update)
