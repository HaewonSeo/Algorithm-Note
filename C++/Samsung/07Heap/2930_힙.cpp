#include <cstdio>

#define MAX 100000

int maxHeap[MAX+1];
int heapSize;

void init(int size) {
	heapSize = 0;
	for (int i = 0; i <= size; i++)
		maxHeap[i] = 0;
}

void heapPush(int n) {

	if (heapSize == MAX)
		return ;

	int cur = ++heapSize;

	while (cur != 1 && n > maxHeap[cur >> 1]) {
		maxHeap[cur] = maxHeap[cur >> 1];
		cur = (cur >> 1);
	}
	maxHeap[cur] = n;
}

int heapPop() {

	if (heapSize == 0)
		return -1;

	int pop = maxHeap[1];	// root 노드
	int last = maxHeap[heapSize--];

	int parent = 1;
	int child = 2;

	// 범위를 벗어나지 않는 동안
	while (child <= heapSize) {

		// child가 2개라면 그 중 큰 노드 선택
		if (child < heapSize) {
			if (maxHeap[child+1] > maxHeap[child])
				child++;
		}

		// last가 큰 자식노드보다 크다면 break
		if (last > maxHeap[child])
			break;

		// 아니면 한단계 아래로 이동
		maxHeap[parent] = maxHeap[child];
		parent = child;
		child = (child << 1);
	}

	// 최종 위치에 last를 저장
	maxHeap[parent] = last;

	return pop;
}

int main() {
	//setbuf(stdout, NULL);

	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		printf("#%d", tc);

		int N;
		scanf("%d", &N);

		init(N);
		for (int n = 1; n <= N; n++) {
			int num;
			scanf("%d", &num);

			if (num == 1) {
				int k;
				scanf("%d", &k);
				heapPush(k);
			}
			else if (num == 2) {
				int pop = heapPop();
				printf(" %d", pop);
			}
		}
		printf("\n");
	}
	return 0;
}
