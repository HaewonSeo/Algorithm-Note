import math

class Heap(object):
	n = 0

	def __init__(self, data):
		self.data = data
		# heap size를 하나 줄여야 한다. 인덱스는 1부터. 인덱스의 2* 연산 가능하도록.
		self.n = len(self.data) - 1
		self.makeHeap2()		# heap 생성

	# heap에 element 추가
	def addElt(self, elt):
		self.data.append(elt)
		self.n += 1
		self.siftUp(self.n)

	def siftUp(self, i):							# i : leaf node
		while (i >= 2):
			parent = i//2
			if self.data[i] > self.data[parent]:	# i node가 parent node보다 크면 swap
				tmp = self.data[parent]
				self.data[parent] = self.data[i]
				self.data[i] = tmp
				i = parent							# i node 갱신
			else:
				break

	def siftDown(self, i):							# i : root node
		siftkey = self.data[i]
		parent = i
		spotfound = False
		while ((2*parent <= self.n) and (not spotfound) and (parent != 0)):
			# childnode 중 큰 node를 선택
			if ((2*parent < self.n) and (self.data[2*parent] < self.data[2*parent + 1])):
				largerchild = 2*parent + 1
			else:
				largerchild = 2*parent
			# i node가 childnode보다 작으면, siftDown
			if siftkey < self.data[largerchild]:
				self.data[parent] = self.data[largerchild]
				parent = largerchild
			else:
				spotfound = True
		self.data[parent] = siftkey

	# depth d-1에 존재하는 node들부터 차례로 siftDown을 수행
	def makeHeap2(self):
		d = int(math.log2(self.n))
		while d > 0:
			for i in range(pow(2, d-1), pow(2, d)):
				self.siftDown(i)
			d -= 1

	# heap의 root node를 추출하고, 가장 아래의 node를 root로 보내고 siftdown하여 heap을 재구성
	def root(self):
		# 추가하였음. 힙이 더이상 없을 때는 down 없음
		if (self.n > 0):
			keyout = self.data[1]
			self.data[1] = self.data[self.n]
			self.n -= 1							# node의 총 개수 -1
			self.siftDown(1)
			self.data.pop(self.n+1)				# 가장 아래의 node를 삭제
			# 가장 아래의 node를 배열에서 삭제하는 pop을 siftDown(1)이후에 해야 함.
			# 만약 siftDown(1) 이전에 pop하면, 마지막 1개의 노드만 남게 되었을 때,
			# 인덱스가 1인 원소가 배열에 없어 siftDown(1)을 못하게 됨.
		return keyout

	# heap의 모든 node를 root node에서 제거하고 heap을 재구성. 제거한 node를 순서대로 S에 저장.
	def removeKeys(self):
		S = []
		for i in range(1, self.n+1):
			S.append(self.root())
		return S

def heapSort(a):
	T = Heap(a)
	S = T.removeKeys()
	return S

# 인덱스를 간단히 하기 위해 처음 엘리먼트 0 추가
a = [0,11,14,2,7,6,3,9,5]
b = Heap(a)
b.makeHeap2()
print("Heap : ", b.data)
b.addElt(50)
print("After addElt(50) : ",  b.data)
s = heapSort(a)
print("HeapSort : ", s)
