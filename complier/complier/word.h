#pragma once
#ifndef _WORD_H_
#define _WORD_H_

#include"main.h"

//词法部分
/*
标识符   <字母>| <字母>（<字母>| <数字字符>)*
十进制整数   0|(1|2|3|4|5|6|7|8|9)(0|1|2|3|4|5|6|7|8|9)*
运算符			+ - * / =    == && || > < >= <= !=
分隔符    ( ) { } ;
关键字    int char  if then else while do
*/

//函数声明
void scan();
void cifa();

#endif // !_WORD_H_

