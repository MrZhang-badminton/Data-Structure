#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100


typedef int ElemType;

typedef struct QNode *PtrToQNode;
struct QNode{
	ElemType *elem;
	int front;
	int rear;
}; 
typedef PtrToQNode Que;

Que CreateQueue(){
	Que Q;
	Q = (Que)malloc(sizeof(struct QNode));
	Q->elem = (ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
	Q->front = Q->rear;
	return Q;
}

bool IsFull(Que Q){
	return (Q->rear+1)%MAXSIZE == Q->front;
}

void Add(Que Q,ElemType Elem){
	if(IsFull(Q)){
		printf("队列已满！\n");
		exit(0); 
	}
	Q->elem[Q->rear] = Elem;
	Q->rear = (Q->rear+1)%MAXSIZE;
}

bool IsEmpty(Que Q){
	return Q->front == Q->rear;
}

ElemType Delete(Que Q){
	ElemType temp;
	if(IsEmpty(Q)){
		printf("队列已空！\n");
		exit(0);
	}
	temp = Q->elem[Q->front];
	Q->front = (Q->front+1)%MAXSIZE;
	return temp;
}


int main(){
	Que Q;
	Q = CreateQueue();
	Add(Q,1);
	Add(Q,2);
	printf("%d\n",Delete(Q));
	printf("%d\n",Delete(Q));
}

