#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100 
#define MaxVertexNum 100
#define bool int
#define false 0
#define true 1 

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

//�������� 
typedef Vertex ElemType;


/*
	�������£�
	������                       2
	����                         1
	����Ϣ(��㣬�յ㣬Ȩ��)     0 1 100  //0 1 Ϊλ�ò���a,b 
	�����ŵ���Ϣ               a
								 b
*/ 


/*-------------------����---------------------*/
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
		printf("����������\n");
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
		printf("�����ѿգ�\n");
		exit(0);
	}
	temp = Q->elem[Q->front];
	Q->front = (Q->front+1)%MAXSIZE;
	return temp;
}

/*-----------------------------------------------*/ 

/*-------------------�ڽӱ��Ĵ���-----------------------*/
//edge
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex V1,V2;
	WeightType Weight; 
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


LGraph CreateGraph(int VertexNum){
//��ʼ��һ����VertexNum�������ͼ
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
	NewNode->Adjv = E->V2;
	NewNode->Weight = E->Weight;
	
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	
	//����ͼ��Ҫ����<v2,v1>
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->Adjv = E->V1;
	NewNode->Weight = E->Weight;
	
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
	 
}

LGraph BuildGraph(){
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv,i;
	
	scanf("%d",&Nv);//���붥�����
	Graph = CreateGraph(Nv);
	
	scanf("%d",&Graph->Ne);//����ߵĸ���
	if(Graph->Ne){
		E = (Edge)malloc(sizeof(struct ENode));
		for(i = 0; i < Graph->Ne; i++){
			scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);
			InsertEdge(Graph,E);
		}
	} 
	//�������������
	for(V = 0; V < Graph->Nv; V++)
		scanf(" %c",&Graph->G[V].Data);
		
	return Graph; 
}

/*--------------------------------------------*/

/*-----------------��Ȩ���·-----------------*/
void Uweighted(LGraph Graph,int dist[], int path[], Vertex S){
	Que Q;
	Vertex V;
	PtrToAdjVNode W;
	
	Q = CreateQueue();
	dist[S] = 0;
	Add(Q,S);
	while(!IsEmpty(Q)){
		printf("111\n");
		V = Delete(Q);
		for(W = Graph->G[V].FirstEdge; W; W = W->Next){
			if(dist[W->Adjv] == -1){
				dist[W->Adjv] = dist[V] + 1;
				path[W->Adjv] = V;
				Add(Q,W->Adjv);
 			}
		}
	}
	
}

/*--------------------------------------------*/

int main(){
	int i,j;
	PtrToAdjVNode cur;
	LGraph Graph = NULL;
	int *dist,*path;
	
	Graph = BuildGraph();
	
	dist = (int *)malloc(sizeof(int)*Graph->Nv);
	path = (int *)malloc(sizeof(int)*Graph->Nv);

	for(i = 0; i < Graph->Nv; i++){
		dist[i] = -1;
		path[i] = -1;
	}
	
/*--------------���ͼ�Ļ�����Ϣ-------------*/	
	for(i = 0; i < Graph->Nv; i++){
		printf("%3c",Graph->G[i].Data);
		cur = Graph->G[i].FirstEdge;
		while(cur){
			//printf("->%3d(%-2d)",cur->Adjv,cur->Weight);
			printf("->%2c(%-2d)",Graph->G[cur->Adjv].Data,cur->Weight);
			cur = cur->Next;
		}
		printf("\n");
	}
	
	for(i = 0; i < Graph->Nv; i++)
		printf("%3c",Graph->G[i].Data);
	
	printf("\n");
	printf("Graph->Nv:%5d\n", Graph->Nv);
	printf("Graph->Ne:%5d\n\n\n", Graph->Ne); 
/*--------------------------------------------*/

	Uweighted(Graph, dist, path, 0);
	
	for(i = 0; i < Graph->Nv; i++)
		printf("%3c",Graph->G[i].Data);
	printf("\n");
	
	for(i = 0; i < Graph->Nv; i++)
		printf("%3d",dist[i]);
	printf("\n");
	
	for(i = 0; i < Graph->Nv; i++)
		printf("%3d",path[i]);
	printf("\n");


}