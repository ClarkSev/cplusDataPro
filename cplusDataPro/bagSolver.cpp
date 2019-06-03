/**@file:     背包问题实现文件
  *@Author：  T.H.
  *@function:
  *@Version： V1.0
  *@Note:     None
*/

/** 引入文件----------------------------------------------------------------------*/
#include "bagSolver.h"
#include <iomanip>

/** 函数实现----------------------------------------------------------------------*/
//打印求出的结果
void printResult(usrStack<StackType>&t_Stack, const ElementType element[])
{
	usrStack<StackType>l_Stack;  //创建中转背包
	StackType stackTmp;
	int l_key = 0;
	cout << "number" << setw(10) << "name" << setw(10) \
		<< "place" << setw(10) << "weight" << endl;
	//中转堆栈
	while (!t_Stack.isEmpty())
	{
		t_Stack.pop(stackTmp);
		l_key = stackTmp.index;
		cout << element[l_key].number\
			<< setw(10) << element[l_key].name\
			<< setw(10) << element[l_key].place\
			<< setw(10) << element[l_key].weight << endl;
		l_Stack.push(stackTmp);
	}
	//将数据重新压入堆栈中
	while (!l_Stack.isEmpty())
	{
		l_Stack.pop(stackTmp);
		t_Stack.push(stackTmp);
	}
}
//求解函数
//szElem 从 1开始计算，表示element的最大索引
void knapSack(const ElementType element[],const int szElem,const int t_totalWeight)
{
	usrStack<StackType>l_Stack;  //创建背包
	StackType stackTmp;
	int l_key = 0, //创建索引
		l_RemainW = t_totalWeight; //用于保存背包剩余重量 
	do 
	{
		while (l_RemainW>0 && l_key < szElem)
		{
			if (element[l_key].weight <= l_RemainW)
			{
				stackTmp.index = l_key;
				l_Stack.push(stackTmp);
				l_RemainW -= element[l_key].weight;
			}
			l_key++;
		}
		if (l_RemainW == 0) //找到一个解
			printResult(l_Stack, element);
		l_Stack.pop(stackTmp);//弹出上一个数据
		//恢复当前索引值--->
		//注意这儿一定要使用该表达进行恢复
		//或是另外定义一个变量存储出错的索引值
		//否则恢复的索引值不对
		l_key = stackTmp.index;  
		l_RemainW += element[l_key].weight;//更新重量
		l_key++;
	} while (!l_Stack.isEmpty() || l_key < szElem);  
}

