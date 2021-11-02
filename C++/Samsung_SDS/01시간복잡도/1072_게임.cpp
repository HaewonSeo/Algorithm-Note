#include <cstdio>
#include <time.h>
time_t startT, endT;
double result;

// 경기 횟수가 정수 범위를 벗어날 수 도 있다. -> LL
typedef long long LL;

LL X, Y, Z;

int main()
{
	scanf("%lld%lld", &X, &Y);

	//Z = ((double)Y / X) * 100;
	// --> double 형변환에 문제가 있는 듯?
	Z = Y * 100 / X;
	// --> 여기서 Z 를 int 형으로 하는 경우 범위를 초과할 수 있었다!
	//printf("%d\n", Z);

	// 예외 상황
		// 승률 100%인 경우
		// 승률 99% 인 경우, 100%가 될 수 없을 것 같다.
	if (Z == 100 || Z == 99){
		printf("-1");
		return 0;
	}

	// 시간복잡도 n
	/*
	startT = time(NULL);
	for (int i = 1; ; i++)
	{
		LL nextZ = ((double)(Y + i) / (X + i)) * 100;
		if (nextZ != Z)
		{
			printf("%d\n", i);
			break;
		}
	}
	endT = time(NULL);
	result = (double)(endT - startT);
	printf("[time] : %lf\n", result);
	*/

	// startT = time(NULL);
	// 이분 탐색 : 시간복잡도 log2n
	LL start = 1, end = 1000000000, ans = 1000000000, mid;
	while (start <= end) {
		mid = (start + end) / 2;
		//long long nextZ = ((double)(Y + mid) / (X + mid)) * 100;
		LL nextZ = (Y + mid) * 100 / (X + mid);
		if (Z < nextZ) {
			if (mid < ans)
				ans = mid;
			end = mid - 1;
		}
		else
			start = mid + 1;
	}
	printf("%lld", ans);

	// endT = time(NULL);
	// result = (double)(endT - startT);
	// printf("[time] : %lf\n", result);
	return 0;
}
