#include <cstdio>
#include <cstring>

int N, M, K;
int cache[201][101];
char ans[201];

int nCr(int n, int r) {
	if (n == r || r == 0)
		return 1;
	if (cache[n][r] != -1)
		return cache[n][r];
	int res = nCr(n-1, r) + nCr(n-1, r-1);
	if (res > 1000000000)
		cache[n][r] = 1000000001;
	else
		cache[n][r] = res;
	return cache[n][r];
}

int main()
{
	scanf("%d%d%d", &N, &M, &K);
	memset(cache, -1, sizeof(int) * 201 * 101);

	if (nCr(N+M, N) < K) {
		printf("-1");
		return 0;
	}
	// aazz
	// azaz
	// azza
	// +3C1=3가지
	// zaaz
	// zaza
	// zzaa
	// +3C2=3가지
	// 4C2

	// 모든 조합을 찾아서 우선순위 큐에 넣는다? ... 너무 경우가 많을 듯?
	// 조합을 순서대로 구하여 가짓수를 센다.

	// 남은 A와 Z 개수
	int cntA = N, cntZ = M;
	for (int i = 0; i < N + M; i++) {
		if (cntA == 0) {
			ans[i] = 'z';
			continue;
		}
		// i번째가 a인 경우
		int cnt = nCr(cntA - 1 + cntZ, cntZ);
		if (cnt >= K) {
			// i번째가 a인 문자열의 개수에 K번째가 포함된다.
			ans[i] = 'a';
			cntA--;
		}
		else {
			// i번째가 a인 문자열의 개수에 K번째가 포함되지 않는다.
			// -> i번째가 z인 문자열의 경우에 K번째가 포함된다.
			// -> K번째는 갱신된다.
			ans[i] = 'z';
			cntZ--;
			K -= cnt;
		}
	}
	printf("%s", ans);
	return 0;
}
