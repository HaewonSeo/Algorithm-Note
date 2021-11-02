#include <cstdio>

#define MAX_NODE 101

// [굳이 left, right를 저장하지 않고, (2*i), (2*i +1) 노드를 찾아 출력해도 된다.]
struct TreeNode {
	char data;
	int left;
	int right;
};

TreeNode treeNode[MAX_NODE];
int nodeCnt;

int init(int NodeCnt) {
	nodeCnt = 0;
	for (register int i = 1; i <= NodeCnt; i++) {
		treeNode[i].left = -1;
		treeNode[i].right = -1;
		treeNode[i].data = NULL;
	}
}

void InorderTraverse(TreeNode *node) {
	if (node->left != -1)
		InorderTraverse(&treeNode[node->left]);

	printf("%c", node->data);

	if (node->right != -1)
		InorderTraverse(&treeNode[node->right]);
}

int main() {

	for (int tc = 1; tc <= 10; tc++) {
		int N;
		scanf("%d", &N);

		init(N);

		// Input
		for (int i = 1; i <= N; i++) {
			int cur, left, right;
			char data;

			// 좌우 자식노드 모두 존재하는 경우
			if (N >= (i * 2) + 1) {
				scanf("%d %c %d %d", &cur, &data, &left, &right);
				treeNode[cur].data = data;
				treeNode[cur].left = left;
				treeNode[cur].right = right;
			}
			// 왼쪽 자식노드만 존재하는 경우
			else if (N == (i * 2)) {
				scanf("%d %c %d", &cur, &data, &left);
				treeNode[cur].data = data;
				treeNode[cur].left = left;
			}
			// 자식노드가 존재하지 않는 경우
			else if (N < (i * 2)) {
				scanf("%d %c", &cur, &data);
				treeNode[cur].data = data;
			}
		}

		printf("#%d ", tc);
		InorderTraverse(&treeNode[1]);
		printf("\n");

	}
}


/*
#include <cstdio>

#define MAX_POOL 100
#define MAX_NODE 100

int memPoolCnt;

struct ListNode {
	int id;
	ListNode *prev;
} listPool[MAX_POOL]; // 메모리 풀 할당

struct TreeNode {
	int parent;
	char data;
	ListNode *child; // 가장 최근에 추가되 자식 노드를 가리키는 포인터
} treeNode[MAX_NODE];

void init() {
	memPoolCnt = 0;
	for (register int i = 0; i < MAX_NODE; i++) {
		treeNode[i].parent = -1;
		treeNode[i].child = nullptr;
	}
}


int main() {
	setbuf(stdout, NULL);

	for (int tc = 1; tc <= 10; tc++) {
		int N;
		scanf("%d", &N);

		for (int n = 1; n <= N; n++) {
			int node, left, right;
			char data;
			scanf("%d %c %d %d", &node, &data, &left, &right);

			treeNode[node].data = data;
			treeNode[left].parent = node;
			treeNode[right].parent = node;

			ListNode *list = &listPool[memPoolCnt++];
			list->id = left;
			list->prev = treeNode[node].child;
			treeNode[node].child = list;


		}
	}
}

*/
