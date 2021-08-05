#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;

//[노드개수 0 하나 안써서 RTE 발생했음]
#define MAX 100000	 // 노드개수
#define MAX_DEPTH 17 // 2^17 > 100000 이므로 트리가 한방향으로 쏠려도 계산 가능하다.

int N;
vector<int> childList[MAX+1];	// i번 노드의 자식노드를 저장
int depth[MAX+1];				// i번 노드의 depth를 저장
int parent[MAX+1][MAX_DEPTH];	// parent[i][j] : i번 노드의 2^j번째 부모노드
//[ans를 int로 잡으니 testcase 2개가 통과되지 않았음]
long long ans;

// [Lowest Common Ancestor] : u와 v의 공통조상을 return
// O(logN) 방식 - 2^k 번째 부모 노드를 확인
int LCA(int u, int v) {
	// 0. v를 깊은 쪽으로 설정
	if (depth[u] > depth[v])
		swap(u, v);

	// 1. u와 v의 깊이를 동일하게 맞춘다.
	//	v의 가장 먼 조상이 u보다 깊으면 조상으로 대체
	for (int i = MAX_DEPTH - 1; i >= 0; i--) {
		if (depth[u] <= depth[parent[v][i]])
			v = parent[v][i];
	}

	// 만약 높이가 같다면, 공통조상=u=v
	if (u == v)
		return u;

	// 2. 깊이가 같은 상태에서 2^k만큼 올라가면서 공동조상을 찾는다.
	for (int i = MAX_DEPTH - 1; i >= 0; i--) {
		// 공통조상이 달라지면, 각각 조상으로 이동
		if (parent[u][i] != parent[v][i]) {
			u = parent[u][i];
			v = parent[v][i];
		}
	}
	// 최종적으로 lca의 자식노드까지 이동함..
	return parent[u][0];
}

// parent[][] 저장
void calcParent() {
	for (int j = 1; j < MAX_DEPTH; j++) {
		for (int i = 1; i <= MAX; i++) {
			// parent[i]의 2^j번째 부모를 DP로 계산
			// (j=4인 경우)
			// parent[i]의 16번째 부모는 (parent[i]의 8번째 부모)의 8번째 부모
			parent[i][j] = parent[parent[i][j-1]][j-1];
		}
	}
}


// 1. DFS로 depth[]와 parent[i][0]를 저장
void getTreeDFS(int par) {
	for (int i = 0; i < childList[par].size(); i++) {
		int cur = childList[par][i];
		depth[cur] = depth[par] + 1;	// depth 저장
		parent[cur][0] = par;			// 2^0=1 번째 부모노드 저장
		getTreeDFS(cur);
	}
}


// 2. BFS로 depth[]와 parent[i][0]을 계산
void getTreeBFS() {
	//queue<int> q;
	//q.push(1);
	int q[MAX];
	int front = -1, rear = -1;
	q[++rear] = 1;
	depth[1] = 1; //root(1번노드)의 depth는 1

	while (front != rear) {
		//int par = q.front(); q.pop();
		int par = q[++front];

		for (int i = 0; i < childList[par].size(); i++) {
			int cur = childList[par][i];
			if (!depth[cur]) {
				depth[cur] = depth[par] + 1;
				parent[cur][0] = par;
				//q.push(cur);
				q[++rear] = cur;
			}
		}
	}
}

// 각 노드를 BFS로 방문할 때의 이동거리를 계산
void calcDist() {
	//[queue를 직접 구현하니 시간 0.2s정도 단축됨]
	//queue<int> q;
	//q.push(1);
	int q[MAX];
	int front = -1, rear = -1;
	q[++rear] = 1;
	int pre = 1;

	while (front != rear) {
		//int cur = q.front(); q.pop();
		int cur = q[++front];

		// 이전노드(pre)와 현재노드(cur)의 거리를 계산
		int lca = LCA(pre, cur);
		ans += (depth[pre] - depth[lca]) + (depth[cur] - depth[lca]);
		pre = cur;

		for (int i = 0; i < childList[cur].size(); i++) {
			int nt = childList[cur][i];
			//q.push(nt);
			q[++rear] = nt;
		}
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	scanf("%d", &T);

	for(test_case = 1; test_case <= T; ++test_case)
	{
		//[memset 사용시 속도 절약됨]
		memset(depth, 0, sizeof(int) * (MAX+1));
		memset(parent, 0, sizeof(int) * (MAX+1) * MAX_DEPTH);

		for (int i = 0; i <= MAX; i++) {
			//depth[i] = 0;
			childList[i].clear();
			//for (int j = 0; j < MAX_DEPTH; j++)
				//[i][j] = 0;
		}

		scanf("%d", &N);

		int parent;
		for (int node = 2; node <= N; node++) {
			scanf("%d", &parent);
			childList[parent].push_back(node);
		}

		// Tree 생성 : depth[]와 parent[][] 계산
		depth[1] = 1;
		//[DFS 사용시 RTE 발생(스택메모리 초과)]
		//getTreeDFS(1);
		getTreeBFS();
		calcParent();

		// 이동 거리를 계산
		ans = 0;
		calcDist();
		printf("#%d %lld\n", test_case, ans);
	}

	return 0;
}
