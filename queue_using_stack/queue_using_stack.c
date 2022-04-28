#include<stdio.h>

#define MAX_SIZE 100

typedef struct { // ��������
	int stk[MAX_SIZE];
	int top;
}stack;

void stk_init(stk); // ���� �ʱ�ȭ
int stk_full(stk1); // ������ ��á���� üũ�ϴ� �Լ�
int stk_empty(stk1); // ������ ����ִ��� üũ�ϴ� �Լ�
void push(stk,data); // ������ �߰��ϴ� �Լ�
int pop(stk); // ���ÿ��� ���Ҹ� ������ �Լ�

typedef struct { // ť ���� - ���� 2���� ���
	stack stk1;
	stack stk2;
}queue;

void q_init(q); // ť �ʱ�ȭ
int q_full(q); // ť�� �����ִ��� üũ�ϴ� �Լ�
int q_empty(q); // ť�� ����ִ��� üũ�ϴ� �Լ�
void enqueue(q,data); // ť�� ���Ҹ� �߰��ϴ� �Լ�
int dequeue(q); // ť���� ���Ҹ� ������ �Լ�

int q_fibo(q); // �θ� ������ �Ǻ��� ��ȯ


// main �Լ�
int main() {
	queue q; // ť ����
	q_init(&q); // ť �ʱ�ȭ
	int input; // ����ڿ��� �Է¹ޱ�
	printf("�Ǻ���ġ ������ ������ �Է����ּ��� : ");
	scanf("%d", &input);
	enqueue(&q, 0); // ť�� �ʱⰪ 0 �߰�
	enqueue(&q, 1); // ť�� �ʱⰪ 1 �߰�

	for (int i = 0; i < input; i++)
		printf("%d ", q_fibo(&q)); // ����ڰ� �Է��Ѹ�ŭ �Ǻ� ȣ��

	return 0;
}

// q �ʱ�ȭ
void stk_init(stack *stk) { // ���� �ʱ�ȭ
	stk->top = -1;
}
void q_init(queue *q) { // ť �ʱ�ȭ
	stk_init(&q->stk1); // ����1 �ʱ�ȭ
	stk_init(&q->stk2); // ����2 �ʱ�ȭ
}

// full �Լ�
int stk_full(stack stk1) {
	if (stk1.top == MAX_SIZE - 1)
		return 1;
	else
		return 0;
}
int q_full(queue q) {
	return stk_full(q.stk1);
}


//empty �Լ�
int stk_empty(stack stk1) {
	if (stk1.top < 0)
		return 1;
	else
		return 0;
}
int q_empty(queue q) {
	return stk_empty(q.stk1);
}

// �߰��Լ�
void push(stack *stk, int data) {
	if (!stk_full(*stk))
		stk->stk[++(stk->top)] = data;
}
void enqueue(queue *q, int data) {
	if (!q_full(*q))
		push(&q->stk1, data);
}

// ������ �Լ�
int pop(stack *stk) {
	if (!stk_empty(*stk))
		return stk->stk[(stk->top)--];
}
int dequeue(queue *q) {
	if (!q_empty(*q)) {
		int re;// ��ȯ�� ���� ������ ����
		while (!stk_empty(q->stk1)) //����1�� �� ������
			push(&q->stk2, pop(&q->stk1)); // ����2�� ����1 ���� ����
		re = pop(&q->stk2); // ���� �������� ����2�� ����� ���� ����
		while(!stk_empty(q->stk2)) // ����2�� �� ������
			push(&q->stk1, pop(&q->stk2)); // �ٽ� ����1�� ����2 ���� ����
		return re; // ���� ��ȯ
	}
}

// �Ǻ���ġ �Լ�
int q_fibo(queue *q) {
	int n1 = dequeue(q); // ù��° ���� ����
	int n2 = dequeue(q); // �ι�° ���� ����
	enqueue(q, n2); //  �ι�° ���� ť�� �߰�
	enqueue(q, n2 + n1); // ù��° �ι�° ������ ������ ť�� �߰�
	return n1; // ù��° ���Ұ� ��ȯ
}