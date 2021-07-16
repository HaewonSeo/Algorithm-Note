#include <cstdio>

int N, M;
//int a[1<<10|1][1<<10|1]; // 굳이 필요없음
int dp[1<<10|1][1<<10|1];

int main() {
	scanf("%d%d", &N, &M);
	int a;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &a);
			dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1] + a;
		}
	}
	int ans, x1, y1, x2, y2;
	while(M--) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		ans = dp[x2][y2] - dp[x2][y1-1] - dp[x1-1][y2] + dp[x1-1][y1-1];
		printf("%d\n", ans);
	}
}
