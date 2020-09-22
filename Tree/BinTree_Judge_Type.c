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
		printf("���������ӣ����Ϊ������-1\n");
		T->left = CreateBinTree();
		printf("�������Һ��ӣ����Ϊ������-1\n");
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
		printf("����������\n");
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
		printf("�����ѿգ�\n");
		exit(0);
	}
	temp = Q->elem[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return temp;
}

/*------------------------------�ж���������----------------------------------------*/
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

/*-----------�ж����Ƿ�ƽ��  ע�������ж��Ƿ�Ϊƽ������� ------------*/
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


/*----------------------�ж��Ƿ��Ƕ���������-------------------------*/
int IsBinSearchTree(BinTree T) {
	BinTree tmpTree, tmpTree2;

	if (!T) return TRUE;
	if (IsBinSearchTree(T->left) == FALSE || IsBinSearchTree(T->right) == FALSE)
		return FALSE;
	if (NULL == T->left && NULL == T->right) {
		//����������ΪNULL
		//��ǰ�ڵ�Ϊ������ƽ�⣬����TRUE
		return TRUE;
	}
	else if (NULL == T->left && NULL != T->right) {
		//������ΪNULL���������ǿ�
		tmpTree = FindMin(T->right);
		if (T->data <= tmpTree->data)
			return TRUE;
		else
			return FALSE;
	}
	else if (NULL != T->left && NULL == T->right) {
		//�������ǿգ�������ΪNULL
		tmpTree = FindMax(T->left);
		if (T->data >= tmpTree->data)
			return TRUE;
		else
			return FALSE;
	}
	else {
		//���������Էǿ�
		tmpTree = FindMax(T->left);
		tmpTree2 = FindMin(T->right);
		if (tmpTree->data <= T->data && T->data <= tmpTree2->data)
			return TRUE;
		else
			return FALSE;
	}
}

//��������������ж��Ƿ��Ƕ��������� 
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



/*------------------------�ж��Ƿ���AVL��--------------------------*/
int IsAVLTree(BinTree T) {
	if (IsBinSearchTree(T) && IsAverage(T))
		return TRUE;
	return FALSE;
}

/*-------------------------�ж��Ƿ�ͬ��------------------------------*/
//�ݹ� 
int IsSameStruct(BinTree T1, BinTree T2) {
	/*if(T1 == NULL && T2 == NULL)
		return TRUE;
	if(T1 == NULL || T2 == NULL)
		return FALSE;*/
		//����ʽ�ӿ��Լ�Ϊ���� 
	if (T1 == NULL || T2 == NULL) return T2 == NULL;

	return IsSameStruct(T1->left, T2->left) && IsSameStruct(T1->right, T2->right);
}

//�ǵݹ�
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
				//����������ΪNULL������������� 
			}
			else if (p != NULL || q != NULL) {
				//��һ������Ϊ�� 
				return FALSE;
			}
			else {
				//��������ȫ���ǿ� 
				Add(Q1, p->left);
				Add(Q2, p->left);
			}

			if (p->right == NULL && q->right == NULL) {
				//����������ΪNULL������������� 
			}
			else if (p != NULL || q != NULL) {
				//��һ������Ϊ�� 
				return FALSE;
			}
			else {
				//��������ȫ���ǿ� 
				Add(Q1, p->right);
				Add(Q2, q->right);
			}
		}
		else if (T1 != NULL || T2 != NULL) {
			return FALSE;
		}
		else {
			//T1��T2��ΪNULL������������� 
		}
	}

	//��������������֮��û�з���FALSE���򷵻�TRUE
	return TRUE;
}

int main() {
	BinTree T1, T2;
	T1 = CreateBinTree();
	/*
	printf("����������ڶ���������Ϣ��\n");
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
		printf("ͬ��\n");
	else
		printf("��ͬ��\n");
		*/
}

