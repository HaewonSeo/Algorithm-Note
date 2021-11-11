// (1) DP 풀이
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

int map[101][101];

int solution(int m, int n, vector<vector<int>> puddles) {
	int answer = 0;

	// m이 열, n이 행임을 주의
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			map[r][c] = 1;
		}
	}

	// 1행 또는 1열 위에 웅덩이 있으면 우하 방향으로 모두 0으로 초기화해주어야 함.
	// 시작점에서 절대 갈 수 없기 때문
	for (auto v : puddles) {
		map[v[1]][v[0]] = 0;

		// puddle[2, 1] -> 1행 2열에 웅덩이
		// 1행 초기화
		if (v[1] == 1) {
			for (int r = v[0]; r <= m; ++r)
				map[1][r] = 0;
		}
		// 1열 초기화
		if (v[0] == 1) {
			for (int c = v[1]; c <= n; ++c)
				map[c][1] = 0;
		}
	}

	for (int r = 2; r <= n; ++r) {
		for (int c = 2; c <= m; ++c) {
			if (map[r][c] == 0)
			   continue;
			map[r][c] = (map[r-1][c] + map[r][c-1]) % 1000000007;   // [여기서 % 연산해서 효율성 pass]
		}
	}
#ifdef DEBUG1
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			printf("%3d ", map[r][c]);
		}
		printf("\n");
	}
#endif
	answer = map[n][m];
	return answer;
}

/*
(2) BFS 풀이 - 시간 초과
// 방향이 우 or 하 이기 때문에 학교까지 가는 모든 경로가 최단 거리이다.
// 돌아가는 경로가 없기 때문, 움직일수록 학교에 가까워진다.

#include <string>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
const int dr[2] = {0, 1}; // 우 하
const int dc[2] = {1, 0};
int map[101][101];

int solution(int m, int n, vector<vector<int>> puddles) {
	int answer = 0;
	queue<pii> q;

	for (auto v : puddles)
		map[v[1]][v[0]] = -1;

	map[m][n] = m + n - 3;
	q.push(pii(1, 1));

	while (!q.empty()) {

		pii cur = q.front(); q.pop();

		if (cur.first == n && cur.second == m)
			answer++;

		for (int i = 0; i <= 1; ++i) {
			pii nt;
			nt.first = cur.first + dr[i];
			nt.second = cur.second + dc[i];
			if (nt.first <= 0 || nt.first > n || nt.second <= 0 || nt.second > m)
				continue;
			if (map[nt.first][nt.second] == -1)
				continue;
			q.push(nt);
		}
	}

	answer %= 1000000007;
	return answer;
}

*/
