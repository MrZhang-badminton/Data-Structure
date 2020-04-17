#include<stdio.h>
#include<stdlib.h>
#include<string.h>//memset

typedef int ElemType;
typedef struct HNode *Heap;
struct HNode{
	ElemType *data;
	int size;
	int capacity;
}; 

typedef Heap MaxHeap;
typedef Heap MinHeap;

#define MAXDATA 1000
 
 MaxHeap InitMaxHeap(int MaxSize){
 	//创建容量为MaxSize 的空的最大堆
 	int i;
	 MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
	 H->data = (ElemType*)malloc((MaxSize + 1) * sizeof(ElemType));
	 //memset(H->data,0,sizeof(ElemType)*(MaxSize + 1));
	/* for(i = 0; i < MaxSize + 1; i++){//可能出问题 搞清楚优先级 是否需要加括号 
	 	H->data[i] = 0;
	 }*/
	 H->size = 0;
	 H->capacity = MaxSize;
	 H->data[0] = MAXDATA;//哨兵
	 
	 return H; 
 }
 
 bool IsFull(MaxHeap H){
 	return (H->size == H->capacity);
 }
 
 bool Insert(MaxHeap H, ElemType x){
 	int i;
 	if(IsFull(H)){
 		printf("堆已满！\n");
 		return false;
	 }
	i = ++H->size;
	for(; H->data[i/2] < x; i /= 2)
	 	H->data[i] = H->data[i/2];
 	H->data[i] = x;
 	
 	return true;
 }
 
 bool IsEmpty(MaxHeap H){
 	return (H->size == 0);
 }
 
 ElemType DeleteMax(MaxHeap H){
 	int parent,child;
 	ElemType max, temp;
 	if(IsEmpty(H)){
 		printf("堆已空！\n");
 		return -1;
	}
	
	max = H->data[1];
	temp = H->data[H->size--];
	for(parent = 1; parent * 2 <= H->size; parent = child){
		child = parent * 2;
		if((child!=H->size) && (H->data[child+1] > H->data[child]))
			child++;
		if(temp > H->data[child])
			break;
		else
			H->data[parent] = H->data[child];
	}
	H->data[parent] = temp;
	
	return max;
 }
 
 //Build MaxHeap
 
 void PerDown(MaxHeap H,int p){
 	int parent,child;
 	ElemType temp;
 	temp = H->data[p];
 	for(parent = p; parent * 2 <= H->size;parent = child){
 		child = parent * 2;
 		if((child != H->size) && (H->data[child+1] > H->data[child]))
 			child++;
 		if(temp > H->data[child])
			break;
		else{
			H->data[parent] = H->data[child];
		}
	 }
	 H->data[parent] = temp;
 }
 
 void BuildHeap(MaxHeap H){
 	//从最后一个数的父节点开始想左向上调整最大堆 
 	int i;
	for(i = H->size/2; i >0; i++){
		PerDown(H,i);
	} 
 }
 
 int main(){
 	MaxHeap H;
 	H = InitMaxHeap(7);
 	
 	//BuildHeap(H);
 	
 	Insert(H,8);
 	Insert(H,9);
 	Insert(H,4);
 	DeleteMax(H);
 	DeleteMax(H);
 	DeleteMax(H);
 	DeleteMax(H);
 	for(int i = 1 ; i <= 3; i++)
 	printf("%5d\n",H->data[i]);
 }
