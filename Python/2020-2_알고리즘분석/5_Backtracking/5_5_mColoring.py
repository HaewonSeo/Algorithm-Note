def color(i, vcolor):
	if promising(i, vcolor):		# 유망성 검사
		if i == n-1:				# 모든 노드가 유망하다면
			print("sol ", vcolor)	# 출력
		else:
			for c in range(1, m+1): # 모든 색깔에 대해서
				vcolor[i+1] = c		# 다음 노드의 색깔을 결정하고
				color(i+1, vcolor)	# 다음 노드를 기준으로 재귀 함수를 호출한다.


def promising(I, vcolor):
	switch = True
	j = 0

	# I노드와 인접한 모든 노드의 색깔이 I노드의 색깔과 같은지를 검사
	while j < I and switch:
		if W[I][j] == 1 and vcolor[I] == vcolor[j]:
			switch = False							# 인접한 노드의 색깔이 같다면, 유망하지 않다.
		j += 1
	return switch


W = [[0,1,1,1],[1,0,1,0],[1,1,0,1],[1,0,1,0]]
n = len(W)										# 문제 크기와 무관하게 작동되기 위함
vcolor = n * [0]								# 각 노드의 색깔을 저장한 배열
m = 3											# 색깔의 개수. 색깔은 1~m으로 표현
color(-1, vcolor)								# root는 0번째 노드이므로 i는 -1부터 시작한다.
