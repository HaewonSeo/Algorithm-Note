#include <cstdio>
#define DEBUG1

#define MAX_NODE 11		// 상위 10개만 필요함

struct HeapNode {
	int income;
	int uID;
} maxHeap[MAX_NODE];

int heapSize;

int addUserCnt, getTopCnt;
int minIncome;
int minIdx;

static void heapPush(HeapNode node, int swapIdx) {

	// full 에 대한 처리는 생략 가능

	int cur;
	if (swapIdx == 0)
		cur = ++heapSize;
	else
		cur = swapIdx;

	while (cur != 1) {
		if (node.income > maxHeap[cur/2].income) {
			maxHeap[cur] = maxHeap[cur/2];
			cur /= 2;
		}
		// income이 동일한 경우 uID를 비교
		else if (node.income == maxHeap[cur/2].income) {
			if (node.uID < maxHeap[cur/2].uID) {
				maxHeap[cur] = maxHeap[cur/2];
				cur /= 2;
			}
			//[여기서 3일을 디버그함......]
			//[사실 나중에 들어온 노드의 uID가 클수밖에 없으므로, 교체가 일어나지 않는다.]
			else
				break;
		}
		else
			break;
	}

	maxHeap[cur] = node;
}

static HeapNode heapPop() {

	HeapNode node = maxHeap[1];
	HeapNode last = maxHeap[heapSize--]; // last 노드를 적절한 위치에 저장해야 함

	int parent = 1;
	int child = 2;
	while (child <= heapSize) {

		// 자식 노드가 2개인 경우 큰 노드를 선택
		if (child < heapSize) {
			if (maxHeap[child].income < maxHeap[child+1].income) {
				child++;
			}
			else if (maxHeap[child].income == maxHeap[child+1].income) {
				if (maxHeap[child].uID > maxHeap[child+1].uID)
					child++;
			}
		}

		// last 노드와 비교 -> max라 판단되면 반복 종료
		if (last.income > maxHeap[child].income)
			break;
		else if (last.income == maxHeap[child].income) {
			if (last.uID < maxHeap[child].uID)
				break;
		}

		// 아니라면, last노드와 child를 swap
		maxHeap[parent] = maxHeap[child];
		parent = child;
		child *= 2;
	}

	// last 노드를 이동
	maxHeap[parent] = last;
	return node;
}

void init()
{
	// maxHeap 초기화
	heapSize = 0;
	addUserCnt = getTopCnt = 0;
	minIncome = 999999;
	minIdx = 10;

	for (int i = 0; i < MAX_NODE; i++) {
		maxHeap[i].income = -1;
		maxHeap[i].uID = -1;
	}
}

void addUser(int uID, int income)
{

	HeapNode node = {income, uID};

	if (heapSize < MAX_NODE - 1) {
		if (income < minIncome)
			minIncome = income;
		heapPush(node, 0);
		// minIdx의 초기값을 결정
		if (heapSize == MAX_NODE - 1) {
			for (int i = 1; i < MAX_NODE; i++)
				if (maxHeap[i].income == minIncome)
					minIdx = i;
		}
	}
	// maxHeap이 포화상태일 때,
	// maxHeap의 최소값을 가지는 노드를 지우고 그 자리에 새로운 노드를 삽입해야 함
	else if (heapSize == MAX_NODE - 1) {

		// maxHeap에서 최소값을 가지는 노드 탐색
		// [minIdx의 초기값을 >]
		minIncome = maxHeap[MAX_NODE-1].income;
		minIdx = MAX_NODE-1;
		for (int i = MAX_NODE-1; i >= 1; i--) {
			if (maxHeap[i].income < minIncome) {
				minIncome = maxHeap[i].income;
				minIdx = i;
			}
			else if (maxHeap[i].income == minIncome) {
				if (maxHeap[i].uID > maxHeap[minIdx].uID)
					minIdx = i;
			}
		}

		if (income < minIncome) {
			return ;
		}
		//[이부분도 고려했어야 함!]
		else if (income == minIncome) {
			if (maxHeap[minIdx].uID < node.uID) {
				return ;
			}
		}


		heapPush(node, minIdx);
	}


#ifdef DEBUG
	printf("[addUser%d] <size=%d> <income=%d> <uID=%d> <minIncome=%d> <minIdx=%d> \n", addUserCnt++, heapSize, income, uID, minIncome, minIdx);
	for (int i = 0; i < MAX_NODE; i++)
		printf("[%d]%d ", maxHeap[i].uID, maxHeap[i].income);
	printf("\n\n");
#endif

}

int getTop10(int result[10])
{
	int size = heapSize;

	HeapNode tmpArr[10];

	// pop
	for (int i = 0; i < size; i++) {
		HeapNode node = heapPop();
		result[i] = node.uID;
		tmpArr[i] = node;
	}

#ifdef DEBUG
	// 다시 push
	printf("[tmpArr]\n");
	for (int i = 0; i < size; i++) {
		printf("[%d]%d ", tmpArr[i].uID, tmpArr[i].income);
		heapPush(tmpArr[i], 0);
	}
	printf("\n");

	printf("[getTop%d] <size=%d> \n", getTopCnt++, heapSize);
	for (int i = 0; i < MAX_NODE; i++)
		printf("[%d]%d ", maxHeap[i].uID, maxHeap[i].income);
	printf("\n");
#endif

#ifndef DEBUG
	for (int i = 0; i < size; i++) {
		heapPush(tmpArr[i], 0);
	}
#endif

	return size;
}
