#include <cstdio>
#include <queue>
using namespace std;

#define MAXN 101
#define MAXL 100

typedef struct s_dir {
	int t;
	char d;
}				t_dir;

typedef struct s_pos {
	int r, c;
}				t_pos;

int N, K, L;
int board[MAXN][MAXN]; //0:비어있는상태, 1:사과, 2:뱀
t_dir dir_list[MAXL];

const int dr[4] = {0, -1, 0, 1}; // 동 북 서 남
const int dc[4] = {1, 0, -1, 0};

t_pos rotate_L(t_pos d) {
	t_pos next;

	for (int i = 0; i < 4; ++i) {
		//[r, c 모두 확인했어야 함]
		if (dr[i] == d.r && dc[i] == d.c) {
			next.r = dr[(i+1) % 4];
			next.c = dc[(i+1) % 4];
			break;
		}
	}
	return next;
}

t_pos rotate_D(t_pos d) {
	t_pos next;

	for (int i = 0; i < 4; ++i) {
		if (dr[i] == d.r && dc[i] == d.c) {
			int next_idx = i - 1;
			if (next_idx == -1)
				next_idx = 3;
			next.r = dr[next_idx];
			next.c = dc[next_idx];
			//printf("i=%d, next_idx=%d, [%d][%d]\n", i, next_idx, next.r, next.c);
			break;
		}
	}
	return next;
}

int run() {

	// head, tail의 좌표
	t_pos head = {1, 1}, tail = {1, 1}, d = {0, 1};
	int i = 0, t = 0, len = 1;
	queue<t_pos> q;
	while (1) {
		t++;

		// move
		head.r += d.r;
		head.c += d.c;
		q.push(head);

		// 종료 조건
			// 1. 벽에 부딪히는 경우
		if (head.r < 1 || head.r > N || head.c < 1 || head.c > N)
			break;
			// 2. 뱀이 자기 자신의 몸과 부딪히는 경우
		if (board[head.r][head.c] == 2)
			break;
		// 사과가 있는 경우
		else if (board[head.r][head.c] == 1) {
			board[head.r][head.c] = 2;
			len++;
		}
		else {
			board[head.r][head.c] = 2;
			board[tail.r][tail.c] = 0;
			//[tail의 위치를 어떻게 이동할 것인지...head의 방향과 같이 움직이면 안된다.]
			//[->뱀의 position 을 큐로 관리]
			tail = q.front(); q.pop();
		}
		printf("t=%d head[%d][%d] tail[%d][%d] len=%d\t", t, head.r, head.c, tail.r, tail.c, len);
		printf("board[%d][%d]=%d\n", head.r, head.c, board[head.r][head.c]);
		// 방향 전환
		if (i < L && t == dir_list[i].t) {
			if (dir_list[i].d == 'L') {
				d = rotate_L(d);
			}
			else if (dir_list[i].d == 'D') {
				d = rotate_D(d);
			}
			printf("t=%d dir[%d][%d]\n", t, d.r, d.c);
			i++;
		}
	}

	return t;
}

int main() {
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	scanf("%d\n%d", &N, &K);

	int r, c;
	for (int i = 0; i < K; ++i) {
		scanf("%d%d", &r,&c);
		board[r][c] = 1;
	}
	scanf("%d", &L);
	for (int i = 0; i < L; ++i) {
		scanf("%d %c", &dir_list[i].t, &dir_list[i].d);
	}

	int ans = run();
	printf("%d\n", ans);

	return 0;
}
