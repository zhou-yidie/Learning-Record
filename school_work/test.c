#include"Stu.h"

int main()
{
    //printf("值得你裂开\n");
    passwd();
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL)
    {
        perror("malloc fail");
        return 0;
        head->next = NULL;
    }
    head->next = NULL;

    while (1)
    {
        welcome();
        int c = 0;
        scanf("%d", &c);
        switch (c)
        {
            case 1:
            {
                input(head);
                system("pause");
                system("cls");
                break;
            }
            case 2:
            {
                Printf(head);
                system("pause");
                system("cls");
                break;
            }
            case 3:
            {
                int nu = count(head);
                printf("The number of students is: %d\n", nu); // 学生人数为:%d\n
                system("pause");
                system("cls");
                break;
            }
            case 4:
            {
                find(head);
                system("pause");
                system("cls");
                break;
            }
            case 5:
            {
                change(head);
                system("pause");
                system("cls");
                break;
            }
            case 6:
            {
                del(head);
                system("pause");
                system("cls");
                break;
            }
            case 7:
            {
                Node* pEnd = head;
                while (pEnd->next)
                {
                    pEnd = pEnd->next;
                }
                Quick_Sort(head,pEnd);
                Printf(head);
                system("pause");
                system("cls");
                break;
            }
            case 8:
            {
                PrintfVictory(head,10);
                system("pause");
                system("cls");
                break;
            }
            case 0:
            {
                printf("Welcome to use it next time.\n"); // 欢迎下次使用
                if (head == NULL)
                {
                    exit(0);
                }
                while (head)
                {
                    Node* del = head;
                    head = head->next;
                    free(del);          //释放空间
                }
                head = NULL;   //指针及时置空防止野指针出现
                return 0;
            }
            default:
            {
                printf("The function you entered does not exist.\n"); // 你输入的功能不存在
                system("pause");
                system("cls");
                break;
            }
        }
    }
    return 0;
}

//菜单
void welcome()
{
    printf("----------------------------\n");
    printf("********Student Management System********\n\n"); // ********学生管理系统********
    printf("Enter 1 --- Enter student information\t\t\n"); // 输入1---输入学生信息
    printf("Enter 2 --- Print student information\t\t\n"); // 输入2---打印学生信息
    printf("Enter 3 --- Count the number of students\t\t\n"); // 输入3---统计学生人数
    printf("Enter 4 --- Search for student information\t\t\n"); // 输入4---查找学生信息
    printf("Enter 5 --- Modify student information\t\t\n"); // 输入5---修改学生信息
    printf("Enter 6 --- Delete student information\t\t\n"); // 输入6---删除学生信息
    printf("Enter 7 --- Organize student information\t\t\n"); // 输入7---整理学生信息
    printf("Enter 0 --- Exit the program\t\t\n"); // 输入0---退出程序
    printf("----------------------------\n");
    printf("Please enter the number corresponding to the function you need.\n"); // 请输入您所需要功能对应的数字
}

//登录核对界面
void passwd()
{
    char ch[20] = { 0 };
    char str[20] = "zhouyidie";
    printf("Please enter the file password: "); // 请输入文件密码：
    while (1)
    {
        scanf("%s", ch);
        if (strcmp(ch, str) != 0)
        {
            printf("The password is incorrect. Please try again.\n"); // 密码错误，请重新操作
        }
        else
        {
            printf("The password is correct.\n"); // 密码正确
            break;
        }
    }
}