/*
	自动扩容栈
	初始化大小为 100
	每次增加 10
*/

#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int Status;
typedef int SElemType;

typedef struct SNode* PtrToSNode;
struct SNode {
	SElemType* base;
	SElemType* top;
	int size;
};
typedef PtrToSNode Stack;

Stack CreateStack() {
	Stack S = (Stack)malloc(sizeof(struct SNode));
	S->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	//if(!S->base) exit(OVERFLOW);
	S->top = S->base;
	S->size = STACK_INIT_SIZE;
	return S;
}

Status IsEmpty(Stack S) {
	return S->top == S->base;
}

Status IsFull(Stack S) {
	return ((S->top - S->base) == S->size);
}

SElemType GetTopElem(Stack S) {
	SElemType tmp;
	if (S->top == S->base) {
		printf("Stack is empty!\n");
		return ERROR;
	}
	tmp = *(S->top - 1);
	return tmp;
}

Status Push(Stack S, SElemType e) {
	SElemType *tmp;
	if ((S->top - S->base) >= S->size) {
		tmp = (SElemType*)realloc(S->base, (S->size + STACKINCREMENT) * sizeof(SElemType));
		if (!tmp)
			S->base = tmp;
		if (!S->base) exit(OVERFLOW);
		S->top = S->base + S->size;
		S->size += STACKINCREMENT;
	}
	*(S->top++) = e;
	return OK;
}

SElemType Pop(Stack S) {
	SElemType tmp;
	if (S->top == S->base)
		return ERROR;
	tmp = *(--S->top);
	return tmp;
}

int main() {
	Stack S;
	int e, i;
	S = CreateStack();
	for (i = 0; i < 10; i++) {
		Push(S, i);
	}

	for (i = 0; i < 10; i++) {
		e = Pop(S);
		printf("%d\n", e);
	}

}
