#include <cstdio>
#include <queue>
using namespace std;

#define DEBUG1

typedef struct s_fire {
	int r, c, m, d, s;	//m:질량, d:방향, s:속도
}				t_fire;

const int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int N, M, K;
int ans;
vector<t_fire> map[50][50];
queue<t_fire> q;

void divide(vector<t_fire> vec) {

	int sum_m = 0, sum_s = 0, cnt = vec.size();
	int dir = (vec[0].d & 1); // 모두 홀수이거나 모두 짝수이면 true
	bool flag = true;
	const int d[2][4] = {{0, 2, 4, 6}, {1, 3, 5, 7}};

	for (int i = 0; i < cnt; ++i) {
		sum_m += vec[i].m;
		sum_s += vec[i].s;
		if (dir != (vec[i].d & 1))
			flag = false;
	}

	// 4개로 분할해서 큐에 push
	for (int i = 0; i < 4; ++i) {
		t_fire cur;

		cur.r = vec[0].r;
		cur.c = vec[0].c;
		cur.m = sum_m / 5;
		cur.s = sum_s / cnt;
		// [index 실수함]
		if (flag)
			cur.d = d[0][i];
		else
			cur.d = d[1][i];

		if (cur.m > 0)
			q.push(cur);
	}
}

void run() {
	while (K--) {

		// 1. move
		int q_size = q.size();
		while (q_size--) {
			t_fire cur = q.front(); q.pop();
			cur.r += cur.s * dr[cur.d];
			cur.c += cur.s * dc[cur.d];
			while (cur.r < 0)
				cur.r += N;
			while (cur.r >= N)
				cur.r -= N;
			while (cur.c < 0)
				cur.c += N;
			while (cur.c >= N)
				cur.c -= N;

			// q의 fire를 이동시킨 후 해당 좌표의 map 벡터에 저장
			map[cur.r][cur.c].push_back(cur);
		}

		// 2. divide & combine fire_balls
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
#ifdef DEBUG
				printf("map[%d][%d] size = %d\n", i, j, map[i][j].size());
#endif
				if (map[i][j].size() == 0)
					continue;
				else if (map[i][j].size() == 1) {
#ifdef DEBUG
				printf("[%d][%d] m=%d s=%d d=%d\n",\
				map[i][j][0].r, map[i][j][0].c,map[i][j][0].m, map[i][j][0].s, map[i][j][0].d);
#endif
					q.push(map[i][j][0]);
					map[i][j].clear();
				}
				else if (map[i][j].size() > 1) {
#ifdef DEBUG
					printf("map[%d][%d] vectore size = %d\n", i, j, map[i][j].size());
					for (int k = 0; k < map[i][j].size(); ++k)
						printf("[%d][%d] m=%d s=%d d=%d\n", \
						map[i][j][k].r, map[i][j][k].c, map[i][j][k].m, map[i][j][k].s, map[i][j][k].d);
#endif
					divide(map[i][j]);
					map[i][j].clear();
				}
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < M; ++i) {
		t_fire tmp;
		scanf("%d%d%d%d%d", &tmp.r, &tmp.c, &tmp.m, &tmp.s, &tmp.d);
		q.push(tmp);
	}

	run();

	while (!q.empty()) {
		t_fire cur = q.front(); q.pop();
		ans += cur.m;
	}
	printf("%d\n", ans);

	return 0;
}
