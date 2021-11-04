// LG전자 코딩테스트 자동차 출차 문제와 비슷한 유형
#include <cstdio>
#include <queue>
using namespace std;

typedef pair<pair<int, int>, int> ppiii;

#define f first
#define s second

// 상 하 좌 우
const int dy[4] = {-1, 1, 0, 0};
const int dx[4] = {0, 0, -1, 1};

int N, M;
char map[1001][1002];
int vt[1001][1002][2];
	// vt[r][c][0] : 벽을 부순 상태에서 해당 칸에 도착하는데 이동한 칸의 개수
	// vt[r][c][1] : 벽을 부수지 않은 상태에서 해당 칸에 도착하는 데 이동한 칸의 개수

int bfs() {
	queue<ppiii> q;
	q.push(ppiii({1, 1}, 1)); // {y,x}, wall. wall은 벽을 뚫을 수 있는 횟수
	vt[1][1][1] = 1;

	while (!q.empty()) {

		int y = q.front().f.f;
		int x = q.front().f.s;
		int wall = q.front().s;
		q.pop();

		// 먼저 목적지에 도착한 경로가 더 짧은 경로임
		if (y == N && x == M)
			return vt[y][x][wall];

		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny <= 0 || ny > N || nx <= 0 || nx > M)
				continue;

			// next가 벽이고, 벽을 아직까지 한번도 안 부수었을 경우
			if (map[ny][nx] == '1' && wall) {
				vt[ny][nx][0] = vt[y][x][1] + 1;
				q.push({{ny, nx}, 0});
			}

			// next가 길이고, 아직 방문하지 않았다면
			if (map[ny][nx] == '0' && vt[ny][nx][wall] == 0) {
				vt[ny][nx][wall] = vt[y][x][wall] + 1;
				q.push({{ny, nx}, wall});
			}
		}
	}
	// 목적지에 도착하지 못하고 탐색이 종료되었을 때
	return -1;
}

int main() {

	freopen("input.txt", "r", stdin);
	scanf("%d%d", &N, &M);

	for (int n = 1; n <= N; ++n)
		scanf("%s", &map[n][1]);

	printf("%d\n", bfs());
}
