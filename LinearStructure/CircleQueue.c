#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100

typedef int QElemType;

typedef struct QNode *PtrToQNode;
struct QNode{
	QElemType *elem;
	int front;
	int rear;
}; 
typedef PtrToQNode Queue;

Queue CreateQueue(){
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->elem = (QElemType*)malloc(sizeof(QElemType) * MAXSIZE);
	Q->front = Q->rear;
	return Q;
}

int IsFull(Queue Q){
	return (Q->rear+1) % MAXSIZE == Q->front;
}

void Add(Queue Q,QElemType elem){
	//确保elem不为NULL
	//实际运用过程中，将NULL入队会带来不必要的麻烦 
	if(elem == NULL) return;  
	if(IsFull(Q)){
		printf("队列已满！\n");
		exit(0); 
	}
	Q->elem[Q->rear] = elem;
	Q->rear = (Q->rear+1) % MAXSIZE;
}

int IsEmpty(Queue Q){
	return Q->front == Q->rear;
}

QElemType Delete(Queue Q){
	QElemType temp;
	if(IsEmpty(Q)){
		printf("队列已空！\n");
		exit(0);
	}
	temp = Q->elem[Q->front];
	Q->front = (Q->front+1) % MAXSIZE;
	return temp;
}
 
void MakeEmpty(Queue Q){
	while(!IsEmpty(Q))
		Delete(Q);
} 

int main(){
	Queue Q;
	Q = CreateQueue();
	Add(Q,1);
	Add(Q,2);
	//MakeEmpty(Q);
	printf("%d\n",Delete(Q));
	printf("%d\n",Delete(Q));
	printf("%d\n",Delete(Q));
}

