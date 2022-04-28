#include <stdio.h>
#include <stdlib.h>

int get_poly(p);
void print_poly(p, count_p);
int sub_poly(p, p2, p3);
int eval_poly(p, x);

int main(void) {
	int** p1 = (int**)malloc(sizeof(int*) * 2);
	int count_p1 = get_poly(p1);
	int** p2 = (int**)malloc(sizeof(int*) * 2);
	int count_p2 = get_poly(p2);
	printf("ù��° ���׽� : ");
	print_poly(p1, count_p1); // �迭 p1 �����Է� Ȯ��.
	printf("�ι�° ���׽� : ");
	print_poly(p2, count_p2); // �迭 p2 �����Է� Ȯ��.

	int** p = (int**)malloc(sizeof(int*) * 2);
	// �޸� ������ ���� p1�� p2�� ���� ���� �ո�ŭ �迭 p �����Ҵ�.
	*p = (int*)malloc(sizeof(int)*(count_p1 + count_p2)); // ���׽��� ��� ����.
	*(p + 1) = (int*)malloc(sizeof(int)*(count_p1 + count_p2)); // ���׽��� ���� ����.
	p = sub_poly(p, p1, p2);
	printf("��� ���׽� : ");
	print_poly(p, count_p1 + count_p2); // ����迭 ���

	int x; // ����ڿ��� x���� �Է� ���� �Լ�
	printf("x���� �Է��ϼ���. : ");
	scanf("%d", &x);
	printf("ù��° ���׽� ����� : %d\n", eval_poly(p1, x));
	printf("�ι�° ���׽� ����� : %d\n", eval_poly(p2, x));
	printf("��� ���׽� ����� : %d\n", eval_poly(p, x));
	free(p1);
	free(p2);
	free(p);
	return 0;
}

int get_poly(int** p) {
	char s[100];
	int count = 0;
	int m = 0; // ���� �Ǻ�
	printf("���׽��� �Է��ϼ���. : ");
	gets(s);
	for (int i = 1; s[i] != '\0'; i++) { // �� ���� ������ ��츦 ���, �ι�° �׺��� üũ�Ѵ�.
		if (s[i] == '+' || s[i] == '-') // �������� ������ ����.
			count++;
	}
	count++; // �ǿ������� ���� �������� ���� +1 �̴�.
	*p = (int*)malloc(sizeof(int)*count); // ���׽��� ��� ����.
	*(p + 1) = (int*)malloc(sizeof(int)*count); // ���׽��� ���� ����.
	count = 0; // ���� ������ �ǹ��ϴ� count ������ �ٽ� 0���� �ʱ�ȭ.
	for (int i = 0; s[i] > 0; i++) {
		if (s[i] == '-') {
			m = 1;
			i++;
		}
		if (s[i] > 47 && s[i] < 58) { // ���ڸ� ��Ͻ�Ų��.
			*(*(p + 0) + count) = s[i] - 48;
			i++;
			for (; s[i] > 47 && s[i] < 58; i++) {
				*(*(p + 0) + count) = *(*(p + 0) + count) * 10 + s[i] - 48;
			}
		}
		else // ����� ���� ��� 1�� ����
			*(*(p + 0) + count) = 1;
		if (m == 1) { // ����� �������
			*(*(p + 0) + count) *= -1;
			m = 0;
		}
		if (s[i] == 'x') {
			*(*(p + 1) + count) = 1; // ����� ���� ���� ���� ���� 1�� ����.
			i++;
			if (s[i] == '^') { // ������ �ִٸ� ������ ����Ѵ�.
				i++;
				*(*(p + 1) + count) = s[i] - 48;
				for (++i; s[i] > 47 && s[i] < 58; i++) {
					*(*(p + 1) + count) = *(*(p + 1) + count) * 10 + s[i] - 48;
				}
			}
			else // x�ڿ� ����ǥ�� '^'�� ���ٸ� x�� 1�����̴�.
				*(*(p + 1) + count) = 1;
		}
		else if (s[i] == '+')
			count++; // ��� üũ �� �����ڸ� �߰��ϸ� �������� üũ�Ѵ�.
		else if (s[i] == '\0') {
			*(*(p + 1) + count) = 0; // x������ ���� ������ ������� Ȯ��.
			break;
		}
		if (s[i] == '+') // ���� üũ �� �����ڸ� �߰��ϸ� �������� üũ�Ѵ�.
			count++;
		if (s[i] == '-') {
			count++;
			if (i == 0)
				count--;
			m = 1;
		}
	}
	return count + 1; // �޸� ������ ���� ���� ���� ��ȯ.
}
void print_poly(int** p, int count_p) {
	for (int i = 0; i < count_p; i++) {
		if (*(*(p + 1) + i) == 0) {// ����� ���
			printf("%d", *(*(p + 0) + i));
			break; // ������� ����� �� ��� ����.
		}
		else if (*(*(p + 1) + i) == 1) {// 1���� ���
			if (*(*(p + 0) + i) == 1) // ����� 1�� ��� x�� ���
				printf("x");
			else
				printf("%dx", *(*(p + 0) + i));
		}
		else {// ������ ������ ���
			if (*(*(p + 0) + i) == 1) // ����� 1�� ��� x�� ���
				printf("x^%d", *(*(p + 1) + i));
			else
				printf("%dx^%d", *(*(p + 0) + i), *(*(p + 1) + i));
		}
		if (i + 1 < count_p && *(*(p + 0) + i + 1) > 0 ) // ������ ����� ��� �� +�� ������� �ʱ� ����.
			printf("+");
	}
	printf("\n");
}


int sub_poly(int** p, int** p2, int** p3) {
	int p_pos = 0; // p �迭�� ��ġüũ ����
	int p2_pos = 0; // p2 �迭�� ��ġüũ ����
	int p3_pos = 0; // p3 �迭�� ��ġüũ ����
	while (1) { // �ݺ���Ų��.
		if (*(*(p2 + 1) + p2_pos) == 0 && *(*(p3 + 1) + p3_pos) == 0) { //�� �� ������̶��
			*(*(p + 1) + p_pos) = 0; // ������ 0, �����
			*(*(p + 0) + p_pos) = *(*(p2 + 0) + p2_pos) - *(*(p3 + 0) + p3_pos);// ����� ���ϱ�.
			break; // ����ױ��� ���� �� ���� ����.
		}
		else if (*(*(p3 + 1) + p3_pos) == *(*(p2 + 1) + p2_pos)) { // p2,p3�� ������ 0�� �ƴϰ� ���� ��,
			*(*(p + 1) + p_pos) = *(*(p2 + 1) + p2_pos); // ����迭�� p2 ���� ���� ����
			*(*(p + 0) + p_pos) = *(*(p2 + 0) + p2_pos) - *(*(p3 + 0) + p3_pos); // ��� �迭�� p2,p3�� �� ���� ����.
			p_pos++;// ��� �迭 ����������
			p2_pos++;// p2�迭 ����������
			p3_pos++;// p3�迭 ����������
		}
		else if (*(*(p2 + 1) + p2_pos) > *(*(p3 + 1) + p3_pos)) { // p2 �迭�� ������ �� ���ٸ�
			*(*(p + 1) + p_pos) = *(*(p2 + 1) + p2_pos); // ��� �迭�� p2�� ���� ���� ����.
			*(*(p + 0) + p_pos) = *(*(p2 + 0) + p2_pos); // ��� �迭�� p2�� ��� ���� ����.
			p_pos++; // ��� �迭 ����������
			p2_pos++; // p2�迭 ����������
		}
		else if (*(*(p3 + 1) + p3_pos) > *(*(p2 + 1) + p2_pos)) { // p3 �迭�� ������ �� ���ٸ�
			*(*(p + 1) + p_pos) = *(*(p3 + 1) + p3_pos) ; // ��� �迭�� p3�� ���� ���� ����.
			*(*(p + 0) + p_pos) = *(*(p3 + 0) + p3_pos) * -1 ; // ��� �迭�� p3�� ��� ���� ������ ����.
			p_pos++; // ��� �迭 ����������
			p3_pos++; // p2�迭 ����������
		}
	}
	return p;
}


int eval_poly(int** p, int x) {
	int i, result = 0;
	int mul = 1; // ���� ���� ���� ����
	for (i = 0; *(*(p + 1) + i) > 0; i++) { // ����迭�� ����� ������ ���
		for (int j = 0; j < *(*(p + 1) + i); j++)
			mul *= x; // ������ŭ x�� ���Ѵ�.
		result += *(*(p + 0) + i) * mul; // ������ŭ x���� ���� �� ����� ���� ������� ���Ѵ�.
		mul = 1; // �������� ����� ������ �ٽ� 1�� �ʱ�ȭ�Ѵ�.
	}
	result += *(*(p + 0) + i); // ������� �����ش�.
	return result;
}
