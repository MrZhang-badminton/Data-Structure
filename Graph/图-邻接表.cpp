#include<stdio.h>
#include<stdlib.h>

#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef char DataType;
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
	NewNode->Adjv = E->V2;
	NewNode->Weight = E->Weight;
	
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	
	//无向图还要插入<v2,v1>
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
	
	scanf("%d",&Nv);//输入顶点个数
	Graph = CreateGraph(Nv);
	
	scanf("%d",&Graph->Ne);//读入边的个数
	if(Graph->Ne){
		E = (Edge)malloc(sizeof(struct ENode));
		for(i = 0; i < Graph->Ne; i++){
			scanf("%d %d %d",&E->V1,&E->V2,&E->Weight);
			InsertEdge(Graph,E);
		}
	} 

	//如果顶点有数据
	for(V = 0; V < Graph->Nv; V++)
		scanf(" %c",&Graph->G[V].Data);
		
	return Graph; 
}

int main(){
	int i,j;
	PtrToAdjVNode cur;
	LGraph Graph = NULL;
	Graph = BuildGraph();
	
	
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
	printf("Graph->Ne:%5d\n", Graph->Ne); 
	
}
