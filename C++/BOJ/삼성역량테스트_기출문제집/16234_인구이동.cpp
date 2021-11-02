#include <cstdio>	// [iostream 에 비해 메모리를 적게 사용한다.
#include <queue>
#include <cstring>
using namespace std;

#define ABS(a) (a < 0 ? (-(a)) : (a))
typedef pair<int, int> pii;

int N, L, R;
int map[50][50];
queue<pii> map_q;
bool vt[50][50];
int ans;

const int dr[4] = {-1, 1, 0, 0}; // 상하좌우
const int dc[4] = {0, 0, -1, 1};

//[inline 으로 실행시간 단축]
inline bool can_move(pii a, pii b) {
	int dif;

	dif = ABS(map[a.first][a.second] - map[b.first][b.second]);
	return (dif >= L && dif <= R);
}

bool bfs(pii now) {

	queue<pii> q;			// for BFS
	vector<pii> alliance;	// for averaging population
	q.push(now);
	alliance.push_back(now);
	int sum = map[now.first][now.second];
	vt[now.first][now.second] = true;

	// bfs로 연합국가 탐색
	while (!q.empty()) {
		pii cur = q.front(); q.pop();
		for (int i = 0; i < 4; ++i) {
			pii nt;
			nt.first = cur.first + dr[i];
			nt.second = cur.second + dc[i];
			if (nt.first < 0 || nt.first >= N || nt.second < 0 || nt.second >= N)
				continue;
			if (vt[nt.first][nt.second])
				continue;
			if (can_move(cur, nt)) {
				vt[nt.first][nt.second] = true;
				q.push(nt);
				alliance.push_back(nt);
				sum += map[nt.first][nt.second];
			}
		}
	}
	// 인구 분배
	// [queue 대신 vector 사용으로 시간 단축]
	int alliance_size = alliance.size();
	int avg = sum / alliance_size;
	if (alliance_size > 1) {
		for (int k = 0; k < alliance_size; ++k) {
			pii country = alliance[k];
			map[country.first][country.second] = avg;
			// [연합국가만 재검사.. 왜냐면 비연합 국가는 재검사해봤자 비연합국가이기 때문. -> 실행시간 단축]
			map_q.push(country);
		}
		return true;
	}
	else
		return false;
}

void new_move() {

	while (1) {

		bool is_moved = false; // 인구이동이 있는지 확인하는 변수

		// map을 돌면서 인구 이동을 실시
		int map_size = map_q.size();
		while (map_size--) {
				pii now = map_q.front(); map_q.pop();
				if (vt[now.first][now.second]) continue;

				queue<pii> q;			// for BFS
				vector<pii> alliance;	// for averaging population
				q.push(now);
				alliance.push_back(now);
				int sum = map[now.first][now.second];
				vt[now.first][now.second] = true;

				// bfs로 연합국가 탐색
				while (!q.empty()) {
					pii cur = q.front(); q.pop();

					for (int i = 0; i < 4; ++i) {
						pii nt;
						nt.first = cur.first + dr[i];
						nt.second = cur.second + dc[i];

						if (nt.first < 0 || nt.first >= N || nt.second < 0 || nt.second >= N)
							continue;
						if (vt[nt.first][nt.second])
							continue;
						if (can_move(cur, nt)) {
							is_moved = true; // 국경선이 열려 인구 이동이 가능하다!
							vt[nt.first][nt.second] = true;
							q.push(nt);
							alliance.push_back(nt);
							sum += map[nt.first][nt.second];
						}
					}
				}

				// 인구 분배
				// [queue 대신 vector 사용으로 시간 단축]
				int alliance_size = alliance.size();
				int avg = sum / alliance_size;

				//[아래 조건문으로 인해 시간을 많이 단축! => 연합국가가 오직 한개인 경우는 재검사하지 않는다! 2개 이상의 국가로 이루어진 연합만 재검사!]
				if (alliance_size > 1) {
					for (int k = 0; k < alliance_size; ++k) {
						pii country = alliance[k];
						map[country.first][country.second] = avg;
						// [연합국가만 재검사.. 왜냐면 비연합 국가는 재검사해봤자 비연합국가이기 때문. -> 실행시간 단축]
						map_q.push(country);
					}
				}
				alliance.clear();	// clear!
			}

		// 인구이동 횟수 계산
		if (is_moved) {
			ans++;
			// vt 초기화
			memset(vt, false, sizeof(vt));
		}
		else
			break;
	}
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
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &map[i][j]);
			// [실행속도 개선을 위해 map_q를 추가]
			map_q.push(pii(i, j));
		}
	}

	//move(); //[처음에 구현한 함수]
	new_move();	// [시간 단축된 함수]

	// [bfs 부분만 함수로 구현한 경우]
	/*
	while (1) {

		bool is_moved = false; // 인구이동이 있는지 확인하는 변수

		// map을 돌면서 인구 이동을 실시
		int map_size = map_q.size();
		while (map_size--) {
				pii now = map_q.front(); map_q.pop();
				if (vt[now.first][now.second]) continue;
				if (bfs(now))
					is_moved = true;
		}
		if (is_moved) {
			ans++;
			memset(vt, false, sizeof(vt));
		}
		else
			break;
	}
	*/

	printf("%d\n", ans);
}
