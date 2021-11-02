#include <cstdio>

int digit[10];
int digit_cnt;

void count_digit(int n) {

	while(n) {
		if (digit[n%10] == 0) {
			digit[n%10] = 1;
			digit_cnt++;
		}
		n /= 10;
	}
}

int main() {
	int T, N;

	scanf("%d", &T);
	for(int i = 1; i <= T; i++) {
		scanf("%d", &N);
		// 초기화
		for (int j = 0; j < 10; j++)
			digit[j] = 0;
		digit_cnt = 0;

		int k = 0;
		while (digit_cnt != 10) {
			count_digit(N * (++k));
		}
		printf("#%d %d\n", i, N * k);
	}
	return 0;
}
