#include <cstdio>
#include <algorithm>
using namespace std;

int N, M, A[8], ans[8];
bool used[8];

void dfs(int k) {
	if (k == M) {
		for (int i = 0 ; i < M; i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
		return;
	}

	int prev = -1;
	int prevAns;
	for (int i = 0 ; i < N ; i++) {
		if (used[i]) continue;
		//printf("[k=%d] i=%d    ans[%d]=%d   A[%d]=%d\n", k, i, k, ans[k], i, A[i]);
		//printf("[k=%d] i=%d    prev=%d   A[%d]=%d\n", k, i, prev, i, A[i]);
		if (k == 0)
			prevAns = -1;
		else
			prevAns = ans[k-1];
		if (prev != A[i] && prevAns <= A[i]) {
			used[i] = true;
			prev = A[i];
			ans[k] = A[i];
			//printf("ans[%d]=%d\n", k, ans[k]);
			dfs(k + 1);
			used[i] = false;
		}
	}
}
// prev를 선언하지 않고, if(ans[k] != A[i]) 를 사용하면 안된다.
// 반례
// 3 3
// 3 4 3
// 위의 이유는 목적이 중복 수열을 피하기 위해
// 나머지는 같은 상태에서! 이전 단계의 값만을 비교해야 하는데..
// 이전 answer의 해당 위치를 비교해버리기 때문이다...


int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0 ; i < N ; i++)
		scanf("%d", &A[i]);
	sort(A, A + N);
	dfs(0);
}



