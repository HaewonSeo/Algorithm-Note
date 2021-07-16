#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair <int, int> pii;

int main() {
	int m, n;
	vector<pii> star, space;

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		pii cur;
		scanf("%d%d", &cur.first, &cur.second);
		star.push_back(cur);
	}
	// x좌표를 기준으로 오름차순 정렬
	sort(star.begin(), star.end());

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		pii cur;
		scanf("%d%d", &cur.first, &cur.second);
		space.push_back(cur);
	}
	sort(space.begin(), space.end());

	// 별자리의 맨왼쪽 별을 우주의 맨왼쪽 별에 맞출때 거리(dx, dy)를 계산
	// 나머지 별들을 (dx, dy)만큼 이동시키며 일치하는지를 확인
	int dx, dy;
	for (int i = 0; i < n; i++) {
		dx = space[i].first - star[0].first;
		dy = space[i].second - star[0].second;
		int find = 1;
		for (int j = 1; j < m && find; j++) {
			pii cur;
			cur.first = star[j].first + dx;
			cur.second = star[j].second + dy;

			// lower_bound의 반환값은 iterator라 실제 인덱스 알고 싶으면
			// 첫번째 주소를 빼주어야 한다.
			int pos = lower_bound(space.begin(), space.end(), cur) - space.begin();
			if (pos < 0 || pos >= n ||\
				cur.first != space[pos].first || cur.second != space[pos].second)
				find = 0;
		}
		if (find)
			printf("%d %d", dx, dy);
	}
}
