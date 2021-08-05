#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

#define endl '\n'
typedef pair<int, int> pii;

// 12시부터 시계방향
const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int N;
int map[300][300];
bool vt[300][300];

// 주변 8 방향의 지뢰가 있는지 확인
int isZero(pii cur) {

	for (int i = 0; i < 8; i++) {
		pii nt = {cur.first + dy[i], cur.second + dx[i]};
		if (nt.first < 0 || nt.second < 0 || nt.first >= N || nt.second >= N) continue;
		if (map[nt.first][nt.second] == -2)
			return false;
	}
	return true;
}

int bfs(pii n) {
	queue<pii> q;
	q.push(n);

	while (!q.empty()) {
		pii cur = q.front();
		q.pop();

		for (int i = 0; i < 8; i++) {
			pii nt = {cur.first + dy[i], cur.second + dx[i]};
			if (nt.first < 0 || nt.second < 0 || nt.first >= N || nt.second >= N) continue;

			// [visited 체크하여 timeout 오류 해결]
			if (vt[nt.first][nt.second]) continue;
			vt[nt.first][nt.second] = true;

			// 주변에 지뢰가 없다면, 주변을 Queue에 추가
			if (isZero(nt))
				q.push(nt);
		}
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL); cout.tie(NULL);
	// freopen("input.txt", "r", stdin);
	// cin>>T;
	scanf("%d", &T);
	for(test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				char c;
				//[" %c" 로 입력받지 않아 오류 발생함.]
				scanf(" %c", &c);
				if (c == '*') {
					map[i][j] = -2;
					vt[i][j] = true;
				}
				else if (c == '.') {
					map[i][j] = -1;
					vt[i][j] = false;
				}
			}
		}

		// [. 순서대로 체크하면 안되고, 0인 .을 우선적으로 bfs해야함]
		int ans = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!vt[i][j] && isZero({i, j})) {
					vt[i][j] = true;
					bfs({i,j});
					ans++;
				}
			}
		}

		// 나머지 방문하지 않은 . 개수를 count
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!vt[i][j]) {
					ans++;
				}
			}
		}
#ifdef _DEBUG
		printf("\n");
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				printf("%d ", vt[i][j]);
			}
			printf("\n");
		}
#endif
		printf("#%d %d\n", test_case, ans);
	}

	return 0;
}
