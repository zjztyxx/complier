#pragma once
#ifndef _MANAGE_H_
#define _MANAGE_H_

//系统库
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>

#define MAX 10000

using namespace std;

//定义使用到的结构体
struct WordString {
	string Word;
	int Category;//关键字1，标识符2，数字3，运算符4，分隔符5，error6
	string left;
	string right;
};
struct SymList {
	string type;//类型
	string name;//名称
	string address;//目标地址
	int  value;//计算结果
};
struct Four {//四元式
	string fir;
	string sec;
	string thi;
	string fou;
};

#endif // !_MANAGE_H_

