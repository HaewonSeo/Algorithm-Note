def promising(i, weight, total):
	# "weight+w[i+1] > W (if weight != W) or weigth+total < W 이면 유망하지 않다."의 Not
	return (weight+total >= W) and (weight == W or weight+w[i+1] <= W)

def s_s(i, weight, total, include):
	if promising(i, weight, total):							# weight : i노드까지 포함된 무게의 합
		if weight == W:										# solution 출력
			print("sol ", include)
		else:
			include[i+1] = 1								# 다음 노드를 합에 포함할 경우
			s_s(i+1, weight+w[i+1], total-w[i+1], include)	# i, weight, total 갱신 후 호출
			include[i+1] = 0								# 다음 노드를 합에 포함하지 않을 경우
			s_s(i+1, weight, total-w[i+1], include)			# i, total 갱신 후 호출

# 연습문제 : S={1,2,...,100}, W=365
# w = []
# for i in range(1,101):
#     w.append(i)
# W = 365

w = [1,4,2,6]
n = len(w)						# 문제 크기와 무관하게 작동되기 위함
W = 6

print("items =", w, "W =", W)
include = n * [0]				# 부분집합의 각 노드의 포함여부를 저장
total = 0						# 남아있는 아이템의 무게의 총합
for k in w:
    total += k
s_s(-1, 0, total, include)		# root는 0번째 노드이므로 i는 -1부터 시작한다.
