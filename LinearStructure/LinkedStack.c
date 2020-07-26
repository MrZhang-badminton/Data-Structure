#include<stdio.h>
#include<stdlib.h>

#define OVERFLOW -1
#define TRUE 1
#define FALSE 0

typedef int ElemType;

typedef struct SNode *PtrToSNode;
struct SNode{
	ElemType data;
	PtrToSNode next;
}; 
typedef PtrToSNode Stack;

Stack CreateStack(){
	Stack S;
	S = (Stack)malloc(sizeof(struct SNode));
	S->next = NULL;
	return S;
}

int IsEmpty(Stack S){
	return S->next == NULL;
}

int Push(Stack S, ElemType elem){
	PtrToSNode tmpCell;
	tmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
	if(!tmpCell) exit(OVERFLOW);
	tmpCell->data = elem;
	tmpCell->next = S->next;
	S->next = tmpCell;
	return TRUE;
}

ElemType Pop(Stack S){
	PtrToSNode firstCell;
	ElemType tmp;
	if(IsEmpty(S)){
		printf("Stack is empty !\n");
		exit(FALSE);
	}else{
		firstCell = S->next;
		S->next = firstCell->next;
		tmp = firstCell->data;
	}
	free(firstCell);
	return tmp;
}

ElemType GetTop(Stack S){
	if(!IsEmpty(S))
		return S->next->data;
	else{
		printf("The stack is empty ! \n");
		return 0;
	}
}

void MakeEmpty(Stack S){
	if( S == NULL)
		printf("The stack is already empty\n");
	else
		while(!IsEmpty(S))
			Pop(S);
}

int main(){
	Stack S;
	int i;
	S = CreateStack();
	for(i = 0; i < 10; ++i)
		Push(S,i);
	//printf("%d\n",GetTop(S));
	MakeEmpty(S);
	for(i = 0; i < 10; ++i)
		printf("%d\n",Pop(S));
}
