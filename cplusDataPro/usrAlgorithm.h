/**@file:     算法类的实现文件
  *@Author：  T.H.
  *@Version： V1.0
  *@Note:     排序算法适用于基本数据类型，算法包含：
			  1.插入排序---------时间复杂度O(n^2)，空间复杂度O(1)，稳定排序
			  2.折半插入排序（与1相近）
			  3.希尔排序---------时间复杂度O(n(logn)^2)，空间复杂度O(1)，不稳定排序


			  查找算法包含:
			  1.二分查找
*/
#pragma once

#ifndef __USRALGORITHM_H__
#define __USRALGORITHM_H__
/** 引入文件----------------------------------------------------------------------*/
#include <iostream>
using namespace std;

/** 私有宏------------------------------------------------------------------------*/
#if !defined EN_NMSPACE_USR_DATASTRUCTURE
#define EN_NMSPACE_USR_DATASTRUCTURE    1  
#endif //EN_NMSPACE_USR_DATASTRUCTURE

#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif //EN_NMSPACE_USR_DATASTRUCTURE

	/** 排序算法定义---------------------------------------------------------*/

	template<typename elemType>void usrInsertSort(elemType Element[],const int szElem, \
		int sortBegin=1, int sortEnd=0);  //插入排序
	template<typename elemType>void usrBinInsertSort(elemType Element[], const int szElem, \
		int sortBegin=1,int sortEnd=0);
	//希尔排序--tspan为分组间隔
	template<typename elemType>void usrShellSort(elemType Element[], const int szElem, const int tspan); 
	template<typename elemType>	void usrBubSort(elemType Element[], const int szElem);  //冒泡排序
	/** 查找算法定义---------------------------------------------------------*/
	//二分查找，针对升序排列的数据，tDat--查找的数据
	template<typename elemType>int usrBinSearch(const elemType Element[],const int szElem,const elemType tDat);  

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif //EN_NMSPACE_USR_DATASTRUCTURE

/** 公有方法的实现---------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif //EN_NMSPACE_USR_DATASTRUCTURE

/** 排序算法实现-------------------------------------------------------------------------------------*/

/**
  @Func: 顺序结构的插入排序
  @Para: Element--待排序的内存，szElem--排序的内存大小
  @Note: 思想-----将内存中的第一个元素作为已经排序过的数据，然后第二个元素和第一个元素比较，
  若较小，则插入在第一个之前（也就是交换数据），若较大，就不改变，
  接下来的元素与前面元素依次比较，若有R(i-1)<Rj<Ri，则插入在Ri之前，同时将后面Ri到Rj-1的数据向后移动
  数据全部插入完成，则排序结束
*/
template<typename elemType>void usrInsertSort(elemType Element[],const int szElem,int sortBegin,int sortEnd)
{
	elemType tmp;
	int i = 0, j = 0;
	if (sortEnd == 0)
		sortEnd = szElem - 1;
	for (i = sortBegin; i <= sortEnd; i++)
	{
		tmp = Element[i]; //缓存需要插入的数据
		for (j = i-1; j >= sortBegin&&Element[j]>tmp; j--)  //把数据向后移动
		{
			Element[j + 1] = Element[j];
		}
		Element[j + 1] = tmp;  //插入数据
	}
}
/**
  @Func: 折半插入排序
  @Para: Element--待排序的内存，szElem--排序的内存大小
  sortBegin/sortEnd-开始排序的位置，索引从 0 开始计算
  @Note: 思想-----和直接插入排序类似，只是在查找技术上有所区别
  查找插入位置时，对已经排完序的数据进行对半查找（二分法）
  eg: usrBinInsertSort(Element,szElem,1,3)---将数组Element索引 1--3 的元素进行排序
*/
template<typename elemType>void usrBinInsertSort(elemType Element[],const int szElem,int sortBegin,int sortEnd) 
{
	elemType tmp;
	int startPos = 0, midPos = 0,endPos = 0;
	int i = 0, j = 0;
	if (sortEnd == 0)
		sortEnd = szElem-1;
	for (i = sortBegin; i <= sortEnd; i++)
	{
		startPos = sortBegin;
		endPos = i-1;
		tmp = Element[i];  //暂存待插入的数据
		while (startPos <= endPos)  //定位插入的位置--满足R(i-1)<Rj<Ri
		{
			midPos = (startPos + endPos) / 2;
			if (Element[midPos] > tmp)
			{
				//向前找
				endPos = midPos - 1;
			}
			else  //为了稳定，所以 = 也从向后查找
			{
				//向后找
				startPos = midPos + 1;
			}
		}
		for (j = i - 1; j > endPos; j--)  //将数据向后移位
		{
			Element[j + 1] = Element[j];
		}
		Element[j+1] = tmp;  //插入数据
	}
}

/**
  @Func: 希尔排序
  @Para: Element--待排序的内存，szElem--排序的内存大小，tspan----表示最开始的分组增量
  @Note: 思想-----将待排序的数据进行多次分组，并在组内可以进行直接插入排序，也可以其他排序
		      每次分组的的增量满足d(i+1)<di，为了方便可以设置 d(i+1) = di/2；
			  直至 di=1 ，表示整个数据都进行了排序
  @Exp:  因为方法的实现使用的是函数调用，这个会占用很多的资源
*/
template<typename elemType>void usrShellSort(elemType Element[], const int szElem,const int tspan)
{
	int span = tspan;
	int *dist = new int[szElem]();  //申请空间并初始化为0
	int begin = 0, end = 0,cnt = 0;
	while (span >= 1)
	{
		//装载元素到 d 中
		for (int i = 0; i < span; i++)
		{
			begin = cnt;
			for (int j = i; j < szElem; j+=span)
			{
				dist[cnt++] = Element[j];
			}
			end = cnt-1;
			//在组内进行直接插入排序
			usrInsertSort(dist, szElem, begin, end);
		}
		//更新间隔
		span = span / 2;
		cnt = 0;  //更新计数器
		//更新数据
		for (int cnt = 0; cnt < szElem; cnt++)
			Element[cnt] = dist[cnt];
	}
	delete[]dist; dist = nullptr;
}

/**
  @Func: 冒泡排序
  @Para: Element--待排序的内存，szElem--排序的内存大小
  @Note: 思想-----
  @Exp:  
*/
template<typename elemType>void usrBubSort(elemType Element[], const int szElem)
{

}



/** 查找算法实现-------------------------------------------------------------------------------------*/

/**
  @Func：二分法查找算法
  @Para: Element--待查找数据的内存，szElem--内存大小，tdat--查找的数据
  @Ret : 返回查找到的坐标，若不存在，返回 -1
  @Note: 针对升序排列的数据---可以使用递归法编写
*/
template<typename elemType>int usrBinSearch(const elemType Element[],const int szElem,const elemType tDat)
{
	int curIndex = 0, retPos = -1;
	int startPos = 0, endPos = szElem-1;
	for(int i=startPos;i<=endPos;i++)
	{
		curIndex = (startPos + endPos )/ 2;
		if (Element[i] == tDat)
		{
			retPos = i; break;
		}
		if (Element[curIndex] > tDat)
		{
			//向前查找
			endPos = curIndex-1;
		}
		else if (Element[curIndex] < tDat)
		{
			//向后查找
			startPos = curIndex + 1;
		}
		else
		{
			retPos = curIndex; break;
		}
	}
	return retPos;
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif //EN_NMSPACE_USR_DATASTRUCTURE

#endif //__USRALGORITHM_H__
