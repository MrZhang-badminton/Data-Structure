#include<stdio.h>
#include<stdlib.h> 

#define MAXSIZE 1000
typedef struct Node{
	int data;
	struct Node *next;
}Node;

Node * init(){
	Node *p = (Node*)malloc(sizeof(Node));
	p->data = -1;
	p->next = NULL;
	return p;
}

void Add(Node *p, int data){
	Node *newNode = (Node*)malloc(sizeof(Node));
	Node *temp = p;
	newNode->data = data;
	newNode->next = NULL;
	
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newNode;
	
}

int Reverse(Node *p){
	Node *pre = p->next;//pre point to head->next
	Node *cur = pre->next;
	if(p->next == NULL){
		printf("The list is null !\n");
		return 0;
	}
	pre->next = NULL;
	while(cur != NULL){
		Node *temp = cur->next;
		cur -> next = pre;
		pre = cur;
		cur = temp;
	}
	p->next = pre;
	return 1;
	
	
	
}

void printList(Node *p){
	Node *temp = p->next;
	while(temp != NULL){
		printf("%5d",temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main(){
	
	Node *List;
	int i;
	
	List = init();
	
	for(i = 0; i < 20; i++)
		Add(List, i);
		
	printList(List);
	Reverse(List);
	printList(List);
}
