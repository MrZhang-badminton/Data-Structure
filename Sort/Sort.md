

# 排序算法学习总结（C语言）

*总结包括：冒泡排序、选择排序、插入排序、希尔排序、堆排序、归并排序、快速排序、桶排序。*

## 冒泡排序（BubbleSort）

冒泡排序是相邻两个数进行比较每次把较大的数移到后面，每一趟执行完成之后，最大数都会被移到该趟的最后面。

时间复杂度 | 最好情况 | 最坏情况 | 额外空间复杂度 | 稳定性
:---:|:---:|:---:|:---:|:---:
O(n^2)|O(n^2)|O(n^2)|O(1)|稳定


```c
void BubbleSort(ElemType Arr[], int N){
	int i,j;
	
	for(i = N-1; i > 0; i--)
		//每组待排元素倒数第二个元素截止 
		for(j = 0; j < i; j++)
			if(Arr[j] > Arr[j+1])
				Swap(Arr+j, Arr+j+1);	
}
```
+ **冒泡算法的改进**  
当冒泡排序中间某一趟跑完之后，数组已经排序完成。但是上述代码还是在继续执行，直到最后最左面两个数比较完才结束。所以，当数组已经排序号（即此趟无交换时）break出来。**最好情况**的时间变成了**O(n)**。
```c
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
```

## 选择排序（SelectSort)
选择排序是每趟将最大或者最小的数放到待排序列的一端。该方法相对更好理解。但是无论最好还是最坏情况，其时间复杂度都是O(n^2)。

时间复杂度 | 最好情况 | 最坏情况 | 额外空间复杂度 | 稳定性
:---:|:---:|:---:|:---:|:---:
O(n^2)|O(n^2)|O(n^2)|O(1)|不稳定

```c
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
```

## 插入排序（InsertSort）
插入排序与生活中打牌类似，每次取牌插入手中已经排好序的牌当中。最好的情况时间复杂度为O(n)，也就是每次都插在排好序的牌的后面(即不需要挪动已经排好的数)。

时间复杂度 | 最好情况 | 最坏情况 | 额外空间复杂度 | 稳定性
:---:|:---:|:---:|:---:|:---:
O(n^2)|O(n)|O(n^2)|O(1)|稳定
```c
void InsertSort(ElemType Arr[], int N){
	int i,j, Tmp;
	
	for(i = 1; i < N; i++){
		Tmp = Arr[i];
		for(j = i; j > 0 && Arr[j-1] > Tmp; j--)
			Arr[j] = Arr[j-1];
		Arr[j] = Tmp;
	}
}
```

## 希尔排序（ShellSort）

希尔排序是插入排序的优化版本。希尔排序也是首次将时间复杂度降到O(n^2)以下的排序算法之一。希尔排序将先比较距离较大的元素。通俗的讲，就是对待排序数组进行预处理，让每组里面两个数的跨度减小。这里采用了Sedgewick增量序列。

时间复杂度 | 最好情况 | 最坏情况 | 额外空间复杂度 | 稳定性
:---:|:---:|:---:|:---:|:---:
O(n^k)|O(n^k)|O(n^2)|O(1)|不稳定

*注： k < 2，取决于选的增量序列。*

```c
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
```

## 堆排序（HeapSort）

堆排序利用的是最小/大堆的结构进行排序。首先将数组调整为堆，然后每次取堆顶元素，与待排序列最后一个数交换，重新下滤，调整为堆结构。

时间复杂度 | 最好情况 | 最坏情况 | 额外空间复杂度 | 稳定性
:---:|:---:|:---:|:---:|:---:
O(nlogn)|O(nlogn)|O(nlogn)|O(1)|不稳定

```c
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
```

## 归并排序（MergeSort）

归并排序采用的是分治思想，选取每次待排序列的中间作为分界。然后，将左边和右边的数组分别递归采用归并排序，然后将排序好的左右两边的数组合并。归并排序有一个缺点就是，占用O(n)的空间。当我们满载运行的时候只能排序空间一半的数。  

**注：**由于每次合并时都要开辟新的数组用于存储排序好的数组，严重占用了内存。这里，将开始申请一个数组，其地址作为参数传入递归函数。这样就相当于每次递归都用这个临时数组的一部分。

时间复杂度 | 最好情况 | 最坏情况 | 额外空间复杂度 | 稳定性
:---:|:---:|:---:|:---:|:---:
O(nlogn)|O(n)|O(nlogn)|O(n)|稳定

+ 递归
```c
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
```
+ 非递归
```c
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
```

## 快速排序（QuickSort）
快速排序采用的是分治法。每次在待排序列中取一个基数，然后将比其小的数都移到左面，比其大的数都移到右面。然后在将左面的数组和右面的数组，分别执行上述过程，直至结束。其中最坏的情况就是每次基数都是待排序列中的最小数或者最大数，导致另一边没有数。

> 该排序算法可联想到找N个无序数中第K大个数问题

时间复杂度 | 最好情况 | 最坏情况 | 额外空间复杂度 | 稳定性
:---:|:---:|:---:|:---:|:---:
O(nlogn)|O(nlogn)|O(n^2)|O(logn)|不稳定

```c
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
//统一接口
void QuickSort(ElemType Arr[], int N){
	QSort(Arr, 0, N-1);
```
**另一种写法**  （更便于理解）

```c
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
}
```

## 桶排序（BucketSort）

桶排序适用于分布较为均匀的数组，如果分布很不均匀用桶排序效率很低。对于每个桶内的元素，这里都采用了快速排序进行排序。

时间复杂度 | 最好情况 | 最坏情况 | 额外空间复杂度 | 稳定性
:---:|:---:|:---:|:---:|:---:
O(N+K)|O(N+K)|O(n^2)|O(N+K)|稳定

```c
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
	for(int i = 0; i < Num; i++){
		//每个桶中元素用快速排序进行排序 
		QuickSort((Ptr + i)->Node, (Ptr +i)->Count);
		
		for(j = 0; j < (Ptr + i)->Count; j++){
			Arr[Pos++] = (Ptr + i)->Node[j];
		}
	}
	//释放桶空间 
	free(Ptr);
} 
```