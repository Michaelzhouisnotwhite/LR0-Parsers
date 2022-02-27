//�������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#define MAXSIZE 2000   /*����ѧ����Ϣ������������Ϊ2000��*/
#define MAXNUM 15      /*�涨 һ��ѧ��һѧ�������15�ǿ�*/

/*��Ҫ�Ľṹ�壺*/
//1.ѧ��������Ϣ��
struct student
{
	char id[12]; /*��׼12λ��ѧ��*/
	char name[20];
	char sex;
	int depart; /*�����--3λ������*/
	char tele[8]; /*��׼8λ���绰����*/
	//�ɼ���Ϣ��
	int num; /*��ѧ����ѧ�ڹ��޵�ѧ������*/
	char classID[MAXNUM][10]; /*�γ̱��*/
	char className[MAXNUM][20]; /*�γ�����*/
	int credit[MAXNUM]; /*ѧ��*/
	int usualScore[MAXNUM]; /*ƽʱ�ɼ�*/
	int laborScore[MAXNUM]; /*ʵ��ɼ�*/
	int paperScore[MAXNUM]; /*����ɼ�*/
	float compreScore[MAXNUM]; /*�ۺϳɼ�*/
	float dueCredit[MAXNUM]; /*Ӧ��ѧ��*/
};

//2.ѧ��������Ϣ��
struct ListA
{
	struct student stu[MAXSIZE];
	int length; /*���������е����ݸ���*/
};

//3.ѧ���ɼ���Ϣ��
struct ListB
{
	struct student stu[MAXSIZE]; /*��B���A�����Ϲ�ͨ*/
	int length;
};

//�Զ��庯��������
void logData(FILE* fp, struct ListA* lA);
int addScore(FILE* fp, struct ListB* lB, struct student* s);
void getCompreScore(struct student* s);
void getDueCredit(struct student* s);
void queryA1(struct ListA* lA, int cA);

//��������������
int main()
{
	/*��Ҫ����*/
	struct student s;
	struct ListA lA;
	struct ListB lB;
	int choice; //ѡ��
	FILE* fp; //�ļ��Ķ�д
	/*�����������*/
	printf(
		"__________________________________________________________________________________________________________________________________\n\n");
	printf("\t\t\t\t\t��ѧ����Ϣ����ϵͳ\n\n");
	/*�������ܽ���*/
	printf("\t\t��ӭ�����ѧ����Ϣ����ƽ̨\n");
	printf("\t\tϵͳ��Ҫ�������£�\n");
	printf(
		"|\t\t1.ѧ���ɼ�¼�����\t\t|\n|\t\t2.ѧ����Ϣ��ѯ����\t\t|\n|\t\t3.ѧ����Ϣɾ������\t\t|\n|\t\t4.ѧ���ɼ��������\t\t|\n|\t\t5.�˳�ϵͳ\t\t|\n");
	printf(
		"__________________________________________________________________________________________________________________________________\n\n");
	printf("\t\t\t�밴��Ź��� ����������Ҫ�Ĺ��ܲ���(0-5)��\n");
	/*������fp��A.txt�����Ϣ����ListA*/

	logData(fp, &lA);
	/*�����û�ѡ�������ز���*/
	scanf("%d", &choice);
	int flag = 1;
	while (flag)
	{
		switch (choice)
		{
		case 1:
			if ((fp = fopen("C:\\Users\\19802\\Desktop\\C++\\����\\B.txt", "w")) == NULL)
			{
				printf("ѧ���ɼ�����ʧ�ܣ�\n");
				break;
			}
			addScore(fp, &lB, &s);
			if (fclose(fp))
			{
				printf("�ļ��ر�ʧ�ܴ������ѣ�������\n");
				exit(0);
			}
		case 2:
			char c;
			printf("����������Ҫ��ѯ����Ϣ���ݣ�\nA:��ѯѧ��������Ϣ\nB:��ѯѧ���ɼ���Ϣ\n");
			scanf("%c", &c);
			switch (c)
			{
			case 'A':
				int cA;
				printf("������ѡ��ʽ���в�ѯ��\n1:ѧ������/ѧ��\n2:ѧ�������\n");
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
			printf("�ɹ��˳���Ϣ����ƽ̨��\n");
			exit(0);
		default:
			continue;
		}
		printf("�Ƿ�������������Ĳ���?\n��:1\n��:2\n");
		scanf("%d", &flag);
	}

	return 0;
}

/*�Զ��庯����*/
/*0.���ļ���Ϣ����ListA��*/
void logData(FILE* fp, struct ListA* lA)
{
	int i = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%s%s%c%d%s", lA->stu[i].id, lA->stu[i].name, lA->stu[i].sex, lA->stu[i].depart, lA->stu[i].tele);
		i++;
	}
	printf("ListA����Ϣˢ�³ɹ���\n");
}

/*1.¼�빦��*/

//1.B���гɼ�¼�룺¼��ɹ� ����1 ¼��ʧ�ܷ���0
int addScore(FILE* fp, struct ListB* lB, struct student* s)
{
	int result = 0; //�Ƿ�¼��ɹ�
	int len = lB->length;
	if (len == MAXSIZE)
	{
		printf("��Ϣ����ϵͳ�����Ѵ����ޣ��޷����гɼ�¼�룡\n");
		return result;
	}

	printf("������ѧ��ѧ�ţ�\n");
	scanf("%s", s->id);
	int i, j;
	int flag = 0; //������ѧ�� �Ƿ�������Ϣ--ԭ�������µĵ�ѧ�� flag=1  �µ�ѧ�� flag=0
	for (i = 0; i < len; i++)
	{
		if (strcmp(s->id, lB->stu[i].id) == 0)
		{
			flag = 1;
			break;
		}
	}
	int count; //ѧ���γ���Ŀ
	if (flag)
	{
		count = s->num; //��ѧ��ԭ�пγ���Ŀ��¼
		int keep = 1; //�ж��Ƿ�����һ�Ƶĳɼ���Ҫ¼��
		while (keep)
		{
			printf("�������ѧ���ɼ������Ϣ��(ÿ���������Կո����)\n");
			printf("�γ̱�� �γ����� ѧ�� ƽʱ�ɼ� ʵ��ɼ� ����ɼ�");
			scanf("%s%s%d%d%d%d", s->classID[count], s->className[count], &s->credit[count], &s->usualScore[count],
			      &s->laborScore[count], &s->paperScore[count]);
			count++;
			printf("�Ƿ���м���¼����һ�Ƶĳɼ���\n��:1\n��:0\n");
			scanf("%d", &keep);
		}
		s->num = count;
		//����ѧ�����ۺϳɼ���Ӧ��ѧ�֣�
		getCompreScore(s);
		getDueCredit(s);
		result = 1;
	}
	else
	{
		lB->length++; //ѧ���ɼ���Ϣ��B������һλ��Ϣ;
		count = 0; //�հ׳ɼ���¼
		int keep = 1; //�ж��Ƿ�����һ�Ƶĳɼ���Ҫ¼��
		while (keep)
		{
			printf("�������ѧ���ɼ������Ϣ��(ÿ���������Կո����)\n");
			printf("�γ̱�� �γ����� ѧ�� ƽʱ�ɼ� ʵ��ɼ� ����ɼ�");
			scanf("%s%s%d%d%d%d", s->classID[count], s->className[count], &s->credit[count], &s->usualScore[count],
			      &s->laborScore[count], &s->paperScore[count]);
			count++;
			printf("�Ƿ���м���¼����һ�Ƶĳɼ���\n��:1\n��:0\n");
			scanf("%d", &keep);
		}
		s->num = count;
		getCompreScore(s);
		getDueCredit(s);
		result = 1;
	}
	//�ļ����룺
	fprintf(fp, "%s", "ѧ��ѧ�� �γ̱�� �γ����� ѧ�� ƽʱ�ɼ� ʵ��ɼ� ����ɼ� �ۺϳɼ� Ӧ��ѧ��\n");
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
	printf("ѧ��%s�ɼ�¼��ɹ�!\n", s->name);
	return result;
}

/*2.���㹦��*/

//1.�����ۺϳɼ���
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
	printf("ѧ��%s�ۺϳɼ�������ɣ�\n", s->id);
}

//2.����Ӧ��ѧ�֣�
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
	printf("ѧ��%sӦ��ѧ�ּ�����ϣ�\n", s->id);
}

/*3.��ѯ����*/

//1.��ѯA��
void queryA1(struct ListA* lA, int cA)
{
	int len = lA->length;
	int i, j;
	//A1ͨ�� ѧ������/ѧ�Ž��в�ѯ
	if (cA == 1)
	{
		char query[20];
		printf("������ѧ��ѧ��/ѧ������:\n");
		scanf("%s", query);
		for (i = 0; i < len; i++)
		{
			if (strcmp(lA->stu[i].id, query) || strcmp(lA->stu[i].name, query) == 0)
			{
				printf("����ѧ��������Ϣ���£�\n");
				printf("ѧ��:%s ����:%s �Ա�:%c �������:%d �绰����:%s \n",
				       lA->stu[i].id, lA->stu[i].name, lA->stu[i].sex, lA->stu[i].depart, lA->stu[i].tele);
				printf("��Ϣ��ʾ��ϣ�\n");
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
				printf("����ѧ��������Ϣ���£�\n");
				printf("ѧ��:%s ����:%s �Ա�:%c �������:%d �绰����:%s \n",
				       lA->stu[i].id, lA->stu[i].name, lA->stu[i].sex, lA->stu[i].depart, lA->stu[i].tele);
				continue;
			}
		}
		printf("��Ϣ��ʾ��ϣ�\n");
	}
	else
	{
		printf("�밴�չ涨���в���ѡ��\n");
	}
}

//2.��ѯB��

/*4.ɾ������*/

/*5.������*/
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
