//[문제를 한번에 이해하지 못해 풀이하는데 오래 걸림]
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

// typedef pair<int, int> pii;
typedef struct s_pos t_pos;

struct s_pos {
	int r, c, dist;

	s_pos (int _r, int _c, int _dist) : r(_r), c(_c), dist(_dist) {}

	bool operator < (const s_pos p) const {
		if (this->dist == p.dist) {
			if (this->r == p.r)
				return (this->c > p.c);
			else
				return (this->r > p.r);
		}
		else
			return (this->dist > p.dist);
	}
};

const int dr[4] = {-1, 1, 0, 0}; //상하좌우
const int dc[4] = {0, 0, -1, 1};

int N;
int map[20][20];
bool vt[20][20];
int ans;
queue<t_pos> shark_q;
priority_queue<t_pos> fish_pq;

void run() {

	int eat_cnt = 0, size = 2;

	while (1) {

		// 초기화
		while (!fish_pq.empty())
			fish_pq.pop();
		memset(vt, false, sizeof(vt));

		// dfs로 상어를 이동시키면서 먹을 수 있는 물고기의 위치와 거리를 저장
		while (!shark_q.empty()) {

			t_pos cur = shark_q.front(); shark_q.pop();

			for (int i = 0; i < 4; ++i) {
				t_pos nt = cur;
				nt.r += dr[i];
				nt.c += dc[i];
				nt.dist++;
				if (nt.r < 0 || nt.r >= N || nt.c < 0 || nt.c >= N)
					continue;
				if (vt[nt.r][nt.c] || map[nt.r][nt.c] > size)
					continue;

				// 1. 상어 push
				vt[nt.r][nt.c] = true;
				shark_q.push(nt);

				// 2. 크기가 작거나 빈칸이 아니면 먹을 수 있는 물고기!
				if (map[nt.r][nt.c] < size && map[nt.r][nt.c] > 0)
					fish_pq.push(nt);
			}
		}

		if (fish_pq.empty())
			break;

		t_pos fish = fish_pq.top(); fish_pq.pop();
		ans += fish.dist;
		fish.dist = 0;
		map[fish.r][fish.c] = 0;
		shark_q.push(fish); // 상어는 먹을 물고기의 위치로 이동

		eat_cnt++;
		if (eat_cnt == size) {
			size++;
			eat_cnt = 0;
		}
	}
	return ;
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				map[i][j] = 0;
				shark_q.push(t_pos(i, j, 0));
			}
		}
	}

	run();

	printf("%d\n", ans);
	return 0;

}
