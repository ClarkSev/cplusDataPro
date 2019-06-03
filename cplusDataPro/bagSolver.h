/**@file:     背包问题定义文件
  *@Author：  T.H.
  *@function: 
  *@Version： V1.0
  *@Note:     None
*/

#pragma once

#ifndef __CPLUS_BAGSOLVER_H__
#define __CPLUS_BAGSOLVER_H__

/** 引入文件----------------------------------------------------------------------*/
#include "usrStack.h"
#include <iostream>
#include <string>

using namespace nmspace_usr_datastructure;

/** 私有宏------------------------------------------------------------------------*/
#define PRODUCES  ElementType

class PRODUCES
{
public:
	string number;
	string name;
	string place;
	int weight;
};
class StackType
{
public:
	int index;
};
/** 函数声明----------------------------------------------------------------------*/
void printResult(usrStack<StackType>&t_Stack,const ElementType element[]);  //打印求出的结果
//求解函数
void knapSack(const ElementType element[], const int szElem, const int t_totalWeight);

#endif //__CPLUS_BAGSOLVER_H__
