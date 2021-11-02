#include <cstdio>

int main()
{
	int n, k;
	int prime[1001] = {-1, 1,};

	scanf("%d%d", &n, &k);

	int cnt = 0;
	for (int i = 2; i <= n; i++) {
		for (int j = i; j <= n; j += i) {
			if (prime[j] == -1) continue;
			// 소수 체크
			if (j == i)
				prime[j] = 1;
			// 소수의 배수 체크
			else
				prime[j] = -1;
			cnt++;
			//printf("prime[%d]=%d, cnt=%d\n", j, prime[j], cnt);
			if (cnt == k) {
				printf("%d", j);
				break;
			}
		}
	}

}
