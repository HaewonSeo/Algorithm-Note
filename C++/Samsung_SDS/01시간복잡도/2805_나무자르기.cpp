#include <cstdio>

typedef long long LL;

int n, m;
LL tree[1000000];
LL ans;

bool cutok(LL h) {
	LL sum = 0;
	for (int i = 0 ; i < n ; i++) {
		if (tree[i] > h) {
			sum += tree[i] - h;
		}
		if (sum >= m) return true;
	}
	return false;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0 ; i < n ; i++) {
		scanf("%lld", &tree[i]);
	}
	// 높이를 변경해가면서 나무를 잘라보고
	// 조건을 만족하는 가장 큰 높이를 찾아본다.....
	// 시간 초과가 발생할 것 같음
	/*
	for (LL h = 0 ; h <= 1000000000 ; h++) {
		if (cutok(h)) {
			ans = h;
		}
		else {
			break;
		}
	}
	*/
	LL start = 0, end = 1000000000, mid;
	while (start <= end) {
		mid = (start + end) / 2;
		if (cutok(mid)) {
			if (ans < mid) ans = mid;
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	printf("%lld", ans);
}
