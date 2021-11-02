#include <cstdio>
#include <queue>
using namespace std;

#define MAX 201
int N, K, belt[MAX], zeroCnt;
bool vt[MAX];

int moveBelt() {
    int t = 0;					// 수행 단계
    int up = 1, down = N;
    queue<int> robot;			// 벨트 위에 있는 로봇의 위치를 저장

    // 4. 내구도 0인 칸의 개수 체크 -> 반복문 조건.
    while (zeroCnt < K) {
        t++;

        // 1.컨베이너벨트 1칸 회전
		up--;
        if (!up) up = 2 * N;
        down--;
        if (!down) down = 2 * N;


        // 2.가장 먼저 올라간 로봇부터 1칸 이동할 수 있다면 이동!
        int qSize = robot.size();
        while (qSize--) {
            int cur = robot.front();
            robot.pop();
			vt[cur] = false;
			
			// down 이라면 이동하는 것이 아니라, 로봇을 내려야 함
			if (cur == down)
				continue;

            // 이동하려는 위치(nt)에 로봇이 있는지(vt[]), 내구도 가능한지(belt[])를 확인
			int nt = cur + 1;
            if (nt > 2 * N) nt = 1;	// 마지막 위치인 경우 그 다음 위치를 1로 설정

			if (!vt[nt] && belt[nt]) {
                robot.push(nt);  // 다음 위치로 이동한 로봇을 enqueue
				vt[nt] = true;
                belt[nt]--; // 내구도 감소
				if (belt[nt] == 0)	// 내구도 0 개수 카운트!
					zeroCnt++;
            }

			// 이동할 수 없으면 가만히 있는다. -> 다시 queue에 enqueue!
			else {
				robot.push(cur);
				vt[cur] = true;
			}

        }

        // 3.올리는 위치에 로봇을 올릴 수 있다면 올린다!
        if (!vt[up] && belt[up]) {
            robot.push(up);
            vt[up] = true;
            belt[up]--; // 내구도 감소
			if (belt[up] == 0)
				zeroCnt++;
        }

		// 회전하기 전에, down 위치에 로봇이 있다면 로봇을 내려야 한다.
		if (robot.size() && robot.front() == down) {
			robot.pop();
			vt[down] = false;
		}
    }
	return t;
}

int main() {

    freopen("input.txt", "r", stdin);

    scanf("%d%d", &N, &K);
    // 1 ~ 2N
    for (int i = 1; i <= 2 * N; ++i) {
        scanf("%d", &belt[i]);
        if (belt[i] == 0)
			zeroCnt++;
    }

	int ans = moveBelt();

    printf("%d\n", ans);

	return 0;
}