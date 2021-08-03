#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node *head, *tail;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	nodeCnt = 0;
	head = getNode(-1);
	tail = getNode(-1);
	head->next = tail;
	tail->prev = head;
}

void addNode2Head(int data)
{
	Node *tmp = getNode(data);
	head->next->prev = tmp;
	tmp->next = head->next;
	tmp->prev = head;
	head->next = tmp;
}

void addNode2Tail(int data)
{
	Node *tmp = getNode(data);
	tail->prev->next = tmp;
	tmp->prev = tail->prev;
	tmp->next = tail;
	tail->prev = tmp;
}

// 지정된 순서에 노드 추가 (1-2-3-4-5-...)
void addNode2Num(int data, int num)
{
	Node *cur = head;
	while (cur->next) {
		cur = cur->next;
		if (--num == 0) break;
	}

	Node *tmp = getNode(data);
	cur->prev->next = tmp;
	tmp->prev = cur->prev;
	tmp->next = cur;
	cur->prev = tmp;
}

// data를 가진 노드의 순서를 리턴
int findNode(int data)
{
	Node *cur = head;
	int idx = 0;
	while (cur->next) {
		cur = cur->next;
		idx++;
		if (cur->data == data) break;
	}

	if (cur->next)
		return idx;
	else
		return -1;
}

// data를 가진 노드를 삭제
void removeNode(int data)
{
	Node *cur = head;
	while (cur->next) {
		cur = cur->next;
		if (cur->data == data) break;
	}

	// cur node를 삭제
	if (cur->next) {
		cur->next->prev = cur->prev;
		cur->prev->next = cur->next;
	}
}

int getList(int output[MAX_NODE])
{
	Node *cur = head;
	int i = 0;
	while (cur->next) {
		cur = cur->next;
		output[i++] = cur->data;
	}

	// tail을 제외한 노드 수 반환
	return (i-1);
}

int getReversedList(int output[MAX_NODE])
{
	Node *cur = tail;
	int i = 0;
	while (cur->prev) {
		cur = cur->prev;
		output[i++] = cur->data;
	}

	// head를 제외한 노드 수 반환
	return (i-1);
}
