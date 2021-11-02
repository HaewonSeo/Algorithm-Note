// Single linked list

#include < stdio.h >

#define MAXN 1000

struct ListNode {
	int idx = -1;
	int data;
	ListNode* next;

	ListNode* myAlloc(int _idx, int _data, ListNode* _next) {
		idx = _idx;
		data = _data;
		next = _next;

		return this;
	}
} buffer[MAXN];

int bufferCnt = 0;

//ListNode *list;
ListNode head, tail;

void init() {
	bufferCnt = 0;
	head.next = &tail;
}


ListNode* getNode(int _idx) {
	ListNode* ptr = &head;

	while (ptr->next) {
		if (ptr->next->idx >= _idx || ptr->next->idx == -1) break;

		ptr = ptr->next;
	}

	return ptr;
}

void update(ListNode* ptr, int _data) {
	ptr->next->data = _data;

	return;
}

void remove(ListNode* ptr) {
	ptr->next = ptr->next->next;
}

int main() {
	init();

	for (int i = 0; i < 10; ++i) {
		int idx, data;
		scanf("%d %d", &idx, &data);

		ListNode* ptr = getNode(idx);
		ptr->next = buffer[bufferCnt++].myAlloc(idx, data, ptr->next);
	}

	for (int i = 0; i < 10; ++i) {
		int idx, newData;
		scanf("%d %d", &idx, &newData);

		ListNode* ptr = getNode(idx);
		if (ptr->next->idx == idx && ptr->next->idx != -1) update(ptr, newData);
	}

	for (int i = 0; i < 10; ++i) {
		int idx;
		scanf("%d", &idx);

		ListNode* ptr = getNode(idx);
		// node 삭제
		if (ptr->next->idx == idx && ptr->next->idx != -1) remove(ptr);
	}

	return 0;
}
