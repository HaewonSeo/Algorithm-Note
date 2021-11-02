#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int a[301];
int dp[301];

int main() {
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &a[i]);
		if (i <= 2)
			dp[i] = dp[i-1] + a[i];
		else
			dp[i] = max(dp[i-2] + a[i], dp[i-3] + a[i-1] + a[i]);
	}
	printf("%d", dp[N]);
}
