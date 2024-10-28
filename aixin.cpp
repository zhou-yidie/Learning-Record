#include<stdio.h>
#include<stdlib.h>

int main(int argc,char*argv[]){
	
float x,y,a;
	
for(y=1.5;y>-1.5;y-=0.1){
		
for(x=-1.5;x<1.5;x+=0.05){

a=x*x+y*y-1;

putchar(a*a*a-x*x*y*y*y<=0.0?'@':' ');

}

system("COLOR 0c");

putchar('\n');
		
}

printf("送您一个爱心，祝你每天开心");

printf("\n\n");

return 0;
	
}
