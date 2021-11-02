#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

int n, h[50][50], dy[] = {-1, 1, 0, 0, -1, -1, 1, 1}, dx[] = {0, 0, -1, 1, -1, 1, -1, 1};
int cnt_k, y_post, x_post;
char vil[50][51];
vector<int> hhh;

// low ~ high의 고도사이로 탐색을 했을때, 배달 할 수 있는 집의 개수를 리턴
int bfs(int low, int high) {
	// to-do
	int cnt = 0;
	bool vt[50][50] = {false, };
	queue<pii> q;
	q.push(pii(y_post, x_post));
	vt[y_post][x_post] = true;
	if (h[y_post][x_post] < low || high < h[y_post][x_post]) return -1;
	while (!q.empty() && cnt < cnt_k) {
		pii cur = q.front();
		q.pop();
		for (int i = 0 ; i < 8 ; i++) {
			int next_y = cur.first + dy[i], next_x = cur.second + dx[i];
			if (next_y < 0 || n <= next_y || next_x < 0 || n <= next_x) continue;
			if (vt[next_y][next_x]) continue;
			if (h[next_y][next_x] < low || high < h[next_y][next_x]) continue;
			if (vil[next_y][next_x] == 'K') {
				cnt++;
			}
			vt[next_y][next_x] = true;
			q.push(pii(next_y, next_x));
		}
	}
	return cnt;
}

// low ~ high의 고도사이로 탐색을 했을때, 배달 할 수 있는 집의 개수를 리턴

//int dfs(int low, int high) {
//  // to-do
//}

int main() {
	// freopen("res/B2842.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0 ; i < n ; i++) {
		scanf("%s", vil[i]);
	}
	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < n ; j++) {
			if (vil[i][j] == 'K') {
				cnt_k++;
			}
			else if (vil[i][j] == 'P') {
				y_post = i, x_post = j;
			}
		}
	}
	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < n ; j++) {
			scanf("%d", &h[i][j]);
			hhh.push_back(h[i][j]);
		}
	}
	// 하고 싶은 것
	// 낮은 높이, 높은 높이를 임의로 정해서 모든 집에 배달 할 수 있는지를 확인하고 싶다

	//if (bfs(low, high) == cnt_k) ==> OK
	// low, high 모든 경우를 탐색하면 시간이 오래걸릴텐데......
	// 1. 이분 탐색을 이용 ==> hint : 특정 low에 대해서 되는 low + "a" 를 찾아보기
	// 2. 투포인터를 이용 ==> hint : 특정 시점에서 low-high가 만족을 했을때 다음 스텝은?
	sort(hhh.begin(), hhh.end());
	int answer = hhh.back() - hhh[0];
	for (int low = 0, high = 0 ; low < hhh.size() && high < hhh.size() && low <= high; ) {
		if (bfs(hhh[low], hhh[high]) == cnt_k) {
			int tmp = hhh[high] - hhh[low];
			if (tmp < answer) {
				answer = tmp;
			}
			low++;
		}
		else {
			high++;
		}
	}
	printf("%d", answer);
}
