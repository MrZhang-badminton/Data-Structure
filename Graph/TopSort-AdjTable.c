#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define MaxVertexNum 100
#define bool int
#define false 0
#define true 1 

//图中定义 
typedef int Vertex;
typedef int WeightType;
typedef char DataType;
//队列中定义 
typedef Vertex ElemType;


/*--------------------------邻接表-------------------------------------*/ 
//Edge 
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex v1,v2;
	WeightType weight;
}; 
typedef PtrToENode Edge;

//vertex
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
	Vertex Adjv;
	WeightType Weight;
	PtrToAdjVNode Next;
};

typedef struct VNode{
	PtrToAdjVNode FirstEdge;
	DataType Data;
}AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToGNode LGraph;


LGraph CreateGraph1(int VertexNum){
//初始化一个有VertexNum个顶点的图
	Vertex V;
	LGraph Graph;
	
	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	
	for(V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;
	
	return Graph; 
}

void InsertEdge(LGraph Graph, Edge E){
	PtrToAdjVNode NewNode;
	
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->Adjv = E->v2;
	NewNode->Weight = E->weight;
	
	NewNode->Next = Graph->G[E->v1].FirstEdge;
	Graph->G[E->v1].FirstEdge = NewNode;
	/*
	//无向图还要插入<v2,v1>
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->Adjv = E->v1;
	NewNode->Weight = E->weight;
	
	NewNode->Next = Graph->G[E->v2].FirstEdge;
	Graph->G[E->v2].FirstEdge = NewNode;*/
	 
}
/*------------------------------------------------------------*/

/*---------------------------队列-----------------------------*/

typedef struct QNode *PtrToQNode;
struct QNode{
	ElemType *elem;
	int front;
	int rear;
}; 
typedef PtrToQNode Que;

Que CreateQueue(){
	Que Q;
	Q = (Que)malloc(sizeof(struct QNode));
	Q->elem = (ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
	Q->front = Q->rear;
	return Q;
}

bool IsFull(Que Q){
	return (Q->rear+1)%MAXSIZE == Q->front;
}

void Add(Que Q,ElemType Elem){
	if(IsFull(Q)){
		printf("队列已满！\n");
		exit(0); 
	}
	Q->elem[Q->rear] = Elem;
	Q->rear = (Q->rear+1)%MAXSIZE;
}

bool IsEmpty(Que Q){
	return Q->front == Q->rear;
}

ElemType Delete(Que Q){
	ElemType temp;
	if(IsEmpty(Q)){
		printf("队列已空！\n");
		exit(0);
	}
	temp = Q->elem[Q->front];
	Q->front = (Q->front+1)%MAXSIZE;
	return temp;
}

/*------------------------------------------------------------*/ 


/*-------------------------拓扑排序-------------------------*/
bool TopSort(LGraph Graph, Vertex TopOrder[]){
	int Indegree[MaxVertexNum],cnt;
	Vertex V;
	PtrToAdjVNode W;
	Que Q = CreateQueue();
	
	for(V = 0; V < Graph->Nv; V++)
		Indegree[V] = 0;
	/*memset(Indegree, 0, sizeof(int)*MaxVertexNum);//引入头文件string.h */
	
	for(V = 0; V < Graph->Nv; V++){
		W = Graph->G[V].FirstEdge;
		while(W){
			Indegree[W->Adjv]++;
			W = W->Next;
		}
	}
	
	for(V = 0; V < Graph->Nv; V++)
		if(Indegree[V] == 0)
			Add(Q, V);
			
	cnt = 0;
			
	while(!IsEmpty(Q)){
		V = Delete(Q);
		TopOrder[cnt++] = V;
		
		W = Graph->G[V].FirstEdge;
		while(W){
			if(--Indegree[W->Adjv] == 0)
				Add(Q, W->Adjv);
			W = W->Next;
		}
	}
	
	if(cnt != Graph->Nv)
		return false;
	else
		return true;
}

/*----------------------------------------------------------*/

int main(){
	
}
