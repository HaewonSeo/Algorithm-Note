#include <cstdio>

bool gear[5][8]; // 12시부터 시계방향으로, 2:3시방향, 6:9시방향
int K;
int cycle[100][2]; // 0:톱니바퀴번호, 1:방향
int ans;

// 1. 기준 톱니바퀴를 회전하기전 인접한 톱니바퀴와 맞닿은 부분 체크
	// 맞닿은 부분의 극이 같다면 회전 x
	// 맞닿은 부분의 극이 다르다면 인접 톱니바퀴는 반대 방향으로 회전
// 2. 기준 톱니바퀴 회전
// 3. 인접 톱니바퀴 회전

void rotate_R(int n) {
	bool copy[8];

	for (int i = 0; i < 8; i++)
		copy[i] = gear[n][i];

	gear[n][0] = copy[7];
	for (int i = 1; i < 8; i++)
		gear[n][i] = copy[i-1];
}

void rotate_L(int n) {
	bool copy[8];

	for (int i = 0; i < 8; i++)
		copy[i] = gear[n][i];

	for (int i = 6; i >= 0; i--)
		gear[n][i] = copy[i+1];
	gear[n][7] = copy[0];
}

void run() {

	for (int k = 0; k < K; ++k) {

		int cur = cycle[k][0];
		int dir = cycle[k][1];
		bool dif[3];
		int is_rotate[5]; // 1:시계, -1:반시계, 0:정지

		for (int i = 1; i <= 3; i++)
			dif[i-1] = (gear[i][2] == gear[i+1][6]);

		is_rotate[cur] = dir;
		// ->
		for (int i = cur; i < 4; i++) {
			if (dif[i-1])
				is_rotate[i+1] = 0;
			else
				is_rotate[i+1] = is_rotate[i] * -1;
		}
		// <-
		for (int i = cur; i > 1; i--) {
			if (dif[i-2])
				is_rotate[i-1] = 0;
			else
				is_rotate[i-1] = is_rotate[i] * -1;
		}

		// rotate
		for (int i = 1; i <= 4; i++) {
			if (is_rotate[i] == 1)
				rotate_R(i);
			else if (is_rotate[i] == -1)
				rotate_L(i);
		}

#ifdef DEBUG
		printf("[k %d]\n", k+1);
		for (int i = 1; i <= 4; i++) {
			for (int j = 0; j < 8; ++j)
				printf("%d ", gear[i][j]);
			printf("\n");
		}
#endif
	}

}

void get_score() {
	for (int i = 1; i <= 4; i++) {
		// S극
		if (gear[i][0] == 1) {
			ans += (1 << (i-1));
			/*
			if (i == 1)
				ans += 1;
			else if (i == 2)
				ans += 2;
			else if (i == 3)
				ans += 4;
			else
				ans += 8;
			*/
		}
	}
}

int main () {
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);

	//[입력숫자가 붙어 있기 때문에 하나의 정수로 읽어옴 -> string to int]
	char str[5][9]; // char *str[5] 로 선언 시 에러 발생!

	for (int i = 1; i <= 4; ++i)
		scanf("%s", str[i]);

	for (int i = 1; i <= 4; ++i) {
		for (int j = 0; j < 8; ++j)
			gear[i][j] = str[i][j] - '0';
	}

#ifdef DEBUG
	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j < 8; ++j)
			printf("%d ", gear[i][j]);
		printf("\n");
	}
#endif

	scanf("%d", &K);
	for (int i = 0; i < K; ++i)
		scanf("%d%d", &cycle[i][0], &cycle[i][1]);

	run();
	get_score();

	printf("%d\n", ans);
}

