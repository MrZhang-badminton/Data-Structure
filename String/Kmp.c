#include<stdio.h>
#include<string.h>

void GetNext(char *p,int *next){
	int pLen = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	
	while(j < pLen - 1){
		if(k == -1 || p[j] == p[k]){
			++k;
			++j;
			next[j] = k;
		}else{
			k = next[k];
		}
	}
}

int KmpSearch(char *s, char *p){
	int i = 0;
	int j = 0;
	int sLen = strlen(s);
	int pLen = strlen(p);
	int next[pLen];
	
	//��ʼ��next[] ���� 
	GetNext(p, next);
	
	while(i < sLen && j < pLen){
		if( j == -1 || s[i] == p[j]){
			i++;
			j++;
		}else{
			j = next[j];
		}
	}
	if( j == pLen)
		return i - j;
	else
		return -1;
}

//����ƥ���㷨 
int SimpleMatch(char *s, char *p){
	int i = 0;
	int j = 0;
	int sLen = strlen(s);
	int pLen = strlen(p);
	
	while( i < sLen && j < pLen){
		if(s[i] == p[j]){
			i++;
			j++;
		}else{
			//����ָ����˵�����ƥ��ͷ����һ��λ�� 
			i = i - j + 1;
			//ģʽ��ָ����˵�ģʽ����һ�� 
			j = 0;
		}
	}
	
	if( j == pLen)
		return i - j;
	else
		return -1;
}

int main(){
	char s[10] = {1,2,3,4,4,4,5,5,5,5};
	char p[3] = {4,4,4};
	int k;
	//k = SimpleMatch(s, p);
	k = KmpSearch(s, p); 
	printf("%d\n",k);
}
