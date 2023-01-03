#include<stdio.h>

struct node 
{
	char name;
	int mark;
}a[200010];


int main()
{
	int n;
	int num_stu;
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
	{
		int num;    //现在的操作编号 
		char name_tmp;   //输入的名字 
		int mark_tmp;    //成绩
		scanf("%d",&num);
		if(num == 1)
		{
			scanf("%s %d", &name_tmp, &mark_tmp);
			int flag =false;
			for(int j = 1;j <= num_stu;j++)
			{
				if(a[j].name == name_tmp)
				{
					a[j].mark =mark_tmp;
					printf("OK");
				}
				if(i != n)flag =true;break;
			}
			if(!flag)
			{
				num_stu ++;
				a[num_stu].name = name_tmp;
				a[num_stu].mark = mark_tmp;
				printf("OK");
			}
		}
		
		if(num == 2)
		{
			scanf("%s", &name_tmp);
			int flag = false;
			for(int j = 1;j <= num_stu;j++)
			if(a[j].name == name_tmp)
			{
				printf("%d",a[j].mark);
				if(i != n)
				flag = true;break;
			}
			if(!flag)
			{
				printf("Not found");
				if(i != n)printf("\n");
			}
		}
		
		if(num == 3)
		{
			scanf("%s",&name_tmp);
			int flag = false;
			for(int j = 1;j <= num_stu;j++)
			if(a[j].name == name_tmp)
			{
				flag = true;
				a[j].name = a[num_stu].name;
				a[j].mark = a[num_stu].mark;
				num_stu--;
				printf("Deleted successfully");
				if(i != n)printf("\n");break;
			}
			if(!flag)
			{
				printf("Not found");
				if(i != n)printf("\n");
			}
			
		}
		
		if(num == 4)
		{
			printf("%d",num_stu);
			if(i != n)printf("\n");
		} 
	}
	return 0;
}
