import queue

class Node:
	def __init__(self, level, weight, profit, include):
		self.level = level
		self.weight = weight
		self.profit = profit
		self.include = include

def kp_BFS():
	global maxProfit
	global bestset

	q = queue.Queue()						# initialize Queue
	v = Node(-1, 0, 0, include)				# root node
	q.put(v)

	while not q.empty():
		v = q.get()

		u = Node(0, 0, 0, v.include[:])				# u node를 생성
		u.level = v.level + 1						# u를 v의 자식마디로 만든다.
		u.weight = v.weight + w[u.level]
		u.profit = v.profit + p[u.level]
		u.include[u.level] = 1						# u를 다음 아이템을 포함하는 자식마디로 놓음.

		if (u.weight <= W and u.profit > maxProfit):	# 최적값과 최적의 set을 유지한다.
			maxProfit = u.profit
			bestset = u.include[:]

		if compBound(u) > maxProfit:				# 계산한 bound가 현재 maxProfit보다 크다면 True -> 유망함
			q.put(u)								# queue에 추가

		t = Node(0, 0, 0, v.include[:])				# t node를 생성
		t.level = v.level + 1						# t를 v의 자식마디로 만든다.
		t.weight = v.weight
		t.profit = v.profit
		t.include[t.level] = 0						# t를 다음 아이템을 포함하지 않는 자식마디로 놓음.

		if compBound(t) > maxProfit:				# 계산한 bound가 현재 maxProfit보다 크다면 True -> 유망함
			q.put(t)								# queue에 추가

def compBound(u):
	if u.weight >= W:								# 남은 공간이 없으면 유망하지 않음
		return False
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
		return result								# result를 return

n = 4
W = 16
p = [40, 30, 50, 10]
w = [2, 5, 10, 5]
include = [0] * n
maxProfit = 0
bestset = n * [0]
kp_BFS()
print("Best set : ", bestset)
print("Max profit : ", maxProfit)
