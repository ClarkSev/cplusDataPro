/**@file:     ��ͼ��Ⱦɫ���ⶨ���ļ�
  *@Author��  T.H.
  *@function:
  *@Version�� V1.0
  *@Note:     None
*/

#pragma once

#ifndef __CPLUS_MAPCOLOR_H__
#define __CPLUS_MAPCOLOR_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "usrStack.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace nmspace_usr_datastructure;
using namespace std;

/** ˽�к�------------------------------------------------------------------------*/
#define MAP              mapElementType
#define MAPCOLORStack    mapStackType
#define AREANUMBER       (7)
#define MAXCOLORNUM      (4)
struct MAP
{
	int areaIndex;
	string areaName;
	int colorIndex;
};
class MAPCOLORStack
{
public:
	int areaIndex; int colorIndex;
};

/** ��������----------------------------------------------------------------------*/
//���հ׵�ͼ���������ɫ���������ӡ����
void printSolver(mapElementType tmap[], usrStack<mapStackType>&stkMap);

//�ж����������Ƿ�����ظ�Ⱦɫ
bool judgeOverlapColor(const int areaRelate[AREANUMBER][AREANUMBER], \
	usrStack<mapStackType>&stkMap, const int t_areaIndex, const int t_colorIndex);

//��ͼȾɫ������⺯��
bool mapSolver(const int areaRelate[AREANUMBER][AREANUMBER], usrStack<mapStackType>&stkMap);

//����Ⱦɫ����
bool mapSolver(const int areaRelate[AREANUMBER][AREANUMBER], \
	usrStack<mapStackType>&stkMap, mapElementType tmap[]);




#endif //__CPLUS_MAPCOLOR_H__
