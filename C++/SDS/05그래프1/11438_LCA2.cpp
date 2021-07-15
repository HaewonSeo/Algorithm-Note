#include <cstdio>
#include <queue>
using namespace std;

int lca(int a, int b) {
	int tmp;
	if (dep[b] < dep[a]) {
		tmp = a, a = b, b = tmp;
	}
	tmp = dep[b] - dep[a];
	for (int i = 0; i < PIV; i++) {
		int bit = (1 << i);
		if ((tmp & bit) == (bit))
			b = par[i][b];
	}
	if (a == b) return a; // a가 바로 lca이므로 리턴

	for (int i = PIV - 1; i >= 0; i--) {
		if (par[i][a] != par[i][b])
			a = par[i][a], b = par[i][b];
	}
	return par[0][a];
}

int main() {
	int N, M, a, b;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
	}
}
