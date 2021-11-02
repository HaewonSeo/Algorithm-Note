#include <cstdio>

int N;
int a[1000000];
int lefgGcd[1000000];
int rigntGcd[1000000];

int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		scanf("%d", &a[i]);


}
