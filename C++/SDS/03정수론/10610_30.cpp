#include <cstdio>

int main()
{
	char N[100001];
	scanf("%s", N);

	// 0~9 숫자의 갯수 계산
	int count[10] = {0,}, sum = 0;
	for (int i = 0; N[i]; i++)
	{
		int pos = N[i] - '0';
		count[pos]++;
		sum += pos;
	}

	// 30의 배수인지 검사
		// 조건 1 : 모든 자리수의 합이 3의 배수
		// 조건 2 : 0의 개수가 최소 1개 이상
	if (sum % 3 != 0 || count[0] == 0) {
		printf("-1");
		return 0;
	}

	// 최대값 계산
	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < count[i]; j++)
			printf("%d", i);
	}
}
