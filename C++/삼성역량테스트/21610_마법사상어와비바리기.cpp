#include <cstdio>

#define MAXN 51
#define MAXM 100

const int dr[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
const int dc[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};

int N, M;
int map[MAXN][MAXN];
bool cloud[MAXN][MAXN]; // 0 : 구름 없음, 1 : 이동한 구름, -1 : 바로 직전에 구름이었음
bool cloud_after[MAXN][MAXN];
int moving[MAXM][2];

void copy_water(int r, int c) {
    int cnt = 0;

    for (int i = 2; i <= 8; i += 2) {
        int nearR, nearC;
        nearR = r + dr[i];
        nearC = c + dc[i];

        if (nearR < 1 || nearR > N ||\
            nearC < 1 || nearC > N) continue;
        
        if (map[nearR][nearC])
            cnt++;
    }

    map[r][c] += cnt;
    return ;
}

void solve() {

    for (int i = 0; i < M; ++i) {
        int d = moving[i][0];
        int s = moving[i][1];
        
        //printf("i=%d, d=%d, s=%d \n", i, d, s);
        // 구름 이동
        for (int r = 1; r <= N; ++r) {
            for (int c = 1; c <= N; ++c) {
                if (!cloud[r][c]) continue;
                
                //printf("cur:[%d][%d]\t", r, c);
                // 1.구름 이동
                int ntR, ntC;
                ntR = (r + (dr[d] * s));
                ntC = (c + (dc[d] * s));
                if (ntR < 1)
                    while (ntR < 1)
                        ntR += N;
                else if (ntR > N)
                    while (ntR > N)
                        ntR -= N;
                if (ntC < 1)
                    while (ntC < 1)
                        ntC += N;
                else if (ntC > N)
                    while (ntC > N)
                        ntC -= N;
                //printf("next:[%d][%d]\n", ntR, ntC);

                // 2.raining
                map[ntR][ntC]++;

                // 이동한 구름을 따로 표시해줘야 함
                cloud_after[ntR][ntC] = 1;
                // 3. 직전 구름을 제거
                cloud[r][c] = 0;
            }
        }
                
        for (int r = 1; r <= N; ++r) {
            for (int c = 1; c <= N; ++c) {
                // 4.구름 주변에 물이 있는지 판단해서 물 복사
                if (cloud_after[r][c])
                    copy_water(r, c);
            }
        }

        for (int r = 1; r <= N; ++r) {
            for (int c = 1; c <= N; ++c) {
                // 기존에 구름이었던 곳은 구름 제거
                if (cloud_after[r][c])
                    cloud_after[r][c] = 0;
                // 5.물의 양이 2 이상인 곳에 구름 생성
                // [4,5 단계를 각각 분리했어야 함 - map 값이 달라지므로]
                else if (map[r][c] >= 2) {
                    map[r][c] -= 2;
                    cloud[r][c] = 1;
                }
            }
        }


        // for (int i = 1; i <= N; ++i) {
        //     for (int j = 1; j <= N; ++j) {
        //         printf("%d ", map[i][j]);
        //     }
        //     printf("\n");
        // }
    }
    return ;
}
int main() {

    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);

    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            scanf("%d", &map[i][j]);

    for (int i = 0; i < M; ++i)
        scanf("%d%d", &moving[i][0], &moving[i][1]);

    cloud[N][1] = 1;
    cloud[N][2] = 1;
    cloud[N-1][1] = 1;
    cloud[N-1][2] = 1;

    solve();

    int ans = 0;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            ans += map[i][j];

    printf("%d\n", ans);

    return 0;
}