#include<stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode{
	ElementType Element;
	Tree left;
	Tree right;
}T1[MaxTree], T2[MaxTree];

Tree BuildTree(struct TreeNode T[]){
	char cl,cr,n;
	int root = Null;
	int check[MaxTree]; 
	int i;
	
	printf("«Î ‰»ÎTreeNode ∏ˆ ˝£∫\n");
	scanf("%d",&n);
	if(!n) return root;
	for(i = 0; i < n; i++) check[i] = 0;
	for(i = 0; i < n; i++){
		scanf("\n%c %c %c",&T[i].Element,&cl,&cr);
		if(cl != '-'){
			T[i].left = cl - '0';
			check[T[i].left] = 1;
		}else{
			T[i].left = Null;
		}
		if(cr !='-'){
			T[i].right = cr - '0';
			check[T[i].right] = 1;
		}else
		{
			T[i].right = Null;
		}
	}
	for(i = 0; i < n; i++){
		if(!check[i])break;
	}
	root = i;
	return root;
}

Tree Isomorphic(Tree R1,Tree R2){
	if(R1 == Null && R2 == Null) return 1;
	if(((R1 != Null)&&(R2 == Null)) || ((R1 == Null)&&(R2 != Null))) 
		return 0;
	if((T1[R1].left == Null) && (T2[R2].left == Null))
		return Isomorphic(T1[R1].right,T2[R2].right); 
	if((T1[R1].left != Null)&&(T2[R2].left != Null) && 
		T1[T1[R1].left].Element == T2[T2[R2].left].Element)
		return (Isomorphic(T1[R1].left,T2[R2].left) &&
				Isomorphic(T1[R1].right,T2[R2].right));
	else{
		return 	(Isomorphic(T1[R1].left,T2[R2].right) &&
				Isomorphic(T1[R1].right,T2[R2].left));
	}
}

int main(){
	Tree R1,R2;
	
	R1 = BuildTree(T1);
	R2 = BuildTree(T2);
	
	if(Isomorphic(R1,R2))printf("Yes\n");
	else printf("No\n");
	return 0;
}
