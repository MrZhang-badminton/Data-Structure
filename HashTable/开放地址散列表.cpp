#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAXTABLESIZE 100000

typedef int ElementType;
typedef int Index;
typedef Index Position;

typedef enum{
	Legitimate, Empty, Deleted
}EntryType; 

typedef struct HashEntry Cell;
struct HashEntry{
	ElementType Data;
	EntryType Info;
};

typedef struct TblNode *HashTable;
struct TblNode{
	int TableSize;
	Cell *Cells;
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
	
	H->Cells = (Cell*)malloc(H->TableSize*sizeof(Cell));
	
	for(i = 0; i < H->TableSize; i++)
		H->Cells[i].Info = Empty;
		
	return H;
}

Position Hash(ElementType Key, int TableSize){
	return Key % TableSize; 
} 

Position Find(HashTable H, ElementType Key){
	Position CurPos, NewPos;
	int CNum = 0;
	
	NewPos = CurPos  = Hash(Key, H->TableSize);
	
	while(H->Cells[NewPos].Info != Empty &&
	H->Cells[NewPos].Data != Empty){
		
		if(++CNum%2){
			NewPos = CurPos + (CNum+1)*(CNum+1)/4;
			//增量为+[(CNum+1)/2]^2 
			if(NewPos >= H->TableSize)
				NewPos = NewPos % H->TableSize;
		}
		else{
			NewPos = CurPos - CNum*CNum/4;
			//增量为(CNum/2)^2 
			while(NewPos < 0)
				NewPos += H->TableSize;
		}
	}
	
	return NewPos;
}

bool Insert(HashTable H, ElementType Key){
	Position Pos = Find(H,Key);
	
	if(H->Cells[Pos].Info != Legitimate){
		H->Cells[Pos].Data = Key;
		H->Cells[Pos].Info = Legitimate;
		
		return true;
	}
	else{
		printf("键值已存在！\n");
		return false;
	}
}

int main(){
	HashTable H;
	H = CreateTable(10);
	Insert(H,1);
	Insert(H,2);
	
	printf("%d\n",Find(H,13));
	
	
} 
