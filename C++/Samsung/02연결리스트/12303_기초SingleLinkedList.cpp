#include <stdio.h>
#define MAX_NODE 10000
#define DEBUG

typedef struct Node {
	int data;
	Node* next;
}Node;

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
#ifdef DEBUG
	printf("init\n");
#endif
	nodeCnt = 0;
	head = getNode(-1);
}

void addNode2Head(int data)
{
#ifdef DEBUG
	printf("addNode2Head\n");
#endif
	// head - tmp - head->next
	Node *tmp = getNode(data);
	tmp->next = head->next;
	head->next = tmp;
}

void addNode2Tail(int data)
{
#ifdef DEBUG
	printf("addNode2Tail\n");
#endif
	Node *cur = head;
	while (cur->next)
		cur = cur->next;

	Node *tmp = getNode(data);
	cur->next = tmp;
}

// 지정된 순서에 노드 추가 (1-2-3-4-5-...)
void addNode2Num(int data, int num)
{
#ifdef DEBUG
	printf("addNode2Num\n");
#endif
	// 추가할 위치 이전 노드 탐색
	Node *cur = head;
	while (cur->next) {
		if (--num == 0) break;
		cur = cur->next;
	}
	Node *tmp = getNode(data);
	tmp->next = cur->next;
	cur->next = tmp;
}

// 주어진 data를 가진 노드 삭제
void removeNode(int data)
{
#ifdef DEBUG
	printf("removeNode\n");
#endif
	Node *cur = head;
	while (cur->next) {
		if (cur->next->data == data) break;
		cur = cur->next;
	}

	// cur->next가 존재한다면, cur->next 를 삭제
	if (cur->next)
		cur->next = cur->next->next;
}

// output[]에 리스트 노드를 차례로 넣고, 총 노드 갯수를 반환
int getList(int output[MAX_NODE])
{
#ifdef DEBUG
	printf("getList\n");
#endif
	Node *cur = head;
	int i = 0;
	while (cur->next) {
		output[i++] = cur->next->data;
		cur = cur->next;
	}
	return (i);
}
