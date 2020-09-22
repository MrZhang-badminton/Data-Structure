#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef struct AVLNode *Position;
typedef Position AVLTree;

struct AVLNode{
	ElemType data;
	AVLTree left;
	AVLTree right;
	int height;
}; 

int Max(int a,int b){
	return a > b ? a : b; 
}

int GetHeight(AVLTree T){
	if(!T)return 0;
	return T->height;
}

AVLTree SingleLeftRotation(AVLTree A){
// A必须有B左子节点 
	AVLTree B = A->left;
	A->left = B->right;
	B->right = A;
	A->height = Max(GetHeight(A->left),GetHeight(A->right)) + 1;
	B->height = Max(GetHeight(B->left),A->height) + 1;
	
	return B;
}

AVLTree SingleRightRotation(AVLTree A){
	AVLTree B = A->right;
	A->right = B->left;
	B->left = A;
	
	A->height = Max(GetHeight(A->left),GetHeight(A->right)) + 1;
	B->height = Max(GetHeight(B->right),A->height) + 1;
	
	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A){ 
	A->left = SingleRightRotation(A->left);
	return SingleLeftRotation(A); 
}

AVLTree DoubleRightLeftRotation(AVLTree A){
	A->right = SingleLeftRotation(A->right);
	return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T,ElemType x){
	if(!T){
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->data = x;
		T->height = 0;
		T->left = T->right = NULL;
	}
	else if(x < T->data){
		T->left = Insert(T->left, x);
		if(GetHeight(T->left) - GetHeight(T->right) == 2){
			if(x < T->left->data)
				T = SingleLeftRotation(T);
			else
				T = DoubleLeftRightRotation(T); 
		}
	}
	else if(x > T->data){
		T->right = Insert(T->left, x);
		if(GetHeight(T->right) - GetHeight(T->left) == 2){
			if(x > T->right->data)
				T = SingleRightRotation(T);
			else
				T = DoubleRightLeftRotation(T);
		}
	}
	else{
		//T->data = x 的情况不需要插入 
	}
	
	T->height = Max(GetHeight(T->left),GetHeight(T->right)) + 1;
	
	return T;
}

int main(){
	AVLTree A = NULL;
	A = Insert(A,3);
	A = Insert(A,2);
	A = Insert(A,1);
	printf("%d\n",A->right->data);
}
