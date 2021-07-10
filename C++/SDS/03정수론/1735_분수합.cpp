#include <cstdio>

int a, b, c, d;

int gcd(int x, int y)
{
	if (y == 0) return x;
	return gcd(y, x % y);
}

int main()
{
	scanf("%d%d%d%d", &a, &b, &c, &d);

	// a/b + c/d
	// (a*d + b*c) / (b * d)
	// 기약분수로 만들기 위해 최소공배수를 구함
	int numerator = a*d + b*c, denominator = b * d;
	int n = gcd(numerator, denominator);
	numerator /= n;
	denominator /= n;
	printf("%d %d", numerator, denominator);
}
