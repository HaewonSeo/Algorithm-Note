#include <cstdio>

#define MAX 200

int corr[MAX];	//corridor

int main() {
	setbuf(stdout, NULL);

	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; ++tc) {

		for (int i = 0; i < MAX; ++i)
			corr[i] = 0;

		int N;
		scanf("%d", &N);

		for (int n = 0; n < N; ++n) {
			int s, e;
			scanf("%d%d", &s, &e);

			if (s > e) {
				int tmp = s;
				s = e;
				e = tmp;
			}

			int corrS, corrE;
			// [연산자 우선순위가 ==가 & 보다 높다--> () 필수]
			if ((s & 1) == 0)
				corrS = (s / 2) - 1;
			else
				corrS = s / 2;
			if ((e & 1) == 0)
				corrE = (e / 2) - 1;
			else
				corrE = e / 2;
			printf("\ncorrS=%d, corrE=%d\n", corrS, corrE);
			for (int i = corrS; i <= corrE; i++)
				corr[i]++;
		}

		int ans = 0;
		for (int i = 0; i < MAX; ++i) {
			if (corr[i] > ans)
				ans = corr[i];
		}
		printf("#%d %d\n", tc, ans);

	}
}

/* 오답
#include <cstdio>

int dupS, dupE;
int ans;

void findDup(int s, int e) {

	// 겹치는 부분이 없는 경우
	if (dupE < s || e < dupS)
		return ;
	// 겹치는 경우
		// dupS~E 이 s~e 보다 앞서거나 같은 경우
	if (dupS <= s) {
		dupS = s;
		if (e < dupE)
			dupE = e;
	}
		// s~e이 dupS~E 보다 앞선 경우
	else if (s < dupS) {
		//dupS = dupS;
		if (e < dupE)
			dupE = e;
	}
	ans++;
	return ;
}


int main() {
	setbuf(stdout, NULL);

	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; ++tc) {

		ans = 1;

		int N;
		scanf("%d", &N);

		for (int n = 0; n < N; ++n) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (n == 0) {
				dupS = a;
				dupE = b;
				continue;
			}
			findDup(a, b);
		}

		printf("#%d %d\n", tc, ans);

	}
}
*/
