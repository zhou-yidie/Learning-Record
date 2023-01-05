#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,k,i,j;
	int **a;
	scanf("%d",&n);
	a=(int **)malloc(sizeof(int*)*(2*n-1));
	for(i=0;i<2*n-1;i++){
		a[i]=(int*)malloc(sizeof(int)*(2*n-1));
	}
	k=1;
	//三层循环，从外到内，“一层覆盖前一层的值”
	while(k<=n){
		for(i=k-1;i<=(2*n-1)-k;i++){
			for(j=k-1;j<=(2*n-1)-k;j++){
				a[i][j]=(n+1-k);
			}
		}
		k++;
	}
//输出正方形
	for(i=0;i<(2*n-1);i++){
		for(j=0;j<(2*n-1);j++){
			if(j>0)
				printf(" ");
			printf("%d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}

