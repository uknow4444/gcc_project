#include<stdio.h>
#define MAX_SIZE 20
#define true 1
#define false 0

typedef struct {
	int stack[MAX_SIZE];
	int top;
}stack_type;

typedef stack_type* stack_type_ptr;


// stack에 사용하는 함수
void init(stack_type_ptr exp); // stack 초기화 함수
void push(stack_type_ptr exp, int item); // stack 추가 함수
int pop(stack_type_ptr exp); // stack 값 추출 함수
int is_empty(stack_type exp); // stack이 비어 있는지 검사
int is_full(stack_type exp); // stack이 꽉차 있는지 검사


int menu(); // 메뉴에 대한 내용을 띄워주는 함수
int get_exp(exp); // 사용자에게 중위식을 입력받는 함수
void postfix(exp,pexp); // 중위식을 후위식으로 변경해주는 함수
char get_symbol(char s[]); // 호출될 때마다 배열의 다음 원소를 반환하는 함수
int eval(char *exp); // 후위식에 대한 값을 계산해주는 함수
void display(exp, pexp, res); // 결과를 출력해주는 함수


int main() {
	char exp[MAX_SIZE];
	char pexp[MAX_SIZE];
	int res;

	while (menu() || get_exp(exp)) {
		postfix(exp, pexp);
		res = eval(pexp);
		display(exp, pexp, res);
	}
	return 0;
}



void init(stack_type_ptr s) {
	s->top = -1;
}

void push(stack_type_ptr s, int item) {
	if (!is_full(*s)) {
		s->stack[++(s->top)] = item;
	}
}

int pop(stack_type_ptr s) {
	if (!is_empty(*s))
		return s->stack[(s->top)--];
	return false;
}

int is_empty(stack_type s) {
	if (s.top < 0)
		return true;
	else
		return false;
}

int is_full(stack_type s) {
	if (s.top == MAX_SIZE - 1)
		return true;
	else
		return false;
}


int menu() {
	printf("** 사용을 중지하고 싶으면 end를 입력하세요. **\n중위식을 입력해주세요: ");
	return false; // 반복문 or 제어를 위한 false 반환.
}

int get_exp(char *exp) {
	gets(exp);
	if (strcmp(exp, "end"))
		return true;
	return false; // end 입력받을 시 false 반환
}

char get_symbol(char s[]) {
	static int pos = 0; // 인덱스값
	if (pos < strlen(s)) {
		while (s[pos] == 32) // 공백이 아닐 때까지
			pos++; // 인덱스 값 추가
		return s[pos++]; // 출력 후 인덱스 값 추가
	}
	return false;
}

void postfix(char exp[],char pexp[]) {
	stack_type st;
	init(&st);
	int num = 0;
	char check; // 배열의 값을 저장할 변수.
	
	for (int i = 0; (check = exp[i]) != false; i++) {
		if (check > '0' && check < '9')
			pexp[num++] = check;
		else {
			if (check == '(') // 좌괄호 발견 시 스택에 추가
				push(&st, check);
			else if (check == ')') {
				while ((check = pop(&st)) != '(') // 우괄호 발견 시 좌괄호까지 스택값 배열에 추가
					pexp[num++] = check;
			}
			else if ((check == '+') || (check == '-')) { // +나 - 발견시
				if (is_empty(st) || (st.stack[st.top] == '(')) // 스택이 비어져있거나 첫값이 좌괄호라면
					push(&st, check); // 스택에 추가
				else { // 연산자가 top이라면
					pexp[num++] = pop(&st); // stack값 배열에 추가
					push(&st, check); // 연산자 stack에 추가
				}
			}
			else{
				if (is_empty(st) || (st.stack[st.top] == '(')) // 스택이 비어져있거나 첫값이 좌괄호라면
					push(&st, check); // 스택에 추가
				else { // 연산자를 만났을 경우
					if ((st.stack[st.top] == '+') || (st.stack[st.top] == '-')) { // 우선순위가 낮다면
						push(&st, check); // stack에 추가
					}
					else{ // 우선순위가 같거나 높다면
						pexp[num++] = pop(&st); // stack값 배열에 추가
						push(&st, check); // 연산자 stack에 추가
					}
				}
			}
		}
	}
	while ((check = pop(&st)) != false) // stack에 남아있는 것이 있다면
		pexp[num++] = check; // 차례로 배열에 추가한다.
	pexp[num] = 0; // 배열의 마지막에 문자열 끝을 추가한다.
}

int eval(char *exp) {
	stack_type st;
	init(&st);
	int a, b;

	for (int i = 0; exp[i] != 0; i++) {
		if (exp[i] > '0' && exp[i] < '9') // 숫자 발견시
			push(&st, (exp[i] - '0'));
		else if (exp[i] == '+') { // 더하기 발견 시
			b = pop(&st);
			a = pop(&st);
			push(&st,(a+b));
		}
		else if (exp[i] == '-') { // 빼기 발견 시
			b = pop(&st);
			a = pop(&st);
			push(&st, (a - b));
		}
		else if (exp[i] == '*') { // 곱하기 발견 시
			b = pop(&st);
			a = pop(&st);
			push(&st, (a * b));
		}
		else if (exp[i] == '/') { // 나누기 발견 시
			b = pop(&st);
			a = pop(&st);
			push(&st, (a / b));
		}
		else if (exp[i] == '%') { // 나머지 연산 발견 시
			b = pop(&st);
			a = pop(&st);
			push(&st, (a % b));
		}
	}
	return pop(&st); // 연산 값 반환
}

void display(char exp[], char pexp[], int res) {
	printf("변경 전 중위식 : %s\n변경 후 후위식 : %s\n결과값 : %d\n", exp, pexp, res);
}