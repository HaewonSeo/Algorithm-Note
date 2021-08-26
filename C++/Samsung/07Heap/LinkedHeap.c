#include < stdio.h >
#include < stdlib.h >

#define MAXN 1000
#define MAXNODE 1000000
#define NULL (0)

typedef struct HeapNode {
	struct HeapNode *parent, *child[2];
	int value;
};

int heapNodePoolCnt;
HeapNode heapNodePool[MAXNODE];

typedef struct Heap {
	HeapNode* root;
	int size;

	void init() {
		size = 0;
	}

	HeapNode* create() {
		HeapNode* node = &heapNodePool[heapNodePoolCnt++]; // 메모리 풀에서 가져옴
		node->parent = node->child[0] = node->child[1] = NULL;
		return node;
	}

	HeapNode* findNode(int ind) {
		if (ind == 1) return root;
		else return findNode(ind >> 1)->child[ind & 1];
	}

	void push(int value) {
		if (size + 1 > MAXNODE) {
			printf("queue is full!\n");
			return;
		}

		HeapNode* cur = create(); // 새로운 노드 생성
		cur->value = value;
		if (size == 0) { // data가 없으면
			root = cur; // 새로운 노드가 root 노드가 된다
			size++;
			return;
		}
		else {
			size++;
			HeapNode* par = findNode(size >> 1); // 부모를 찾는다
			par->child[size & 1] = cur; // 찾은 부모와 새로 생성한 노드를 부모-자식 관계로 연결한다
			cur->parent = par;
			while (cur != root && cur->value < cur->parent->value) { // 추가한 자식과 부모의 우선순위 비교
				// 자식의 우선순위가 더 높으면 부모와 값을 바꿔준다
				int temp = cur->value;
				cur->value = cur->parent->value;
				cur->parent->value = temp;
				cur = cur->parent;
			}
		}
	}

	int pop() {
		if (size <= 0) {
			printf("queue is empty!\n");
			return -1;
		}
		else if (size == 1) { // data가 하나이면, 그 값을 리턴
			size = 0;
			return root->value;
		}

		int value = root->value;
		HeapNode* cur = findNode(size); // heap의 마지막 노드를 찾는다
		root->value = cur->value; // 마지막 노드의 값을 root에 저장
		cur->parent->child[size & 1] = NULL; // 마지막 노드 제거
		size--;

		// root에 저장된 값을 올바른 위치로 옮긴다
		cur = root;
		while (cur->child[0] != NULL) {
			HeapNode* child;
			if (cur->child[1] == NULL)
				child = cur->child[0];
			else
				child = cur->child[0]->value < cur->child[1]->value ? cur->child[0] : cur->child[1];

			if (cur->value < child->value)
				break;

			int temp = child->value;
			child->value = cur->value;
			cur->value = temp;
			cur = child;
		}

		return value;
	}
};

Heap heap[MAXN];


void main() {
	srand(11);
	heapNodePoolCnt = 0;
	for (int i = 0; i < MAXN; i++)
		heap[i].init();

	for (int i = 0; i < MAXNODE; i++) { // 총 1,000,000 data 할당
		int ind = rand() % MAXN;
		heap[ind].push(rand() % MAXNODE);
	}

	for (int i = 0; i < MAXN; i++) {
		printf("heap[%d]: ", i);
		for (int j = 0; j < 10; j++) // 우선순위가 높은 data 10 개 출력
			printf(" %d", heap[i].pop());
		printf("\n");
	}
	printf("\n");
}
