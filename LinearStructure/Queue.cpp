#include<stdio.h>
#include<stdlib.h>


typedef int ElemType;

typedef struct QNode{
	ElemType data;
	struct QNode *next;
}QNode,*Queueptr;

typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQue;

LinkQue * InitQueue(){
	LinkQue *q = (LinkQue *)malloc(sizeof(LinkQue));
	q->front = q->rear = NULL;
	return q;
}

void Enqueue(LinkQue *q, ElemType ele){
	Queueptr p = (Queueptr)malloc(sizeof(QNode));
	if(p == NULL)return;
	p->data = ele;
	p->next = NULL;
	if(q->front == NULL){
		q->front = p;
		q->rear = p;
	}else{
		q->rear->next = p;
		q->rear = p; 
	}
}

int isEmpty(LinkQue *q){
	return q->front == NULL;
}


ElemType Dequeue(LinkQue *q){
	if(isEmpty(q)){
		printf("Error!\n");
		exit(0);
	}
	
	Queueptr p = q->front;
	ElemType temp = q->front->data;
	
	
	if(q->front == q->rear){
		q->front = NULL;
		q->rear = NULL;
	}else{
		q->front = q->front->next;
	}
	free(p);
	return temp;
	
}

int main(){
	LinkQue *que;
	que = InitQueue();
	Enqueue(que,1);
	Enqueue(que,2);
	printf("%d",Dequeue(que));
}
