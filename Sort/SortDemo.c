#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h> 

#define MAXSIZE 10  //排序的数的个数 
#define inf 0x3f3f3f3f
#define bool int
#define false 0
#define true 1 

typedef int ElemType;

void Swap(ElemType *a, ElemType *b){
	ElemType t;
	t = *a;
	*a = *b;
	*b = t;
}

void BubbleSort(ElemType Arr[], int N){
	int i,j;
	
	for(i = N-1; i > 0; i--)
		//每组待排元素倒数第二个元素 
		for(j = 0; j < i; j++)
			if(Arr[j] > Arr[j+1])
				Swap(Arr+j, Arr+j+1);	
}



void BubbleSort_2(ElemType Arr[], int N){
	int i,j;
	bool flag;//是否有交换标志
	
	for(i = N-1; i > 0; i--){
	    flag = false;
		//每组待排元素倒数第二个元素截止 
		for(j = 0; j < i; j++)
			if(Arr[j] > Arr[j+1]){
				Swap(Arr+j, Arr+j+1);
			    flag = true;
			}	
	    if(!flag)break;//无交换时退出循环 
	}
}

void SelectSort(ElemType Arr[], int N){
	int i, j, Min, Index;
	
	for(i = 0; i < N; i++){
		Min = inf;
		for(j = i; j < N; j++)
			if(Arr[j] < Min){
				Index = j;
				Min = Arr[j];
			}
		Swap(Arr+Index,Arr+i);
		//等价于Swap(&Arr[Index],&Arr[i]); 
	}
}

void InsertSort(ElemType Arr[], int N){
	int i,j, Tmp;
	
	for(i = 1; i < N; i++){
		Tmp = Arr[i];
		for(j = i; j > 0 && Arr[j-1] > Tmp; j--)
			Arr[j] = Arr[j-1];
		Arr[j] = Tmp;
	}
}

void ShellSort(ElemType Arr[], int N){
	int Index, i, j, Interval;
	ElemType Tmp;
	
	int Sedgewick[] = {929, 505, 209, 41, 19, 5, 1, 0};
	//找到不大于N的Sedgewick值 
	for(Index = 0; Sedgewick[Index] > N; Index++);
	
	for(Interval = Sedgewick[Index]; Interval > 0; Interval = Sedgewick[++Index])
		for(i =	Interval; i < N; i++){
			Tmp = Arr[i];
			for(j = i; j >= Interval && Arr[j-Interval] > Tmp; j -= Interval)
				Arr[j] = Arr[j-Interval];
			Arr[j] = Tmp;
		}
}

//下滤操作 
void PerDown(ElemType Arr[], int Pos, int N){
    int Parent, Child;
   	ElemType Tmp;
    Tmp = Arr[Pos];
    
    for(Parent = Pos;(Parent*2)+ 1 < N;Parent = Child ){
        Child = Parent*2 + 1;
        if((Child + 1) < N && Arr[Child] < Arr[Child+1])
            Child++;
        if(Tmp < Arr[Child])
        	Arr[Parent] = Arr[Child];
		else
			break;
    }
    
    Arr[Parent] = Tmp;
    
}

void HeapSort(ElemType Arr[], int N){
    int i;
    //建堆 
    for(i = N/2-1; i >= 0; i--)
       	PerDown(Arr, i, N);
    //依次取出待排序列中的最大数 
    for(i = N - 1; i > 0; i--){
        Swap(Arr, Arr+i);
        PerDown(Arr, 0, i);
    }
}

/*
int Partition(ElemType Arr[], int Left, int Right){
	ElemType Tmp;
	
	Tmp = Arr[Left];
	
	while(Left < Right){
		while(Left < Right && Arr[Right] >= Tmp) Right--;
		Arr[Left] = Arr[Right];
		while(Left < Right && Arr[Left] <= Tmp) Left++;
		Arr[Right] = Arr[Left];
		
	}
	Arr[Left] = Tmp;
	return Left;
	
}

void QSort(ElemType Arr[], int Left, int Right){
	int Pivot;
	
	if(Right <= Left) return;
	Pivot = Partition(Arr, Left, Right);
	
	QSort(Arr, Left, Pivot-1);
	QSort(Arr, Pivot+1, Right);
}*/

void QSort(ElemType Arr[], int Left, int Right){
	int Low, High;
	ElemType Tmp;
	
	if(Left >= Right) return;
	Low = Left;
	High = Right;
	Tmp = Arr[Left];
	while(Low < High){
		while(Low < High && Arr[High] >= Tmp) High--;
		Arr[Low] = Arr[High];
		while(Low < High && Arr[Low] <= Tmp) Low++;
		Arr[High] = Arr[Low];
	}
	Arr[Low] = Tmp;
	QSort(Arr, Left, Low-1);
	QSort(Arr, Low+1, Right);
} 

void QuickSort(ElemType Arr[], int N){
	QSort(Arr, 0, N-1);
}
/*------------------------递归归并排序-----------------------*/ 
void Merge(ElemType Arr[], int TArr[], int Left, int Center, int Right){
	int i, j, Index, ArrNums;
	i = Left;
	j = Center + 1;
	Index = Left;
	ArrNums = Right - Left + 1;
	
	while(i <= Center && j <= Right){
		if(Arr[i] <= Arr[j])
			TArr[Index++] = Arr[i++];
		else
			TArr[Index++] = Arr[j++];
	}
	while(i <= Center) TArr[Index++] = Arr[i++];
	while(j <= Right) TArr[Index++] = Arr[j++];
	
	for(i = 0; i < ArrNums; i++, Left++)
		Arr[Left] = TArr[Left];
}

void MSort(ElemType Arr[], ElemType TArr[], int Left, int Right){
	int Center;
	
	if(Left < Right){
		Center = (Left + Right) / 2;
		MSort(Arr, TArr, Left, Center);
		MSort(Arr, TArr, Center+1, Right);
		Merge(Arr, TArr, Left, Center, Right);
	}
	
}

void MergeSort(ElemType Arr[], int N){
	ElemType *TArr;
	TArr = (ElemType*)malloc(sizeof(ElemType)*N);
	
	MSort(Arr, TArr, 0, N-1);
	//释放临时数组空间 
	free(TArr);
}
/*---------------------------------------------------------------------*/


/*------------------------非递归排序-------------------------*/ 
void Merge_2(ElemType Arr[], int TArr[], int Left, int Center, int Right){
	int i, j, Index, ArrNums;
	i = Left;
	j = Center + 1;
	Index = Left;
	ArrNums = Right - Left + 1;
	
	while(i <= Center && j <= Right){
		if(Arr[i] <= Arr[j])
			TArr[Index++] = Arr[i++];
		else
			TArr[Index++] = Arr[j++];
	}
	while(i <= Center) TArr[Index++] = Arr[i++];
	while(j <= Right) TArr[Index++] = Arr[j++];
	

}

void MSort_2(ElemType Arr[], ElemType TArr[], int N, int Length){
	int i, j;
	
	for(i = 0; i < N - 2*Length; i += 2*Length)
		Merge_2(Arr, TArr, i, i + Length - 1, i + 2*Length - 1);
	//单独处理尾巴	
	if(i + Length < N)
		Merge_2(Arr, TArr, i, i + Length - 1, N - 1);
	else
		for(j = i; j < N; j++)
			TArr[j] = Arr[j]; 
}

void MergeSort_2(ElemType Arr[], int N){
	ElemType *TArr;
	int Length;
	
	Length = 1;
	TArr = (ElemType*)malloc(sizeof(ElemType)*N);
	
	while(Length < N){
		//MSort_2函数中不再将TArr临时数组拷贝回 Arr 
		MSort_2(Arr, TArr, N, Length);
		Length *= 2;
		MSort_2(TArr, Arr, N, Length);
		Length *= 2;
	}
	//释放临时数组空间 
	free(TArr);
}
/*---------------------------------------------------------------*/

//桶排序  以下代码还有缺陷只能针对规模较小的数组 
 typedef struct Node{
	ElemType Node[100];// volume of each bucket
	int Count;
}Bucket;

void BucketSort(ElemType Arr[],int N){
	ElemType Max, Min;
	int i, j, k, Num, Pos; 
	Bucket *Ptr;
	
	Max = Arr[0];
	Min = Arr[0];
	for(i = 1; i < N; i++){
		if(Arr[i] > Max)
			Max = Arr[i];
		if(Arr[i] < Min)
			Min = Arr[i];
	}

	Num = (Max - Min + 1)/100 + 1;

	Ptr = (Bucket *)malloc(sizeof(Bucket) * Num);
	//本题中作用是将每个桶中的Node[]数组和Count置0
	//可自行百度 
	memset(Ptr, 0, sizeof(Bucket) * Num);
	
	//将数组装入每个桶中 
	for(i = 0; i < N; i++){
		k = (Arr[i] - Min + 1)/100;
		(Ptr + k)->Node[(Ptr + k)->Count] = Arr[i];
		(Ptr + k)->Count++;
	} 
	
	Pos = 0;
 	//将桶中元素分别排序好，依次放入原来数组中 
	for(i = 0; i < Num; i++){
		//每个桶中元素用快速排序进行排序 
		QuickSort((Ptr + i)->Node, (Ptr +i)->Count);
		
		for(j = 0; j < (Ptr + i)->Count; j++){
			Arr[Pos++] = (Ptr + i)->Node[j];
		}
	}
	//释放桶空间 
	free(Ptr);
} 

void PrintArray(ElemType Arr[], int N){
	int i;
	for(i = 0; i < N; i++){
		printf("%5d",Arr[i]);
		if(!((i+1)%10))
			printf("\n");
	}
	printf("\n");
}

int main(){
	//int Arr[MAXSIZE] = {7,21,6,66,24,82,99,1,10,11};
	int i;
	int Arr[MAXSIZE];
	srand((unsigned)time(NULL));
	for(i = 0; i < MAXSIZE; i++)
		Arr[i] = rand()%101;
		
	printf("排序前的数组：\n\n");
	PrintArray(Arr,MAXSIZE);
	
	BucketSort(Arr,MAXSIZE);
	
	printf("排序后的数组：\n\n");
	PrintArray(Arr,MAXSIZE);
}
