// 완전탐색으로 풀이했으나,
// DP로 접근 가능!

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
#define f first
#define s second
int N, ans;
vector<pii> a;

void dfs(int n, int sum) {

    if (sum > ans)
        ans = sum;

    for (int i = n; i < N; ++i) {
        if (i + a[i].f > N) continue;

        dfs(i + a[i].f, sum + a[i].s);
    }
}

int main() {

    //freopen("input.txt", "r", stdin);

    scanf("%d", &N);
    
    for (int i = 0; i < N; ++i) {
        pii tmp;
        scanf("%d%d", &tmp.f, &tmp.s);
        a.push_back(tmp);
    }

    dfs(0, 0);

    printf("%d\n", ans);
       
}