#include<stdio.h>
#define MAX_SIZE 20
#define true 1
#define false 0

typedef struct {
	int stack[MAX_SIZE];
	int top;
}stack_type;

typedef stack_type* stack_type_ptr;


// stack�� ����ϴ� �Լ�
void init(stack_type_ptr exp); // stack �ʱ�ȭ �Լ�
void push(stack_type_ptr exp, int item); // stack �߰� �Լ�
int pop(stack_type_ptr exp); // stack �� ���� �Լ�
int is_empty(stack_type exp); // stack�� ��� �ִ��� �˻�
int is_full(stack_type exp); // stack�� ���� �ִ��� �˻�


int menu(); // �޴��� ���� ������ ����ִ� �Լ�
int get_exp(exp); // ����ڿ��� �������� �Է¹޴� �Լ�
void postfix(exp,pexp); // �������� ���������� �������ִ� �Լ�
char get_symbol(char s[]); // ȣ��� ������ �迭�� ���� ���Ҹ� ��ȯ�ϴ� �Լ�
int eval(char *exp); // �����Ŀ� ���� ���� ������ִ� �Լ�
void display(exp, pexp, res); // ����� ������ִ� �Լ�


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
	printf("** ����� �����ϰ� ������ end�� �Է��ϼ���. **\n�������� �Է����ּ���: ");
	return false; // �ݺ��� or ��� ���� false ��ȯ.
}

int get_exp(char *exp) {
	gets(exp);
	if (strcmp(exp, "end"))
		return true;
	return false; // end �Է¹��� �� false ��ȯ
}

char get_symbol(char s[]) {
	static int pos = 0; // �ε�����
	if (pos < strlen(s)) {
		while (s[pos] == 32) // ������ �ƴ� ������
			pos++; // �ε��� �� �߰�
		return s[pos++]; // ��� �� �ε��� �� �߰�
	}
	return false;
}

void postfix(char exp[],char pexp[]) {
	stack_type st;
	init(&st);
	int num = 0;
	char check; // �迭�� ���� ������ ����.
	
	for (int i = 0; (check = exp[i]) != false; i++) {
		if (check > '0' && check < '9')
			pexp[num++] = check;
		else {
			if (check == '(') // �°�ȣ �߰� �� ���ÿ� �߰�
				push(&st, check);
			else if (check == ')') {
				while ((check = pop(&st)) != '(') // ���ȣ �߰� �� �°�ȣ���� ���ð� �迭�� �߰�
					pexp[num++] = check;
			}
			else if ((check == '+') || (check == '-')) { // +�� - �߽߰�
				if (is_empty(st) || (st.stack[st.top] == '(')) // ������ ������ְų� ù���� �°�ȣ���
					push(&st, check); // ���ÿ� �߰�
				else { // �����ڰ� top�̶��
					pexp[num++] = pop(&st); // stack�� �迭�� �߰�
					push(&st, check); // ������ stack�� �߰�
				}
			}
			else{
				if (is_empty(st) || (st.stack[st.top] == '(')) // ������ ������ְų� ù���� �°�ȣ���
					push(&st, check); // ���ÿ� �߰�
				else { // �����ڸ� ������ ���
					if ((st.stack[st.top] == '+') || (st.stack[st.top] == '-')) { // �켱������ ���ٸ�
						push(&st, check); // stack�� �߰�
					}
					else{ // �켱������ ���ų� ���ٸ�
						pexp[num++] = pop(&st); // stack�� �迭�� �߰�
						push(&st, check); // ������ stack�� �߰�
					}
				}
			}
		}
	}
	while ((check = pop(&st)) != false) // stack�� �����ִ� ���� �ִٸ�
		pexp[num++] = check; // ���ʷ� �迭�� �߰��Ѵ�.
	pexp[num] = 0; // �迭�� �������� ���ڿ� ���� �߰��Ѵ�.
}

int eval(char *exp) {
	stack_type st;
	init(&st);
	int a, b;

	for (int i = 0; exp[i] != 0; i++) {
		if (exp[i] > '0' && exp[i] < '9') // ���� �߽߰�
			push(&st, (exp[i] - '0'));
		else if (exp[i] == '+') { // ���ϱ� �߰� ��
			b = pop(&st);
			a = pop(&st);
			push(&st,(a+b));
		}
		else if (exp[i] == '-') { // ���� �߰� ��
			b = pop(&st);
			a = pop(&st);
			push(&st, (a - b));
		}
		else if (exp[i] == '*') { // ���ϱ� �߰� ��
			b = pop(&st);
			a = pop(&st);
			push(&st, (a * b));
		}
		else if (exp[i] == '/') { // ������ �߰� ��
			b = pop(&st);
			a = pop(&st);
			push(&st, (a / b));
		}
		else if (exp[i] == '%') { // ������ ���� �߰� ��
			b = pop(&st);
			a = pop(&st);
			push(&st, (a % b));
		}
	}
	return pop(&st); // ���� �� ��ȯ
}

void display(char exp[], char pexp[], int res) {
	printf("���� �� ������ : %s\n���� �� ������ : %s\n����� : %d\n", exp, pexp, res);
}