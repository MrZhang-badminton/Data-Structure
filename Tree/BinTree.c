#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
typedef int TElemType;//----------------->TElemType

typedef struct TNode* PtrToTNode;
typedef PtrToTNode BinTree;
struct TNode {
	TElemType data;
	BinTree left;
	BinTree right;
};

typedef BinTree QElemType;//-------------->QElemType 
typedef struct QNode* PtrToQNode;
struct QNode {
	QElemType* elem;
	int front;
	int rear;
};
typedef PtrToQNode Queue;


/*----------------------------Queue--------------------------------------------*/
Queue CreateQueue() {
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->elem = (QElemType*)malloc(sizeof(QElemType) * MAXSIZE);
	Q->front = Q->rear = 0;
	return Q;
}

int IsFull(Queue Q) {
	return (Q->rear + 1) % MAXSIZE == Q->front;
}

void Add(Queue Q,QElemType elem){
	if(elem == NULL) return; 
	if(IsFull(Q)){
		printf("队列已满！\n");
		exit(0); 
	}
	Q->elem[Q->rear] = elem;
	Q->rear = (Q->rear+1) % MAXSIZE;
}

int IsEmpty(Queue Q) {
	return Q->front == Q->rear;
}

QElemType Delete(Queue Q) {
	QElemType temp;
	if (IsEmpty(Q)) {
		printf("队列已空！\n");
		exit(0);
	}
	temp = Q->elem[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return temp;
}

/*---------------------------Tree------------------------------------------*/
BinTree CreateBinTree() {
	BinTree T;
	int i;

	scanf("%d", &i);
	if (i == -1)
		T = NULL;
	else {
		T = (BinTree)malloc(sizeof(struct TNode));
		T->data = i;
		printf("请输入左孩子：如果为空输入-1\n");
		T->left = CreateBinTree();
		printf("请输入右孩子：如果为空输入-1\n");
		T->right = CreateBinTree();
	}
	return T;
}
void PreTravel(BinTree T) {
	if (T) {
		printf("%d ", T->data);
		PreTravel(T->left);
		PreTravel(T->right);
	}
}

void InTraverl(BinTree T) {
	if (T) {
		InTraverl(T->left);
		printf("%d ", T->data);
		InTraverl(T->right);
	}
}

void PostTravel(BinTree T) {
	if (T) {
		PostTravel(T->left);
		PostTravel(T->right);
		printf("%d ", T->data);
	}
}

void LevelTravel(BinTree T) {
	Queue Q;
	PtrToTNode tmpNode;

	if (!T) return;

	Q = CreateQueue();
	Add(Q, T);
	while (!IsEmpty(Q)) {
		tmpNode = Delete(Q);
		printf("%d ", tmpNode->data);
		if (T->left) Add(Q, tmpNode->left);
		if (T->right) Add(Q, tmpNode->right);
	}
}

/*----------------------------IsAVLTree----------------------------------------*/ 
int Max(int a,int b){
	return a > b ? a : b; 
}

//获得树的高度  
int GetHeight(BinTree T){
	int a , b;
	if(!T)return 0;
	a = GetHeight(T->left);
	b = GetHeight(T->right);
	
	return Max(a,b) + 1;
} 

int IsAVLTree(BinTree T){
	int a, b;
	int h1,h2;
	if(!T) return 1;
	
	a = IsAVLTree(T->left);
	b = IsAVLTree(T->right);
	if(a == 0 || b == 0)
		return 0;
	
	h1 = GetHeight(T->left);
	h2 = GetHeight(T->right);
	return (h1 - h2 >= 2) || (h1 - h2 <= -2) ? 0 : 1;
}

int main() {
	BinTree T;
	T = CreateBinTree();
	LevelTravel(T);
	if(IsAVLTree(T)){
		printf("avl!\n");
	}else{
		printf("not avl!\n");
	}
}

