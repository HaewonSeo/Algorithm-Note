#include <cstdio>

int cache[1001][1001];

int nCr(int n, int r) {
	if (r == 0 || n == r) {
		return 1;
	}
	if (cache[n][r] != -1) {
		return cache[n][r];
	}
	int tmp = (nCr(n - 1, r - 1) + nCr(n - 1, r)) % 10007;
	cache[n][r] = tmp;
	return cache[n][r];
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0 ; i <= n; i++) {
		for (int j = 0 ; j <= k; j++) {
			// n < k 인 값은 계산하지 않으므로
			if (n >= k)
				cache[i][j] = -1;
		}
	}
	printf("%d", nCr(n, k));
}
