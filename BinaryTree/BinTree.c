#include<stdio.h>
#include<stdlib.h>
typedef struct Node ElemType;
//二叉树结构 
typedef struct Node{
	int data;
	struct Node *left;
	struct Node *right;
}*BinTree; 
//队列 
typedef struct QNode{
	ElemType val;
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
	p->val = ele;
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
	ElemType temp = q->front->val;
	
	
	if(q->front == q->rear){
		q->front = NULL;
		q->rear = NULL;
	}else{
		q->front = q->front->next;
	}
	free(p);
	return temp;
	
}



//二叉树的实现  初始化和遍历 

void CreateBinTree(BinTree *T){
	int i;
	scanf("%d", &i);
	if(i == -1) 
		*T = NULL;
	else{
		*T = (BinTree)malloc(sizeof(struct Node));
		(*T)->data = i;
		printf("请输入左孩子：如果为空输入-1\n");
		CreateBinTree(&(*T)->left);
		printf("请输入右孩子：如果为空输入-1\n");
		CreateBinTree(&(*T)->right);
	}
	
}

void PreTravel(BinTree T){
	if(T == NULL) return;
	printf("%5d", T->data);
	PreTravel(T->left);
	PreTravel(T->right);
}

void InTravel(BinTree T){
	if(T == NULL) return;
	InTravel(T->left);
	printf("%5d", T->data);
	InTravel(T->right);
}

void PostTravel(BinTree T){
	if(T == NULL) return;
	PostTravel(T->left);
	PostTravel(T->right);
	printf("%5d", T->data);
}

void LevelTravel(BinTree T){
	LinkQue *Q;
	struct Node temp;
	if(!T) return;
	
	Q = InitQueue();
	Enqueue(Q,*T);
	while(!isEmpty(Q)){
		temp = Dequeue(Q);
		printf("%5d",temp.data);
		if(temp.left)Enqueue(Q,*(temp.left));
		if(temp.right)Enqueue(Q,*(temp.right));
	}
}


int Max(int a,int b){
	return a > b ? a : b; 
}

int GetHeight(BinTree T){
	int a , b;
	if(!T)return 0;
	a = GetHeight(T->left);
	b = GetHeight(T->right);
	
	if(((a-b) >= 2) ||((a-b)<= -2)){
		return -1;
	}
	
	return Max(a,b) + 1;
	
} 

int main(){
	int a;
	BinTree Tree;
	printf("请输入头结点:\n"); 
	CreateBinTree(&Tree);
	a = GetHeight(Tree);
	if(a > 0)
		printf("\n是AVL！\n");
	else
		printf("\n不是AVL\n");
	LevelTravel(Tree);
}
