#include<stdio.h>
#include<stdlib.h> 

typedef int ElemType;

typedef struct TNode *Position;
typedef Position BinTree;

struct TNode{
	ElemType data;
	BinTree left;
	BinTree right;
}; 

BinTree Insert(BinTree BST, ElemType x){
	if(!BST){
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->data = x;
		BST->left = BST->right = NULL;
	}else{
		if(x < BST->data){
			BST->left = Insert(BST->left,x);
		}else if(x > BST->data){
			BST->right = Insert(BST->right,x);
		}//else相等的情况什么也不做 
	}
	return BST;
}

BinTree FinMin(BinTree BST){
	if(!BST) return NULL;
	while(BST->left){
		BST = BST->left;
	}
	return BST;
}

BinTree Delete(BinTree BST, ElemType x){
	BinTree temp;
	if(!BST)
		printf("要删除的元素未找到！\n");
	if(x < BST->data)
		BST->left = Delete(BST->left,x);
	else if (x > BST->data)
		BST->right = Delete(BST->right,x);
	else{
		if(BST->left && BST->right){
			temp = FinMin(BST->right);
			BST->data = temp->data;
			BST->right = Delete(BST->right,temp->data);
		}else{
			temp = BST;
			if(BST->left)
				BST = BST->left;
			else
				BST = BST->right;
			free(temp); 
		}
	}
	return BST;
}

int main(){
	BinTree T = NULL;
	T = Insert(T,3);

	T = Insert(T,1);
	T = Insert(T,2);
	T = Insert(T,5);
	T = Insert(T,4);
	T = Delete(T,1);
	printf("%5d\n",FinMin(T)->data);
	
}
