#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define FALSE 0
#define TRUE 1
#define OVERFLOW -1

typedef int TElemType;//TElemType

/*------------------------------CreateTree------------------------------------------*/
typedef struct TNode* PtrToTNode;
typedef PtrToTNode BinTree;
struct TNode {
	TElemType data;
	BinTree left;
	BinTree right;
};
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


/*------------------------------Queue-------------------------------------*/
typedef BinTree QElemType;
typedef struct QNode* PtrToQNode;
struct QNode {
	QElemType* elem;
	int front;
	int rear;
};
typedef PtrToQNode Queue;


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

/*------------------------------判断树的类型----------------------------------------*/
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

/*-----------判断树是否平衡  注：并非判断是否为平衡二叉树 ------------*/
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


/*----------------------判读是否是二叉排序树-------------------------*/
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

//基于中序遍历的判断是否是二叉搜索树 
int IsBinSearchTree2(BinTree T) {
	static int preVal = -32767;

	int b1, b2;
	if (!T) {
		return 1;
	}
	else {
		b1 = IsBinSearchTree2(T->left);
		if (b1 == 0 || preVal >= T->data)
			return 0;
		preVal = T->data;
		b2 = IsBinSearchTree2(T->right);
		return b2;
	}

}



/*------------------------判断是否是AVL树--------------------------*/
int IsAVLTree(BinTree T) {
	if (IsBinSearchTree(T) && IsAverage(T))
		return TRUE;
	return FALSE;
}

/*-------------------------判断是否同构------------------------------*/
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
	/*
	printf("下面请输入第二棵树的信息：\n");
	T2 = CreateBinTree();

	LevelTravel(T);
	printf("\nThe height is: %d\n", GetHeight(T));
	if(IsAverage(T)){
		printf("The tree is Average !\n");
	}else{
		printf("The tree is not Average !\n");
	}*/
	if (IsBinSearchTree2(T1)) {
		printf("The tree is BinSearchTree !\n");
	}
	else {
		printf("The tree is not BinSearchTree !\n");
	}

	/*
	if(IsAVLTree(T))
		printf("The tree is AVLTree ! \n");
	else
		printf("The tree is not AVLTree ! \n");
	*/


	/*
	if(IsSameStruct2(T1, T2))
		printf("同构\n");
	else
		printf("不同构\n");
		*/
}

