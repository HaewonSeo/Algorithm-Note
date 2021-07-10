#include <cstdio>
#include <algorithm>
//#include <vector>
#include <queue>
using namespace std;

// #define debug

typedef pair<int, int> pii;
typedef long long LL;

int N, K;
// M(무게), V(가격)
pii jewel[300000];
int bag[300000];

bool compare(pii &x, pii &y)
{
	return x.first < y.first;
}

int main()
{
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &jewel[i].first, &jewel[i].second);
	}
	for (int i = 0; i < K; i++) {
		scanf("%d", &bag[i]);
	}

	// 보석의 무게 순으로 오름차순
	sort(jewel, jewel + N, compare);
	// 가방의 무게 순으로 오름차순
	sort(bag, bag + K);

#ifdef debug
	for (int i = 0; i < N; i++){
		printf("[%d %d]\n", jewel[i].first, jewel[i].second);
	}
	for (int i = 0; i < K; i++){
		printf("<%d>\n", bag[i]);
	}
#endif
	//가벼운 가방에 넣을 수 있는 보석 중 값이 비싼 보석 선택
	//그 다음 가벼운 가방에 넣을 수 있는 보석을 추가하여 그 중 가장 비싼 보석을 선택

	// 작은 가방부터 무엇을 넣을지 판단
	//vector<pii> candJewel; 후보 보석 중에서 정렬이 필요함...시간복잡도 증가함...
	// 따라서 우선순위 큐 사용.
	priority_queue<int> max_pq; // 값어치만 계산할 것이므로 가격만을 저장
	LL ans = 0;
	int posJewel = 0;
	for (int i = 0; i < K ; i++) {
		int curBag = bag[i];
		// 현재 가방에 넣을 수 있는 보석을 우선순위 큐에 삽입
		while (posJewel < N && jewel[posJewel].first <= curBag) {
			//candJewel.push_back(jewel[j]);
			max_pq.push(jewel[posJewel].second);
			posJewel++;
		}
		// 우선순위 큐에서 max를 결과에 더함
		if (!max_pq.empty()) {
			ans += max_pq.top();
			max_pq.pop();
		}
	}
	printf("%lld", ans);
}
