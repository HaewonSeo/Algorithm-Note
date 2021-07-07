#include <cstdio>
typedef long long LL;

int main()
{
	int n;
	scanf("%d", &n);

	LL fb[91] = {0, 1}, ans;
	for (int i = 2; i <= n; i++)
		fb[i] = fb[i-2] + fb[i-1];
	printf("%lld", fb[n]);
}
