#define MAXN (1 << 15)	// Add 함수 최대 호출 수
#define MAXB (1 << 10)	// 전체 bucket의 크기
#define DIV 10			// 개별 bucket에 들어가는 숫자 개수, 2^10개


struct Node {
    int val, idx;
    Node *prev;
    Node *next;

    Node *alloc(int _val, int _idx, Node *_prev, Node *_next) {
        val = _val;
        idx = _idx;
        prev = _prev;
        next = _next;

        if (next) {
            next->prev = this;
        }

        return this;
    }
} buf[MAXN], bucket[MAXB];	// buf: 정적 할당을 위한 buffer, bucekt: linked list의 head.

int bcnt, bucketCnt[MAXB];	// bucketCnt: 각 bucket에 담긴 숫자의 개수를 담음.


void init();
void add(int data);
int remove(int index);
int access(int index);
Node *getNode(int index);


// 초기화
void init() {
    bcnt = 0;
    for (int i = 0; i < MAXB; ++i) {
        bucketCnt[i] = 0;
        bucket[i].next = 0;	// head->next --> null
    }
}


Node *getNode(int index) {
    Node *ptr;
    int sum = 0, i = 0;

	// bucket cnt의 누적합 >= index --> break
    while (sum + bucketCnt[i] < index) {
        sum += bucketCnt[i];
        i++;
    }

	// bucket[i]는 index 번째 숫자가 존재하는 linked list.
	// bucket[i](head) --> node_1 --> node_2 --> ... --> null
    ptr = &bucket[i];


    while (ptr->next) {
        sum++;
        ptr = ptr->next;
        if (index == sum) break;
    }
    return ptr;
}


void add(int data) {
    Node *ptr;
    int index = data >> DIV;	// bucket의 index = data / (1 << 10)
    ptr = &bucket[index];
    bucketCnt[index]++;

    while (ptr->next) {
        if (ptr->next->val >= data) break;
        ptr = ptr->next;
    }
    ptr->next = buf[bcnt++].alloc(data, index, ptr, ptr->next);
}


int remove(int index) {
    Node *ptr = getNode(index + 1);
    ptr->prev->next = ptr->next;
    if (ptr->next) ptr->next->prev = ptr->prev;
    bucketCnt[ptr->idx]--;
    return ptr->val;
}


int access(int index) {
    Node *ptr = getNode(index + 1);
    return ptr->val;
}
