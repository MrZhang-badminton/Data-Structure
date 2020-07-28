#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define FALSE 0
#define TRUE 1

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

/*----------------------------判断树的类型----------------------------------------*/ 
int Max(int a,int b){
	return a > b ? a : b; 
}

int GetHeight(BinTree T){
	int a , b;
	if(!T)return 0;
	a = GetHeight(T->left);
	b = GetHeight(T->right);
	
	return Max(a,b) + 1;
} 

int GetBalanceFactor(BinTree T1, BinTree T2){
	return GetHeight(T1) - GetHeight(T2);
} 

BinTree FindMin(BinTree T){
	if(!T) return NULL;
	while(T->left)
		T = T->left;
	return T;
}

BinTree FindMax(BinTree T){
	if(!T) return NULL;
	while(T->right)
		T = T->right;
	return T;
}

/*------------------判断树是否平衡  注：并非判断是否为平衡二叉树 ---------------*/
int IsAverage(BinTree T){
	int a, b;
	int balanceFactor;
	if(!T) return TRUE;
	
	a = IsAverage(T->left);
	b = IsAverage(T->right);
	if(a == FALSE || b == FALSE)
		return FALSE;
	
	balanceFactor = GetBalanceFactor(T->left, T->right);
	return (balanceFactor >= 2) || (balanceFactor <= -2) ? FALSE : TRUE;
}

/*--------------------------判读是否是二叉排序树------------------------------*/ 
int IsBinSearchTree(BinTree T){
	BinTree tmpTree,tmpTree2;
	
	if(!T) return TRUE;
	if(IsBinSearchTree(T->left) == FALSE || IsBinSearchTree(T->right) == FALSE)
		return FALSE;
	if(NULL == T->left && NULL == T->right){ 
	//左右子树都为NULL
	//则当前节点为根的树平衡，返回TRUE
		return TRUE;
	} else if(NULL == T->left && NULL != T->right){
	//左子树为NULL，右子树非空
		tmpTree = FindMin(T->right);
		if(T->data <= tmpTree->data)
			return TRUE;
		else
			return FALSE;
	}else if(NULL != T->left && NULL == T->right){
	//左子树非空，右子树为NULL
		tmpTree = FindMax(T->left);
		if(T->data >= tmpTree->data)
			return TRUE;
		else
			return FALSE;
	}else{
	//左右子树皆非空
		tmpTree = FindMax(T->left);
		tmpTree2 = FindMin(T->right);
		if(tmpTree->data <= T->data && T->data <= tmpTree2->data)
			return TRUE;
		else
			return FALSE;
	}
}

/*-------------------------判断是否是AVL树---------------------------*/ 
int IsAVLTree(BinTree T){
	if(IsBinSearchTree(T) && IsAverage(T))
		return TRUE;
	return FALSE;
}

int main() {
	BinTree T;
	T = CreateBinTree();
	LevelTravel(T);
	printf("\nThe height is: %d\n", GetHeight(T));
	/*if(IsAverage(T)){
		printf("The tree is Average !\n");
	}else{
		printf("The tree is not Average !\n");
	}
	if(IsBinSearchTree(T)){
		printf("The tree is BinSearchTree !\n");
	}else{
		printf("The tree is not BinSearchTree !\n");
	}*/
	
	if(IsAVLTree(T))
		printf("The tree is AVLTree ! \n");
	else
		printf("The tree is not AVLTree ! \n");
}

