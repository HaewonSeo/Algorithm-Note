#include <cstdio>

const int unit[8] = {50000, 10000, 5000, 1000, 500, 100, 50, 10};
int main() {

	setbuf(stdout, NULL);
	int T;
	scanf("%d", &T);

	int cnt[8] = {0,};
	for (int tc = 1; tc <= T; ++tc) {
		int money;
		scanf("%d", &money);

		for (int i = 0; i < 8; ++i)
			cnt[i] = 0;

		for (int k = 0; k < 8; k++) {
			cnt[k] = money / unit[k];
			money %= unit[k];
		}

		printf("#%d\n", tc);
		for (int i = 0; i < 8; ++i)
			printf("%d ", cnt[i]);
		printf("\n");
	}
}
