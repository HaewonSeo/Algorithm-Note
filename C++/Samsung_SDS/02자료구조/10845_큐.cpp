#include <cstdio>
#include <cstdlib>

typedef struct s_CircularQueue {
	int front;
	int rear;
	int data[10000];
} t_queue;

int n;

int main()
{
	scanf("%d", &n);

	char input[6];
	t_queue q;
	q.front = 0, q.rear = 0;

	for (int i = 0; i < n; i++)
	{
		scanf("%s", input);
		//push
		if (input[0] == 'p' && input[1] == 'u') {
			int num;
			scanf("%d", &num);
			q.rear = (q.rear + 1) % 10000;
			q.data[q.rear] = num;
		}
		//pop
		else if (input[0] == 'p') {
			if (q.rear == q.front) printf("-1\n");
			else {
				q.front = (q.front + 1) % 10000;
				printf("%d\n", q.data[q.front]);
			}
		}
		//size
		else if (input[0] == 's') {
			printf("%d\n", q.rear - q.front);
		}
		//empty
		else if (input[0] == 'e') {
			printf("%d\n", (q.rear == q.front));
		}
		//front
		else if (input[0] == 'f') {
			if (q.rear == q.front) printf("-1\n");
			else printf("%d\n", q.data[q.front + 1]);
		}
		//back
		else if (input[0] == 'b') {
			if (q.rear == q.front) printf("-1\n");
			else printf("%d\n", q.data[q.rear]);
		}
	}
}
