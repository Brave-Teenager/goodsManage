#pragma once

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define true 1
#define false 0
const char fileGoods[50] = "goods.txt";
const char fileLogs[50] = "log.txt";

typedef struct Goods
{
	char name[100]; // ���� 
	int count; // ���� 

}Goods, * Good;

struct Goods food[100];
//���һ���
Good find_goods(char name[]);

void save_file();
int S = 0;
///��ʾ��ǰ����б�������Ʒ����������
void show_goods();
//�鿴�ֿ��е�name��Ʒ
//�ѳ��������¼д����־�ļ���
void write_log(char name[], int count, int flag);

//�ļ���д
//д�ļ�
void Save_file();
//���ļ�
void Open_file();

//��������Ӧ����ģ�飬��ʾ��ǰ����һ������Ϊcount��name��Ʒ
int add_goods(char name[], int count);
//���¿����Ϣ����Ӧ���ӿ���ӹ��ܣ���name��Ʒ����count����
int increase_count(char name[],int count);
//���¿���б���Ӧ������Ʒ�ӹ��ܣ�����name��Ʒ�ҳ�ʼ����Ϊcount
int add_to_list(char name[], int count);

//��������Ӧ����ģ�飬��ʾ��ǰ����һ������Ϊcount��name��Ʒ
int delete_goods(char name[], int count);
//���¿����Ϣ����Ӧ���ٿ���ӹ��ܣ���name��Ʒ����count����
int increase_count(char name[], int count);
//���¿���б���Ӧɾ����Ʒ�ӹ��ܣ�ɾ����Ʒ�б���name��Ʒ
int delete_from_list(char name[]);
//�ѳ��������¼д����־�ļ���
void write_log(char name[], int count, int flag);

//���浽�ļ�
void save();
//��������
int delete_goods(char name[], int count)
{
	Good good;
	good = find_goods(name);

	if (count > good->count&& good->count != 0) {//�жϻ�����ͳ�����
		printf("\t���ﲻ��\n");
		return false;
	}
	else
		if (good->count == 0)//û�иû�������
		{
			printf("\tû�д˻���\n");
			return false;
		}
		else//���Գ�������
		{
			delete_count(name, count);
			if (good->count == 0)//�����������
			{
				printf("\t������㣬ɾ���û�����Ϣ��\n");
				delete_from_list(name);
			}
		}
	printf("\t����ɹ���\n");
	write_log(name, count, 0);
	save_file();
	return true;
}

//��������
int add_goods(char name[], int count)
{
	Good good;
	good = find_goods(name);

	if (good->count == 0) {//�ж��Ƿ��иû���
		add_to_list(name, count);
	}
	else {//û�иû�������
		add_count(name, count);
	}
	printf("\t���ɹ���\n");
	write_log(name, count, 1);
	save_file();
	return true;
}

//���¿����Ϣ����Ӧ���ӿ���ӹ��ܣ���name��Ʒ����count����
int add_count(char name[], int count)
{
	Good good;
	good = find_goods(name);
	good->count += count;
	return true;
}

//���¿���б���Ӧ������Ʒ�ӹ��ܣ�����name
int add_to_list(char name[], int count)
{
	S++;
	strcpy(food[S].name, name);
	food[S].count = count;
	return true;
}

//���¿����Ϣ����Ӧ���ٿ���ӹ��ܣ���name��Ʒ����count����
int delete_count(char name[], int count)
{

	Good good;
	good = find_goods(name);
	good->count -= count;
	return true;
}

//���¿���б���Ӧɾ����Ʒ�ӹ��ܣ�ɾ����Ʒ�б���name��Ʒ
int delete_from_list(char name[])
{
	int i;
	for (i = 0; i <= S; i++) {
		if (strcmp(name, food[i].name) == 0) {
			break;
		}
	}
	for (; i <= S; i++) {
		food[i] = food[i + 1];
	}
	S--;
	return true;
}


//��ʾ��ǰ����б�������Ʒ����������
void show_goods()
{
	int i;
	char c;
	printf("\t����\t����\n");
	for (i = 0; i <= S; i++)
	{
		printf("\t%s\t %d\n", food[i].name, food[i].count);
	}
	printf("\n\n");
}

//���һ��ﺯ��
Good find_goods(char name[])
{
	int i;
	Good good;
	for (i = 0; i <= S; i++)
	{
		if (strcmp(name, food[i].name) == 0) {
			return &food[i];
		}
	}

	return  &food[S + 1];
}

//���ļ�
void open()
{
	S = 0;//�����±�
	
	FILE* fp;
	if ((fp = fopen(fileGoods, "r")) != NULL) {
		while (!feof(fp)) {//������ʾ
			if ((fscanf(fp, "%s\t%d\n", &food[S].name, &food[S].count)) == EOF)//�ļ�������ʶ
				break;
			//���ļ���Ϣ
			S++;
		}
		S--;
	}
	else
	{
		printf("�ļ���Ϣ��ȡʧ�ܣ�\n");
	}

	if (fp != NULL) {
		fclose(fp);
	}
}

//������ļ�
void save()
{
	FILE* fp = fopen(fileGoods, "w");
	int i;
	if (fp  != NULL) {
		for (i = 0; i <= S; i++) {//������ʾ
			(fprintf(fp, "%s\t%d\n", food[i].name, food[i].count));
			//д�ļ���Ϣ
		}
		printf("\t�ļ���Ϣ����ɹ���\n");
	}
	if (fp != NULL) {
		fclose(fp);
	}

}


//������ļ�
void save_file()
{
	FILE* fp;
	int i;
	if ((fp = fopen(fileGoods, "w")) != NULL) {
		for (i = 0; i <= S; i++) {//������ʾ
			(fprintf(fp, "%s\t%d\n", food[i].name, food[i].count));
			//д�ļ���Ϣ
		}
		printf("\t�ļ���Ϣ����ɹ���\n");
	}
	else printf("\t�ļ���Ϣ����ʧ�ܣ�\n");
	fclose(fp);
}

//д��־����
void write_log(char name[], int count, int flag) //flag�����ж��ǳ��ⷿ���ǽ��ⷿ flag=1Ϊ��⣬flag=0Ϊ���� 
{
	FILE* fp = fopen(fileLogs, "a");
	time_t timep;//ʱ��
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);//��ȡ��ǰʱ��

	if (fp == NULL) {//׷���ļ���Ϣ 
		printf("\tд����־ʧ��");
	}
	else
	{
		if (flag == 0)
			fprintf(fp, "%d/%d/%d--%d:%d\t������%s�D�D�D�D%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, name, count);
		else
			fprintf(fp, "%d/%d/%d--%d:%d\t������%s�D�D�D�D%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, name, count);
	}
	if (fp != NULL) {
		fclose(fp);
	}
}
