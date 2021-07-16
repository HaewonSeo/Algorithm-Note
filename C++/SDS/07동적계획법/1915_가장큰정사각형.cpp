#include <cstdio>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int n, m, len;
//int a[1000][1000]; // 굳이 필요 없다.
int a;
int dp[1000][1000];
char str[1001]; // 문자열 입력을 위해서는 정적 공간을 할당해야 함.

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		for (int j = 0; j < m; j++) {
			a = str[j] - '0';
			// dp 갱신
			if (i == 0 || j == 0)
				dp[i][j] = a;
			else if (a)
				dp[i][j] = MIN(MIN(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
			len = MAX(dp[i][j], len);
		}
	}
#ifdef DEBUG
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d", dp[i][j]);
		}
		printf("\n");
	}
#endif
	printf("%d", len * len);
}
