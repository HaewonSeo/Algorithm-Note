#include <cstdio>
using namespace std;

int N, A[1000000], B, C; 
long long ans;

int main() {

    //freopen("input.txt", "r", stdin);
    
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    scanf("%d%d", &B, &C);

    // 총감독이 감시할 수 있는 인원 -
    for (int i = 0; i < N; ++i) {
        // major
        ans++;
        A[i] -= B;
    }

    for (int i = 0; i < N; ++i) {
        if (A[i] <= 0) continue;

        // 감시하지 못한 인원으로 부감독 인원 계산
        ans += (A[i] / C);
        if ((A[i] % C) != 0)
            ans++;
    }

    printf("%lld\n", ans);
}
