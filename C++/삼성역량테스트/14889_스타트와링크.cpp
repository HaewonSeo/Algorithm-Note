#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define MAX 2147483647

int N;
int a[21][21];
vector<int> start, link;
int ans = MAX;

int calcDiff() {

    int sum_start = 0, sum_link = 0;

    for (int i = 0; i < N / 2; ++i) {
        for (int j = i + 1; j < N / 2; ++j) {
            
            sum_start += a[start[i]][start[j]] + a[start[j]][start[i]];
            sum_link += a[link[i]][link[j]] + a[link[j]][link[i]];
        }
    }

    return abs(sum_start - sum_link);
}

void dfs(int idx) {

    if (idx > N) {
        if (start.size() == N / 2 && link.size() == N / 2)
            ans = min(ans, calcDiff());
        return ;
    }

    // 스타트팀
    start.push_back(idx);
    dfs(idx + 1);
    start.pop_back();

    // 링크팀
    link.push_back(idx);
    dfs(idx + 1);
    link.pop_back();
}


int main() {

    freopen("input.txt", "r", stdin);

    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            scanf("%d", &a[i][j]);

    dfs(1);

    printf("%d\n", ans);
}
