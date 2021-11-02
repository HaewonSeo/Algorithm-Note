#include <cstdio>
#include <cstring>
using namespace std;

int cache[31][31];

int nCr(int n, int r) {
	if (r == 0 || n == r)
		return 1;
	if (cache[n][r] != -1)
		return cache[n][r];
	int res = nCr(n-1, r) + nCr(n-1, r-1);
	cache[n][r] = res;
	return res;
}

int main() {
	int T;
	scanf("%d", &T);

	int N, M;
	for (int i = 0; i < T; i++) {
		scanf("%d%d", &N, &M);
		memset(cache, -1, sizeof(int) * 31 * 31);
		printf("%d\n", nCr(M, N));
	}
}
