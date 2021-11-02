#include <cstdio>
#include <queue>
#include <cmath>	//pow
#include <cstring>	// memcpy
using namespace std;

typedef struct s_pos {
	int r, c;	// 위치
	int love;	// 주변에 좋아하는 학생 수 
	int empty;	// 주변에 비어있는 자리 수 
} t_pos;

const int dR[4] = {-1, 1, 0, 0};
const int dC[4] = {0, 0, -1, 1}; // 상 하 좌 우

int N, a[401][5], tb[21][21];

void setTable() {

	for (int n = 1; n <= N * N; ++n) {

		// 후보 자리를 큐에 저장
		queue<t_pos> q;
		for (int r = 1; r <= N; ++r) {
			for (int c = 1; c <= N; ++c) {

				// 비어있지 않은 칸은 여기서 걸러냄
				if (tb[r][c]) continue;
				
				t_pos cur = {r, c, 0, 0};
				// 주변(상하좌우) 확인
				for (int k = 0; k < 4; ++k) {
					int nR = r + dR[k];
					int nC = c + dC[k];
					if (nR < 1 || nR > N || nC < 1 || nC > N) continue;
					if (!tb[nR][nC])
						cur.empty++;
					else {
						// 좋아하는 사람에 해당하는지 확인
						for (int i = 1; i <= 4; ++i) {
							if (tb[nR][nC] == a[n][i])
								cur.love++;
						}
					}
				}

				// 큐에 저장
				q.push(cur);
			}
		}

		// queue에서 자리 선정
		// [구조체의 깊은 복사를 놓침]
		// [bestPos의 초기값으로 q의 첫번재 값으로 하지 않고 0으로 초기화해서 오류 발생함]
		t_pos bestPos = q.front(); q.pop();
		while (!q.empty()) {
			t_pos pos = q.front(); q.pop();
			// printf("qSize=%lu ", q.size());
			// printf("[%d][%d] love=%d empty=%d\n", pos.r, pos.c, pos.love, pos.empty);
			// 비어있는 칸(이미 처리) -> 주변에 좋아하는사람수 -> 주변의 비어있는 칸 수
			if (pos.love > bestPos.love)
				memcpy(&bestPos, &pos, sizeof(t_pos));
			else if (pos.love == bestPos.love) {
				if (pos.empty > bestPos.empty)
					memcpy(&bestPos, &pos, sizeof(t_pos));
			}
		}
		// 자리 지정
		// printf("n=%d\t [%d][%d]=%d love=%d empty=%d\n", n, bestPos.r, bestPos.c, a[n][0], bestPos.love, bestPos.empty);
		tb[bestPos.r][bestPos.c] = a[n][0];
	}

	// for (int r = 1; r <= N; ++r) {
	// 	for (int c = 1; c <= N; ++c)
	// 		printf("%d ", tb[r][c]);
	// 	printf("\n");
	// }
}


int getScore() {
	
	int score = 0;


	for (int r = 1; r <= N; ++r) {
		for (int c = 1; c <= N; ++c) {
			
			// n 찾기
			int n = 1;
			for (; n <= N * N; ++n)
				if (tb[r][c] == a[n][0])
					break;

			int cnt = 0;
			// 주변 확인
			for (int k = 0; k < 4; ++k) {
				int nR = r + dR[k];
				int nC = c + dC[k];
				if (nR < 1 || nR > N || nC < 1 || nC > N) continue;
				// 좋아하는 사람에 해당하는지 확인
				for (int i = 1; i <= 4; ++i) {
					if (tb[nR][nC] == a[n][i])
						cnt++;
				}
			}
			// printf("cnt=%d\n", cnt);
			if (cnt)
				score += (int)pow(10, cnt - 1);
		}
	}
	return score;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    scanf("%d", &N);
	// [N*N을 N으로 하여 오류 발생했음]
    for (int i = 1; i <= N * N; ++i) {
        for (int j = 0; j <= 4; ++j)
            scanf("%d", &a[i][j]);
    }

	setTable();
    int ans = getScore();

    printf("%d\n", ans);
    
    return 0;
}