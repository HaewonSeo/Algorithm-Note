#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int n;

class ArrayStack
{
private:
	int top;
	int data[10000];
public:
	ArrayStack() {top = -1;}
	~ArrayStack() {}

	void push(int x)
	{
		if (full()) return ;
		data[++top] = x;
	}

	int pop()
	{
		if (empty()) return -1;
		return data[top--];
	}

	bool empty()
	{
		return (top == -1);
	}

	bool full()
	{
		return (top == 9999);
	}

	int size()
	{
		return (top + 1);
	}

	int gettop()
	{
		if (empty()) return -1;
		return (data[top]);
	}
};

int main()
{
	scanf("%d", &n);

	ArrayStack stk;
	char input[20];

	for (int i = 0; i < n; i++)
	{
		scanf("%s", input);

		if (strcmp(&input[i], "push") == 0) {
			char num[7];
			scanf("%s", num);
			stk.push(atoi(num));
		}
		else if (strcmp(&input[i], "pop") == 0) {
			int data = stk.pop();
			printf("%d\n", data);
		}
		else if (strcmp(&input[i], "size") == 0) {
			int size = stk.size();
			printf("%d\n", size);
		}
		else if (strcmp(&input[i], "empty") == 0) {
			int empty = stk.empty();
			printf("%d\n", empty);
		}
		else if (strcmp(&input[i], "top") == 0) {
			int top = stk.gettop();
			printf("%d\n", top);
		}
	}
}
