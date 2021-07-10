#include <cstdio>

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);

	// DP 접근법
	// nCk
	// n * (n-1) * (n-2) * (n-3) ... * (n - k + 1): k 개의 곱
	// -----------------------------
	// k * (k-1) * (k-2) * (k-3) ... * 1
	// 분모는 1부터 나누어주어야 /으로 인한 오차가 없다.
	int ans = 1;
	for (int i = n, j = 1; j <= k; i--, j++) {
		ans *= i;
		ans /= j;
	}
	printf("%d", ans);
}
