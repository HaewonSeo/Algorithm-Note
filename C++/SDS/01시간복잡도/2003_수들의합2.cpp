#include <cstdio>

int n, m, sum, cnt;
int A[10000];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);

	// 2 pointer
	// 10 5
	// 1 2 3 4 2 5 3 1 1 2
	// s
	//       e
	// e를 한칸씩 ++
	// s~e의 합이 m이면 cnt++
		// e를 늘려도 합이 m이상이므로 s++
	// s~e의 합이 m을 넘어가면 sum에서 A[s]를 빼고, s++

	/*
	int s = 0, e = 0;
	while (s < n && e < n) {
		// e 이동
		for (; e < n; e++){
			sum += A[e];
			if (sum == m){
				cnt++;
				e++;
				break;
			}
			else if (sum > m) {
				e++;
				break;
			}
		}

		// s 이동
		while (s < n && sum >= m) {
			sum -= A[s];
			s++;
			if (sum == m)
				cnt++;
		}
	}
	*/

	for (int s = 0, e = 0; e < n; e++){
		sum += A[e];
		while (sum > m) {
			sum -= A[s];
			s++;
		}
		if (sum == m) cnt++;
	}

	printf("%d", cnt);
}
