parent = dict()
rank = dict()

def make_singleton_set(v):		# 정점의 parent와 rank를 초기화
    parent[v] = v				# parent = {v : v}
    rank[v] = 1					# rank = {v : 1}

def find(v):					# 집합의 root node를 반환한다.
    if parent[v] != v:
        parent[v] = find(parent[v])
    return parent[v]

def union(r1, r2):				# 집합의 원소수가 많은 쪽으로 합쳐진다.
    if r1 != r2:
        if rank[r1] > rank[r2]:
            parent[r2] = r1
            rank[r1] += rank[r2]
        else:
            parent[r1] = r2
            if rank[r1] == rank[r2]: rank[r2] += rank[r1]

def kruskal(graph):
	F = set()							# MST를 이루는 이음선의 집합

	for v in graph['vertices']:			# 초기 집합 생성
		make_singleton_set(v)

	edges = list(graph['edges'])		# set을 list로 변경 후 오름차순으로 정렬
	edges.sort()
	n = len(graph['vertices'])          # 정점의 개수 n = 5

	k = 0
	while (len(F) < n - 1):				# F에 속하는 edge의 개수가 n-1보다 작다.
		i, j = edges[k][1], edges[k][2]
		p = find(i)
		q = find(j)
		if p != q:						# 두 부분집합이 서로소인 경우
			union(p, q)					# 두 부분집합을 하나로 합친다.
			F.add(edges[k])				# F에 해당 edge를 추가한다.
		k += 1

	return F

graph = {
        'vertices': ['A', 'B', 'C', 'D', 'E'],
        'edges': set([
            (1, 'A', 'B'),
            (3, 'A', 'C'),
            (3, 'B', 'C'),
            (6, 'B', 'D'),
            (4, 'C', 'D'),
            (2, 'C', 'E'),
            (5, 'D', 'E'),
            ])
        }

mst = kruskal(graph)
print("F : ", mst)
