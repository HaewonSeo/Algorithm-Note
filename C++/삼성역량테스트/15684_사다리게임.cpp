#include <cstdio>

#define DEBUG1
#define MIN(a, b) ((a < b) ? (a) : (b))
int N, M, H; // N:세로선, M:가로선, H:세로선마다 가로선을 놓을 수 있는 위치
int ladder[11][31]; // [세로선][가로선위치]
int ans;

// 1. 가로선을 하나씩 놓아보고 (단, 연속되게 놓을 수는 없음)
// 2. i번의 세로선의 결과가 i번인지를 확인.
// 3. 2번이 확인된다면 가로선의 개수의 최솟값을 갱신

// i번 세로선의 결과가 i번이면 return 1; 아니면 return 0;
int run_ladder() {

	for (int n = 1; n <= N; ++n) {
		int c = n;
		for (int h = 1; h <= H; ++h) {
			if (ladder[c][h])
				c++;
			else if (ladder[c - 1][h])
				c--;
		}
		if (c != n)
			return 0;
	}
	return 1;
}

int dfs(int add, int hh, int nn, int i) {

	// 종료 조건은?
	if (ans == i)
	 	return 0;

#ifdef DEBUG
		printf("%d\n", add);
		for (int h = 1; h <= H; ++h) {
			for (int n = 1; n <= N - 1; ++n) {
				printf("%d ", ladder[n][h]);
			}
		printf("\n");
		}
#endif
	if (add == i) {
		if (run_ladder())
			ans = i;
		return 0;
	}

	// [단순히 (좌우 방향 -> 세로 방향) 순이 (세로 방향 -> 좌우 방향) 순으로 가로선 넣었을 때보다 실행시간이 더 짧았다.]
	// [[그러나 세로 -> 좌우 순으로 진행하되, 아래의 while()문을 추가함으로써 실행시간을 많이 단축할 수 있다.] 라고 생각했는데 이해가 안된다!!!... 나중에 한번더 확인!]
	for (int n = nn; n <= N - 1; ++n) {
		for (int h = 1; h <= H; ++h) {
			if (n == nn && h < hh) // 새로운 가로선을 추가할 위치 결정
				continue;
			if (ladder[n][h]) // 이미 가로선이 존재하는 경우
				continue;
			if (ladder[n-1][h] || ladder[n+1][h]) // 가로선이 연속되는 경우
				continue;

			ladder[n][h] = 2;
			dfs(add + 1, h, n, i);
			ladder[n][h] = 0;

			// [[아래같이 생각했는데, 아래 반복문 추가시 결과는 오답.. 다시 읽어봐도 아닌 것 같다.]]
			// "해당 세로 줄에서 좌우로 나가는 가로선이 없다면 -> 해당 세로줄에 가로선을 넣어볼 필요가 없다"
			// 왜냐면, 게임의 목적상 다시 동일한 세로줄로 돌아와야 하는데 추가로 가로선을 넣으면 불필요하게 다른 세로선을 갔다가 다시 와야하기 때문..
			//while (!ladder[n-1][h] && !ladder[n+1][h])
			//	h++;

			// [아래 코드는 넣으면 에러]
			// dfs(add, h, n, i);
		}
	}
	return 0;
}

int main() {
	//setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	int a, b;

	scanf("%d%d%d", &N, &M, &H);
	for (int m = 0; m < M; ++m) {
		scanf("%d %d", &a, &b);
		ladder[b][a] = 1;
	}

	ans = 4;
	//[i변수를 추가하여 0개를 추가했을 때부터 사다리게임이 가능한지 확인한다.]
	//[사다리게임이 가능하다면 바로 return해서 불필요한 dfs()를 없애 실행 시간 단축이 가능!]
	for (int i = 0; i < 4; ++i) {
		dfs(0, 1, 1, i);
		if (ans == i) {
			printf("%d\n", ans);
			return 0;
		}
	}
	printf("-1\n");

	return 0;
}
