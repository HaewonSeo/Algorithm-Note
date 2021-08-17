#include <cstdio>

#define MAXPOS 6

int N, C;
int digit[MAXPOS];
int ans, startPos;

int swap(int *a, int *b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int digitToNum(){
	int num = 0;
	for (int i = 0; i < MAXPOS; i++)
		num = (num * 10) + digit[i];
	return num;
}

void dfs(int pos, int cnt) {
	if (cnt == C) {
		int num = digitToNum();
		//printf("num=%d\n", num);
		if (num > ans)
			ans = num;
		return ;
	}

	for (int i = pos; i < MAXPOS - 1; i++) {
		for (int next = i+1; next < MAXPOS; next++) {
			//[1.교환 횟수를 채워야 하기 때문에 대소 상관없이 비교해야함]
			//[2.대소비교하고 교환한뒤, 남은 교환횟수를 상황에 맞게 소모하는 방법도 존재]
				// [이 경우, 시간 단축 가능!]
			//if (digit[i] > digit[next]) continue;
			swap(&digit[i], &digit[next]);
			dfs(i, cnt+1);
			swap(&digit[i], &digit[next]);
		}
	}
}

int main() {
	setbuf(stdout, NULL);
	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; ++tc) {
		for (int i = 0; i < MAXPOS; i++)
			digit[i] = 0;
		scanf("%d%d", &N, &C);

		int n = N;
		startPos = 0;
		for (int i = MAXPOS - 1; i >= 0; i--) {
			digit[i] = n % 10;
			n /= 10;
			if (n == 0) {
				startPos = i;
				break;
			}
		}
		// [교환횟수가 numLen-1만큼만 있으면 numLen-1번으로 최대값 구할 수 있다.]
		// -> 완벽히 이해되지 않음..!
		int numLen = MAXPOS - startPos + 1;
		if (C > numLen-1)
			C = numLen-1;

		//printf("startPos=%d\n", startPos);
		// [ans의 초기값은 0! -> N보다 작아질수있기 때문]
		ans = 0;
		dfs(startPos, 0);
		printf("#%d %d\n", tc, ans);
	}
}
