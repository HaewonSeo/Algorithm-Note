import queue

class Node:
	def __init__(self, level, weight, profit, bound, include):
		self.level = level
		self.weight = weight
		self.profit = profit
		self.bound = bound
		self.include = include

	# You need to provide the rich comparison methods for ordering in Python 3,
	# which are __lt__, __gt__, __le__, __ge__, __eq__, and __ne__.
	# See also: PEP 207 -- Rich Comparisons. _cmp__ is no longer used.

	# def __cmp__(self, other):
	# 	return cmp(self.bound, other.bound)

	def __lt__(self, other):					# __lt__ method를 추가하여, 객체 간의 대소 비교를 bound로 수행한다.
		return self.bound < other.bound

def kp_Best_FS():
	global maxProfit
	global bestset

	temp = n * [0]
	pq = queue.PriorityQueue()				# min heap을 사용하면 원소들이 항상 정렬된 상태로 추가되고 삭제되며,
											# min heap에서 가장 작은값은 언제나 인덱스 0, 즉, 이진 트리의 루트에 위치한다.
	v = Node(-1, 0, 0, 0.0, temp)
	v.bound = compBound(v)					# bound는 음수로 저장된다.
	pq.put(v)

	while not pq.empty():
		v = pq.get()								# 최고의 bound를 가진 마디를 get
		if v.bound < -maxProfit:					# 마디가 아직 유망한지 확인
			u = Node(0, 0, 0, 0.0, temp)			# u node를 생성
			u.level = v.level + 1					# u를 v의 자식마디로 만든다.
			u.weight = v.weight + w[u.level]
			u.profit = v.profit + p[u.level]
			u.include = v.include[:]
			u.include[u.level] = 1					# u를 다음 아이템을 포함하는 자식마디로 놓음.

			if u.weight <= W and u.profit > maxProfit:		# profit과 maxProfit의 비교는 양수로 비교함.
				maxProfit = u.profit				# 최적값과 최적의 set을 유지한다.
				bestset = u.include[:]

			u.bound = compBound(u)					# 계산한 bound가 maxProfit보다 크다면, 유망하다.
			if u.bound < -maxProfit:				# bound와 maxProfit 비교시에는 음수로 비교한다.(minheap이므로)
				pq.put(u)							# PriorityQueue에 추가

			t = Node(0, 0, 0, 0.0, temp)			# t node를 생성
			t.level = v.level + 1					# t를 v의 자식마디로 만든다.
			t.weight = v.weight
			t.profit = v.profit
			t.include = v.include[:]
			t.include[t.level] = 0					# t를 다음 아이템을 포함하지 않는 자식마디로 놓음.

			t.bound = compBound(t)					# 계산한 bound가 maxProfit보다 크다면, 유망하다.
			if t.bound < -maxProfit:				# bound와 maxProfit 비교시에는 음수로 비교한다.(minheap이므로)
				pq.put(t)							# PriorityQueue에 추가

def compBound(u):
	if u.weight >= W:								# 남은 공간이 없으면 유망하지 않음
		return 0
	else:
		j = u.level + 1								# 현재 아이템의 다음 아이템부터 계산
		result = u.profit							# 현재 이익
		totweight = u.weight						# 현재 무게

		while j < n and totweight + w[j] <= W:		# 공간이 남으면 남은 아이템에 대해 반복
			totweight = totweight + w[j]			# 다음 아이템을 넣어, 총 무게를 갱신
			result = result + p[j]					# 다음 아이템을 넣어, 총 이익을 갱신
			j += 1

		k = j
		if k < n:									# 남은 공간만큼 k번째 아이템의 단위무게당 이익을 계산하여 result에 추가한다.
			result = result + ((W-totweight) * (p[k]/w[k]))	 # result : 이론적으로 현 상태에서 얻을 수 있는 최대 이익
		return -result								# -result를 return


# heap이 minheap이라 bound를 계산하여 -를 하여 리턴한다. 비교를 < maxProfit으로 수행한다.
n = 4
W = 16
p = [40,30,50,10]
w = [2,5,10,5]
include = [0] * n
maxProfit = 0
bestset = n * [0]
kp_Best_FS()
print("Best set : ", bestset)
print("Max profit : ", maxProfit)
