#include <cstdio>
#include <algorithm>
using namespace std;

int n, m;
int a[100000];
int b[100000];

bool BinarySearch(int key)
{
	int start = 0;
	int end = n - 1;
	int mid = -1;

	while(start <= end)
	{
		mid = (start + end) / 2;
		if (key == a[mid])
			return true;
		else if (key < a[mid])
			end = mid - 1;
		else
			start = mid + 1;
	}
	return false;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 0; i < m; i++)
		scanf("%d", &b[i]);

	sort(a, a+n);

	for (int i = 0; i < m; i++)
	{
		printf("%d\n", BinarySearch(b[i]));
	}
}
