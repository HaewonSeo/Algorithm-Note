//Double linked list

struct ListNode {
	int idx = -1;
	int data;
	ListNode* prev;
	ListNode* next;

	ListNode* myAlloc(int _idx, int _data, ListNode* _prev, ListNode* _next) {
		idx = _idx;
		data = _data;
		prev = _prev;
		next = _next;
		_next->prev = this;	// 현재 node를 다음 node의 이전 node로 연결.

		return this;
	}
} buffer[MAXN];

int bufferCnt = 0;


ListNode* getNode(int _idx) {
	ListNode* ptr = &head;

	while (ptr->next) {
		if (ptr->next->idx >= _idx || ptr->next->idx == -1) break;

		ptr = ptr->next;
	}

	return ptr;
}


// ptr <--> ptr->next <--> ptr->next->next
void remove(ListNode* ptr) {
	ListNode* tmp = ptr->next;

	ptr->next = tmp->next;	// ptr --> ptr->next->next
	tmp->next->prev = ptr;	// ptr <-- ptr->next->next
}

int main() {
	init();

	for (int i = 0; i < 10; ++i) {
		int idx, data;
		scanf("%d %d", &idx, &data);

		ListNode* ptr = getNode(idx);
		ptr->next = buffer[bufferCnt++].myAlloc(idx, data, ptr, ptr->next);
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
