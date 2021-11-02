#include <stdio.h>

int main(void)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);

	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case)
	{
		unsigned int N, M;
		scanf("%d%d", &N, &M);
		//2^5-1 = 0b1111 & M
		unsigned int mask = 1 << N;
		// printf의 호출을 줄일수록 실행시간이 단축된다.
		if ((M & (mask-1)) == (mask-1))
			printf("#%d ON\n", test_case);
		else
			printf("#%d OFF\n", test_case);
	}
	return 0;
}
