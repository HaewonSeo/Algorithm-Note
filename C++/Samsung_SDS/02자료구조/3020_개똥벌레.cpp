#include <cstdio>

// range update point query 라는 개념이 나옴...

int n, h, answer, count;
int sum[500010];

int main() {
	scanf("%d %d", &n, &h);
	for (int i = 0 ; i < n ; i++) {
		int bar;
		scanf("%d", &bar);
		if (i & 1) {
			// 종유석
			sum[h - bar + 1]++;
		}
		else {
			// 석순
			sum[1]++;
			sum[bar + 1]--;
		}
	}
	answer = -1;
	for (int i = 1 ; i <= h ; i++) {
		sum[i] += sum[i - 1];
		if (answer == -1 || sum[i] < answer) {
			answer = sum[i];
			count = 1;
		}
		else if (sum[i] == answer) {
			count++;
		}
	}

	printf("%d %d", answer, count);
}



/*
#include <cstdio>

int n, h, answer, count;
int seok[200000], jong[200000];

// x구간으로 날아갈때 k번째 석순과 만나는지
bool check_seok(int k, int x) {
	if (x <= seok[k]) return true;
	return false;
}

// x구간으로 날아갈때 k번째 종유석과 만나는지
bool check_jong(int k, int x) {
	if (h - jong[k] + 1 <= x) return true;
	return false;
}

int fly(int x) {
	int res = 0;
	for (int i = 0 ; i < n ; i += 2) {
		// 석순과 만나는지
		if (check_seok(i, x)) res++;
		// 종유석과 만나는지
		if (check_jong(i, x)) res++;
	}
	return res;
}

int main() {
	scanf("%d %d", &n, &h);
	for (int i = 0 ; i < n ; i += 2) {
		scanf("%d", &seok[i]);
		scanf("%d", &jong[i]);
	}
	answer = -1;
	for (int i = 1 ; i <= h ; i++) {
		int crash = fly(i);
		if (answer == -1 || crash < answer) {
			answer = crash;
			count = 1;
		}
		else if (crash == answer) {
			count++;
		}
	}
	printf("%d %d", answer, count);
}
*/
