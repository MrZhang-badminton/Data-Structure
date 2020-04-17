#include<stdio.h>

int Partion(int arr[],int left,int right){
	int info;
	int i,mid,temp;	
	
	info = arr[left];
	mid = left;

	for(i = left + 1; i <= right; i++){
		if(arr[i] <= info){
			mid++;
			temp = arr[mid];
			arr[mid] = arr[i];
			arr[i] = temp;
		}
	}
	
	temp = arr[left];
	arr[left] = arr[mid];
	arr[mid] = temp;
	
	return mid;
}

int Find(int arr[], int left, int right, int k){ 
	int mid = Partion(arr,left,right);

	if(k == mid)
		return arr[mid];
	else if(k < mid)
		return Find(arr,left,mid-1,k);
	else if(k > mid)
		return Find(arr,mid+1,right,k);
}


int main(){
	int arr[10]={6,7,2,8,1,9,3,5,4,10};
	int k,result;
	scanf("%d",&k);
	result = Find(arr,0,9,k-1); //找位置在4上的数，即找第五大的数 
	printf("%d\n",result);
}
