def kp(i, profit, weight):
    global bestset
    global maxp

    if (weight <= W and profit > maxp):         # 최적값과 최적의 set 을 유지한다.
        maxp = profit
        bestset = include[:]

	# best = include는 best를 include의 reference로 만든다.
	# 한 번 동일한 값을 가진 후 그 이후는 계속 동일함.
	# 그 후 include를 바꿔가면서 bestset에 저장하면서 최적의 set을 찾는다.

	# DFS
    if (promising(i, weight, profit)):			# 남은 공간이 있고, 확장 시 bound값이 현재 값보다 크면
        include[i+1] = 1						# i+1 포함시
        kp(i+1, profit+p[i+1], weight+w[i+1])
        include[i+1] = 0						# i+1 미포함시
        kp(i+1, profit, weight)


def promising(i, weight, profit):
    global maxp

    if (weight >= W):
        return False							# 남은 공간이 없으면 유망하지 않음
    else:
        j = i+1									# 현재 아이템의 다음 아이템부터 계산
        bound = profit							# 현재 이익
        totweight = weight						# 현재 무게

        while j < n and totweight + w[j] <= W:	# 공간이 남으면 남은 아이템에 대해 반복
            totweight = totweight + w[j]		# 다음 아이템을 넣어, 총 무게를 갱신
            bound = bound + p[j]				# 다음 아이템을 넣어, 총 이익을 갱신
            j += 1

        k = j
        if k < n:								# 남은 공간만큼 k번째 아이템의 단위무게당 이익을 계산하여 bound에 추가한다.
            bound = bound + ((W-totweight) * (p[k]/w[k])) # bound : 이론적으로 현 상태에서 얻을 수 있는 최대 이익
        return bound > maxp						# 계산한 bound가 현재 maxp보다 크다면 True -> 유망함

n = 4               # item 수
W = 16              # 최대 공간
p = [40,30,50,10]   # profit, pi/wi 의 값이 큰 것부터 내림차순으로 아이템을 정렬한다
w = [2,5,10,5]      # weight. pi/wi 의 값이 큰 것부터 내림차순으로 아이템을 정렬한다
maxp = 0
include = [0,0,0,0]
bestset = [0,0,0,0]
kp(-1,0,0)
print("Best set : ", bestset)
print("Max profit : ", maxProfit)
