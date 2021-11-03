#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

#define MAX 20001

int graph[MAX][MAX];
int vt[MAX];

int bfs(int size) {

	queue<int> q;
	q.push(1);
	vt[1] = 1;

	int maxLen = 0;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (int next = 1; next <= size; next++) {
			if (!graph[cur][next]) continue;
			if (vt[next]) continue;

			q.push(next);
			vt[next] = vt[cur] + 1;
			if (vt[next] > maxLen)
				maxLen = vt[next];
		}
	}

	int cnt = 0;
	for (int i = 1; i <= size; i++)
		if (vt[i] == maxLen) {
			cnt++;
			cout << i << " " << maxLen << endl;
		}

	return cnt;
}

int solution(int n, vector<vector<int>> edge) {
	int answer = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			vt[i] = 0;
			graph[i][j] = 0;
		}
	}


	for (vector<int> v : edge) {
		graph[v[0]][v[1]] = 1;
		graph[v[1]][v[0]] = 1;
	}

	answer = bfs(n);

	return answer;
}
