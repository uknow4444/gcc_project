#include <stdio.h> 

int** input(int** A, int* size, int* n);
int** matrix_multiply(A, size, n);
void display (arr, size);

int main(void) {
	int **A = NULL;
	int size, n;
	int **sum = NULL;

	A = input(A, &size, &n);
	display(A, size);
	sum = matrix_multiply(A, size, n);
	display(sum, size);
	return 0;
}

int** input(int **A, int* size, int* n) {
	int i, j;

	printf("몇 자리 행렬을 만들까요?? : ");
	scanf("%d", size);

	A = (int**)malloc(sizeof(int*)*(*size));
	for (i = 0; i < *size; i++) {
		A[i] = (int*)malloc(sizeof(int)*(*size));
	}
	for (int i = 0; i < *size; i++) {
		printf("%d 번째 행 입력 : ", i + 1);
		for (int j = 0; j < *size; j++)
			scanf("%d", A[i]+j);
	}
	printf("\n제곱 수 입력 : ");
	scanf(" %d", n);

	return A;
}

int** matrix_multiply(int** A,int size,int n) {
	int** sum;
	if (n > 1)
		sum = matrix_multiply(A, size, n - 1);
	if (n == 1)
		return A;
	else {
		int** store = (int**)malloc(sizeof(int*)*(size));
		for (int i = 0; i < size; i++)
			store[i] = (int*)malloc(sizeof(int)*(size));
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				store[i][j] = 0;
				for (int k = 0; k < size; k++)
					store[i][j] += sum[i][k] * A[k][j];
			}
		}
		return store;
	}
	
}

void display(int **arr,int size) {
	printf("\n\n");
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}