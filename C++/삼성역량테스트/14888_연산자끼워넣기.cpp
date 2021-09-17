#include <cstdio>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int N, a[11], opCnt[4]; // + - * / 의 개수
int maxValue = -1000000000, minValue = 1000000000;

void dfs(int i, int res) {

    if (i == N) {
        maxValue = MAX(res, maxValue);
        minValue = MIN(res, minValue);
        return ;
    }

    for (int j = 0; j < 4; ++j){
        if (opCnt[j] == 0) continue;

        int curValue = res;
        if (j == 0)
            curValue += a[i];
        else if (j == 1)
            curValue -= a[i];
        else if (j == 2)
            curValue *= a[i];
        else
            curValue /= a[i];

        opCnt[j]--;
        dfs(i + 1, curValue);
        opCnt[j]++;
    }
}

int main() {
    
    freopen("input.txt", "r", stdin);

    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
        scanf("%d", &a[i]);
    for (int i = 0; i < 4; ++i)
        scanf("%d", &opCnt[i]);

    dfs(1, a[0]);

    printf("%d\n%d\n", maxValue, minValue);
}
