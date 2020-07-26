#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct Node *PtrToNode;
struct Node{
	ElemType data;
	PtrToNode next;
};
typedef PtrToNode List;

List createList(){
	List L;
	L = (PtrToNode)malloc(sizeof(struct Node));
	L->next = NULL;
	return L;
}

int addTail(List L, ElemType e){
	PtrToNode p,tmp;
	p = L;	
	while(p->next) p = p->next;
	tmp = (PtrToNode)malloc(sizeof(struct Node));
	
	tmp->data = e;
	tmp->next = NULL;
	
	p->next = tmp;
}

ElemType deleteTail(List L){
	PtrToNode p;
	ElemType tmp;
	
	p = L;
	while(p->next->next) p = p->next;
	tmp = p->next->data;
	free(p->next);
	p->next = NULL;
	
	return tmp;
	
}

int main(){
	List L;
	L = createList();
	addTail(L,123);
	addTail(L,456);
	
	printf("%d\n",L->next->data);
	printf("%d\n",L->next->next->data);
}

