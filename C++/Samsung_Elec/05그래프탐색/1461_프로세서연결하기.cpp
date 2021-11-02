#include <cstdio>
#define DEBUG

struct pos {
	int y, x;
};

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

int N;
int map[12][12];
pos core[12];
int coreCnt;
int minLen;
int maxConn;

void dfs(int n, int len, int conn) {

	// 1. 전원에 연결된 코어 개수가 같거나 많은가?
	// 2. 1인 상태에서의 최소 길이인가?
	if (n == coreCnt) {
		if (conn == maxConn) {
			if (len < minLen)
				minLen = len;
		}
		else if (conn > maxConn) {
			maxConn = conn;
			minLen = len;
		}
#ifdef DEBUG
		printf("n=%d len=%d conn=%d minLen=%d maxConn=%d\n", n, len, conn, minLen, maxConn);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				printf("%d ", map[i][j]);
			printf("\n");
		}
#endif
		return ;
	}

	pos cur = core[n];
	for (int i = 0; i < 4; i++) {
		// core 의 위치부터 검사
		pos next = cur;
		int addLen = 0;
		bool isConn = false;
		while (1) {
			// 한칸 이동
			next = {next.y + dy[i], next.x + dx[i]};
			// 범위 체크
			if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) break;
			// 코어(1)/전선(2) 체크
			if (map[next.y][next.x] >= 1) break;
			// [지나가는 위치->x!! ]및 길이를 임시로 저장
			addLen++;
			// Connect!
			if (next.y == 0 || next.x == 0 || next.y == N-1 || next.x == N-1) {
				isConn = true;
				break;
			}
		}

		if (isConn) {
			// 지나온길을 전선으로 연결한 후 dfs호출
			// [지나온길을 전역배열로 저장하여 dfs 호출마다 값이 변경되는 오류 해결함]
			pos line = cur;
			for (int k = 0; k < addLen; k++) {
				line = {line.y + dy[i], line.x + dx[i]};
				map[line.y][line.x] = 2;
			}

			dfs(n+1, len+addLen, conn+1);

			// 전선을 다시 지운다.
			line = cur;
			for (int k = 0; k < addLen; k++) {
				line = {line.y + dy[i], line.x + dx[i]};
				map[line.y][line.x] = 0;
			}
		}
	}
	// 아무쪽도 연결 안하는 경우도 체크 ... dfs호출
	dfs(n+1, len, conn);
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	setbuf(stdout, NULL);
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d", &T);
	for(test_case = 1; test_case <= T; ++test_case)
	{
		coreCnt = 0;
		minLen = 100;
		maxConn = 0;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				// 가장자리가 아닌 코어는 따로 저장
				if (map[i][j] && !(i == 0 || j == 0 || i == N-1 || j == N-1))
					core[coreCnt++] = {i, j};
			}
		}
		dfs(0, 0, 0);
		printf("#%d %d\n", test_case, minLen);
	}
	return 0;
}
