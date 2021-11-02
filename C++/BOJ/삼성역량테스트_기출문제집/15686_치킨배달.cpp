#include <cstdio>
#include <vector>
using namespace std;

#define DEBUG1
#define MAXINT 2147483647;
#define MIN(a, b) ((a < b) ? (a) : (b))
#define ABS(a) ((a < 0) ? (-(a)) : (a))
typedef pair<int, int> pii;

//[N, M 의 범위를 잘 확인하기!]
int N, M;
int map[51][51]; // 0:빈집, 1:집, 2:치킨집, 3:선택한 치킨집
vector<pii> home_v;
vector<pii> chicken_v;
vector<pii> select_v;
int ans;

// M개의 치킨 집 선택
// 도시의 치킨 거리 계산 후 최솟값 결정
void get_min_distance() {
	int city_dist = 0;

	for (int i = 0; i < home_v.size(); ++i) {
		pii cur_home = home_v[i];
		int chicken_dist = MAXINT;
		for (int j = 0; j < select_v.size(); ++j) {
			pii cur_select = select_v[j];
			int tmp = 0;
			tmp += ABS(cur_home.first - cur_select.first);
			tmp += ABS(cur_home.second - cur_select.second);
			chicken_dist = MIN(chicken_dist, tmp);
		}
		city_dist += chicken_dist;
	}

#ifdef DEBUG
	if (city_dist < ans) {
		printf("city_dist=%d \t", city_dist);
		printf("select size = %lu\t", select_v.size());
		for (int i = 0; i < select_v.size(); ++i)
			printf("[%d][%d] ", select_v[i].first, select_v[i].second);
		printf("\n");
	}
#endif

	ans = MIN(ans, city_dist);
}

void dfs(int n, int cnt) {
	if (cnt == M) {
		get_min_distance();
		return;
	}

	// 치킨집 선택
	for (int i = n; i < chicken_v.size(); ++i) {
		pii cur = chicken_v[i];
		select_v.push_back(cur);
		dfs(i + 1, cnt + 1);
		select_v.pop_back();
	}
}

int main() {

	freopen("input.txt", "r", stdin);

	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)
				home_v.push_back(pii(i, j));
			else if (map[i][j] == 2)
				chicken_v.push_back(pii(i, j));
		}
	}

	ans = MAXINT;
	dfs(0, 0);
	printf("%d\n", ans);
	return 0;
}
