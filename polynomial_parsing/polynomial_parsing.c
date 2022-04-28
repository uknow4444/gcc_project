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
	printf("첫번째 다항식 : ");
	print_poly(p1, count_p1); // 배열 p1 정상입력 확인.
	printf("두번째 다항식 : ");
	print_poly(p2, count_p2); // 배열 p2 정상입력 확인.

	int** p = (int**)malloc(sizeof(int*) * 2);
	// 메모리 절약을 위해 p1과 p2의 항의 개수 합만큼 배열 p 동적할당.
	*p = (int*)malloc(sizeof(int)*(count_p1 + count_p2)); // 다항식의 계수 저장.
	*(p + 1) = (int*)malloc(sizeof(int)*(count_p1 + count_p2)); // 다항식의 지수 저장.
	p = sub_poly(p, p1, p2);
	printf("결과 다항식 : ");
	print_poly(p, count_p1 + count_p2); // 결과배열 출력

	int x; // 사용자에게 x값을 입력 받을 함수
	printf("x값을 입력하세요. : ");
	scanf("%d", &x);
	printf("첫번째 다항식 결과값 : %d\n", eval_poly(p1, x));
	printf("두번째 다항식 결과값 : %d\n", eval_poly(p2, x));
	printf("결과 다항식 결과값 : %d\n", eval_poly(p, x));
	free(p1);
	free(p2);
	free(p);
	return 0;
}

int get_poly(int** p) {
	char s[100];
	int count = 0;
	int m = 0; // 음수 판별
	printf("다항식을 입력하세요. : ");
	gets(s);
	for (int i = 1; s[i] != '\0'; i++) { // 맨 앞이 음수일 경우를 대비, 두번째 항부터 체크한다.
		if (s[i] == '+' || s[i] == '-') // 연산자의 개수를 샌다.
			count++;
	}
	count++; // 피연산자의 수는 연산자의 개수 +1 이다.
	*p = (int*)malloc(sizeof(int)*count); // 다항식의 계수 저장.
	*(p + 1) = (int*)malloc(sizeof(int)*count); // 다항식의 지수 저장.
	count = 0; // 항의 개수를 의미하는 count 변수를 다시 0으로 초기화.
	for (int i = 0; s[i] > 0; i++) {
		if (s[i] == '-') {
			m = 1;
			i++;
		}
		if (s[i] > 47 && s[i] < 58) { // 숫자를 기록시킨다.
			*(*(p + 0) + count) = s[i] - 48;
			i++;
			for (; s[i] > 47 && s[i] < 58; i++) {
				*(*(p + 0) + count) = *(*(p + 0) + count) * 10 + s[i] - 48;
			}
		}
		else // 계수가 없을 경우 1을 대입
			*(*(p + 0) + count) = 1;
		if (m == 1) { // 계수가 음수라면
			*(*(p + 0) + count) *= -1;
			m = 0;
		}
		if (s[i] == 'x') {
			*(*(p + 1) + count) = 1; // 계수가 없는 항의 지수 값에 1을 대입.
			i++;
			if (s[i] == '^') { // 지수가 있다면 지수를 기록한다.
				i++;
				*(*(p + 1) + count) = s[i] - 48;
				for (++i; s[i] > 47 && s[i] < 58; i++) {
					*(*(p + 1) + count) = *(*(p + 1) + count) * 10 + s[i] - 48;
				}
			}
			else // x뒤에 지수표시 '^'가 없다면 x는 1차항이다.
				*(*(p + 1) + count) = 1;
		}
		else if (s[i] == '+')
			count++; // 계수 체크 후 연산자를 발견하면 다음항을 체크한다.
		else if (s[i] == '\0') {
			*(*(p + 1) + count) = 0; // x차수도 없고 마지막 상수항을 확인.
			break;
		}
		if (s[i] == '+') // 지수 체크 후 연산자를 발견하면 다음항을 체크한다.
			count++;
		if (s[i] == '-') {
			count++;
			if (i == 0)
				count--;
			m = 1;
		}
	}
	return count + 1; // 메모리 절약을 위한 항의 개수 반환.
}
void print_poly(int** p, int count_p) {
	for (int i = 0; i < count_p; i++) {
		if (*(*(p + 1) + i) == 0) {// 상수항 출력
			printf("%d", *(*(p + 0) + i));
			break; // 상수항을 출력할 시 출력 종료.
		}
		else if (*(*(p + 1) + i) == 1) {// 1차항 출력
			if (*(*(p + 0) + i) == 1) // 계수가 1일 경우 x만 출력
				printf("x");
			else
				printf("%dx", *(*(p + 0) + i));
		}
		else {// 나머지 고차항 출력
			if (*(*(p + 0) + i) == 1) // 계수가 1일 경우 x만 출력
				printf("x^%d", *(*(p + 1) + i));
			else
				printf("%dx^%d", *(*(p + 0) + i), *(*(p + 1) + i));
		}
		if (i + 1 < count_p && *(*(p + 0) + i + 1) > 0 ) // 마지막 상수항 출력 후 +를 출력하지 않기 위함.
			printf("+");
	}
	printf("\n");
}


int sub_poly(int** p, int** p2, int** p3) {
	int p_pos = 0; // p 배열의 위치체크 변수
	int p2_pos = 0; // p2 배열의 위치체크 변수
	int p3_pos = 0; // p3 배열의 위치체크 변수
	while (1) { // 반복시킨다.
		if (*(*(p2 + 1) + p2_pos) == 0 && *(*(p3 + 1) + p3_pos) == 0) { //둘 다 상수항이라면
			*(*(p + 1) + p_pos) = 0; // 지수는 0, 상수항
			*(*(p + 0) + p_pos) = *(*(p2 + 0) + p2_pos) - *(*(p3 + 0) + p3_pos);// 상수항 더하기.
			break; // 상수항까지 덧셈 후 루프 종료.
		}
		else if (*(*(p3 + 1) + p3_pos) == *(*(p2 + 1) + p2_pos)) { // p2,p3의 차수가 0이 아니고 같을 때,
			*(*(p + 1) + p_pos) = *(*(p2 + 1) + p2_pos); // 결과배열에 p2 지수 값을 대입
			*(*(p + 0) + p_pos) = *(*(p2 + 0) + p2_pos) - *(*(p3 + 0) + p3_pos); // 결과 배열에 p2,p3의 차 값을 대입.
			p_pos++;// 결과 배열 다음항으로
			p2_pos++;// p2배열 다음항으로
			p3_pos++;// p3배열 다음항으로
		}
		else if (*(*(p2 + 1) + p2_pos) > *(*(p3 + 1) + p3_pos)) { // p2 배열의 차수가 더 높다면
			*(*(p + 1) + p_pos) = *(*(p2 + 1) + p2_pos); // 결과 배열에 p2의 지수 값을 대입.
			*(*(p + 0) + p_pos) = *(*(p2 + 0) + p2_pos); // 결과 배열에 p2의 계수 값을 대입.
			p_pos++; // 결과 배열 다음항으로
			p2_pos++; // p2배열 다음항으로
		}
		else if (*(*(p3 + 1) + p3_pos) > *(*(p2 + 1) + p2_pos)) { // p3 배열의 차수가 더 높다면
			*(*(p + 1) + p_pos) = *(*(p3 + 1) + p3_pos) ; // 결과 배열에 p3의 지수 값을 대입.
			*(*(p + 0) + p_pos) = *(*(p3 + 0) + p3_pos) * -1 ; // 결과 배열에 p3의 계수 값의 음수를 대입.
			p_pos++; // 결과 배열 다음항으로
			p3_pos++; // p2배열 다음항으로
		}
	}
	return p;
}


int eval_poly(int** p, int x) {
	int i, result = 0;
	int mul = 1; // 지수 곱에 쓰일 변수
	for (i = 0; *(*(p + 1) + i) > 0; i++) { // 결과배열에 상수항 전까지 계산
		for (int j = 0; j < *(*(p + 1) + i); j++)
			mul *= x; // 지수만큼 x를 곱한다.
		result += *(*(p + 0) + i) * mul; // 지수만큼 x값을 곱한 후 계수를 곱해 결과값에 더한다.
		mul = 1; // 지수곱을 계산할 변수를 다시 1로 초기화한다.
	}
	result += *(*(p + 0) + i); // 상수항을 더해준다.
	return result;
}
