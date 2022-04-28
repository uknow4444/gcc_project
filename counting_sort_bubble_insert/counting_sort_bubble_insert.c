#include<stdio.h>

void bubble(int arr[], int n, int *count);
void insert(int arr[], int n, int *count);

int main(void) {
	int arr_1[] = { 10,9,8,5,6,7,4,3,2,1 };
	int arr_2[] = { 10,9,8,5,6,7,4,3,2,1 };
	int n = sizeof(arr_1) / 4;
	int count = 0;

	bubble(arr_1, n, &count);
	for (int i = 0; i < n; i++)
		printf("%d ", arr_1[i]);
	printf("\n");
	printf("버블정렬 횟수 : %d\n ", count);

	count = 0;
	insert(arr_2, n, &count);
	for (int i = 0; i < n; i++)
		printf("%d ", arr_2[i]);
	printf("\n");
	printf("삽입정렬 횟수 : %d\n", count);

	return 0;
}
void bubble(int arr[], int n, int *count) {
	int temp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) { //swap
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			(*count)++;
		}
	}
}
void insert(int arr[], int n, int *count) {
	int j, i, m;
	for (i = 1; i < n; i++) {
		for (j = 0; j < i;j++) {
			(*count)++;
			if (arr[i] < arr[j]) // 큰 숫자가 앞에 있다면 종료.
				break;
		}
		if (i != j) { // 현재값보다 큰 항이 있다면
			m = arr[i]; // 현재값을 저장하고
			for (int k = i; k > j; k--)
				arr[k] = arr[k-1]; // 한칸씩 뒤로 미루기
			arr[j] = m;
		}
	}
}