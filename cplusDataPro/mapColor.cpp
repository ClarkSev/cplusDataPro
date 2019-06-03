/**@file:     地图四染色问题实现文件
  *@Author：  T.H.
  *@function:
  *@Version： V1.0
  *@Note:     None
*/

/** 引入文件----------------------------------------------------------------------*/
#include "mapColor.h"

/** 函数实现----------------------------------------------------------------------*/
////将空白地图进行填充颜色，并将染色组合打印出来
void printSolver(mapElementType tmap[], usrStack<mapStackType>&stkMap)
{
	usrStack<mapStackType>l_stk;
	mapStackType t_stk_dat;
	//if (stkMap.isEmpty())   //判断染色器是否求解成功
	//	return;
	cout << "map colored--->\n";
	while (!stkMap.isEmpty())
	{
		stkMap.pop(t_stk_dat);
		l_stk.push(t_stk_dat);
		//地图染色
		tmap[t_stk_dat.areaIndex].colorIndex = t_stk_dat.colorIndex;
		//显示部分
		cout <<setw(10) << "Index = " << t_stk_dat.areaIndex\
			<< setw(10) << "name = " << tmap[t_stk_dat.areaIndex].areaName\
			<< setw(10) << "color = " << tmap[t_stk_dat.areaIndex].colorIndex\
			<< endl;
	}
	//恢复堆栈数据
	while (!l_stk.isEmpty())
	{
		l_stk.pop(t_stk_dat);
		stkMap.push(t_stk_dat);
	}
}
//判断相邻区域是否存在重复染色
//return: 如果存在重复则返回 true，否则为 false
bool judgeOverlapColor(const int areaRelate[AREANUMBER][AREANUMBER], \
	usrStack<mapStackType>&stkMap,const int t_areaIndex,const int t_colorIndex)
{
	usrStack<mapStackType>l_stk;
	mapStackType t_stk_dat;
	bool l_flag=false;
	while (!stkMap.isEmpty() && !l_flag)
	{
		stkMap.pop(t_stk_dat);
		l_stk.push(t_stk_dat);
		if (t_stk_dat.colorIndex == t_colorIndex &&\
			areaRelate[t_stk_dat.areaIndex][t_areaIndex])
			l_flag = true;
	}
	while (!l_stk.isEmpty())
	{
		l_stk.pop(t_stk_dat);
		stkMap.push(t_stk_dat);
	}
	return l_flag;
}

//地图染色问题求解函数，找到解决方法就结束
//AREANUMBER---是需要染色区域的数目
//parameter----地图的区域索引从0开始计算
//areaRelate---表示区域是否相邻的矩阵，如果相邻为 1 ，否则为0
//return-------成功求解为 true ，否则为 false
bool mapSolver(const int areaRelate[AREANUMBER][AREANUMBER], usrStack<mapStackType>&stkMap)
{
	int curColor = 1, curArea = 0;   //从0开始计算
	mapStackType curdat;
	curdat.areaIndex = curArea;
	curdat.colorIndex = curColor;
	stkMap.push(curdat);
	curArea += 1; curColor += 1;
	while (curArea < AREANUMBER)
	{
		while (judgeOverlapColor(areaRelate,stkMap,curArea,curColor))  //判断是否存在重复颜色
		{
			curColor += 1;
			//如果存在重复颜色，就颜色增加；
			//若达到最大颜色，则弹出数据；继续进行比对
			while (curColor > MAXCOLORNUM)   //表示已经遍历全部颜色
			{
				if (stkMap.isEmpty())
					return false;
				stkMap.pop(curdat);
				curArea = curdat.areaIndex;
				curColor = curdat.colorIndex+1;
			}
		}
		curdat.areaIndex = curArea;
		curdat.colorIndex = curColor;
		stkMap.push(curdat);
		curArea += 1;   //下一个区域
		curColor = 1;   //从第一种颜色开始遍历
	}
	if (stkMap.isEmpty())
		return false;
	return true;
}

bool mapSolver(const int areaRelate[AREANUMBER][AREANUMBER],\
	usrStack<mapStackType>&stkMap, mapElementType tmap[])
{
	int curColor = 1, curArea = 0;   //从0开始计算
	bool fullFlag = false;
	mapStackType curdat;
	curdat.areaIndex = curArea;
	curdat.colorIndex = curColor;
	stkMap.push(curdat);
	curArea += 1; curColor += 1;
	while(1) //(curArea < AREANUMBER)
	{
		if (curArea == AREANUMBER)
		{
			printSolver(tmap, stkMap);  //填充地图
			//继续查找下一染色方法
			stkMap.pop(curdat);
			curArea = curdat.areaIndex;
			curColor += 1;
			if (curColor > MAXCOLORNUM)
				goto POP_LABEL;
			fullFlag = true;
		}
		while (judgeOverlapColor(areaRelate, stkMap, curArea, curColor))  //判断是否存在重复颜色
		{
			curColor += 1;
			//如果存在重复颜色，就颜色增加；
			//若达到最大颜色，则弹出数据；继续进行比对
POP_LABEL:	while (curColor > MAXCOLORNUM)   //表示已经遍历全部颜色
			{
				if (stkMap.isEmpty())
					return false;
				stkMap.pop(curdat);
				curArea = curdat.areaIndex;
				curColor = curdat.colorIndex + 1;
			}
		}
		curdat.areaIndex = curArea;
		curdat.colorIndex = curColor;
		stkMap.push(curdat);
		curArea += 1;   //下一个区域
		if (!fullFlag)
			curColor = 1;   //从第一种颜色开始遍历
	}
	if (stkMap.isEmpty())
		return false;
	return true;
}
