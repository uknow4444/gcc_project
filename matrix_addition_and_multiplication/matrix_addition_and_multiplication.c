#include <stdio.h> 

int** input(A, m, k, l);
int** multiply(A, m, k, l);
void display(arr, row, col);

int main(void) {
	int **A = NULL;
	int **B = NULL;
	int m, k, l;
	int **sum = NULL;
	k = 0;
	A = input(A, &m, &k);
	display(A, m, k);
	B = input(A, &k, &l);
	display(B, k, l);
	sum = multiply(A, B, m, k, l);
	display(sum, m, l);
	return 0;
}

int** input(int **arr, int* a, int* b) {
	int i, j;

	if (*b == 0) {
		printf("A행렬 = m x k 행렬을 만들겁니다. 어떤 크기로 만들까요?? (m k): ");
		scanf("%d %d", a, b);
	}
	else {
		printf("B행렬 = %d x l 행렬을 만들겁니다. 어떤 크기로 만들까요?? (l): ", *a);
		scanf("%d", b);
	}

	arr = (int**)malloc(sizeof(int*)*(*a));
	for (i = 0; i < *a; i++) {
		arr[i] = (int*)malloc(sizeof(int)*(*b));
	}
	for (int i = 0; i < *a; i++) {
		printf("%d 번째 행 입력 : ", i + 1);
		for (int j = 0; j < *b; j++)
			scanf("%d", arr[i] + j);
	}

	return arr;
}

int** multiply(int** arr1,int** arr2, int m, int k, int l) {
	int** store = (int**)malloc(sizeof(int*)*m);
	for (int i = 0; i < m; i++)
		store[i] = (int*)malloc(sizeof(int)*l);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < l; j++) {
			store[i][j] = 0;
			for (int h = 0; h < k; h++)
				store[i][j] += arr1[i][h] * arr2[h][j];
		}
	}
	return store;
}


void display(int **arr, int a, int b) {
	printf("\n\n");
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}