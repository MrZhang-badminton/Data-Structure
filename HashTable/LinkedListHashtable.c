#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAXTABLESIZE 100000
#define KEYLENGTH 15
#define bool int
#define false 0
#define true 1 

typedef char ElementType[KEYLENGTH+1];//关键词用字符串类型
typedef int Index;

typedef struct LNode *PtrToLNode;
struct LNode{
	ElementType Data;
	PtrToLNode Next;
}; 

typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode *HashTable;
struct TblNode{
	int TableSize;
	List Heads;
};

//返回大于N的最小素数 
int NextPrime(int N){
	int i, p;
	 p = (N%2)? N+2 : N+1;
	 
	 while(p < MAXTABLESIZE){
	 	for( i = (int)sqrt(p); i > 2; i--)
	 		if(!p%i)break;
	 	if(i == 2) break;
	 	else p += 2;//试探下一个奇数 
	 }
	 
	 return p;
}

HashTable CreateTable(int TableSize){
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(struct TblNode));
	
	H->TableSize = NextPrime(TableSize);
	H->Heads = (List)malloc(sizeof(struct LNode)*H->TableSize);

	for(i = 0; i < H->TableSize; i++){
		H->Heads[i].Data[0] = '\0';
		H->Heads[i].Next = NULL;
		
	}

	return H;
}
//注意这里要处理的是字符串 
Index Hash(ElementType Key, int TableSize){
	unsigned int h = 0;
	char *Ptr;
	int Count = 0;
	Ptr = Key;
	while(*Ptr != '\0'){
		Ptr++;
		Count++;
	}
	
	while(*Key !='\0')
		h = (h << Count) + *Key++;
	
	return h % TableSize;
} 

Position Find(HashTable H, ElementType Key){
	Position P;
	Index Pos;
	
	Pos = Hash(Key, H->TableSize);
	P = H->Heads[Pos].Next;
	
	while(P && strcmp(P->Data,Key))
		P = P->Next;
		
	return P;		
}

bool Insert(HashTable H, ElementType Key){
	
	Position P, NewCell;
	Index Pos;
	
	P = Find(H, Key);

	if(!P){
		NewCell = (Position)malloc(sizeof(struct LNode));
		strcpy(NewCell->Data,Key);
		Pos = Hash(Key,H->TableSize);
		
		NewCell->Next = H->Heads[Pos].Next;
		H->Heads[Pos].Next = NewCell;
		
		return true;
	}
	else{
		printf("键值已存在！\n");
		return false;
	}
}

void DestroyTable(HashTable H){
	int i;
	Position P, Temp;
	
	for(i = 0; i < H->TableSize; i++){
		P = H->Heads[i].Next;
		while(P){
			Temp = P->Next;
			free(P);
			P = Temp;
		}
	}
	free(H->Heads);
	free(H);
}

int main(){
	HashTable H;

	char Str1[15] = "123";
	H = CreateTable(10);
	Insert(H, Str1);
	Insert(H, Str1);
	Insert(H, "321");
} 
