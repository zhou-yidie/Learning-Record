#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>//ͷ�ļ� 

struct bicycle {
	char tele_num[12];//�û��ĵ绰���� 
	char name[13];//�û�������
	char sex[7];//�û����Ա� 
	char bic_num[12];//���г��ı�� 
	struct bicycle* next;
};

int iCount = 0;
struct bicycle* pHead = NULL;

void key(); //���� 
void menu();//�˵� 
void create();//���������� 
void print(); //����������г�����Ϣ
void insert();//�������г�����Ϣ
void search();//���� 
void dele();//ɾ����Ϣ����
void modify();//2.�޸����г�����Ϣ
void excheng(struct bicycle* pStra, struct bicycle* Midd);//��������
void sort();//6.���г���Ϣ������

int main() {


	menu();
	printf("123");

	return 0;
}

//�������ҳ�� 
void key() {
	char key[20], m[20];
	FILE* k;
	k = fopen("key.txt", "r");                                          //
	if (k == NULL)
	{
		k = fopen("key.txt", "wt");
		printf("�봴������:\n");
		scanf("%s", key);
		fprintf(k, "%s", key);
		fclose(k);
		printf("��ϲ�������ɹ�!\n");
		getchar();
		printf("�����������...");
		getchar();
		return;
	}
	else
	{
		fscanf(k, "%s", m);
		fclose(k);
		printf("�������������:");
		scanf("%s", key);
		if (strcmp(m, key) == 0)
		{
			printf("������ȷ!\n");
			getchar();
			printf("�����������...");
			getchar();
			return;
		}
		else
		{
			printf("�������!\n");
			getchar();
			printf("�����������...");
			getchar();
			return;
		}
	}
}

//��ʾ�˵�����Ϣ 
void menu() {
	key();
	int select = -1;

	while (select != 0) {
		system("cls");                                                                //
		printf("\n\n\t==============��ӭʹ�����г�����ϵͳ==============\n");
		printf("\t\t\t=======��ѡ����=======\n");
		printf("\t\t\t1.¼�����г���Ϣ\n");
		printf("\t\t\t2.�޸����г���Ϣ\n");
		printf("\t\t\t3.ɾ�����г���Ϣ\n");
		printf("\t\t\t4.��ѯ���г���Ϣ\n");
		printf("\t\t\t5.��ӡ���г���Ϣ\n");
		printf("\t\t\t6.���г���Ϣ����\n");
		printf("\t\t\t7.�������г���Ϣ\n");
		printf("\t\t\t0.��   ��   ��  ��\n");
		printf("\n��ѡ��");
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

//����������
void create() {
	system("cls");     //�������� 

	struct bicycle* pEnd, * pNew;
	struct bicycle* p;
	pEnd = pNew = (struct bicycle*)malloc(sizeof(struct bicycle));

	printf("��������������г�����Ϣ(�˳��밴0):\n");

	//¼�����г���ţ���Ų������ظ�
	int flag1 = 1, flag2, n;
	struct bicycle* pTemp;
	printf("\n���г��ı��(�˳��밴0):");
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
				printf("����������,���г����%s����!(�˳��밴0):\n", pNew->bic_num);
				printf("���г��ı��:");
				scanf("%s", pNew->bic_num);
				flag1 = 1;
			}

			if (flag2 == 1) flag1 = 0;
		}
	}

	//¼��������Ϣ�����flag1=0�������Ҫ�˳�����ô������Ϣ������¼
	if (flag1 != 1) {
		printf("����:");
		scanf("%s", pNew->name);

		//�Ա�ֻ������woman��man���������޷������
		while (1) {
			printf("�Ա�(woman��man):");
			scanf("%s", pNew->sex);
			if (strcmp(pNew->sex, "woman") == 0 || strcmp(pNew->sex, "man") == 0) break;
			else printf("�Ա����벻�淶����˶Ժ���������!\n");
		}

		//�绰������11λ���������ǲ��淶��
		while (1) {
			printf("�绰(11λ��):");
			scanf("%s", pNew->tele_num);
			if (strlen(pNew->tele_num) == 11) break;
			else printf("�绰���벻�淶������11λ��!\n");
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


		printf("\n���г��ı��(�˳��밴0):");
		scanf("%s", pNew->bic_num);
		flag1 = 1;//ÿ��ѭ������flag1=1�˳�;flag1=0�����������Ҫֵ0
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
					printf("����������,���г��ı��%s����!(�˳��밴0):\n", pNew->bic_num);
					printf("���г��ı��:");
					scanf("%s", pNew->bic_num);
					flag1 = 1;
				}

				if (flag2 == 1) flag1 = 0;
			}
		}

		//¼��������Ϣ�����flag1=0�������Ҫ�˳�����ô������Ϣ������¼
		if (flag1 != 1) {
			printf("����:");
			scanf("%s", pNew->name);

			//�Ա�ֻ������woman��man�������ǲ��淶��
			while (1) {
				printf("�Ա�(woman��man):");
				scanf("%s", pNew->sex);
				if (strcmp(pNew->sex, "woman") == 0 || strcmp(pNew->sex, "man") == 0) break;
				else printf("�Ա����벻�淶����˶Ժ�����!\n");
			}

			//�绰����11λ���������ǲ��淶��
			while (1) {
				printf("�绰(11λ��):");
				scanf("%s", pNew->tele_num);
				if (strlen(pNew->tele_num) == 11) break;
				else printf("�绰���벻�淶������11λ��!\n");
			}

		}                                          //22

	}

	free(pNew);
}

//����������г�����Ϣ
void print() {

	//ҳ���Ż�
	system("cls");
	printf("\n\n\t\t\t\t===================5.��ӡ���г�����Ϣ===================\n");

	struct bicycle* pTemp;
	int iIndex = 1;

	printf("**********�������й���%d�����г���Ϣ�����е���Ϣ����:**********\n", iCount);
	printf("��� ����  �Ա�  �绰 ���г���� \n");
	pTemp = pHead;

	while (pTemp != NULL) {
		printf("%d  %s  %s  %s  %s\n", iIndex, pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
		pTemp = pTemp->next;
		iIndex++;
	}
	printf("�������������һ��");
	getch();
}

//�������г�����Ϣ
void insert() {
	//ҳ���Ż�
	system("cls");
	printf("\n\n\t\t\t\t===================7.�������г�����Ϣ===================\n");
	printf("#\n˵������������λ�ö�����\n#");
	create();
	printf("������Ϣ�ɹ���");
	printf("�������������һ��");
	getch();
}

//��Ϣ��ѯ����
void search() {
	//ҳ���Ż�

	printf("\n\n\t\t\t\t===================4.��ѯ���г�����Ϣ===================");

	int select = -1;
	while (select != 0) {
		system("cls");
		printf("\t\t\t1.�����г��ı�Ų�ѯ\n");
		printf("\t\t\t0.�˳���ҳ��\n");
		printf("��ѡ��");
		scanf("%d", &select);
		int flag = 1, flag1 = 1;
		char number[12];
		char name[12];
		struct bicycle* pTemp = pHead;

		//�����г��ı�Ų�ѯ
		if (select == 1) {

			printf("��������Ҫ���ҵ����г����:");
			scanf("%s", number);
			while (pTemp != NULL && flag)
			{
				if (strcmp(pTemp->bic_num, number) == 0)
				{
					printf("%s�ҵ��ˣ�������Ϣ����:\n\n", number);

					printf("\t����  �Ա�  �绰 ���г���� \n");
					printf("\t%s  %s  %s  %s\n", pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
					printf("\n");
					flag = 0;
				}
				pTemp = pTemp->next;
			}
			if (flag == 1)  printf("���%s������!\n", number);
		}
		printf("�������������һ��");
		getch();
	}
}

//ɾ����Ϣ����
void dele() {
	//ҳ���Ż�
	system("cls");
	printf("\n\n\t\t\t\t===================3.ɾ�����г�����Ϣ(�����)===================");

	int select = -1;
	while (select != 0) {
		printf("\t\t\t1.�����г��ı��ɾ��\n");
		printf("\t\t\t2.��   ��  ��  ɾ �� \n");
		printf("\t\t\t0.�˳���ҳ��(lv4)\n");

		printf("��ѡ��");
		scanf("%d", &select);

		if (select == 0) return;
		else if (select == 1 || select == 2) break;
		else printf("������������������\n");
	}

	if (select == 1) {

		if (iCount == 0)  printf("\n\n���������޷����д˲�������������˳�!\n");
		else
		{                                                              //33

			char number[12];
			int  i, flag = 1;
			char option;
			struct bicycle* pTemp;
			struct bicycle* pPre;
			pTemp = pHead;

			int iIndex = 0;
			printf("\n������Ҫɾ�����г��ı��:");
			scanf("%s", number);

			while (pTemp != NULL && flag) {
				if (strcmp(pTemp->bic_num, number) == 0) {
					printf("\n%s�ҵ��ˣ���Ҫɾ������Ϣ����\n\n", number);
					//��ʾ��Ҫɾ���˵���Ϣ
					printf("\t����  �Ա�  �绰 ���г���� \n");
					printf("\t%s  %s  %s  %s\n", pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
					printf("\n");
					flag = 0;

					printf("ȷ��ɾ������1�������������ּ��˳�\n");
					scanf("%d", &option);
				}


				pTemp = pTemp->next;
				iIndex++;
			}
			if (flag == 1) { printf("���%s������!", number);  return; }



			if (option == 1) {
				pTemp = pHead;
				pPre = pTemp;//���ܶ���
				//printf("----------ɾ����%d��ѧ��----------\n",iIndex);

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
				printf("ɾ���ɹ���������˳�!");
			}
			else  printf("ɾ��ʧ�ܰ�������˳�!");
		}                                                               //33

		getch();

	}
	else {
		if (iCount == 0)  printf("\n\n���������޷����д˲�������������˳�!\n");
		else
		{                                                              //33
			char name[12];
			int  i, flag = 1;
			char option;
			struct bicycle* pTemp;
			struct bicycle* pPre;
			pTemp = pHead;

			int iIndex = 0;
			printf("\n������Ҫɾ�����г���Ӧ����������:");
			scanf("%s", name);

			while (pTemp != NULL && flag) {
				if (strcmp(pTemp->name, name) == 0) {
					printf("\n%s�ҵ��ˣ���Ҫɾ������Ϣ����\n\n", name);
					//��ʾ��Ҫɾ���˵���Ϣ
					printf("\t����  �Ա�  �绰 ���г���� \n");
					printf("\t%s  %s  %s  %s\n", pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
					printf("\n");
					flag = 0;

					printf("ȷ��ɾ������1�������������ּ��˳�\n");
					scanf("%d", &option);
				}


				pTemp = pTemp->next;
				iIndex++;
			}
			if (flag == 1) { printf("����%s������!", name);  return; }



			if (option == 1) {
				pTemp = pHead;
				pPre = pTemp;//���ܶ���
				//printf("----------ɾ����%d��ѧ��----------\n",iIndex);

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
				printf("ɾ���ɹ���������˳�!");
			}
			else  printf("ɾ��ʧ�ܰ�������˳�!");
		}                                                               //33

		getch();
	}

}

//2.�޸����г�����Ϣ
void modify() {

	//ҳ���Ż�
	system("cls");
	printf("\n\n\t\t\t\t===================2.�޸����г�����Ϣ===================");

	int post;
	int flag = 1, flag1;
	char number[12];
	struct bicycle* pTemp = pHead, * pPre = pTemp;

	printf("\n��������Ҫ�޸����г���Ϣ��Ӧ���г��ı��:");
	scanf("%s", number);

	while (pTemp != NULL && flag)
	{

		if (strcmp(pTemp->bic_num, number) == 0)
		{
			printf("��Ҫ�޸ĵı��%s������Ϣ����\n", number);
			printf("\t����  �Ա�  �绰 ���г���� \n");
			printf("\t%s  %s  %s  %s\n", pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
			printf("\n");
			flag = 0;
		}
		pPre = pTemp;       //����pTemp
		pTemp = pTemp->next;
	}

	if (flag == 1)  printf("��Ҫ�޸ĵı��%s������!", number);
	else
	{
		printf("ȷ���޸��밴1,�����밴�������ּ�!\n��ѡ��");
		scanf("%d", &post);

		while (post == 1)
		{
			printf("��ѡ����Ҫ�޸ĵ���Ŀ(1.���� 2.�Ա� 3.�绰���� 4.���г��ı�� 5.�޸�ȫ��)\n");
			scanf("%d", &flag1);

			if (flag1 == 1)
			{
				printf("������:");
				scanf("%s", pPre->name);
				printf("�޸����,��������˳�!");
			}

			else if (flag1 == 2)
			{
				printf("���Ա�:");
				scanf("%s", pPre->sex);
				printf("�޸����,��������˳�!");
			}

			else if (flag1 == 3)
			{

				while (1) {
					printf("�绰(11λ��):");
					scanf("%s", pPre->tele_num);
					if (strlen(pPre->tele_num) == 11) break;
					else printf("�绰���벻�淶������11λ��!\n");
				}

				printf("�޸����,��������˳�!");
			}

			else if (flag1 == 4)
			{
				printf("�±��:");
				scanf("%d", &pPre->bic_num);
				printf("�޸����,��������˳�!");
			}

			else {

				printf("������:");
				scanf("%s", pPre->name);

				printf("���Ա�:");
				scanf("%s", pPre->sex);

				while (1) {
					printf("�绰(11λ��):");
					scanf("%s", pPre->tele_num);
					if (strlen(pPre->tele_num) == 11) break;
					else printf("�绰���벻�淶������11λ��!\n");
				}

				printf("�±��:");
				scanf("%s", pPre->bic_num);

			}
			break;
		}


	}

	printf("�޸���ɣ���������˳�");
	getch();

}

//��������
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

//6.���г���Ϣ������
void sort() {

	//ҳ���Ż�
	printf("\n\n\t\t===================4.����ϵͳ===================");

	int i, j;
	struct bicycle* pStra, * pMidd;

	int result;
	int select = -1;
	while (select != 0)
	{
		system("cls");
		printf("\n\t\t\t=======��ѡ�����б�=======\n");
		printf("\t\t\t1.�����г������������\n");
		printf("\t\t\t2.�����г���Ž�������\n");
		printf("\t\t\t0.�˳���ҳ��\n");
		printf("��ѡ��");
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


		printf("\t\t\t3.��ʾ�������Ľ��Ϊ��\n\n");
		printf("------------------------------------------------------");
		struct bicycle* pTemp;
		int iIndex = 1;

		printf("**********�������й���%d�����г���Ϣ��:**********\n", iCount);
		printf("��� ����  �Ա�  �绰 ���г���� \n");
		pTemp = pHead;

		while (pTemp != NULL) {
			printf("%d  %s  %s  %s  %s\n", iIndex, pTemp->name, pTemp->sex, pTemp->tele_num, pTemp->bic_num);
			pTemp = pTemp->next;
			iIndex++;
		}

		printf("------------------------------------------------------");


		printf("\n\n����ɹ��������������!");

		getch();
	}
}
