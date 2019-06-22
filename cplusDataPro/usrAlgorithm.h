/**@file:     算法类的实现文件
  *@Author：  T.H.
  *@Version： V1.0
  *@Note:     排序算法适用于基本数据类型，算法包含：
			  1.插入排序---------时间复杂度O(n^2)，空间复杂度O(1)，稳定排序
			  2.折半插入排序（与1相近）
			  3.希尔排序---------时间复杂度O(n(logn)^2)，空间复杂度O(1)，不稳定排序
			  4.冒泡排序---------时间复杂度O(n^2)，不稳定排序
			  5.快速排序---------平均时间复杂度O(nlogn)，空间复杂度O(n)
							     不稳定排序（目前平均速度最快的排序算法之一）
			  6.直接选择排序-----和冒泡排序相似
			  7.堆排序-----------使用最大堆树，进行排序，时间复杂度O(nlogn)


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

	/** 排序算法定义一览表---------------------------------------------------------*/
	//插入排序
	template<typename elemType>void usrInsertSort(elemType Element[],const int szElem, \
		int sortBegin=1, int sortEnd=0);  
	template<typename elemType>void usrBinInsertSort(elemType Element[], const int szElem, \
		int sortBegin=1,int sortEnd=0);
	//希尔排序--tspan为分组间隔
	template<typename elemType>void usrShellSort(elemType Element[], const int szElem, const int tspan); 
	//冒泡排序
	template<typename elemType>void usrBubSort(elemType Element[], const int szElem);  
	//快排分组
	template<typename elemType>int usrQuickSort_Partition(elemType Element[],int low,int high);
	template<typename elemType>void usrQuickSort(elemType Element[],const int sortBegin,const int sortEnd); //快速排序
	template<typename elemType>void usrQuickSort(elemType Element[], const int szElem);  //多态---快速排序的用户接口

	//直接选择排序
	template<typename elemType>void usrSelectSort(elemType Element[], const int szElem);
	//堆排序
	template<typename elemType>void usrHeapSort(elemType Element[], const int szElem);
	template<typename elemType>void usrInitMaxHeap(elemType Element[], const int szElem);
	template<typename elemType>bool usrDelHeapNode(elemType Element[], const int szElem, elemType &ret);

	//归并排序
	template<typename elemType>void usrMergeSort(elemType Element[], const int szElem);

	/** 查找算法定义一览表---------------------------------------------------------*/
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
  @Note: 思想-----每相邻元素比较大小，较大就进行交换，将大的数据交换到后面，
		 经过一次排序，最后一个数据就是最大的元素；每排序一次，就可以只对前n-i个数据进行排序
		 直到所有的数据排序完成。
  @Exp:  
*/
template<typename elemType>void usrBubSort(elemType Element[], const int szElem)
{
	bool change = true;  //检测是否有数据交换
	int i = 0, j = szElem;
	elemType tmp;
	while (j > 0&&change)
	{
		change = false;
		for (i = 0; i < j-1; i++)
		{
			if (Element[i] > Element[i + 1])
			{
				tmp = Element[i + 1];
				Element[i + 1] = Element[i];
				Element[i] = tmp;
				change = true;
			}
		}
		j--;
	}
}

/**
  @Func：快速排序
  @Para：Element--待排序的内存，szElem--排序的内存大小
		 sortBegin--排序的起始索引（包含） sortEnd----排序的结束索引（包含）

  @Note：思想-----在待排序的那个记录中任意选取一个记录Ri作为标准，调节序列中各个记录的位置，
          使排在Ri前面的记录都小于Ri，排在Ri后面的记录都大于等于Ri，我们把这样的一个过程称作一次快速排序；
		  第一次快排之后，确定了Ri的排列位置，同时将剩下的记录分为两个子序列。对这两个子序列分别进行快排；
		  如此重复下去，当每个子序列的长度为1时，全部记录排序完成。
*/
template<typename elemType>void usrQuickSort(elemType Element[], const int sortBegin,const int sortEnd)
{
	int local = 0;
	if (sortBegin < sortEnd)
	{
		local = usrQuickSort_Partition(Element, sortBegin, sortEnd);
		usrQuickSort(Element, sortBegin, local - 1);//将左边的进行排序
		usrQuickSort(Element, local+1, sortEnd);//将右边的进行排序
	}
}
template<typename elemType>void usrQuickSort(elemType Element[], const int szElem)
{
	usrQuickSort(Element, 0, szElem - 1);
}
//快排的分组函数，并返回定位点
//划重点----这个定位分组函数--思想很好
template<typename elemType>int usrQuickSort_Partition(elemType Element[],int low,int high)
{
	elemType tmp = Element[low];
	while (low<high)
	{
		while (low < high&&Element[high] >= tmp)
			high--;
		if (low < high)
			Element[low++] = Element[high];
		while (low < high&&Element[low] < tmp)
			low++;
		if (low < high)
			Element[high--] = Element[low];
	}
	Element[low] = tmp;
	return low;
}
/**
  @Func：直接选择排序
  @Para：Element--待排序的内存，szElem--排序的内存大小
  @Note：思想-----和冒泡排序差不多，冒泡排序是将大的交换到后面，
				而这是直接选择小的记录，并交换到前面，然后只对后面数据进行排序
*/
template<typename elemType>void usrSelectSort(elemType Element[], const int szElem)
{
	int i = 0, j = 0, minIndex = 0;
	elemType tmp;
	for (i = 0; i < szElem; i++)
	{
		minIndex = i;
		for (j = i + 1; j < szElem; j++)
		{
			if (Element[minIndex] > Element[j])
				minIndex = j;
		}
		//交换数据
		if (minIndex != i)
		{
			tmp = Element[i];
			Element[i] = Element[minIndex];
			Element[minIndex] = tmp;
		}
	}
}
/**
  @Func：堆排序
  @Para：Element--待排序的内存，szElem--排序的内存大小
  @Note：思想-----先将数据完全二叉树(可以是顺序结构)初始化为最大堆树
				然后从根结点开始删除节点，节点并不是真正的删除，而是将结点数据保存在最后；
				这样树结点全部删除时，就排序完成

  @Attd：需要注意，在此算法中由于使用的是顺序存储的树结构；因为通过索引计算树结点的孩子或是双亲结点时，
		 使用相除或是相乘计算，所以数据的 0 索引值不用，从 1 开始计算。
				
*/
template<typename elemType>void usrHeapSort(elemType Element[], const int szElem)
{
	elemType tmp;
	//申请空间
	elemType *cache = new elemType[szElem+1]();
	//将数据存入空间中,而且将cache[0]作为临时存储区，不存储Element数据
	memcpy(cache + 1, Element, sizeof(elemType)*szElem);
	//将数据转换为最大堆树
	usrInitMaxHeap(cache, szElem + 1);
	for (int i = szElem; i > 0; i--)
	{
		usrDelHeapNode(cache, i + 1, tmp);
		Element[i - 1] = tmp;  //将删除的根结点放在元素最后
	}
	delete[]cache; cache = nullptr;
}
//初始化最大堆树
//Element----内存中Element[0]作为临时缓存区，不存储Element数据
//szElem-----包含了 0 索引的值(0....szElem)
template<typename elemType>void usrInitMaxHeap(elemType Element[], const int szElem)
{
	int szData = szElem - 1;
	for (int parent = szData / 2; parent > 0; parent--)
	{
		Element[0] = Element[parent];
		int son = parent * 2;
		while (son <= szData)
		{
			if (son < szData)  //选择最大孩子结点
				if (Element[son] < Element[son + 1])
					son++;
			if (Element[0] > Element[son])  //
				 break;
			Element[son / 2] = Element[son]; //孩子结点往上移
			son = son * 2;
		}
		Element[son/2] = Element[0];
	}
}
//删除根节点，并将其保存在最后----边删除，边构建为完全二叉树
//Element----内存中Element[0]作为临时缓存区，不存储Element数据
//szElem-----包含了 0 索引的值(0...szElem)
//ret--------删除的结点元素
template<typename elemType>bool usrDelHeapNode(elemType Element[], const int szElem, elemType &ret)
{
	//申请空间
	if (szElem == 0)return false;
	int son = 2,parent=1,
		szCache = szElem - 1;
	ret = Element[1];
	Element[0] = Element[szCache--];  //保存当前最后叶子的数据，并更新树结点
	while (son<= szCache)
	{
		if(son<szCache)
			if (Element[son] < Element[son + 1])
				son++;
		if (Element[0] > Element[son])
			break;
		Element[parent] = Element[son];
		parent = son;
		son = son * 2;
	}
	Element[parent] = Element[0];
	return true;
}


template<typename elemType>void usrMergeSort(elemType Element[], const int szElem)
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
