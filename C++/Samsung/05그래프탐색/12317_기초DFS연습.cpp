int childList[100][5]; // [i][j], i값을 가지는 왕의 자식을 저장
int childCnt[100]; // [i], i값을 가지는 왕의 자식수

void dfs_init(int N, int path[40][2])
{
	for (int i = 0; i < 100; i++) {
		childCnt[i] = 0;
		for (int j = 0; j < 5; j++)
			childList[i][j] = 0;
	}

	// path정보를 childList에 저장, childCnt 갱신
	for (int i = 0; i < N - 1; i++) {
		int cur = path[i][0];
		int j = childCnt[cur]++;
		childList[cur][j] = path[i][1];
	}

}

int dfs(int n)
{
	int top = -1;
	int stack[40] = {0,};
	int parent = n;

	stack[++top] = n;
	while(top != -1) {
		// pop
		int cur = stack[top--];
		if (cur > parent)
			return cur;

		// push (left -> rigth)
		for (int next = childCnt[cur] - 1; next >= 0; next--) {
			stack[++top] = childList[cur][next];
		}
	}

	return -1;
}
