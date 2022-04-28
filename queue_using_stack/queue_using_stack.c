#include<stdio.h>

#define MAX_SIZE 100

typedef struct { // 스택정의
	int stk[MAX_SIZE];
	int top;
}stack;

void stk_init(stk); // 스택 초기화
int stk_full(stk1); // 스택이 꽉찼는지 체크하는 함수
int stk_empty(stk1); // 스택이 비어있는지 체크하는 함수
void push(stk,data); // 스택을 추가하는 함수
int pop(stk); // 스택에서 원소를 꺼내는 함수

typedef struct { // 큐 정의 - 스택 2개를 사용
	stack stk1;
	stack stk2;
}queue;

void q_init(q); // 큐 초기화
int q_full(q); // 큐가 꽉차있는지 체크하는 함수
int q_empty(q); // 큐가 비어있는지 체크하는 함수
void enqueue(q,data); // 큐에 원소를 추가하는 함수
int dequeue(q); // 큐에서 원소를 꺼내는 함수

int q_fibo(q); // 부를 때마다 피보값 반환


// main 함수
int main() {
	queue q; // 큐 선언
	q_init(&q); // 큐 초기화
	int input; // 사용자에게 입력받기
	printf("피보나치 수열의 개수를 입력해주세요 : ");
	scanf("%d", &input);
	enqueue(&q, 0); // 큐에 초기값 0 추가
	enqueue(&q, 1); // 큐에 초기값 1 추가

	for (int i = 0; i < input; i++)
		printf("%d ", q_fibo(&q)); // 사용자가 입력한만큼 피보 호출

	return 0;
}

// q 초기화
void stk_init(stack *stk) { // 스택 초기화
	stk->top = -1;
}
void q_init(queue *q) { // 큐 초기화
	stk_init(&q->stk1); // 스택1 초기화
	stk_init(&q->stk2); // 스택2 초기화
}

// full 함수
int stk_full(stack stk1) {
	if (stk1.top == MAX_SIZE - 1)
		return 1;
	else
		return 0;
}
int q_full(queue q) {
	return stk_full(q.stk1);
}


//empty 함수
int stk_empty(stack stk1) {
	if (stk1.top < 0)
		return 1;
	else
		return 0;
}
int q_empty(queue q) {
	return stk_empty(q.stk1);
}

// 추가함수
void push(stack *stk, int data) {
	if (!stk_full(*stk))
		stk->stk[++(stk->top)] = data;
}
void enqueue(queue *q, int data) {
	if (!q_full(*q))
		push(&q->stk1, data);
}

// 꺼내기 함수
int pop(stack *stk) {
	if (!stk_empty(*stk))
		return stk->stk[(stk->top)--];
}
int dequeue(queue *q) {
	if (!q_empty(*q)) {
		int re;// 반환할 값을 저장할 변수
		while (!stk_empty(q->stk1)) //스택1이 빌 때까지
			push(&q->stk2, pop(&q->stk1)); // 스택2에 스택1 원소 저장
		re = pop(&q->stk2); // 가장 마지막에 스택2에 저장된 원소 저장
		while(!stk_empty(q->stk2)) // 스택2가 빌 때까지
			push(&q->stk1, pop(&q->stk2)); // 다시 스택1에 스택2 원소 저장
		return re; // 원소 반환
	}
}

// 피보나치 함수
int q_fibo(queue *q) {
	int n1 = dequeue(q); // 첫번째 원소 저장
	int n2 = dequeue(q); // 두번째 원소 저장
	enqueue(q, n2); //  두번째 원소 큐에 추가
	enqueue(q, n2 + n1); // 첫번째 두번째 원소의 덧셈값 큐에 추가
	return n1; // 첫번째 원소값 반환
}