#include<stdio.h>
#include<stdlib.h>

#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;
typedef char DataType;
typedef int ElemType;
int Visited[MaxVertexNum] ={false};

/*-------------------����---------------------*/
typedef struct QNode{
	ElemType data;
	struct QNode *next;
}QNode,*Queueptr;

typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQue;

LinkQue * InitQueue(){
	LinkQue *q = (LinkQue *)malloc(sizeof(LinkQue));
	q->front = q->rear = NULL;
	return q;
}

void Enqueue(LinkQue *q, ElemType ele){
	Queueptr p = (Queueptr)malloc(sizeof(QNode));
	if(p == NULL)return;
	p->data = ele;
	p->next = NULL;
	if(q->front == NULL){
		q->front = p;
		q->rear = p;
	}else{
		q->rear->next = p;
		q->rear = p; 
	}
}

int isEmpty(LinkQue *q){
	return q->front == NULL;
}


ElemType Dequeue(LinkQue *q){
	if(isEmpty(q)){
		printf("Error!\n");
		exit(0);
	}
	
	Queueptr p = q->front;
	ElemType temp = q->front->data;
	
	
	if(q->front == q->rear){
		q->front = NULL;
		q->rear = NULL;
	}else{
		q->front = q->front->next;
	}
	free(p);
	return temp;
	
}
/*-----------------------------------------------*/ 

/*-------------------�ڽӱ�Ĵ���-----------------------*/
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

/*---------------------DFS--------------------*/
void Visit(Vertex V){
	printf("���ڷ��ʶ���%d\n");
}

void DFS(LGraph Graph, Vertex V,void (*visit)(Vertex)){
	PtrToAdjVNode W;
	
	Visit(V);
	Visited[V] = true;
	
	for(W = Graph->G[V].FirstEdge;W;W = W->Next){
		if(!Visited[W->Adjv])
			DFS(Graph, W->Adjv, Visit);
	}
}
/*--------------------------------------------*/

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
	DFS(Graph,0,Visit);
}
