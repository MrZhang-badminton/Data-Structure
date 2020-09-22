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


/*-------------------------------Stack---------------------------------------*/
typedef BinTree SElemType;
typedef struct SNode* PtrToSNode;
struct SNode {
	SElemType data;
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

int Push(Stack S, SElemType elem) {
	PtrToSNode tmpCell;
	tmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
	if (!tmpCell) exit(OVERFLOW);
	tmpCell->data = elem;
	tmpCell->next = S->next;
	S->next = tmpCell;
	return TRUE;
}

SElemType Pop(Stack S) {
	PtrToSNode firstCell;
	SElemType tmp;
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

SElemType GetTop(Stack S) {
	if (!IsStackEmpty(S))
		return S->next->data;
	else {
		printf("The stack is empty ! \n");
		return 0;
	}
}

/*------------------------------Tree------------------------------------------*/
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
void PreOrder(BinTree T) {
	if (T) {
		Visit(T);
		PreOrder(T->left);
		PreOrder(T->right);
	}
}

void InOrder(BinTree T) {
	if (T) {
		InOrder(T->left);
		Visit(T);
		InOrder(T->right);
	}
}

void PostOrder(BinTree T) {
	if (T) {
		PostOrder(T->left);
		PostOrder(T->right);
		Visit(T);
	}
}

void LevelOrder(BinTree T) {
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




int main() {
	BinTree T1, T2;
	T1 = CreateBinTree();

	printf("前序遍历：");
	PreOrder2(T1);

	printf("\n中序遍历：");
	InOrder2(T1);

	printf("\n后序遍历：");
	PostOrder2(T1);

	printf("\n层次遍历：");
	LevelOrder(T1);


	
}

