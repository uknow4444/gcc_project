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
	printf("�������� Ƚ�� : %d\n ", count);

	count = 0;
	insert(arr_2, n, &count);
	for (int i = 0; i < n; i++)
		printf("%d ", arr_2[i]);
	printf("\n");
	printf("�������� Ƚ�� : %d\n", count);

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
			if (arr[i] < arr[j]) // ū ���ڰ� �տ� �ִٸ� ����.
				break;
		}
		if (i != j) { // ���簪���� ū ���� �ִٸ�
			m = arr[i]; // ���簪�� �����ϰ�
			for (int k = i; k > j; k--)
				arr[k] = arr[k-1]; // ��ĭ�� �ڷ� �̷��
			arr[j] = m;
		}
	}
}