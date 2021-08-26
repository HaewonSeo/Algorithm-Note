#include <stdbool.h>

#define HASH_SIZE (1 << 18)
#define DIV (HASH_SIZE - 1)
#define MAXN 100000

typedef unsigned long long ll;

bool strCmp(char a[], char b[]) {
	int i = 0;

	for (; a[i]; i++) {
		if (a[i] != b[i])
			return false;
	}

	return (a[i] == b[i]);
}

void strCpy(char dst[], char src[]) {
	while (*src)
		*dst++ = *src++;

	*dst = 0;
}

struct Node {
	char key[11];
	int data;
	Node *next;

	Node *alloc(char _key[], int _data, Node *_next) {
		strCpy(key, _key);
		data = _data;
		next = _next;
		return this; // 현재 구조체의 주소를 반환
	}

	/* 찾는 node의 바로 이전 node를 반환한다 */
	Node *getPrevNode(char _key[]) {
		Node *ptr = this;

		while (ptr->next) {
			if (strCmp(_key, ptr->next->key))
				break;
			ptr = ptr->next;
		}
		return ptr;
	}
};

int bCnt;
Node buf[MAXN];
Node hashTable[HASH_SIZE];


void init() {
	bCnt = 0;
	for (int i = 0; i < HASH_SIZE; ++i)
		hashTable[i].next = 0;
}

int getKey(char str[]) {
	ll key = 5381;

	for (int i = 0; str[i]; ++i)
		key = ((key << 5) + key) + (str[i] - 'a' + 1);

	return (int) (key & DIV); // 해당 code에서 hash 값은 int_32 범위를 초과할 일이 없음.
}

int find(char key[]) {
	Node *prevNode;
	int target = getKey(key);
	prevNode = hashTable[target].getPrevNode(key);

	return prevNode->next->data;
}

// header - next1 - next2 - next3 - NULL
// add 이후
// header - new - next1 - next2 - next3 - NULL
void add(char key[], int data) {
	int target = getKey(key);
	hashTable[target].next = buf[bCnt++].alloc(key, data, hashTable[target].next);
}

int remove(char key[]) {
	Node *prevNode, *targetNode;
	int target = getKey(key);

	prevNode = hashTable[target].getPrevNode(key);
	targetNode = prevNode->next;
	prevNode->next = targetNode->next;

	return targetNode->data;
}

/*

input data의 조건입니다.
1. add는 최대 100000
2. key 문자열의 길이는 2~10입니다.
3. 존재하지 않는 key를 찾거나 제거하는 경우는 없다.


1. Hash table을 일반 변수로 선언하여 header로 사용했습니다.
2. Chaining을 linked list로 구현했습니다.
3. Single linked list기 때문에 삭제를 위해 이전 node를 반환하고 있습니다.
4. Hash에 원본 data(key 문자열)을 복사하는 이유는 충돌 때문입니다.
충돌이 발생하면 두 개 이상의 node가 동일한 hash 값을 갖습니다.
Hash 값은 일반적으로 복호화가 불가능하기 때문에 원본 data를 알수 없습니다.
그래서 원본을 저장하는 것입니다.

*/


// HASH_TABLE_SIZE은 2의 거듭제곱 or 는 소수를 사용한다.
// 2의 거듭제곱이 rehash에도 유리하고 bitmasking으로 빠른 연산이 가능하여 많이 사용된다.
unsigned long djb2(const char* str)
{
    unsigned long hash = 5381; // base
    int c;
    while (c = *str++)
    {
        hash = (((hash << 5) + hash) + c); // hash = hash * 33 + ascii code of str[i]
    }
    return hash % HASH_SIZE;
}
