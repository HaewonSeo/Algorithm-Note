#include <cstdio>
using namespace std;
#define MAX_NODE 100000

// Double Linked List
struct Node {
	int data;
	Node *prev;
	Node *next;
};

int nodeCnt;
Node node[MAX_NODE];
Node *head, *tail;

Node *getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void addNode2Tail(int data) {
	Node *tmp = getNode(data);
	tail->prev->next = tmp;
	tmp->prev = tail->prev;
	tmp->next = tail;
	tail->prev = tmp;
}

// num 번째 노드를 반환
Node *getNodePos(int num) {
	Node *cur = head;
	while (cur->next) {
		cur = cur->next;
		if (--num == 0) break;
	}

	if (cur->next)
		return cur;
	else
		return tail;
}

// 특정 위치에 노드 추가. pos->prev - tmp - pos
void addNode2Pos(Node *pos, int data) {
	Node *tmp = getNode(data);
	pos->prev->next = tmp;
	tmp->prev = pos->prev;
	tmp->next = pos;
	pos->prev = tmp;
}

void removeNode(Node *pos) {
	if (pos->next) {
		pos->next->prev = pos->prev;
		pos->prev->next = pos->next;
	}
}

void init() {
	nodeCnt = 0;
	head = getNode(-1);
	tail = getNode(-1);
	head->next = tail;
	tail->prev = head;
}

void printNode() {
	Node *cur = head;
	int cnt = 10;
	while (cur->next->next && cnt--) {
		cur = cur->next;
		printf("%d ", cur->data);
	}
}

void run() {
	int ori_len, data, inst_cnt, x, y, s;
	char inst;
	Node *cur;
	//line1
	scanf("%d", &ori_len);
	//line2
	for (int i = 0; i < ori_len; i++) {
		scanf("%d", &data);
		addNode2Tail(data);
	}
	//line3
	scanf("%d", &inst_cnt);
	//line4
	for (int i = 0; i < inst_cnt; i++) {
		// 공백문자를 고려한 입력
		scanf(" %c", &inst);

		switch (inst) {
		case 'I':
			scanf("%d%d", &x, &y);
			cur = getNodePos(x+1);
			while (y--) {
				scanf("%d", &s);
				addNode2Pos(cur, s);
			}
			break;
		case 'D':
			scanf("%d%d", &x, &y);
			cur = getNodePos(x);
			while (y--)
				removeNode(cur->next);
			break;
		case 'A':
			scanf("%d", &x);
			while (x--) {
				scanf("%d", &s);
				addNode2Tail(s);
			}
			break;
		}
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	freopen("1230_input.txt", "r", stdin);
	T = 10;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		init();
		run();
		printf("#%d ", test_case);
		printNode();
		printf("\n");
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
