#include <cstdio>
#include <algorithm>
using namespace std;

struct s_edge {
	int a, b, weight;
	bool operator <(s_edge const& other) {
		return weight < other.weight;
	}
};

struct s_edge edge[100000];
int parent[1000001];

int find(int a) {
	if (parent[a] == a) return a;
	else
		return parent[a] = find(parent[a]);
}

int uni(int a, int b) {
	int rootA = find(a), rootB = find(b);
	if (rootA == rootB)
		return 0;
	parent[rootB] = rootA;
	return 1;
}

int main() {
	int N, M;
	// N:컴퓨터 수, M:선의 수
	scanf("%d%d", &N, &M);

	for (int i = 0, a, b, c; i < M; i++) {
		scanf("%d%d%d", &a, &b, &c);
		edge[i] = {a, b, c};
	}

	// 비용 순으로 오름차순 정렬
	sort(edge, edge + M);

#ifdef DEBUG
	for (int i = 0; i < M; i++) {
		printf("%d%d%d\n", edge[i].a, edge[i].b, edge[i].weight);
	}
#endif

	// Kruskal
		// 가중치가 가장 작은 e 를 뽑는다.
		// 신장트리에 넣을 경우 사이클이 생기는지 확인
		// 사이클이 생기지 않으면 삽입


}
