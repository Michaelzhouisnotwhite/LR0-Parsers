//导入包：
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#define MAXSIZE 2000   /*限制学生信息管理人数上限为2000人*/
#define MAXNUM 15      /*规定 一个学生一学期最多修15们课*/

/*重要的结构体：*/
//1.学生基本信息：
struct student
{
	char id[12]; /*标准12位数学号*/
	char name[20];
	char sex;
	int depart; /*宿舍号--3位数整数*/
	char tele[8]; /*标准8位数电话号码*/
	//成绩信息：
	int num; /*此学生本学期共修的学科总数*/
	char classID[MAXNUM][10]; /*课程编号*/
	char className[MAXNUM][20]; /*课程名称*/
	int credit[MAXNUM]; /*学分*/
	int usualScore[MAXNUM]; /*平时成绩*/
	int laborScore[MAXNUM]; /*实验成绩*/
	int paperScore[MAXNUM]; /*卷面成绩*/
	float compreScore[MAXNUM]; /*综合成绩*/
	float dueCredit[MAXNUM]; /*应得学分*/
};

//2.学生基本信息表：
struct ListA
{
	struct student stu[MAXSIZE];
	int length; /*表中所含有的数据个数*/
};

//3.学生成绩信息表：
struct ListB
{
	struct student stu[MAXSIZE]; /*表B与表A理论上贯通*/
	int length;
};

//自定义函数声明：
void logData(FILE* fp, struct ListA* lA);
int addScore(FILE* fp, struct ListB* lB, struct student* s);
void getCompreScore(struct student* s);
void getDueCredit(struct student* s);
void queryA1(struct ListA* lA, int cA);

//主函数运行区：
int main()
{
	/*主要参数*/
	struct student s;
	struct ListA lA;
	struct ListB lB;
	int choice; //选择
	FILE* fp; //文件的读写
	/*基础界面设计*/
	printf(
		"__________________________________________________________________________________________________________________________________\n\n");
	printf("\t\t\t\t\t大学生信息管理系统\n\n");
	/*基本功能介绍*/
	printf("\t\t欢迎进入大学生信息管理平台\n");
	printf("\t\t系统主要功能如下：\n");
	printf(
		"|\t\t1.学生成绩录入操作\t\t|\n|\t\t2.学生信息查询操作\t\t|\n|\t\t3.学生信息删除操作\t\t|\n|\t\t4.学生成绩排序操作\t\t|\n|\t\t5.退出系统\t\t|\n");
	printf(
		"__________________________________________________________________________________________________________________________________\n\n");
	printf("\t\t\t请按序号功能 输入你所需要的功能操作(0-5)：\n");
	/*先利用fp将A.txt相关信息读入ListA*/

	logData(fp, &lA);
	/*根据用户选择进行相关操作*/
	scanf("%d", &choice);
	int flag = 1;
	while (flag)
	{
		switch (choice)
		{
		case 1:
			if ((fp = fopen("C:\\Users\\19802\\Desktop\\C++\\课设\\B.txt", "w")) == NULL)
			{
				printf("学生成绩表单打开失败！\n");
				break;
			}
			addScore(fp, &lB, &s);
			if (fclose(fp))
			{
				printf("文件关闭失败错误提醒！！！！\n");
				exit(0);
			}
		case 2:
			char c;
			printf("请输入你所要查询的信息内容：\nA:查询学生基本信息\nB:查询学生成绩信息\n");
			scanf("%c", &c);
			switch (c)
			{
			case 'A':
				int cA;
				printf("请问是选择方式进行查询：\n1:学生姓名/学号\n2:学生宿舍号\n");
				scanf("%d", &cA);
				queryA1(&lA, cA);
				break;
			case 'B':
				break;
			}
			break;
		case 3:

		case 4:

		case 5:
			printf("成功退出信息管理平台！\n");
			exit(0);
		default:
			continue;
		}
		printf("是否继续进行其他的操作?\n是:1\n否:2\n");
		scanf("%d", &flag);
	}

	return 0;
}

/*自定义函数区*/
/*0.将文件信息读入ListA中*/
void logData(FILE* fp, struct ListA* lA)
{
	int i = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%c%d%s", lA->stu[i].id, lA->stu[i].name, lA->stu[i].sex, lA->stu[i].depart, lA->stu[i].tele);
		i++;
	}
	printf("ListA表信息刷新成功！\n");
}

/*1.录入功能*/

//1.B表中成绩录入：录入成功 返回1 录入失败返回0
int addScore(FILE* fp, struct ListB* lB, struct student* s)
{
	int result = 0; //是否录入成功
	int len = lB->length;
	if (len == MAXSIZE)
	{
		printf("信息管理系统数据已达上限！无法进行成绩录入！\n");
		return result;
	}

	printf("请输入学生学号：\n");
	scanf("%s", s->id);
	int i, j;
	int flag = 0; //检测此名学生 是否已有信息--原有数据新的的学生 flag=1  新的学生 flag=0
	for (i = 0; i < len; i++)
	{
		if (strcmp(s->id, lB->stu[i].id) == 0)
		{
			flag = 1;
			break;
		}
	}
	int count; //学生课程数目
	if (flag)
	{
		count = s->num; //此学生原有课程数目记录
		int keep = 1; //判断是否还有下一科的成绩需要录入
		while (keep)
		{
			printf("请输入该学生成绩相关信息：(每个数据中以空格隔开)\n");
			printf("课程编号 课程名称 学分 平时成绩 实验成绩 卷面成绩");
			scanf("%s%s%d%d%d%d", s->classID[count], s->className[count], &s->credit[count], &s->usualScore[count],
			      &s->laborScore[count], &s->paperScore[count]);
			count++;
			printf("是否进行继续录入下一科的成绩？\n是:1\n否:0\n");
			scanf("%d", &keep);
		}
		s->num = count;
		//计算学生的综合成绩与应得学分：
		getCompreScore(s);
		getDueCredit(s);
		result = 1;
	}
	else
	{
		lB->length++; //学生成绩信息表B中增加一位信息;
		count = 0; //空白成绩记录
		int keep = 1; //判断是否还有下一科的成绩需要录入
		while (keep)
		{
			printf("请输入该学生成绩相关信息：(每个数据中以空格隔开)\n");
			printf("课程编号 课程名称 学分 平时成绩 实验成绩 卷面成绩");
			scanf("%s%s%d%d%d%d", s->classID[count], s->className[count], &s->credit[count], &s->usualScore[count],
			      &s->laborScore[count], &s->paperScore[count]);
			count++;
			printf("是否进行继续录入下一科的成绩？\n是:1\n否:0\n");
			scanf("%d", &keep);
		}
		s->num = count;
		getCompreScore(s);
		getDueCredit(s);
		result = 1;
	}
	//文件读入：
	fprintf(fp, "%s", "学生学号 课程编号 课程名称 学分 平时成绩 实验成绩 卷面成绩 综合成绩 应得学分\n");
	for (i = 0; i < lB->length; i++)
	{
		for (j = 0; i < s->num; j++)
		{
			fprintf(fp, "%s %s %s %d %d %d %d %.2f %.2f\n",
			        lB->stu[i].id, lB->stu[i].classID[j], lB->stu[i].className[j], lB->stu[i].credit[j],
			        lB->stu[i].usualScore[j],
			        lB->stu[i].laborScore[j],
			        lB->stu[i].paperScore[j], lB->stu[i].compreScore[j], lB->stu[i].dueCredit[j]);
		}
	}
	printf("学生%s成绩录入成功!\n", s->name);
	return result;
}

/*2.计算功能*/

//1.计算综合成绩：
void getCompreScore(struct student* s)
{
	int len = s->num;
	int i;
	for (i = 0; i < len; i++)
	{
		if (s->laborScore[i] != -1)
		{
			s->compreScore[i] = s->usualScore[i] * (0.15) + s->laborScore[i] * (0.15) + s->paperScore[i] * (0.7);
		}
		else
		{
			s->compreScore[i] = s->usualScore[i] * (0.3) + s->paperScore[i] * (0.7);
		}
	}
	printf("学生%s综合成绩计算完成！\n", s->id);
}

//2.计算应得学分：
void getDueCredit(struct student* s)
{
	int len = s->num;
	int i, level;
	for (i = 0; i < len; i++)
	{
		int level = s->compreScore[i] / 10;
		switch (level)
		{
		case 10:
			s->dueCredit[i] = s->credit[i];
			break;
		case 9:
			s->dueCredit[i] = s->credit[i];
			break;
		case 8:
			s->dueCredit[i] = s->credit[i] * (0.8);
			break;
		case 7:
			s->dueCredit[i] = s->credit[i] * (0.75);
			break;
		case 6:
			s->dueCredit[i] = s->credit[i] * (0.6);
			break;
		default:
			s->dueCredit[i] = 0;
		}
	}
	printf("学生%s应得学分计算完毕！\n", s->id);
}

/*3.查询功能*/

//1.查询A表：
void queryA1(struct ListA* lA, int cA)
{
	int len = lA->length;
	int i, j;
	//A1通过 学生姓名/学号进行查询
	if (cA == 1)
	{
		char query[20];
		printf("请输入学生学号/学生姓名:\n");
		scanf("%s", query);
		for (i = 0; i < len; i++)
		{
			if (strcmp(lA->stu[i].id, query) || strcmp(lA->stu[i].name, query) == 0)
			{
				printf("此名学生基本信息如下：\n");
				printf("学号:%s 姓名:%s 性别:%c 宿舍号码:%d 电话号码:%s \n",
				       lA->stu[i].id, lA->stu[i].name, lA->stu[i].sex, lA->stu[i].depart, lA->stu[i].tele);
				printf("信息显示完毕！\n");
				break;
			}
		}
	}
	else if (cA == 2)
	{
		int query2;
		scanf("%d", &query2);
		for (i = 0; i < len; i++)
		{
			if (lA->stu[i].depart == query2)
			{
				printf("此名学生基本信息如下：\n");
				printf("学号:%s 姓名:%s 性别:%c 宿舍号码:%d 电话号码:%s \n",
				       lA->stu[i].id, lA->stu[i].name, lA->stu[i].sex, lA->stu[i].depart, lA->stu[i].tele);
				continue;
			}
		}
		printf("信息显示完毕！\n");
	}
	else
	{
		printf("请按照规定进行操作选择！\n");
	}
}

//2.查询B表：

/*4.删除功能*/

/*5.排序功能*/
void order(struct ListB* lB)
{
	int len = lB->length;
	int i, j;
	for (i = 0; i < len - 1; i++)
	{
		for (j = i + 1; j < len; j++)
		{
			//	if(lB->stu[i].compreScore)
		}
	}
}
