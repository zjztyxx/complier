#pragma once
#ifndef _MANAGE_H_
#define _MANAGE_H_

//ϵͳ��
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<fstream>

#define MAX 10000

using namespace std;

//����ʹ�õ��Ľṹ��
struct WordString {
	string Word;
	int Category;//�ؼ���1����ʶ��2������3�������4���ָ���5��error6
	string left;
	string right;
};
struct SymList {
	string type;//����
	string name;//����
	string address;//Ŀ���ַ
	int  value;//������
};
struct Four {//��Ԫʽ
	string fir;
	string sec;
	string thi;
	string fou;
};

#endif // !_MANAGE_H_

