#include <cstdio>
#include <vector>
using namespace std;

typedef struct s_cctv {
	int r, c, type;
}				t_cctv;
#define MIN(a, b) (a < b ? (a) : (b))
#define DEBUG

int N, M;
int map[9][9];
vector<t_cctv> cctv_v;
int cctv;	//size
int ans;

// 상하좌우
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};
// 북동, 동남, 남서, 서북
const int dr3[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int dc3[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
// ㅗ ㅜ ㅓ ㅏ
const int dr4[4][3] = {{0, -1, 0}, {0, 1, 0}, {0, -1, 1}, {-1, 1, 0}};
const int dc4[4][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 0}, {0, 0, 1}};

void calc_unsafe() {
	int cnt = 0;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (map[i][j] == 0)
				cnt++;
		}
	}
#ifdef DEBUG
	if (cnt < ans) {
		printf("[cnt=%d]\n", cnt);
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				printf("%d ", map[i][j]);
			}
			printf("\n");
		}
	}
#endif
	ans = MIN(ans, cnt);
}

void look_dir(t_cctv cur, int dr, int dc) {
	int nr, nc;
	nr = cur.r;
	nc = cur.c;

	while (1) {
		nr += dr;
		nc += dc;
		if (nr < 1 || nr > N || nc < 1 || nc > M) break;
		if (map[nr][nc] == 6) break;
		if (map[nr][nc] >= 1 && map[nr][nc] <= 5) continue;
		//[누적 감시 횟수를 저장]
		if (map[nr][nc] == 0)
			map[nr][nc] = 7;
		else if (map[nr][nc] >= 7)
			map[nr][nc]++;
	}
}

void look_dir_remove(t_cctv cur, int dr, int dc) {
	int nr, nc;
	nr = cur.r;
	nc = cur.c;

	while (1) {
		nr += dr;
		nc += dc;
		if (nr < 1 || nr > N || nc < 1 || nc > M) break;
		if (map[nr][nc] == 6) break;
		//[누적 감시 횟수만큼 차감]
		if (map[nr][nc] == 7)
			map[nr][nc] = 0;
		else if (map[nr][nc] > 7)
			map[nr][nc]--;
	}
}


void dfs(int cnt) {

	if (cnt == cctv) {
		calc_unsafe();
		return ;
	}

	t_cctv cur = cctv_v[cnt];

	// cctv 1
	if (cur.type == 1) {
		for (int i = 0; i < 4; ++i) {
			look_dir(cur, dr[i], dc[i]);
			dfs(cnt + 1);
			look_dir_remove(cur, dr[i], dc[i]);
		}
	}
	// 2
	else if (cur.type == 2) {
		for (int i = 0; i < 4; i+=2) {
			look_dir(cur, dr[i], dc[i]);
			look_dir(cur, dr[i+1], dc[i+1]);
			dfs(cnt + 1);
			look_dir_remove(cur, dr[i], dc[i]);
			look_dir_remove(cur, dr[i+1], dc[i+1]);
		}
	}
	// 3
	else if (cur.type == 3) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 2; ++j)
				look_dir(cur, dr3[i][j], dc3[i][j]);
			dfs(cnt + 1);
			for (int j = 0; j < 2; ++j)
				look_dir_remove(cur, dr3[i][j], dc3[i][j]);
		}
	}
	// 4
	else if (cur.type == 4) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 3; ++j)
				look_dir(cur, dr4[i][j], dc4[i][j]);
			dfs(cnt + 1);
			for (int j = 0; j < 3; ++j)
				look_dir_remove(cur, dr4[i][j], dc4[i][j]);
		}
	}
	// 5
	else if (cur.type == 5) {
		for (int i = 0; i < 4; ++i)
			look_dir(cur, dr[i], dc[i]);
		dfs(cnt + 1);
		for (int i = 0; i < 4; ++i)
			look_dir_remove(cur, dr[i], dc[i]);
	}

}

int main() {
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d", &map[i][j]);
			if (map[i][j] >= 1 && map[i][j] <= 5) {
				t_cctv cur;
				cur.r = i;
				cur.c = j;
				cur.type = map[i][j];
				cctv_v.push_back(cur);
			}
		}
	}
	cctv = cctv_v.size();
	ans = N * M;
	dfs(0);

	printf("%d\n", ans);
}
