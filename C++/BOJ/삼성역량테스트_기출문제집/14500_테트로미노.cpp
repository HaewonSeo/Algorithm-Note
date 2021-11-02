#include <cstdio>

// [N과 M의 범위를 제대로 파악하지 못함]
#define MAXNM 501
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int N, M;
int map[MAXNM][MAXNM];
bool vt[MAXNM][MAXNM];
int ans;

const int dr[4] = {0, 0, 1, -1}; //동서남북
const int dc[4] = {1, -1, 0, 0};

// ㅗ ㅜ ㅏ ㅓ -> 천천히 생각
const int er[4][4] = {{0, 0, 0, -1}, {0, 0, 0, 1}, {0, 1, 2, 1}, {0, 1, 2, 1}};
const int ec[4][4] = {{0, 1, 2, 1}, {0, 1, 2, 1}, {0, 0, 0, 1}, {0, 0, 0, -1}};

// [ㅗ ㅜ ㅏ ㅓ 모양은 dfs로 만들 수 없다. => 예외적으로 처리]
void dfs(int r, int c, int cnt, int sum) {
	if (cnt == 4) {
		ans = MAX(ans, sum);
		return ;
	}

	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i], nc = c + dc[i];
		// [아래 두 조건문의 순서도 중요.. 범위를 먼저 확인해야 함]
		if (nr < 1 || nr > N || nc < 1 || nc > M)
			continue;
		if (vt[nr][nc])
			continue;
		vt[nr][nc] = 1;
		dfs(nr, nc, cnt + 1, sum + map[nr][nc]);
		// [dfs 가 종료될 때 vt를 0으로 저장해주기 때문에 별도의 초기화가 필요없다.]
		vt[nr][nc] = 0;
	}
}

void handle_exception(int r, int c) {

	for (int i = 0; i < 4; ++i) {
		bool isIn = true;
		int sum = 0;

		// ㅗ ㅜ ㅏ ㅓ
		for (int j = 0; j < 4; ++j) {
			int nr = r + er[i][j], nc = c + ec[i][j];

			if (nr < 1 || nr > N || nc < 1 || nc > M) {
				isIn = false;
				break;
			}
			sum += map[nr][nc];
		}
		if (isIn) {
			ans = MAX(ans, sum);
		}
	}

}

/*
void init_vt() {
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			vt[i][j] = 0;
		}
	}
}
*/

int main(){
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			scanf("%d", &map[i][j]);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			//[init_vt()로 시간 초과]
			//init_vt();
			vt[i][j] = 1;
			dfs(i, j, 1, map[i][j]);
			vt[i][j] = 0;
			handle_exception(i, j);
		}
	}

	printf("%d\n", ans);

	return 0;
}
