#include <cstdio>

#define MAX_SE 100000000
#define MAX_N 100001
#define MAX(A,B) (((A) > (B)) ? (A) : (B));
int arrS[MAX_N], arrE[MAX_N];
int sumStoE[MAX_N]; //누적합
int L, N, ans;
int test_case;

// Lower Bound : 찾고자하는 값 이상이 처음으로 나타나는 위치
// Upper Bound : 찾고자하는 값보다 큰 값이 처음으로 나타나는 위치
int binarySearch(int s, int e, int target) {
	int ans = e + 1;

	while (s <= e) {
		int m = (s + e) / 2;

		// Upper bound
		// if (arrE[m] > target)

		// Lower Bound
		if (arrE[m] >= target) {
			ans = m;
			e = m - 1;
		}
		else s = m + 1;
		//if (arrE[m] == target) return m;
		//else if (arrE[m] < target) s = m + 1;
		//else e = m - 1;
	}
	return ans;
}

void run() {

	// 모든 arrS[] 에 대해 arrS[] + L 이 포함되는 구간(s~e)을 찾아.
	// 이 구간이 광고시간이 최대로 겹칠 수 있는 후보 구간임
	// 여기서 겹치는 길이를 찾아.
	// arrS[]를 바꾸어가면서 반복, 구간의 끝은 이진탐색으로 탐색.
	for (int i = 1; i <= N; i++) {
		int curS = arrS[i];
		int end = curS + L;

		// 초과 범위 고려
		if (end >= MAX_SE)
			end = MAX_SE - 1;
		int lastRange = binarySearch(i, N, end);

		int len = 0;
		// 마지막으로 겹치는 구간 이전까지의 합
		len = sumStoE[lastRange-1] - sumStoE[i-1];
		// 마지막으로 겹치는 구간 합
		// [구간 내에 존재하는 경우만, 마지막 구간 길이를 합함]
		// [lastRange <= N 조건 넣은 경우
		// lastRange가 N+1인 경우, 마지막 피크시간대까지만 검사해야 하므로]
		if (arrS[lastRange] < end && lastRange <= N)
			len += end - arrS[lastRange];

		ans = MAX(ans, len);
		if (ans == L)
			break;
	}
/*
	// 시간 초과
	int s = arrS[0], e = s + 1;
	int len = 0;
	while (e <= arrE[N-1]) {
		if (peak[e]) {
			len++;
			ans = MAX(ans, len);
			if (ans == L)
				break;
		}
		e++;
		if (e - s > L) {
			if (peak[s+1])
				len--;
			s++;
		}
	}
*/
}

int main() {
	int T;

	setbuf(stdout, NULL);
	//freopen("2_input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case) {

		scanf("%d", &L);
		scanf("%d", &N);
		for (int n = 1; n <= N; n++) {
			scanf("%d%d", &arrS[n], &arrE[n]);
			sumStoE[n] = sumStoE[n-1] + (arrE[n] - arrS[n]);
		}

		ans = 0;
		run();
		printf("#%d %d\n", test_case, ans);
	}
}
