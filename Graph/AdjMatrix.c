#include<stdio.h>
#include<stdlib.h>

#define MaxVertexNum 100
#define INFINITY 100

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

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
	Graph->G[E->v2][E->v1] = E->weight;//no direction graph
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
		scanf("%c\n",&Graph->Data[V]);
		
	return Graph;
}

int main(){
	int i,j;
	MGraph Graph = NULL;
	Graph = BuildGraph();
	
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
}
