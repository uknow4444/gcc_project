#include<stdio.h>
#include<string.h>
#define MAX 44
#define true 1
#define false 0


typedef struct node* nodeptr;
typedef struct node {
	char data;
	nodeptr left,right;
}node;


typedef struct stack {
	nodeptr st[MAX];
	int top;
}stack;


void input(char* arr); // 사용자에게 중위식 입력받기.
int full(stack stk); // 스택이 가득 찼는지.
int empty(stack stk); // 스택이 비었는지.
void init(stack* stk); // 스택 초기화
void push(stack* stk, char data); // 스택 추가 - DATA값을 노드로 만들어서 추가
nodeptr pop(stack* stk); // 스택에서 꺼내기
stack* make_pexp(char* exp); // 후위식을 만드는 함수.
nodeptr create_node(char c); // 노드 생성함수
int check(nodeptr node); // 노드의 DATA값이 숫자인지 체크하는 함수
void node_push(stack* stk, nodeptr no); // 노드를 스택에 추가하는 함수
nodeptr make_tree(stack stk); // 후위식 트리 만들기
int result_tree(nodeptr root); // 후위식 트리로 결과 구하기
void display_stk(stack stk); // 후위식 출력함수.

int main() {
	char exp[MAX];
	stack* stk;
	nodeptr root;

	input(exp); // 식 입력받기

	stk = make_pexp(exp);

	root = make_tree(*stk);
	printf("%d\n",result_tree(root));

	return 0;
}


void input(char* arr) {
	printf("계산할 식을 입력해 주세요. : ");
	gets(arr);
}
void init(stack* stk) {
	stk->top = -1;
}
int full(stack stk) {
	if (stk.top == MAX - 1)
		return true;
	else
		return false;
}
int empty(stack stk) {
	if (stk.top < 0)
		return true;
	else
		return false;
}
void push(stack* stk, char data) {
	if (!full(*stk)) {
		stk->st[++(stk->top)] = create_node(data);
	}
}
nodeptr pop(stack* stk) {
	if (!empty(*stk))
		return stk->st[(stk->top)--];
	else
		return NULL;
}

nodeptr create_node(char c) {
	nodeptr re_node = (nodeptr)malloc(sizeof(node));
	re_node->data = c;
	re_node->left = NULL;
	re_node->right = NULL;
	return re_node;
}

stack* make_pexp(char* exp) {
	stack sub,stk;
	init(&sub); // sub 스택 init
	init(&stk); // 메인 스택 init
	nodeptr c_sub; // 스택에 저장된 연산자를 임시 저장할 포인터
	for (int i = 0; i < strlen(exp); i++) {
		if ('1' <= exp[i] && '9' >= exp[i]) { // 숫자라면
			push(&stk,exp[i]);
		}
		else { // 연산자들
			if (exp[i] == '(') { // 왼쪽 괄호 발견시 SUB 스택에 추가
				push(&sub, exp[i]);
			}
			else if (exp[i] == '*' || exp[i] == '/') {
				if (!empty(sub)) { // sub가 비워져있지 않다면
					c_sub = pop(&sub);
					if (c_sub->data == '*' || c_sub->data == '/') {
						push(&stk, c_sub->data);
						push(&sub, exp[i]);
					}
					else { // 전 연사자가 (+-일 경우
						push(&sub, c_sub->data);
						push(&sub, exp[i]);
					}
					
				}
				else // sub가 비워져 있다면
					push(&sub, exp[i]);
			}
			else if (exp[i] == '+' || exp[i] == '-') {
				if (!empty(sub)) {
					c_sub = pop(&sub);
					if (c_sub->data == '*' || c_sub->data == '/' || c_sub->data == '+' || c_sub->data == '-') {
						push(&stk, c_sub->data);
						push(&sub, exp[i]);
					}
					else {// 전 연사자가 (일 경우
						push(&sub, c_sub->data);
						push(&sub, exp[i]);
					}
				}
				else // 연산자가 비워져있다면
					push(&sub, exp[i]);
			}
			else {// )괄호 발견시
				c_sub = pop(&sub);
				while ('(' != c_sub->data) {
					push(&stk, c_sub->data); // ( 괄호까지 연산자 모두 넣기
					c_sub = pop(&sub);
				}
			}
		}
	}
	while (sub.top > -1) {
		c_sub = pop(&sub);
		push(&stk, c_sub->data);
	}
	display_stk(stk);
	return &stk;
}

int check(nodeptr no) {
	if (no->data > 48 && no->data < 58)
		return true;
	else
		return false;
}
void node_push(stack* stk, nodeptr no) {
	if (!full(*stk))
		stk->st[++(stk->top)] = no;
}
nodeptr make_tree(stack stk) {
	nodeptr root = stk.st[stk.top]; // 현재 stack의 top을 root로
	nodeptr ro, no1, no2;
	stack sub;
	init(&sub);
	ro = pop(&stk);
	while (!empty(stk)) {
		no1 = pop(&stk);
		no2 = pop(&stk);
		if (no2 == NULL || ro->left != NULL) { // 마지막 1개씩 추가하는 경우
			ro->right = no1;
			if(no2 != NULL)
				node_push(&stk, no2);
			ro = pop(&sub);
		}
		else if (check(no1) && check(no2)) {
			ro->left = no1;
			ro->right = no2;
			ro = pop(&sub);
		}
		else if (!check(no1)) {//no1이 연산자인 경우
			ro->left = no1;
			node_push(&sub, ro); // 현재 루트 스택에 저장
			node_push(&stk, no2); // 꺼낸 값 다시 스택으로
			ro = no1;
		}
		else if (!check(no2)) {//no2만 연산자인 경우
			ro->left = no1;
			ro->right = no2;
			ro = no2; // ro는 no2로
		}	
	}
	return root;
}


int result_tree(nodeptr root) {
	int a, b;
	if (root->left != NULL)
		a = result_tree(root->left);
	if (root->right != NULL)
		b = result_tree(root->right);
	if (root->left == NULL && root->right == NULL) // 둘다 NULL이면
		return (root->data-48); // 데이타 반환
	if (root->data == '*')
		return (a * b);
	else if (root->data == '/')
		return (b / a);
	else if (root->data == '+')
		return (a + b);
	else if (root->data == '-')
		return (b - a);
}
void display_stk(stack stk) { 
	for (int i = 0; i < stk.top+1; i++) {
		printf("%c", stk.st[i]->data);
	}
	printf("\n");
}