#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define MaxVertexNum 100
#define INFINITY 100

typedef int Vertex;
typedef int WeightType;
typedef char DataType;


/*--------------------邻接矩阵的创建----------------*/ 
//defination of edge
typedef struct ENode *PtrToENode;
struct ENode{
	Vertex v1,v2;
	WeightType weight;
}; 
typedef PtrToENode Edge;

//defination of vertex
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv;//num of vertex
	int Ne;//num of edge
	WeightType G[MaxVertexNum][MaxVertexNum];
	DataType Data[MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph(int VertexNum){
//init a graph with no edge but VertexNum vertexs
	Vertex v,w;
	MGraph Graph;
	
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	
	for(v = 0; v < Graph->Nv; v++)
		for(w = 0; w < Graph->Nv; w++)
			Graph->G[v][w] = INFINITY;
			
	return Graph;
}
/*
void InsertEdge(MGraph Graph, Edge E){
	Graph->G[E->v1][E->v2] = E->weight;
	Graph->G[E->v2][E->v1] = E->weight;
}

MGraph BuildGraph(){
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv,i;
	
	scanf("%d",&Nv);//the number of vertex;
	Graph = CreateGraph(Nv);
	
	scanf("%d",&Graph->Ne);
	if(Graph->Ne){
		E = (Edge)malloc(sizeof(struct ENode));
		for(i = 0; i < Graph->Ne; i++){
			scanf("%d %d %d",&E->v1,&E->v2,&E->weight);//起始边从0开始，注意不是1 
			InsertEdge(Graph,E);
		}
	}
	//如果顶点存放数据的话，输入定点数据 
	for(V= 0; V < Graph->Nv; V++)
		scanf(" %c",&Graph->Data[V]);
		
	return Graph;
}*/
/*---------------------------------------------*/




/*--------------------------邻接表--用于生成MST------------------------------*/ 

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

typedef struct GGNode *PtrToGGNode;
struct GGNode{
	int Nv;
	int Ne;
	AdjList G;
};
typedef PtrToGGNode LGraph;


LGraph CreateGraph1(int VertexNum){
//初始化一个有VertexNum个顶点的图
	Vertex V;
	LGraph Graph;
	
	Graph = (LGraph)malloc(sizeof(struct GGNode));
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




/*------------------------Prime--------------------------*/ 


Vertex FindMinDist(MGraph Graph, WeightType dist[]){
	Vertex MinV,V;
	WeightType MinDist = INFINITY;
	
	for(V = 0; V < Graph->Nv; V++){
		if(dist[V] != 0 && dist[V] < MinDist){
			MinDist = dist[V];
			MinV = V;
		}
	}
	
	if(MinDist < INFINITY)
		return MinV;
	return ERROR;
}

int Prim(MGraph Graph,LGraph MST){
	WeightType dist[MaxVertexNum],TotalWeight;
	Vertex parent[MaxVertexNum],V,W;
	int VCount;
	Edge E;
	
	
	//初始化dist[]  parent[]
	for(V = 0; V < Graph->Nv; V++){
		dist[V] = Graph->G[0][V];
		parent[V] = 0;
	} 
	
	/*初始化权重和    收录定点数*/
	TotalWeight = 0;
	VCount = 0;
	
	E = (Edge)malloc(sizeof(struct ENode));
	
	
	dist[0] = 0;
	parent[0] = -1;
	VCount++;
	
	while(1){
		V = FindMinDist(Graph, dist);
		if(V == ERROR)//不存在这样的点就退出 
			break;
		E->v1 = V;
		E->v2 = parent[V];
		E->weight = dist[V];
		InsertEdge(MST, E);
		MST->Ne++;
		TotalWeight += dist[V];
		dist[V] = 0;
		VCount++;
		
		for(W = 0; W < Graph->Nv; W++){
			if(dist[W] != 0 && Graph->G[V][W] < INFINITY){
				if(Graph->G[V][W] < dist[W]){
					dist[W] = Graph->G[V][W];
					parent[W] = V;
				}
			}
		}
	}
	if(VCount < Graph->Nv)
		TotalWeight = ERROR;

		
	return TotalWeight;
}

/*-------------------------------------------------------*/



int main(){
	
	int i,j,TotalWeight;
	PtrToAdjVNode cur;
	MGraph Graph;
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
------------------------此处改成自己手动初始化图-----------------------------*/
	Graph = CreateGraph(7);//定点数 
	MST = CreateGraph1(Graph->Nv);
	Graph->Ne = 12;//边数 
	for(i = 0; i < Graph->Nv; i++)
		for(j = 0; j < Graph->Nv; j++)
			if(temp[i][j] != 0)
				Graph->G[i][j] = temp[i][j];
				
	MST->G[0].Data='1'; 
	MST->G[1].Data='2';
	MST->G[2].Data='3';
	MST->G[3].Data='4';
	MST->G[4].Data='5';
	
	MST->G[5].Data='6';
	MST->G[6].Data='7';
	
/*----------------------------------------------------------*/


/*----------------------打印邻接矩阵-----------------------------*/
	printf("邻接矩阵:\n"); 
	for(i = 0;i < Graph->Nv; i++){
		for(j = 0; j < Graph->Nv; j++)
			printf("%5d",Graph->G[i][j]);
		printf("\n");		
	}
	
	printf("Graph->Nv:%5d\n",Graph->Nv);
	printf("Graph->Ne:%5d\n",Graph->Ne);
	printf("\n"); 
/*----------------------------------------------------------*/


/*-----------------------Prim----------------------------*/
	
	TotalWeight = Prim(Graph, MST);
	if(TotalWeight == ERROR){
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
