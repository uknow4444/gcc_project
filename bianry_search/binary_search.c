#include <stdio.h>
#define true 1
#define false 0

#define n 10

int get_val();
int seach(a, a_len, val);
void display(boolean);

int main() {
	int a[n] = {2,4,6,8,10,12,14,16,18,20}; // 10��

	int val = get_val();
	display(seach(a,n,val));
	
}

int get_val() {
	int re;
	printf("ã�����ϴ� ���ڸ� �Է����ּ��� : ");
	scanf("%d",&re);
	return re;
}
int seach(int a[], int k, int val) {
	int l = 0;
	int r = k - 1;
	int mid;
	while (l != r) {
		mid = (l + r) / 2;
		if (a[mid] == val)
			return true;
		else if (a[mid] > val)
			r = mid;
		else
			l = mid+1;
	}
	return false;
}
void display(int result) {
	if (result)
		printf("�ش� ���ڰ� �ֽ��ϴ�.\n");
	else
		printf("�ش� ���ڰ� �����ϴ�.\n");
}