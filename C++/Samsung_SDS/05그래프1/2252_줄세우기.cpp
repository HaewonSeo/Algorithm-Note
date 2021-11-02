#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int inDegree[32001];
vector<int> adjacentList[32001];
queue<int> q;
vector<int> ans;

int main() {
	int N, M, a, b;
	// N명, M번의 비교
	scanf("%d%d", &N, &M);

	while (M--) {
		scanf("%d%d", &a, &b);
		// 인접노드 추가
		adjacentList[a].push_back(b);
		// in-degree ++
		inDegree[b]++;
	}

	for (int i = 1; i <= N; i++) {
		if (inDegree[i] == 0)
			q.push(i);
	}

	while (!q.empty()) {

		int cur = q.front();
		q.pop();
		ans.push_back(cur);

		// 정답에 추가한 노드에 연결된 인접노드들의 inDegree--
		// 인접노드 중 inDegree가 0인 노드를 q에 추가...
		for (int j = 0; j < adjacentList[cur].size(); j++) {
			int adjacentNode = adjacentList[cur][j];
			inDegree[adjacentNode]--;
			if (inDegree[adjacentNode] == 0)
				q.push(adjacentNode);
		}
	}

	for (int i = 0; i < ans.size(); i++) {
		printf("%d ", ans[i]);
	}
}
