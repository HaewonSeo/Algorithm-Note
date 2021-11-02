#include <cstdio>

int parent[1000001];

int find(int a) {
	if (parent[a] == a) return a;
	else
		return parent[a] = find(parent[a]);
}

void uni(int a, int b) {
	int rootA = find(a), rootB = find(b);
	parent[rootB] = rootA;
}

int main() {
	int m, n, a, b, c;
	scanf("%d%d", &n, &m);

	// 초기화
	for (int i = 0; i <= n; i++)
		parent[i] = i;

	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		// b, c를 합친다.
		if (a == 0) {
			uni(b, c);
		}
		// b, c가 같은 집합에 포함되어 있는지 확인
		else if (a == 1) {
			int rootB = find(b), rootC = find(c);
			if (rootB == rootC)
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
}
