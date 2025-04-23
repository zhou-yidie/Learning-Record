#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<assert.h>
#include<string.h>
#include<Windows.h>
//结构体定义
//唔我浅浅直接初始化一下吧，这算是类了
typedef struct _student
{
    char name[20] ;      //学生姓名
    int number ;                //学号
    char gender[20];       //性别
    char tel[20] ;          //电话号
    int height ;               //身高
    int weight ;                //体重
} student;

//定义结点,方便修改数据
typedef struct _Node
{
    student student;
    struct _Node* next;
} Node;

void passwd();                            //登录操作
void welcome();                           //菜单界面

void input(Node* head);                   //输入数据
void del(Node* head);                     //删除数据
void change(Node* head);                  //修改数据
void find(Node* head);                    //查找数据

void Printf(Node* head);                  //打印数据

int count(Node* head);                    //统计人数

int* Quick_Sort(Node* pBegin, Node* pEnd);               //排序
void PrintfVictory(Node* head, int x);
