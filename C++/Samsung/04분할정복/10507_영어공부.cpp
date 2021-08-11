#include <cstdio>
#define MAX_DAY 1000001

#define MAX(A,B) ((A > B) ? (A) : (B));

int N, P;
bool day[MAX_DAY]; // true : studied

// 투포인터
int run() {
	int maxLen = P + 1;
	int len = 0, s = 0, e = 0;

	while (e < MAX_DAY) {
		if (day[e]) { // 공부를 해서 해킹할 필요 없는 날
			len++;
			maxLen = MAX(maxLen, len);
			e++;
		}
		else {	// 공부를 하지 않아 해킹해야 하는 날
			if (P) {	// 해킹 횟수가 남아있을 경우
				P--;
				len++;
				e++;
			}
			// 해킹 횟수가 남아있지 않는 경우...
			// start를 이동시켜 해킹 횟수를 확보헤야 함
			else {
				maxLen = MAX(maxLen, len); // 해킹 횟수 모두 쓴 경우에 확인
				if (!day[s]) // start가 해킹한 날이면 해킹가능 횟수 증가
					P++;
				s++;
				len--;
			}
		}
	}
	return maxLen;
}

int main() {
	int T;

	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case) {

		// 초기화
		for (int i = 0; i < MAX_DAY; i++)
			day[i] = false;

		// 입력
		scanf("%d%d", &N, &P);
		int studyDay;
		for (int i = 0; i < N; i++) {
			scanf("%d", &studyDay);
			day[studyDay] = true;
		}

		int ans = run();
		printf("#%d %d\n", test_case, ans);
	}
	return 0;
}
