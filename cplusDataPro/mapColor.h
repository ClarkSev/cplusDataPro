/**@file:     地图四染色问题定义文件
  *@Author：  T.H.
  *@function:
  *@Version： V1.0
  *@Note:     None
*/

#pragma once

#ifndef __CPLUS_MAPCOLOR_H__
#define __CPLUS_MAPCOLOR_H__

/** 引入文件----------------------------------------------------------------------*/
#include "usrStack.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace nmspace_usr_datastructure;
using namespace std;

/** 私有宏------------------------------------------------------------------------*/
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

/** 函数声明----------------------------------------------------------------------*/
//将空白地图进行填充颜色，并将其打印出来
void printSolver(mapElementType tmap[], usrStack<mapStackType>&stkMap);

//判断相邻区域是否存在重复染色
bool judgeOverlapColor(const int areaRelate[AREANUMBER][AREANUMBER], \
	usrStack<mapStackType>&stkMap, const int t_areaIndex, const int t_colorIndex);

//地图染色问题求解函数
bool mapSolver(const int areaRelate[AREANUMBER][AREANUMBER], usrStack<mapStackType>&stkMap);

//多种染色方法
bool mapSolver(const int areaRelate[AREANUMBER][AREANUMBER], \
	usrStack<mapStackType>&stkMap, mapElementType tmap[]);




#endif //__CPLUS_MAPCOLOR_H__
