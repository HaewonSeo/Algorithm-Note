#include <cstdio>
#include <queue>
using namespace std;

#define MAXNM 9
#define MAX(a, b) (a > b ? (a) : (b))
typedef pair<int, int> pii;

const int dr[4] = {-1, 1, 0, 0}; 	// 상 하 좌 우
const int dc[4] = {0, 0, -1, 1};

int N, M;
int map[MAXNM][MAXNM]; // 0:빈칸, 1:벽, 2:바이러스
int ans;

// int tmpCnt = 0;
// 1. 3개의 벽을 세워보고 => DFS
// 2. 바이러스 확산에 따른 안전영역의 크기를 파악. -> BFS

// bfs
void spread_virus() {

	int map_copy[MAXNM][MAXNM];
	queue<pii> virus_q;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			map_copy[i][j] = map[i][j];
			if (map_copy[i][j] == 2) {
				pii cur = pii(i, j);
				virus_q.push(cur);
			}
		}
	}

	while (!virus_q.empty()) {
		pii cur = virus_q.front(); virus_q.pop();

		for (int i = 0; i < 4; ++i) {
			pii nt = pii(cur.first + dr[i], cur.second + dc[i]);
			if (nt.first < 1 || nt.first > N || nt.second < 1 || nt.second > M)
				continue;
			if (map_copy[nt.first][nt.second] == 0) {
				map_copy[nt.first][nt.second] = 2;
				virus_q.push(nt);
			}
		}
	}

	// count safe area
	int cnt = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (map_copy[i][j] == 0)
				cnt++;
		}
	}
#ifdef DEBUG
	if (cnt > ans) {
		printf("%d\n", tmpCnt++);
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j)
				printf("%d ", map_copy[i][j]);
			printf("\n");
		}
	}
#endif
	ans = MAX(ans, cnt);
}

// dfs
void make_wall(int r, int c, int cnt) {
	if (cnt == 3) {
		spread_virus();
		return ;
	}

	for (int i = r; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			/* [i ==r && j <= c로 조건을 주어 틀림]
			[반례]
			3 4
			0 2 1 0
			0 1 1 2
			0 0 1 0
			위의 틀린 조건으로는 (1, 1)에 벽을 세우지 못한다..
			*/
			if (i == r && j < c) continue;
			if (map[i][j] == 1 || map[i][j] == 2) continue;

			map[i][j] = 1;
			make_wall(i, j, cnt + 1);
			map[i][j] = 0;
		}
	}
}

int main() {
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			scanf("%d", &map[i][j]);

	make_wall(1, 1, 0);

	printf("%d\n", ans);

	return 0;
}
