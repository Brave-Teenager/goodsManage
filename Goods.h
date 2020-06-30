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
	char name[100]; // 名称 
	int count; // 数量 

}Goods, * Good;

struct Goods food[100];
//查找货物
Good find_goods(char name[]);

void save_file();
int S = 0;
///显示当前库存列表，包括商品名及其库存量
void show_goods();
//查看仓库中的name商品
//把出库和入库记录写入日志文件夹
void write_log(char name[], int count, int flag);

//文件读写
//写文件
void Save_file();
//读文件
void Open_file();

//进货，对应进货模块，表示当前进货一批数量为count的name商品
int add_goods(char name[], int count);
//更新库存信息，对应增加库存子功能，对name商品新增count数量
int increase_count(char name[],int count);
//更新库存列表，对应新增商品子功能，新增name商品且初始数量为count
int add_to_list(char name[], int count);

//出货，对应出货模块，表示当前出货一批数量为count的name商品
int delete_goods(char name[], int count);
//更新库存信息，对应减少库存子功能，对name商品减少count数量
int increase_count(char name[], int count);
//更新库存列表，对应删除商品子功能，删除商品列表中name商品
int delete_from_list(char name[]);
//把出库和入库记录写入日志文件夹
void write_log(char name[], int count, int flag);

//保存到文件
void save();
//出货函数
int delete_goods(char name[], int count)
{
	Good good;
	good = find_goods(name);

	if (count > good->count&& good->count != 0) {//判断货物库存和出货量
		printf("\t货物不足\n");
		return false;
	}
	else
		if (good->count == 0)//没有该货物的情况
		{
			printf("\t没有此货物\n");
			return false;
		}
		else//可以出库的情况
		{
			delete_count(name, count);
			if (good->count == 0)//库存清零的情况
			{
				printf("\t库存清零，删除该货物信息！\n");
				delete_from_list(name);
			}
		}
	printf("\t出库成功！\n");
	write_log(name, count, 0);
	save_file();
	return true;
}

//进货函数
int add_goods(char name[], int count)
{
	Good good;
	good = find_goods(name);

	if (good->count == 0) {//判断是否有该货物
		add_to_list(name, count);
	}
	else {//没有该货物的情况
		add_count(name, count);
	}
	printf("\t入库成功！\n");
	write_log(name, count, 1);
	save_file();
	return true;
}

//更新库存信息，对应增加库存子功能，对name商品新增count数量
int add_count(char name[], int count)
{
	Good good;
	good = find_goods(name);
	good->count += count;
	return true;
}

//更新库存列表，对应新增商品子功能，新增name
int add_to_list(char name[], int count)
{
	S++;
	strcpy(food[S].name, name);
	food[S].count = count;
	return true;
}

//更新库存信息，对应减少库存子功能，对name商品减少count数量
int delete_count(char name[], int count)
{

	Good good;
	good = find_goods(name);
	good->count -= count;
	return true;
}

//更新库存列表，对应删除商品子功能，删除商品列表中name商品
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


//显示当前库存列表，包括商品名及其库存量
void show_goods()
{
	int i;
	char c;
	printf("\t名称\t数量\n");
	for (i = 0; i <= S; i++)
	{
		printf("\t%s\t %d\n", food[i].name, food[i].count);
	}
	printf("\n\n");
}

//查找货物函数
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

//打开文件
void open()
{
	S = 0;//数组下标
	
	FILE* fp;
	if ((fp = fopen(fileGoods, "r")) != NULL) {
		while (!feof(fp)) {//结束表示
			if ((fscanf(fp, "%s\t%d\n", &food[S].name, &food[S].count)) == EOF)//文件结束标识
				break;
			//读文件信息
			S++;
		}
		S--;
	}
	else
	{
		printf("文件信息读取失败！\n");
	}

	if (fp != NULL) {
		fclose(fp);
	}
}

//输出到文件
void save()
{
	FILE* fp = fopen(fileGoods, "w");
	int i;
	if (fp  != NULL) {
		for (i = 0; i <= S; i++) {//结束表示
			(fprintf(fp, "%s\t%d\n", food[i].name, food[i].count));
			//写文件信息
		}
		printf("\t文件信息保存成功！\n");
	}
	if (fp != NULL) {
		fclose(fp);
	}

}


//输出到文件
void save_file()
{
	FILE* fp;
	int i;
	if ((fp = fopen(fileGoods, "w")) != NULL) {
		for (i = 0; i <= S; i++) {//结束表示
			(fprintf(fp, "%s\t%d\n", food[i].name, food[i].count));
			//写文件信息
		}
		printf("\t文件信息保存成功！\n");
	}
	else printf("\t文件信息保存失败！\n");
	fclose(fp);
}

//写日志函数
void write_log(char name[], int count, int flag) //flag用于判断是出库房还是进库房 flag=1为入库，flag=0为出库 
{
	FILE* fp = fopen(fileLogs, "a");
	time_t timep;//时间
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);//获取当前时间

	if (fp == NULL) {//追加文件信息 
		printf("\t写入日志失败");
	}
	else
	{
		if (flag == 0)
			fprintf(fp, "%d/%d/%d--%d:%d\t出货：%s――――%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, name, count);
		else
			fprintf(fp, "%d/%d/%d--%d:%d\t进货：%s――――%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, name, count);
	}
	if (fp != NULL) {
		fclose(fp);
	}
}
