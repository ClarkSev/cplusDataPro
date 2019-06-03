/**@file:     �������ⶨ���ļ�
  *@Author��  T.H.
  *@function: 
  *@Version�� V1.0
  *@Note:     None
*/

#pragma once

#ifndef __CPLUS_BAGSOLVER_H__
#define __CPLUS_BAGSOLVER_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "usrStack.h"
#include <iostream>
#include <string>

using namespace nmspace_usr_datastructure;

/** ˽�к�------------------------------------------------------------------------*/
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
/** ��������----------------------------------------------------------------------*/
void printResult(usrStack<StackType>&t_Stack,const ElementType element[]);  //��ӡ����Ľ��
//��⺯��
void knapSack(const ElementType element[], const int szElem, const int t_totalWeight);

#endif //__CPLUS_BAGSOLVER_H__
