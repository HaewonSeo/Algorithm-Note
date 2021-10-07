#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

#define ABS(a) (a < 0 ? (-(a)) : (a))
typedef pair<int, int> pii;

int N, L, R;
int map[51][51];
bool vt[51][51];
int ans;

const int dr[4] = {-1, 1, 0, 0}; // 상하좌우
const int dc[4] = {0, 0, -1, 1};

bool can_move(pii a, pii b) {
	int dif;

	dif = ABS(map[a.first][a.second] - map[b.first][b.second]);
	return (dif >= L && dif <= R);
}

void move() {

	queue<pii> q;			// for BFS
	queue<pii> alliance;	// for averaging population
	int sum = 0;

	while (1) {

		bool is_moved = false; // 인구이동이 있는지 확인하는 변수

		// map을 돌면서 인구 이동을 실시
		for (int r = 1; r <= N; ++r) {
			for (int c = 1; c <= N; ++c) {
				if (vt[r][c]) continue;

				q.push(pii(r, c));
				alliance.push(pii(r, c));
				sum = map[r][c];
				vt[r][c] = true;

				// bfs로 연합국가 탐색
				while (!q.empty()) {
					pii cur = q.front(); q.pop();

					for (int i = 0; i < 4; ++i) {
						pii nt;
						nt.first = cur.first + dr[i];
						nt.second = cur.second + dc[i];

						if (nt.first < 1 || nt.first > N || nt.second < 1 || nt.second > N)
							continue;
						if (vt[nt.first][nt.second])
							continue;
						if (can_move(cur, nt)) {
							is_moved = true; // 국경선이 열려 인구 이동이 가능하다!
							vt[nt.first][nt.second] = true;
							q.push(nt);
							alliance.push(nt);
							sum += map[nt.first][nt.second];
						}
					}
				}

				// 인구 분배
				int avg = sum / alliance.size();
				while (!alliance.empty()) {
					pii country = alliance.front(); alliance.pop();
					map[country.first][country.second] = avg;
				}
			}
		}
		// vt 초기화
		memset(vt, 0, sizeof(vt));

		// 인구이동 횟수 계산
		if (is_moved)
			ans++;
		else
			break;
	}
}

int main() {

	freopen("input.txt", "r", stdin);

	scanf("%d%d%d", &N, &L, &R);
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			scanf("%d", &map[i][j]);

	move();

	printf("%d\n", ans);
}
