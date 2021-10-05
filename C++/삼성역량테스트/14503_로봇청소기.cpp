#include <cstdio>
#include <algorithm>
using namespace std;

#define DEBUG
#define MAXNM 50
typedef pair<int, int> pii;

int N, M;
int map[MAXNM][MAXNM]; // 0 빈공간, 1 벽
bool vt[MAXNM][MAXNM];
int ans;

// 0북/ 1동/ 2남/ 3서
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

int rotate_L(int d) {
	int next = d - 1;

	if (next == -1)
		next = 3;

	return next;
}

pii move_back(pii cur, int d) {
	pii next;

	next.first = cur.first + ((-2) * dr[d]);
	next.second = cur.second + ((-2) * dc[d]);

	return next;
}

void clean(pii cur, int d) {

	vt[cur.first][cur.second] = true;
	ans++;

	int nd = d;
	int t = 0;
	for (int i = 0; i < 4; ++i) {
		nd = rotate_L(nd);
		pii nt = pii(cur.first + dr[nd], cur.second + dc[nd]);
		if (nt.first < 0 || nt.first >= N || nt.second < 0 || nt.second >= M)
			continue;

#ifdef DEBUG
		if (ans < 30) {
			printf("\n[t %d]\ni=%d\nnd=%d\nans=%d\n", t++, i, nd, ans);
			printf("cur[%d][%d]\n", cur.first, cur.second);
			printf("next[%d][%d]\n", nt.first, nt.second);
			for (int x = 0; x < N; ++x) {
				for (int y = 0; y < M; ++y) {
					if (map[x][y] == 1)
						printf("1 ");
					else if (vt[x][y] == 1)
						printf("* ");
					else
						printf("%d ", vt[x][y]);
				}
				printf("\n");
			}
		}
#endif

		// a
		if (vt[nt.first][nt.second] == 0 && map[nt.first][nt.second] == 0) {
			// clean
			vt[nt.first][nt.second] = true;
			ans++;
			// move
			cur = nt;
			i = -1;
		}
		// b
		else if (vt[nt.first][nt.second] || map[nt.first][nt.second]) {
			// c, d
			if (i == 3) {
				// c : move backward
				// [4방향 돌면서(x) 현재 방향 반대로(o) 1칸 후진]
				// [2칸 후진이 아니라 1칸 후진!! 문제 제대로 읽기]
				pii nnt;
				nnt.first = cur.first - dr[nd];
				nnt.second = cur.second - dc[nd];
				// d
				if (map[nnt.first][nnt.second] == 1)
					return ;

				// clean
				if (vt[nnt.first][nnt.second] == 0) {
					vt[nnt.first][nnt.second] = true;
					ans++;
				}
				// move
				cur = nnt;
				i = -1;
			}
		}
	}
}

int main() {
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	pii s;
	int d;

	scanf("%d%d", &N, &M);
	scanf("%d%d%d", &s.first, &s.second, &d);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			scanf("%d", &map[i][j]);

	clean(s, d);

	printf("%d\n", ans);
}
