#include <cstdio>

// [hash size 1<<18로 하니 RTE... 발생함 ㅜㅜ]
#define HASH_SIZE (1 << 17)
#define MAXN 100000
#define MAX 51

bool strCmp(char a[], char b[]) {
	int i = 0;

	for (; a[i]; i++)
		if (a[i] != b[i]) return false;

	return a[i] == b[i];
}

void strCpy(char dst[], char src[]) {
	while (*src)
		*dst++ = *src++;
	*dst = 0;
}

struct Node {
	char key[MAX]; // \0
	Node *next;
	//int data;

	Node *alloc(char _key[], Node *_next) {
		strCpy(key, _key);
		next = _next;
		return this;
	}

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

int bufCnt;
Node buf[MAXN];
Node hashTable[HASH_SIZE];

void init() {
	bufCnt = 0;
	for (int i = 0; i < HASH_SIZE; ++i)
		hashTable[i].next = 0;
}

int djb2(char *str) {
	long long hash = 5381;

	for (int i = 0; str[i]; i++)
		hash = ((hash << 5) + hash) + (str[i] - 'a' + 1);

	return (int) (hash & (HASH_SIZE - 1));
}

void add(char key[]) {
	int target = djb2(key);
	hashTable[target].next = buf[bufCnt++].alloc(key, hashTable[target].next);
}

int find(char key[]) {
	Node *prevNode;
	int target = djb2(key);

	// [같은 hash 번째 배열에 다른 key들이 존재할 수 있다.]
	// [따라서, 단순히 next값을 체크하면 안되고,
	// getPrevNode()를 통해 해당 chaining에서 일치하는 key값이 존재하는지 판단해야 한다.]
	prevNode = hashTable[target].getPrevNode(key);

	if (prevNode->next)
		return 1;
	else
		return 0;
}

int main() {

	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; ++tc) {
		int N, M;
		scanf("%d %d", &N, &M);

		char str[MAX];
		int ans = 0;
		// [init() 을 생략하여 RTE 발생]
		init();

		for (int i = 0; i < N; ++i) {

			scanf("%s", str);
			add(str);

		}

		for (int i = 0; i < M; ++i) {
			scanf("%s", str);
			if (find(str))
				ans++;
		}
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}
