#include <cstdio>

int N, M;
int a[100001];
int sum[100001];

int main()
{
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &a[i]);
		sum[i] = sum[i-1] + a[i];
	}
	int a, b, ans;
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &a, &b);
		ans = sum[b] - sum[a-1];
		printf("%d\n", ans);
	}
}
