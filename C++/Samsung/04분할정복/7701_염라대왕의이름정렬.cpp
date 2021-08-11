#include <cstdio>
#include <string.h>

int N;
char nameList[20000][51];
int idxList[20000];
int buf[20000];

int cmp(const char *s1, const char *s2) {
	int len1 = strlen(s1), len2 = strlen(s2);

	// 길이가 같으면 문자열 비교
	if (len1 == len2)
		return (strcmp(s1, s2));
	else // 길이 다르면 짧은것이 먼저
		return (len1 - len2);
}

void mergeSortbyLen(int s, int e) {
	if (s >= e) return;

	int m = (s + e) / 2;
	mergeSortbyLen(s, m);
	mergeSortbyLen(m+1, e);

	//merge
	int i = s, j = m + 1, k = s;
	while (i <= m && j <= e) {
		//buf[k++] = lenList[idxList[i]] <= lenList[idxList[j]] ? idxList[i++] : idxList[j++];
		//buf[k++] = strcmp(nameList[idxList[i]], nameList[idxList[j]]) ? idxList[j++] : idxList[i++];
		// strcmp를 활용하여 정렬?
		// [strcmp는 한글자씩 비교하므로 앞 문자열의 길이가 짧더라도 결과가 클 수 있다.]
		// 1. string.compare() 는 앞 문자열길이가 짧으면 <0 을 리턴한다.
		// 2. 임의로 비교함수를 만들자.
		int compare = cmp(nameList[idxList[i]], nameList[idxList[j]]);
		if (compare <= 0)
			buf[k++] = idxList[i++];
		else
			buf[k++] = idxList[j++];
	}
	while (i <= m)
		buf[k++] = idxList[i++];
	while (j <= e)
		buf[k++] = idxList[j++];

	for (i = s; i <= e; i++)
		idxList[i] = buf[i];

}


void mergeSort(int arr[], int s, int e) {
	if (s >= e) return;

	int m = (s + e) / 2;
	mergeSort(arr, s, m);
	mergeSort(arr, m+1, e);

	//merge
	int i = s, j = m + 1, k = 0;
	int len = e - s + 1;
	int *buf = new int[len];

	while (i <= m && j <= e)
		buf[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
	while (i <= m)
		buf[k++] = arr[i++];
	while (j <= e)
		buf[k++] = arr[j++];

	for (i = s, k = 0; i <= e; i++, k++)
		arr[i] = buf[k];

	delete buf;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	scanf("%d", &T);
	for(test_case = 1; test_case <= T; ++test_case)
	{
		for (int i = 0; i < N; i++) {
			nameList[i][0] = '\0';
			idxList[i] = -1;
		}

		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%s", &nameList[i]);
			idxList[i] = i;
		}

		// 1. 이름길이 순으로 정렬 ... index을 따루 두어 정렬
		// O(NlogN)
		mergeSortbyLen(0, N-1);

		printf("#%d\n", test_case);
		for (int i = 0; i < N; i++) {
			// 중복 제거
			if (!strcmp(nameList[idxList[i]], nameList[idxList[i+1]])) continue;
			printf("%s\n", nameList[idxList[i]]);
		}
	}
	return 0;
}
