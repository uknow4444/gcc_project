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


void input(char* arr); // ����ڿ��� ������ �Է¹ޱ�.
int full(stack stk); // ������ ���� á����.
int empty(stack stk); // ������ �������.
void init(stack* stk); // ���� �ʱ�ȭ
void push(stack* stk, char data); // ���� �߰� - DATA���� ���� ���� �߰�
nodeptr pop(stack* stk); // ���ÿ��� ������
stack* make_pexp(char* exp); // �������� ����� �Լ�.
nodeptr create_node(char c); // ��� �����Լ�
int check(nodeptr node); // ����� DATA���� �������� üũ�ϴ� �Լ�
void node_push(stack* stk, nodeptr no); // ��带 ���ÿ� �߰��ϴ� �Լ�
nodeptr make_tree(stack stk); // ������ Ʈ�� �����
int result_tree(nodeptr root); // ������ Ʈ���� ��� ���ϱ�
void display_stk(stack stk); // ������ ����Լ�.

int main() {
	char exp[MAX];
	stack* stk;
	nodeptr root;

	input(exp); // �� �Է¹ޱ�

	stk = make_pexp(exp);

	root = make_tree(*stk);
	printf("%d\n",result_tree(root));

	return 0;
}


void input(char* arr) {
	printf("����� ���� �Է��� �ּ���. : ");
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
	init(&sub); // sub ���� init
	init(&stk); // ���� ���� init
	nodeptr c_sub; // ���ÿ� ����� �����ڸ� �ӽ� ������ ������
	for (int i = 0; i < strlen(exp); i++) {
		if ('1' <= exp[i] && '9' >= exp[i]) { // ���ڶ��
			push(&stk,exp[i]);
		}
		else { // �����ڵ�
			if (exp[i] == '(') { // ���� ��ȣ �߽߰� SUB ���ÿ� �߰�
				push(&sub, exp[i]);
			}
			else if (exp[i] == '*' || exp[i] == '/') {
				if (!empty(sub)) { // sub�� ��������� �ʴٸ�
					c_sub = pop(&sub);
					if (c_sub->data == '*' || c_sub->data == '/') {
						push(&stk, c_sub->data);
						push(&sub, exp[i]);
					}
					else { // �� �����ڰ� (+-�� ���
						push(&sub, c_sub->data);
						push(&sub, exp[i]);
					}
					
				}
				else // sub�� ����� �ִٸ�
					push(&sub, exp[i]);
			}
			else if (exp[i] == '+' || exp[i] == '-') {
				if (!empty(sub)) {
					c_sub = pop(&sub);
					if (c_sub->data == '*' || c_sub->data == '/' || c_sub->data == '+' || c_sub->data == '-') {
						push(&stk, c_sub->data);
						push(&sub, exp[i]);
					}
					else {// �� �����ڰ� (�� ���
						push(&sub, c_sub->data);
						push(&sub, exp[i]);
					}
				}
				else // �����ڰ� ������ִٸ�
					push(&sub, exp[i]);
			}
			else {// )��ȣ �߽߰�
				c_sub = pop(&sub);
				while ('(' != c_sub->data) {
					push(&stk, c_sub->data); // ( ��ȣ���� ������ ��� �ֱ�
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
	nodeptr root = stk.st[stk.top]; // ���� stack�� top�� root��
	nodeptr ro, no1, no2;
	stack sub;
	init(&sub);
	ro = pop(&stk);
	while (!empty(stk)) {
		no1 = pop(&stk);
		no2 = pop(&stk);
		if (no2 == NULL || ro->left != NULL) { // ������ 1���� �߰��ϴ� ���
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
		else if (!check(no1)) {//no1�� �������� ���
			ro->left = no1;
			node_push(&sub, ro); // ���� ��Ʈ ���ÿ� ����
			node_push(&stk, no2); // ���� �� �ٽ� ��������
			ro = no1;
		}
		else if (!check(no2)) {//no2�� �������� ���
			ro->left = no1;
			ro->right = no2;
			ro = no2; // ro�� no2��
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
	if (root->left == NULL && root->right == NULL) // �Ѵ� NULL�̸�
		return (root->data-48); // ����Ÿ ��ȯ
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