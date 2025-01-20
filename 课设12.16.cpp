#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>//头文件 

struct bicycle {
	char tele_num[12];//用户的电话号码 
	char name[13];//用户的姓名
	char sex[7];//用户的性别 
	char bic_num[12];//自行车的编号 
	struct bicycle* next;
};

int iCount = 0;
struct bicycle* pHead = NULL;

void key(); //密码 
void menu();//菜单 
void create();//创建链表函数 
void print(); //输出链表自行车的信息
void insert();//插入自行车的信息
void search();//查找 
void dele();//删除信息函数
void modify();//2.修改自行车的信息
void excheng(struct bicycle* pStra, struct bicycle* Midd);//交换函数
void sort();//6.自行车信息的排序

int main() {


	menu();
	printf("123");

	return 0;
}

//密码管理页面 
void key() {
	char key[20], m[20];
	FILE* k;
	k = fopen("key.txt", "r");                                          //
	if (k == NULL)
	{
		k = fopen("key.txt", "wt");
		printf("请创建密码:\n");
		scanf("%s", key);
		fprintf(k, "%s", key);
		fclose(k);
		printf("恭喜您创建成功!\n");
		getchar();
		printf("按任意键继续...");
		getchar();
		return;
	}
	else
	{
		fscanf(k, "%s", m);
		fclose(k);
		printf("请输入管理密码:");
		scanf("%s", key);
		if (strcmp(m, key) == 0)
		{
			printf("密码正确!\n");
			getchar();
			printf("按任意键继续...");
			getchar();
			return;
		}
		else
		{
			printf("密码错误!\n");
			getchar();
			printf("按任意键继续...");
			getchar();
			return;
		}
	}
}

//显示菜单的信息 
void menu() {
	key();
	int select = -1;

	while (select != 0) {
		system("cls");                                                                //
		printf("\n\n\t==============欢迎使用自行车管理系统==============\n");
		printf("\t\t\t=======请选择功能=======\n");
		printf("\t\t\t1.录入自行车信息\n");
		printf("\t\t\t2.修改自行车信息\n");
		printf("\t\t\t3.删除自行车信息\n");
		printf("\t\t\t4.查询自行车信息\n");
		printf("\t\t\t5.打印自行车信息\n");
		printf("\t\t\t6.自行车信息排序\n");
		printf("\t\t\t7.插入自行车信息\n");
		printf("\t\t\t0.退   出   菜  单\n");
		printf("\n请选择：");
		scanf("%d", &select);
		switch (select) {
		case 1:
			create();
			break;
		case 2:
			modify();
			break;
		case 3:
			dele();
			break;
		case 4:
			search();
			break;
		case 5:
			print();
			break;
		case 6:
			sort();
			break;
		case 7:
			insert();
			break;
		case 0:break;
		default:
			exit(1);
			break;
		}
	}


}

//创建链表函数
void create() {
	system("cls");     //清屏函数 

	struct bicycle* pEnd, * pNew;
	struct bicycle* p;
	pEnd = pNew = (struct bicycle*)malloc(sizeof(struct bicycle));

	printf("请输入所存放自行车的信息(退出请按0):\n");

	//录入自行车编号，编号不可以重复
	int flag1 = 1, flag2, n;
	struct bicycle* pTemp;
	printf("\n自行车的编号(退出请按0):");
	scanf("%s", pNew->bic_num);

	while (flag1) {
		if (strcmp(pNew->bic_num, "0") == 0) {
			flag1 = 1;
			break;
		}

		else {
			pTemp = pHead;
			n = iCount;
			flag2 = 1;

			while (n && flag2) {
				if (strcmp(pTemp->bic_num, pNew->bic_num) == 0)  flag2 = 0;                   // strcmp() 
				pTemp = pTemp->next;
				n = n - 1;
			}

			if (flag2 == 0) {
				printf("请重新输入,自行车编号%s存在!(退出请按0):\n", pNew->bic_num);
				printf("自行车的编号:");
				scanf("%s", pNew->bic_num);
				flag1 = 1;
			}

			if (flag2 == 1) flag1 = 0;
		}
	}

	//录入其他信息，如果flag1=0，则表明要退出，那么其他信息不用再录
	if (flag1 != 1) {
		printf("姓名:");
		scanf("%s", pNew->name);

		//性别只能输入woman或man，否则是无法保存的
		while (1) {
			printf("性别(woman或man):");
			scanf("%s", pNew->sex);
			if (strcmp(pNew->sex, "woman") == 0 || strcmp(pNew->sex, "man") == 0) break;
			else printf("性别输入不规范，请核对后重新输入!\n");
		}

		//电话必须是11位数，否则是不规范的
		while (1) {
			printf("电话(11位数):");
			scanf("%s", pNew->tele_num);
			if (strlen(pNew->tele_num) == 11) break;
			else printf("电话输入不规范，必须11位数!\n");
		}

	}




	while (strcmp(pNew->bic_num, "0") != 0)
	{
		iCount++;

		if (pHead == NULL) {
			pNew->next = NULL;
			pEnd = pNew;
			pHead = pNew;
		}


		else {

			p = pHead;

			while (p && p->next != NULL) p = p->next;
			
			{
				p->next = pNew;
				pNew->next = NULL;
		    }
		}
		pNew = (struct bicycle*)malloc(sizeof(struct bicycle));


		printf("\n自行车的编号(退出请按0):");
		scanf("%s", pNew->bic_num);
		flag1 = 1;//每次循环结束flag1=1退出;flag1=0则继续，所以要值0
		while (flag1) {

			if (strcmp(pNew->bic_num, "0") == 0) {
				flag1 = 1;
				break;
			}

			else {
				pTemp = pHead;
				n = iCount;
				flag2 = 1;

				while (n && flag2) {
					if (strcmp(pTemp->bic_num, pNew->bic_num) == 0)  flag2 = 0;
					pTemp = pTemp->next;
					n = n - 1;
				}

				if (flag2 == 0) {
					printf("请重新输入,自行车的编号%s存在!(退出请按0):\n", pNew->bic_num);
					printf("自行车的编号:");
					scanf("%s", pNew->bic_num);
					flag1 = 1;
				}

				if (flag2 == 1) flag1 = 0;
			}
		}

		//录入其他信息，如果flag1=0，则表明要退出，那么其他信息不用再录
		if (flag1 != 1) {
			printf("姓名:");
			scanf("%s", pNew->name);

			//性别只能输入woman或man，否则是不规范的
			while (1) {
				printf("性别(woman或man):");
				scanf("%s", pNew->sex);
				if (strcmp(pNew->sex, "woman") == 0 || strcmp(pNew->sex, "man") == 0) break;
				else printf("性别输入不规范，请核对后重输!\n");
			}

			//电话必须11位数，否则是不规范的
			while (1) {
				printf("电话(11位数):");
				scanf("%s", pNew->tele_num);
				if (strlen(pNew->tele_num) == 11) break;
				else printf("电话输入不规范，必须11位数!\n");
			}

		}                                          //22

	}

	free(pNew);
}

//输出链表自行车的信息
void print() {

	//页面优化
	system("cls");
	printf("\n\n\t\t\t\t===================5.打印自行车的信息===================\n");

	struct bicycle* pTemp;
	int iIndex = 1;

	printf("**********本名单中共有%d个自行车信息，所有的信息如下:**********\n", iCount);
	printf("序号 姓名  性别  电话 自行车编号 \n");
	pTemp = pHead;

	while (pTemp != NULL) {
		printf("%d  %s  %s  %s  %s\n", iIndex, pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
		pTemp = pTemp->next;
		iIndex++;
	}
	printf("按任意键返回上一级");
	getch();
}

//插入自行车的信息
void insert() {
	//页面优化
	system("cls");
	printf("\n\n\t\t\t\t===================7.插入自行车的信息===================\n");
	printf("#\n说明：插入任意位置都可以\n#");
	create();
	printf("插入信息成功，");
	printf("按任意键返回上一级");
	getch();
}

//信息查询函数
void search() {
	//页面优化

	printf("\n\n\t\t\t\t===================4.查询自行车的信息===================");

	int select = -1;
	while (select != 0) {
		system("cls");
		printf("\t\t\t1.按自行车的编号查询\n");
		printf("\t\t\t0.退出此页面\n");
		printf("请选择：");
		scanf("%d", &select);
		int flag = 1, flag1 = 1;
		char number[12];
		char name[12];
		struct bicycle* pTemp = pHead;

		//按自行车的编号查询
		if (select == 1) {

			printf("请输入你要查找的自行车编号:");
			scanf("%s", number);
			while (pTemp != NULL && flag)
			{
				if (strcmp(pTemp->bic_num, number) == 0)
				{
					printf("%s找到了，具体信息如下:\n\n", number);

					printf("\t姓名  性别  电话 自行车编号 \n");
					printf("\t%s  %s  %s  %s\n", pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
					printf("\n");
					flag = 0;
				}
				pTemp = pTemp->next;
			}
			if (flag == 1)  printf("编号%s不存在!\n", number);
		}
		printf("按任意键返回上一级");
		getch();
	}
}

//删除信息函数
void dele() {
	//页面优化
	system("cls");
	printf("\n\n\t\t\t\t===================3.删除自行车的信息(按编号)===================");

	int select = -1;
	while (select != 0) {
		printf("\t\t\t1.按自行车的编号删除\n");
		printf("\t\t\t2.按   姓  名  删 除 \n");
		printf("\t\t\t0.退出此页面(lv4)\n");

		printf("请选择：");
		scanf("%d", &select);

		if (select == 0) return;
		else if (select == 1 || select == 2) break;
		else printf("输入有误请重新输入\n");
	}

	if (select == 1) {

		if (iCount == 0)  printf("\n\n暂无数据无法进行此操作，按任意键退出!\n");
		else
		{                                                              //33

			char number[12];
			int  i, flag = 1;
			char option;
			struct bicycle* pTemp;
			struct bicycle* pPre;
			pTemp = pHead;

			int iIndex = 0;
			printf("\n请输入要删除自行车的编号:");
			scanf("%s", number);

			while (pTemp != NULL && flag) {
				if (strcmp(pTemp->bic_num, number) == 0) {
					printf("\n%s找到了，将要删除的信息如下\n\n", number);
					//显示将要删除人的信息
					printf("\t姓名  性别  电话 自行车编号 \n");
					printf("\t%s  %s  %s  %s\n", pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
					printf("\n");
					flag = 0;

					printf("确认删除请输1，否则按任意数字键退出\n");
					scanf("%d", &option);
				}


				pTemp = pTemp->next;
				iIndex++;
			}
			if (flag == 1) { printf("编号%s不存在!", number);  return; }



			if (option == 1) {
				pTemp = pHead;
				pPre = pTemp;//可能多余
				//printf("----------删除第%d个学生----------\n",iIndex);

				if (iIndex != 1)
				{
					for (i = 1; i < iIndex; i++)
					{
						pPre = pTemp;
						pTemp = pTemp->next;
					}

					pPre->next = pTemp->next;

				}


				if (iIndex == 1)	pHead = pTemp->next;
				free(pTemp);
				iCount--;
				printf("删除成功按任意键退出!");
			}
			else  printf("删除失败按任意键退出!");
		}                                                               //33

		getch();

	}
	else {
		if (iCount == 0)  printf("\n\n暂无数据无法进行此操作，按任意键退出!\n");
		else
		{                                                              //33
			char name[12];
			int  i, flag = 1;
			char option;
			struct bicycle* pTemp;
			struct bicycle* pPre;
			pTemp = pHead;

			int iIndex = 0;
			printf("\n请输入要删除自行车对应户主的姓名:");
			scanf("%s", name);

			while (pTemp != NULL && flag) {
				if (strcmp(pTemp->name, name) == 0) {
					printf("\n%s找到了，将要删除的信息如下\n\n", name);
					//显示将要删除人的信息
					printf("\t姓名  性别  电话 自行车编号 \n");
					printf("\t%s  %s  %s  %s\n", pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
					printf("\n");
					flag = 0;

					printf("确认删除请输1，否则按任意数字键退出\n");
					scanf("%d", &option);
				}


				pTemp = pTemp->next;
				iIndex++;
			}
			if (flag == 1) { printf("姓名%s不存在!", name);  return; }



			if (option == 1) {
				pTemp = pHead;
				pPre = pTemp;//可能多余
				//printf("----------删除第%d个学生----------\n",iIndex);

				if (iIndex != 1)
				{
					for (i = 1; i < iIndex; i++)
					{
						pPre = pTemp;
						pTemp = pTemp->next;
					}

					pPre->next = pTemp->next;

				}


				if (iIndex == 1)	pHead = pTemp->next;
				free(pTemp);
				iCount--;
				printf("删除成功按任意键退出!");
			}
			else  printf("删除失败按任意键退出!");
		}                                                               //33

		getch();
	}

}

//2.修改自行车的信息
void modify() {

	//页面优化
	system("cls");
	printf("\n\n\t\t\t\t===================2.修改自行车的信息===================");

	int post;
	int flag = 1, flag1;
	char number[12];
	struct bicycle* pTemp = pHead, * pPre = pTemp;

	printf("\n请输入你要修改自行车信息对应自行车的编号:");
	scanf("%s", number);

	while (pTemp != NULL && flag)
	{

		if (strcmp(pTemp->bic_num, number) == 0)
		{
			printf("将要修改的编号%s具体信息如下\n", number);
			printf("\t姓名  性别  电话 自行车编号 \n");
			printf("\t%s  %s  %s  %s\n", pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
			printf("\n");
			flag = 0;
		}
		pPre = pTemp;       //保存pTemp
		pTemp = pTemp->next;
	}

	if (flag == 1)  printf("你要修改的编号%s不存在!", number);
	else
	{
		printf("确认修改请按1,放弃请按任意数字键!\n请选择：");
		scanf("%d", &post);

		while (post == 1)
		{
			printf("请选择你要修改的项目(1.姓名 2.性别 3.电话号码 4.自行车的编号 5.修改全部)\n");
			scanf("%d", &flag1);

			if (flag1 == 1)
			{
				printf("新姓名:");
				scanf("%s", pPre->name);
				printf("修改完成,按任意键退出!");
			}

			else if (flag1 == 2)
			{
				printf("新性别:");
				scanf("%s", pPre->sex);
				printf("修改完成,按任意键退出!");
			}

			else if (flag1 == 3)
			{

				while (1) {
					printf("电话(11位数):");
					scanf("%s", pPre->tele_num);
					if (strlen(pPre->tele_num) == 11) break;
					else printf("电话输入不规范，必须11位数!\n");
				}

				printf("修改完成,按任意键退出!");
			}

			else if (flag1 == 4)
			{
				printf("新编号:");
				scanf("%d", &pPre->bic_num);
				printf("修改完成,按任意键退出!");
			}

			else {

				printf("新姓名:");
				scanf("%s", pPre->name);

				printf("新性别:");
				scanf("%s", pPre->sex);

				while (1) {
					printf("电话(11位数):");
					scanf("%s", pPre->tele_num);
					if (strlen(pPre->tele_num) == 11) break;
					else printf("电话输入不规范，必须11位数!\n");
				}

				printf("新编号:");
				scanf("%s", pPre->bic_num);

			}
			break;
		}


	}

	printf("修改完成，按任意键退出");
	getch();

}

//交换函数
void excheng(struct bicycle* pStra, struct bicycle* pMidd) {
	int t;
	struct bicycle* pTemp;
	pTemp = (struct bicycle*)malloc(sizeof(struct bicycle));

	strcpy(pTemp->tele_num, pStra->tele_num);
	strcpy(pStra->tele_num, pMidd->tele_num);
	strcpy(pMidd->tele_num, pTemp->tele_num);

	strcpy(pTemp->bic_num, pStra->bic_num);
	strcpy(pStra->bic_num, pMidd->bic_num);
	strcpy(pMidd->bic_num, pTemp->bic_num);

	strcpy(pTemp->name, pStra->name);
	strcpy(pStra->name, pMidd->name);
	strcpy(pMidd->name, pTemp->name);

	strcpy(pTemp->sex, pStra->sex);
	strcpy(pStra->sex, pMidd->sex);
	strcpy(pMidd->sex, pTemp->sex);

	free(pTemp);

}

//6.自行车信息的排序
void sort() {

	//页面优化
	printf("\n\n\t\t===================4.排序系统===================");

	int i, j;
	struct bicycle* pStra, * pMidd;

	int result;
	int select = -1;
	while (select != 0)
	{
		system("cls");
		printf("\n\t\t\t=======请选择功能列表=======\n");
		printf("\t\t\t1.按自行车编号升序排序\n");
		printf("\t\t\t2.按自行车编号降序排序\n");
		printf("\t\t\t0.退出此页面\n");
		printf("请选择：");
		scanf("%d", &select);

		result = select;
		if (select != 1 && select != 2) return;


		pStra = pHead;
		pMidd = pStra->next;


		for (i = 0; i < iCount; i++)
		{
			pStra = pHead;
			pMidd = pStra->next;

			for (j = 0; j < iCount - i - 1 && pMidd != NULL; j++)
			{
				if (result == 1) { if (strcmp(pStra->bic_num, pMidd->bic_num) > 0)           excheng(pStra, pMidd); }
				else if (result == 2) { if (strcmp(pStra->bic_num, pMidd->bic_num) < 0)      excheng(pStra, pMidd); }
				pStra = pMidd;
				pMidd = pMidd->next;
			}
		}


		printf("\t\t\t3.显示排完序后的结果为：\n\n");
		printf("------------------------------------------------------");
		struct bicycle* pTemp;
		int iIndex = 1;

		printf("**********本名单中共有%d个自行车信息，:**********\n", iCount);
		printf("序号 姓名  性别  电话 自行车编号 \n");
		pTemp = pHead;

		while (pTemp != NULL) {
			printf("%d  %s  %s  %s  %s\n", iIndex, pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
			pTemp = pTemp->next;
			iIndex++;
		}

		printf("------------------------------------------------------");


		printf("\n\n排序成功，按任意键返回!");

		getch();
	}
}
