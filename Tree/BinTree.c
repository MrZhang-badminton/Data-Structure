#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define FALSE 0
#define TRUE 1
#define OVERFLOW -1

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

void Add(Queue Q, QElemType elem) {
	//if(elem == NULL) return; 
	if (IsFull(Q)) {
		printf("队列已满！\n");
		exit(0);
	}
	Q->elem[Q->rear] = elem;
	Q->rear = (Q->rear + 1) % MAXSIZE;
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

/*----------------------------Stack---------------------------------------*/
typedef BinTree ElemType;
typedef struct SNode* PtrToSNode;
struct SNode {
	ElemType data;
	PtrToSNode next;
};
typedef PtrToSNode Stack;

Stack CreateStack() {
	Stack S;
	S = (Stack)malloc(sizeof(struct SNode));
	S->next = NULL;
	return S;
}

int IsStackEmpty(Stack S) {
	return S->next == NULL;
}

int Push(Stack S, ElemType elem) {
	PtrToSNode tmpCell;
	tmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
	if (!tmpCell) exit(OVERFLOW);
	tmpCell->data = elem;
	tmpCell->next = S->next;
	S->next = tmpCell;
	return TRUE;
}

ElemType Pop(Stack S) {
	PtrToSNode firstCell;
	ElemType tmp;
	if (IsStackEmpty(S)) {
		printf("Stack is empty !\n");
		exit(FALSE);
	}
	else {
		firstCell = S->next;
		S->next = firstCell->next;
		tmp = firstCell->data;
	}
	free(firstCell);
	return tmp;
}

ElemType GetTop(Stack S) {
	if (!IsStackEmpty(S))
		return S->next->data;
	else {
		printf("The stack is empty ! \n");
		return 0;
	}
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
void Visit(BinTree T) {
	if (!T)return;
	printf("%d ", T->data);
}
void PreTravel(BinTree T) {
	if (T) {
		Visit(T);
		PreTravel(T->left);
		PreTravel(T->right);
	}
}

void InTravel(BinTree T) {
	if (T) {
		InTravel(T->left);
		Visit(T);
		InTravel(T->right);
	}
}

void PostTravel(BinTree T) {
	if (T) {
		PostTravel(T->left);
		PostTravel(T->right);
		Visit(T);
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
		Visit(tmpNode);
		if (tmpNode->left) Add(Q, tmpNode->left);
		if (tmpNode->right) Add(Q, tmpNode->right);
	}
}

/*-------------------以下为非递归前、中、后序遍历--------------------*/
void PreOrder2(BinTree T) {
	Stack S = CreateStack();
	BinTree p = T;
	while (p || !IsStackEmpty(S)) {
		if (p) {
			Visit(p);
			Push(S, p);
			p = p->left;
		}
		else {
			p = Pop(S);
			p = p->right;
		}
	}
}

void InOrder2(BinTree T) {
	Stack S = CreateStack();
	BinTree p = T;
	while (p || !IsStackEmpty(S)) {
		if (p) {
			Push(S, p);
			p = p->left;
		}
		else {
			p = Pop(S);
			Visit(p);
			p = p->right;
		}
	}
}

void PostOrder2(BinTree T) {
	Stack S = CreateStack();
	BinTree p = T, r = NULL;
	while (p || !IsStackEmpty(S)) {
		if (p) {
			Push(S, p);
			p = p->left;
		}
		else {
			p = GetTop(S);
			if (p->right && p->right != r) {
				p = p->right;
			}
			else {
				p = Pop(S);
				Visit(p);
				r = p;
				p = NULL;
			}
		}
	}
}

/*----------------------------判断树的类型----------------------------------------*/
int Max(int a, int b) {
	return a > b ? a : b;
}

int GetHeight(BinTree T) {
	int a, b;
	if (!T)return 0;
	a = GetHeight(T->left);
	b = GetHeight(T->right);

	return Max(a, b) + 1;
}

int GetBalanceFactor(BinTree T1, BinTree T2) {
	return GetHeight(T1) - GetHeight(T2);
}

BinTree FindMin(BinTree T) {
	if (!T) return NULL;
	while (T->left)
		T = T->left;
	return T;
}

BinTree FindMax(BinTree T) {
	if (!T) return NULL;
	while (T->right)
		T = T->right;
	return T;
}

/*------------------判断树是否平衡  注：并非判断是否为平衡二叉树 ---------------*/
int IsAverage(BinTree T) {
	int a, b;
	int balanceFactor;
	if (!T) return TRUE;

	a = IsAverage(T->left);
	b = IsAverage(T->right);
	if (a == FALSE || b == FALSE)
		return FALSE;

	balanceFactor = GetBalanceFactor(T->left, T->right);
	return (balanceFactor >= 2) || (balanceFactor <= -2) ? FALSE : TRUE;
}

/*--------------------------判读是否是二叉排序树------------------------------*/
int IsBinSearchTree(BinTree T) {
	BinTree tmpTree, tmpTree2;

	if (!T) return TRUE;
	if (IsBinSearchTree(T->left) == FALSE || IsBinSearchTree(T->right) == FALSE)
		return FALSE;
	if (NULL == T->left && NULL == T->right) {
		//左右子树都为NULL
		//则当前节点为根的树平衡，返回TRUE
		return TRUE;
	}
	else if (NULL == T->left && NULL != T->right) {
		//左子树为NULL，右子树非空
		tmpTree = FindMin(T->right);
		if (T->data <= tmpTree->data)
			return TRUE;
		else
			return FALSE;
	}
	else if (NULL != T->left && NULL == T->right) {
		//左子树非空，右子树为NULL
		tmpTree = FindMax(T->left);
		if (T->data >= tmpTree->data)
			return TRUE;
		else
			return FALSE;
	}
	else {
		//左右子树皆非空
		tmpTree = FindMax(T->left);
		tmpTree2 = FindMin(T->right);
		if (tmpTree->data <= T->data && T->data <= tmpTree2->data)
			return TRUE;
		else
			return FALSE;
	}
}

/*-------------------------判断是否是AVL树---------------------------*/
int IsAVLTree(BinTree T) {
	if (IsBinSearchTree(T) && IsAverage(T))
		return TRUE;
	return FALSE;
}

/*-------------------------判断是否同构-------------------------------*/
//递归 
int IsSameStruct(BinTree T1, BinTree T2) {
	/*if(T1 == NULL && T2 == NULL)
		return TRUE;
	if(T1 == NULL || T2 == NULL)
		return FALSE;*/
		//上述式子可以简化为如下 
	if (T1 == NULL || T2 == NULL) return T2 == NULL;

	return IsSameStruct(T1->left, T2->left) && IsSameStruct(T1->right, T2->right);
}

//非递归
int IsSameStruct2(BinTree T1, BinTree T2) {
	Queue Q1, Q2;
	BinTree p, q;

	Q1 = CreateQueue();
	Q2 = CreateQueue();

	Add(Q1, T1);
	Add(Q2, T2);

	while (IsEmpty(Q1) == FALSE && IsEmpty(Q2) == FALSE) {
		p = Delete(Q1);
		q = Delete(Q2);

		if (p != NULL && q != NULL) {
			if (p->left == NULL && q->left == NULL) {
				//两右子树都为NULL的情况不做处理 
			}
			else if (p != NULL || q != NULL) {
				//有一颗子树为空 
				return FALSE;
			}
			else {
				//两左子树全部非空 
				Add(Q1, p->left);
				Add(Q2, p->left);
			}

			if (p->right == NULL && q->right == NULL) {
				//两右子树都为NULL的情况不做处理 
			}
			else if (p != NULL || q != NULL) {
				//有一颗子树为空 
				return FALSE;
			}
			else {
				//两左子树全部非空 
				Add(Q1, p->right);
				Add(Q2, q->right);
			}
		}
		else if (T1 != NULL || T2 != NULL) {
			return FALSE;
		}
		else {
			//T1，T2都为NULL的情况不作处理 
		}
	}

	//整棵树遍历完了之后没有返回FALSE，则返回TRUE
	return TRUE;
}

int main() {
	BinTree T1, T2;
	T1 = CreateBinTree();
	/*printf("下面请输入第二棵树的信息：\n");
	T2 = CreateBinTree();*/
	/*
	LevelTravel(T);
	printf("\nThe height is: %d\n", GetHeight(T));
	if(IsAverage(T)){
		printf("The tree is Average !\n");
	}else{
		printf("The tree is not Average !\n");
	}
	if(IsBinSearchTree(T)){
		printf("The tree is BinSearchTree !\n");
	}else{
		printf("The tree is not BinSearchTree !\n");
	}

	if(IsAVLTree(T))
		printf("The tree is AVLTree ! \n");
	else
		printf("The tree is not AVLTree ! \n");
	*/

	printf("前序遍历：");
	PreOrder2(T1);

	printf("\n中序遍历：");
	InOrder2(T1);

	printf("\n后序遍历：");
	PostOrder2(T1);

	printf("\n层次遍历：");
	LevelTravel(T1);


	/*
	if(IsSameStruct2(T1, T2))
		printf("同构\n");
	else
		printf("不同构\n");
		*/
}

