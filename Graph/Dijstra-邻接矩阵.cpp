#include<stdio.h>
#include<stdlib.h>
#define ERROR -1
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

void InsertEdge(MGraph Graph, Edge E){
	Graph->G[E->v1][E->v2] = E->weight;
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
	
	for(V= 0; V < Graph->Nv; V++)
		scanf(" %c",&Graph->Data[V]);
		
	return Graph;
}
/*---------------------------------------------*/


/*--------------------Dijkstra--------------------*/ 
Vertex FindMinDist(MGraph Graph, int dist[], int collected[]){
	Vertex V,MinV;
	int MinDist = INFINITY;
	for(V = 0; V < Graph->Nv; V++){
		if(collected[V] == false && dist[V] < MinDist){
			MinDist = dist[V];
			MinV = V;
		}
	}
	if(MinDist < INFINITY)
		return MinV;
	else
		return ERROR;
}


bool Dijkstra(MGraph Graph, int dist[], int path[], Vertex S){
	int collected[MaxVertexNum];
	Vertex V,W;
	
	for(V = 0; V < Graph->Nv; V++){
		dist[V] = Graph->G[S][V];
		if(dist[V] < INFINITY)
			path[V] = S;
		else
			path[V] = -1;
		collected[V] = false;
	}
	
	dist[S] = 0;
	collected[S] = true;
	
	while(1){
		V = FindMinDist(Graph, dist, collected);
		if(V == ERROR)
			break;
		collected[V] = true;
		for(W = 0; W < Graph->Nv; W++){
			if((collected[W] == false) && (Graph->G[V][W] < INFINITY)){
				if(Graph->G[V][W] < 0)
					return false;
				if(dist[V] + Graph->G[V][W] < dist[W]){
					dist[W] = dist[V] + Graph->G[V][W];
					path[W] = V;
				}
			}
		}
	}
	return true;
} 

/*-------------------------------------------------*/

/*--------------------Floyd--------------------*/ 



/*-------------------------------------------------*/



int main(){
	
	int i,j;
	MGraph Graph = NULL;
	int *dist,*path;
	
/*-----------------------初始化-----------------------------*/
	Graph = BuildGraph();
	
	dist = (int *)malloc(sizeof(int)*Graph->Nv);
	path = (int *)malloc(sizeof(int)*Graph->Nv);

	for(i = 0; i < Graph->Nv; i++){
		dist[i] = -1;
		//path[i] = -1;
	}
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
	
	printf("点存储的值");
	for(i = 0; i < Graph->Nv; i++)
		printf("%5c",Graph->Data[i]);
	printf("\n"); 
/*----------------------------------------------------------*/


/*-----------------------Dijkstra----------------------------*/

	Dijkstra(Graph, dist, path, 0);

/*----------------------------------------------------------*/

/*---------------------打印最短路信息------------------------------*/	
	
	for(i = 0; i < Graph->Nv; i++)
		printf("%3c",Graph->Data[i]);
	printf("\n");
	
	for(i = 0; i < Graph->Nv; i++)
		printf("%3d",dist[i]);
	printf("\n");
	
	for(i = 0; i < Graph->Nv; i++)
		printf("%3d",path[i]);
	printf("\n");
/*----------------------------------------------------------*/
	
}
