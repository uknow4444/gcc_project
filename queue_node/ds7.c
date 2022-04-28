#include<stdio.h>
#include<stdlib.h>
#define MAX_QUEUE_SIZE 5
#define true 1
#define false 0


typedef int element;
typedef struct node* nodeptr;
typedef struct node{
	element data;
	nodeptr link;
}node;

typedef struct QueueType* QueueTypePtr;
typedef struct QueueType {
	nodeptr front;
	nodeptr rear;
}QueueType;



void init(q);
nodeptr create_node(data);
void enqueue(q, item);
int dequeue(q);
int is_empty(q);
void display(q);



int main() {
	QueueType q;
	init(&q);
	enqueue(&q, 1);
	enqueue(&q, 2);
	dequeue(&q);
	enqueue(&q, 3);
	enqueue(&q, 4);
	dequeue(&q);
	enqueue(&q, 5);
	enqueue(&q, 6);
	display(q);

	return 0;
}


void init(QueueType* q) {
	q->front = NULL;
	q->rear = NULL;
}

nodeptr create_node(int data) {
	nodeptr re_node=(nodeptr)malloc(sizeof(node));
	re_node->data = data;
	re_node->link = NULL;
	return re_node;
}


void enqueue(QueueType* q, int item) {
	nodeptr no = create_node(item);
	if (!is_empty(*q)) {
		q->rear->link = no;
		q->rear = no;
		q->rear->link = q->front;
	}
	else {
		q->front = no;
		q->rear = no;
		q->rear->link = q->front;
	}
}

element dequeue(QueueType* q) {
	if (!is_empty(*q)) {
		nodeptr no = q->front;
		element re = no->data;
		if (q->front == q->rear) {
			q->front = NULL;
			q->rear = NULL;
		}
		else {
			q->front = q->front->link;
			q->rear->link = q->front;
		}
		free(no);
		return re;
	}
	else
		printf("큐가 비어있습니다.\n");
}

int is_empty(QueueType q) {
	if (q.front == NULL)
		return true;
	else
		return false;
}

void display(QueueType q) {
	nodeptr qptr = q.front;
	if (!is_empty(q)) {
		do {
			printf("%d ", qptr->data);
			qptr = qptr->link;
		} while (qptr != q.front);
		printf("\n");
	}
	else
		printf("비어있구나!!!!!\n");
	/*
	while(!is_empty(q))
		printf("%d ", dequeue(&q));
	이런 식으로 dequeue를 사용한 출력도 가능
	*/

}