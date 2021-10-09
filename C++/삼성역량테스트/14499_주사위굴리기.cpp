
#include <cstdio>
#include <utility>
using namespace std;

#define DEBUG1

typedef pair<int, int> pii;
const int dr[5] = {0, 0, 0, -1, 1}; //0동서북남
const int dc[5] = {0, 1, -1, 0, 0};

int N, M, x, y, K;
int map[20][20];
int order[1000];
int dice[7]; // 1~6(전개도 참고), 1:윗면, 3:동, 6:바닥면
pii cur;

// 주사위를 굴리기 전의 값을 저장하여 굴린 이후의 주사위 값을 결정
void roll(int d) {
	// 매번 배열을 선언하지 않고 전역변수로만 사용할 수 도 있다.
	int tmp[7];

	for (int i = 0; i < 7; ++i)
		tmp[i] = dice[i];

	// 이 문제에서는 일반화하기보다는 경우를 나누어 풀이하는게 좋다.
	if (d == 1) {
		dice[1] = tmp[4];
		dice[4] = tmp[6];
		dice[6] = tmp[3];
		dice[3] = tmp[1];
	}
	else if (d == 2) {
		dice[1] = tmp[3];
		dice[3] = tmp[6];
		dice[6] = tmp[4];
		dice[4] = tmp[1];
	}
	else if (d == 3) {
		dice[1] = tmp[5];
		dice[5] = tmp[6];
		dice[6] = tmp[2];
		dice[2] = tmp[1];
	}
	else if (d == 4) {
		dice[1] = tmp[2];
		dice[2] = tmp[6];
		dice[6] = tmp[5];
		dice[5] = tmp[1];
	}
}

// dice를 고정
void run2() {

	for (int k = 0; k < K; ++k) {
		int d = order[k];
		cur.first += dr[d];
		cur.second += dc[d];
		if (cur.first < 0 || cur.first >= N || cur.second < 0 || cur.second >= M) {
			cur.first -= dr[d];
			cur.second -= dc[d];
			continue;
		}

		roll(d);

		if (map[cur.first][cur.second] == 0)
			map[cur.first][cur.second] = dice[6];
		else {
			dice[6] = map[cur.first][cur.second];
			map[cur.first][cur.second] = 0;
		}

		printf("%d\n", dice[1]);
	}
}

int main() {
	freopen("input.txt", "r", stdin);

	scanf("%d%d%d%d%d", &N, &M, &x, &y, &K);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			scanf("%d", &map[i][j]);
	//cur = pii{x, y};
	cur.first = x;
	cur.second = y;

	for (int i = 0; i < K; ++i)
		scanf("%d", &order[i]);

	run2();

	return 0;
}


/* run()
const int ns[4] = {2, 1, 5, 6};
const int we[4] = {4, 1, 3, 6};
int bottom_idx = 3;
int bottom_idx2 = 3;
int bottom;
int top;
pii cur;

// 실패 -> 풀이가 점점 복잡해져서 다른 방법으로 재풀이..
void run() {
	for (int i = 0; i < K; ++i) {
		// map position 결정
		int d = order[i];
		cur.first += dr[d];
		cur.second += dc[d];
		if (cur.first < 0 || cur.first >= N || cur.second < 0 || cur.second >= M) {
			cur.first -= dr[d];
			cur.second -= dc[d];
			continue;
		}

		// 주사위 바닥면 결정
		if (d == 3 || d == 4) {
			if (d == 3) {
				bottom_idx += 1;
				while (bottom_idx >= 4)
					bottom_idx %= 4;
			}
			else if (d == 4) {
				bottom_idx -= 1;
				while (bottom_idx < 0)
					bottom_idx += 4;
			}
			bottom = ns[bottom_idx];
			top = ns[(bottom_idx + 2) % 4];
		}
		else if (d == 1 || d == 2) {
			if (d == 2) {
				bottom_idx2 += 1;
				while (bottom_idx2 >= 4)
					bottom_idx2 %= 4;
			}
			else if (d == 1) {
				bottom_idx2 -= 1;
				while (bottom_idx2 < 0)
					bottom_idx2 += 4;
			}
			bottom = we[bottom_idx2];
			top = we[(bottom_idx2 + 2) % 4];
		}

		// 주사위의 바닥면이 map에 복사됨
		if (map[cur.first][cur.second] == 0) {
			map[cur.first][cur.second] = dice[bottom];
		}
		// map이 주사위의 바닥면으로 복사됨, map은 0으로 변경
		else {
			dice[bottom] = map[cur.first][cur.second];
			map[cur.first][cur.second] = 0;
		}

#ifdef DEBUG
		printf("[t=%d]\ntop=%d bottom=%d\n", i, top, bottom);
		printf("1 2 3 4 5 6 --- index\n");
		for (int k = 1; k <= 6; ++k)
			printf("%d ", dice[k]);
		printf(" --- dice\n");
#endif

		printf("%d\n", dice[top]);
	}
}
*/
