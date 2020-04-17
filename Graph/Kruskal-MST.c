#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define MaxVertexNum 100
#define INFINITY 100
#define bool int
#define false 0
#define true 1 

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef Vertex ElementType;
typedef Vertex SetName;
typedef ElementType SetType[MaxVertexNum];

/*--------------------------邻接表--用于生成MST------------------------------*/ 
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
	
	//无向图还要插入<v2,v1>
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->Adjv = E->v1;
	NewNode->Weight = E->weight;
	
	NewNode->Next = Graph->G[E->v2].FirstEdge;
	Graph->G[E->v2].FirstEdge = NewNode;
	 
}
/*------------------------------------------------------------*/

/*------------------------并查集--------------------------*/ 
void InitializeVSet(SetType S, int N){
	ElementType X;
	for(X = 0; X < N; X++)S[X] = -1;
} 

void Union(SetType S, SetName Root1, SetName Root2){
	if(S[Root2] < S[Root1]){
		S[Root2] += S[Root1];
		S[Root1] = Root2;
	}
	else{
		S[Root1] += S[Root2];
		S[Root2] = Root1;
	}
}


SetName Find(SetType S, ElementType X){
	if(S[X] < 0)
		return X;
	else
		return S[X] = Find(S, S[X]); 
}

bool CheckCycle(SetType VSet, Vertex V1, Vertex V2){
	Vertex Root1,Root2;
	
	Root1 = Find(VSet, V1);
	Root2 = Find(VSet, V2);
	
	if(Root1 == Root2)
		return false;
	else{
		Union(VSet, Root1, Root2);
		return true;
	}
}

/*-------------------------------------------------------*/

/*------------------------最小堆--------------------------*/  
void PercDown(Edge ESet, int p, int N){
	int parent,child;
	struct ENode x;
	
	x = ESet[p];
	for(parent = p; (2*parent+1) < N; parent = child){
		child = parent * 2 + 1;
		if((child != N-1) && (ESet[child].weight > ESet[child+1].weight))
			child = child + 1;
		if(x.weight <= ESet[child].weight)break;
		else
			ESet[parent] = ESet[child];
	}
	ESet[parent] = x; 
}

void InitialiseESet(LGraph Graph, Edge ESet){
	Vertex V;
	PtrToAdjVNode W;
	int ECount;
	//将边录入ESet数组 
	ECount = 0;
	for(V = 0; V < Graph->Nv; V++)
		for(W = Graph->G[V].FirstEdge; W; W = W->Next)
			if(V < W->Adjv){
				ESet[ECount].v1 = V;
				ESet[ECount].v2 = W->Adjv;
				ESet[ECount++].weight = W->Weight;
			}
	//对最小堆初始化 
	for(ECount = Graph->Ne/2;ECount >= 0; ECount--)
		PercDown(ESet, ECount, Graph->Ne);
}



void Swap(Edge E1, Edge E2){
	Vertex v1,v2;
	WeightType weight;
	v1 = E1->v1;
	v2 = E1->v2;
	weight = E1->weight;
	
	E1->v1 = E2->v1;
	E1->v2 = E2->v2;
	E1->weight = E2->weight;
	
	E2->v1 = v1;
	E2->v2 = v2;
	E2->weight = weight;
}

int GetEdge(Edge ESet, int CurrentSize){
	Swap(&ESet[0], &ESet[CurrentSize-1]);
	PercDown(ESet, 0, CurrentSize-1);
	
	return CurrentSize - 1;
}
/*-------------------------------------------------------*/



/*------------------------Kruskal--------------------------*/
int Kruskal(LGraph Graph, LGraph MST){
	WeightType TotalWeight;
	int ECount, NextEdge;
	SetType VSet;
	Edge ESet;
	//初始化并查集 
	InitializeVSet(VSet, Graph->Nv);
	ESet = (Edge)malloc( sizeof(struct ENode)*Graph->Ne);
	//初始化最小堆
	InitialiseESet( Graph, ESet );
	//初始化数据
	TotalWeight = 0;
	ECount = 0;
	
	NextEdge = Graph->Ne; 
	
	while(ECount < Graph->Nv-1){
		NextEdge = GetEdge(ESet, NextEdge);
		if(NextEdge < 0 )break;
		
		//判断是否构成回路
		if(CheckCycle(VSet, ESet[NextEdge].v1, ESet[NextEdge].v2) == true){
			
			InsertEdge(MST, ESet + NextEdge);
			MST->Ne++;
			TotalWeight += ESet[NextEdge].weight;
			ECount++;//生成树中边加一 
		} 
	}
	if(ECount < Graph->Nv-1)
		TotalWeight = -1;
	
	return TotalWeight;
} 
/*-------------------------------------------------------*/



int main(){
	
	Vertex i,j;
	int TotalWeight;
	PtrToAdjVNode cur;
	Edge TempEdge;
	
	LGraph Graph;
	LGraph MST;
	
	WeightType temp[7][7]=
	{
	0,2,4,1,0,  0,0,
	2,0,0,3,10,  0,0,
	4,0,0,2,0,  5,0,
	1,3,2,0,7,  8,4,
	0,10,0,7,0,  0,6,
	
	0,0,5,8,0,  0,1,
	0,0,0,3,6,  1,0,
	 }; 
	
/*-----------------------本意是控制台输入但是测试太麻烦----------------------- 
------------------------此处改成自己手动初始化图-------------------------
-----------------------只能手动设置了一种情况-----------------------------*/
	Graph =  CreateGraph1(7);
	Graph->Ne = 12;
	
	MST = CreateGraph1(7);
	//将手动定义的以邻接矩阵存储的图的边插入Graph 
	for(i = 0; i < Graph->Nv; i++){
		cur = Graph->G[i].FirstEdge;
		for(j = i+1; j < Graph->Nv; j++){
			if(temp[i][j] != 0){
				TempEdge = (Edge)malloc(sizeof(struct ENode));
				TempEdge->v1 = i;
				TempEdge->v2 = j;
				TempEdge->weight = temp[i][j];
				InsertEdge(Graph, TempEdge);
			}
		}
	}
				
	MST->G[0].Data='a'; 
	MST->G[1].Data='b';
	MST->G[2].Data='c';
	MST->G[3].Data='d';
	MST->G[4].Data='e';
	
	MST->G[5].Data='f';
	MST->G[6].Data='g';
	
/*----------------------------------------------------------*/

/*-----------------------打印原来图---------------------------*/
	
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
	
	printf("\n");
	printf("Graph->Nv:%5d\n", Graph->Nv);
	printf("Graph->Ne:%5d\n", Graph->Ne);
/*--------------------------------------------------------------------*/



/*-----------------------Kruskal---------------------------*/
	
	TotalWeight = Kruskal(Graph, MST);
	if(TotalWeight == -1){
		printf("图中有环！无法产生最小生成树！\n");
		exit(0); 
	}
	
	printf("\nTotalWeight = %5d\n\n\n",TotalWeight);
/*--------------------------------------------------------------------*/
	
	printf("-------------------------------------------------------------\n");
	printf("----------------------MST的领接表----------------------------\n");
	printf("--------------------------------------------------------------\n");
	
	for(i = 0; i < MST->Nv; i++){
		
		printf("%3c",MST->G[i].Data);
		cur = MST->G[i].FirstEdge;
		while(cur){
			//printf("->%3d(%-2d)",cur->Adjv,cur->Weight);
			printf("->%2c(%-2d)",MST->G[cur->Adjv].Data,cur->Weight);
			cur = cur->Next;
		}
		printf("\n");
	}
	
	printf("\n");
	printf("Graph->Nv:%5d\n", MST->Nv);
	printf("Graph->Ne:%5d\n", MST->Ne); 
	
	

/*----------------------------------------------------------*/
	
}
