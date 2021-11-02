#include <cstdio>
#include <algorithm>

int n;
int tri[501][501];
int dp[501][501]; // 현재까지의 경로 중 합이 최대가 되는 경로에 있는 수의 합을 저장
int ans;

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			scanf("%d", &tri[i][j]);
			dp[i][j] = tri[i][j] + std::max(dp[i-1][j-1], dp[i-1][j]);
		}
	}
	for (int j = 1; j <= n; j++)
		ans = std::max(dp[n][j], ans);

	printf("%d", ans);
}
