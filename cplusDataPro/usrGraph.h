/**@file:     用户图类的定义与实现文件
  *@Author：  T.H.
  *@Version： V1.0
  *@Note:     目前在析构的时候没有将邻接表的数据析构完全，
			  只是使用的vector将邻接表头指针数据清除，并没有释放后继指针的数据

			  该图类实现，极为不方便，存在很多的局限性，只适用于学习图的相关算法
			  不具有普遍性
*/

#pragma once

#pragma warning(disable:4996)

#ifndef __CPLUS_USRGRAPH_H__
#define __CPLUS_USRGRAPH_H__

/** 引入文件----------------------------------------------------------------------*/
#include "usrList.h"
#include "usrStack.h"
#include "usrQueue.h"
#include <math.h>
#include <list>
#include <vector>
#include <map>
#include <cstring>
#include <memory>  //载入智能指针库
/** 私有宏------------------------------------------------------------------------*/
#if !defined EN_USR_GRAPH_CLASS
	#define EN_USR_GRAPH_CLASS       (1)      //使用用户堆栈类
#endif  //EN_USR_GRAPH_CLASS

#if EN_USR_GRAPH_CLASS
	#define macroGpStkTmp     usrStackUnique  //没有重复数据的堆栈
	#define macroGpDeqTmp     usrQueue
#else
	#define macroGpStkTmp     stack
	#define macroGpDeqTmp     deque
#endif //EN_USR_GRAPH_CLASS


#define EN_MULIT_INFOTYPE               (0)       //设置邻接表结点数据的类型
												  //0：表示常规的基本类型 1：表示结构体或是类类型的结点数据

#define EN_OCCUPYIDE                    (0)       //是否在删除图结点时，使用占位符
#define GRAPH_MAX_WEIGHT_LINE           (65535)   //最大权重值

#if EN_OCCUPYIDE
#define OCCUPIED_POSITION_CHAR         (-2)      //占位符宏
#endif //EN_OCCUPYIDE

/** 类定义------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//使用邻接表的形式进行存储图结点的关系//

//---------------------------------图的方法定义------------------------------------//
template<typename nodeDataType,typename infoType>
class usrGraph
{
private:
	//usrList<nodeDataType, infoType>adjList;
	int m_numNode;
	int m_numEdge;
	vector< HeadNode<nodeDataType,infoType>* >m_vecHead;  //用于装载头结点
protected:
	//结点数据访问
	bool visitNode(const nodeDataType &tdat, HeadNode<nodeDataType,infoType> *tptr_Node, bool tbMode = false)
	{
		if (tbMode)
		{
			if (!memcmp(&tptr_Node->nodeDat, &tdat, sizeof(nodeDataType)))
				return true;
		}
		else
		{
#if EN_MULIT_INFOTYPE
			cout << "结点数据：" << tptr_Node->nodeDat.Index << endl;
#else //输出基本类型数据
			cout << "结点数据：" << tptr_Node->nodeDat << endl;
#endif
		}
		return false;
	}
	int m_getInfoIndex(const Node<infoType>* tptr_Node)
	{
		//如果infoType是结构体或是类 类型，需要更改此处程序
#if EN_MULIT_INFOTYPE
		return  tptr_Node->nodeDat.Index;// tptr_Node->nodeDat.Index;  
#else
		return tptr_Node->nodeDat;
#endif //EN_MULIT_INFOTYPE
	}
	//将邻接表转换为邻接矩阵，索引值从0开始
	//graphMode--表示图的模式，默认为无向图  true表示有向图
	void listInvertTable(vector< vector<int> >&t_table, bool graphMode=false)const;   
public:
	usrGraph();
	~usrGraph();
	//创建图
	template<typename ...pack_infoType>
	void createGraph(const nodeDataType t_graphNode, pack_infoType...t_line);
	void createGraph(const nodeDataType t_graphNode);  //多态---结点的边为空时的图结点构建
	//删除图中的结点以及相应以该结点为尾的弧
	void deleteGraphNode(const nodeDataType t_graphNode);

	//设置边的权值
	bool m_setLineWeight(HeadNode<nodeDataType, infoType>* tHeadPtr, int tLineIndex, int tLineWeight);
	//找出头结点所指链表的最小权重边的结点索引值
	int m_findMinLine(HeadNode<nodeDataType, infoType>* tHeadPtr);
	//定位元素索引 从 1 开始计数
	int LocalElem(const nodeDataType t_graphNode);

	//=========================== 图的基本应用 ===========================//
	//深度优先遍历
	//t_searchMode  表示搜索模式，false---表示忽略数据，直接全部遍历
	bool deepFirstSearch(const nodeDataType &t_startElem, const nodeDataType &t_searchData,\
		const bool t_searchMode = false);
	//宽度优先遍历
	bool breadthFirstSearch(const nodeDataType &t_startElem, const nodeDataType &t_searchData, \
		const bool t_searchMode = false);
	
	void minCostPrim();//最小代价生成树----针对无向图
	void minRoadLenDijksra(const nodeDataType &t_startElem);   //最短路径算法---针对有向图
	void topSort_AOV();
	void AOE();  //AOE网络
	//针对AOV网络，使用拓扑排序算法检测网络中是否存在环路
};

//---------------------------------图的方法实现------------------------------------//
template<typename nodeDataType, typename infoType>
usrGraph<nodeDataType, infoType>::usrGraph() :m_numNode(0), m_numEdge(0)
{
	//初始化私有变量
}
template<typename nodeDataType, typename infoType>
usrGraph<nodeDataType, infoType>::~usrGraph()
{
	//HeadNode<nodeDataType, infoType> *l_ptrHead = nullptr;
	//析构Vector里的链表数据
	while(m_vecHead.size())
	{
		deleteGraphNode(m_vecHead[0]->nodeDat);
	}
}
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
listInvertTable(vector< vector<int> >&t_table,bool graphMode)const   //将邻接表转换为邻接矩阵
{
	//传入的参数t_table需要是一个m_numNode大小数组的向量
	//将向量表t_table设置为m_numNode*m_numNode的矩阵
	for (auto &vecElem:t_table)
	{
		//vecElem.resize(m_numNode);
#if EN_MULIT_INFOTYPE
		//将所有边预设为最大权重
		vecElem.assign(m_numNode, GRAPH_MAX_WEIGHT_LINE);  //设置数组的大小与初值
#else //基本类型
		vecElem.assign(m_numNode, 0);  //设置数组的大小与初值
#endif //EN_MULIT_INFOTYPE
	}
	int curIndex = 0;
	Node<infoType>* curPtr = nullptr;
	for (auto elem : m_vecHead)
	{
		curPtr = elem->ptrNext;
		while (curPtr)
		{
			//对称矩阵
#if EN_MULIT_INFOTYPE
			t_table[curIndex][(curPtr->nodeDat.Index)-1] = curPtr->nodeDat.Weight;
#else //基本类型
			t_table[curIndex][(curPtr->nodeDat) - 1] = 1;  //1：表示邻接
#endif //EN_MULIT_INFOTYPE
			if (!graphMode)  //若是有向图 graphMode=true 此时邻接矩阵就不一定不是对称矩阵
				t_table[(curPtr->nodeDat.Index) - 1][curIndex] = t_table[curIndex][(curPtr->nodeDat.Index) - 1];
			curPtr = curPtr->ptrNext;
		}
		curIndex++;
	}
}
//================================= 图操作相关方法 ============================================//
//function：在解包时调用，判断链表中是否存在重复数据，若存在，则不插入信息
//return：返回是否存在重复数据
template<typename nodeDataType,typename infoType>
int usr_unpack_line(usrList<nodeDataType, infoType>*t_headVec, infoType t_elem)
{
	if ((t_headVec->findData(t_elem) != -1) && (!t_headVec->isEmpty()))
	{
		return 1;
	}
	t_headVec->insertAfter(t_elem); return 0;
}
//查找最小权重的边索引值
template<typename nodeDataType, typename infoType>int usrGraph<nodeDataType, infoType>::
m_findMinLine(HeadNode<nodeDataType, infoType>* tHeadPtr)
{
	int minWeight = GRAPH_MAX_WEIGHT_LINE;
	int minIndex = 0;
#if  EN_MULIT_INFOTYPE
	Node<infoType>* lPtr = tHeadPtr->ptrNext;
	while (lPtr)
	{
		if (lPtr->nodeDat.Weight < minWeight)
		{
			minWeight = lPtr->nodeDat.Weight;
			minIndex = lPtr->nodeDat.Index;
		}
		lPtr = lPtr->ptrNext;
	}
#endif //EN_MULIT_INFOTYPE
	return minIndex;
}
//设置边的权重
template<typename nodeDataType, typename infoType>bool usrGraph<nodeDataType, infoType>::
m_setLineWeight(HeadNode<nodeDataType, infoType>* tHeadPtr, int tLineIndex, int tLineWeight)
{
#if EN_MULIT_INFOTYPE
	Node<infoType>* lPtr = tHeadPtr->ptrNext;
	while (lPtr)
	{
		if (lPtr->nodeDat.Index == tLineIndex)
		{
			lPtr->nodeDat.Weight = tLineWeight; return true;
		}
		lPtr = lPtr->ptrNext;
	}
#endif //EN_MULIT_INFOTYPE
	return false;
}

//查找元素在表中位置--从 1 开始计算
template<typename nodeDataType, typename infoType>int usrGraph<nodeDataType, infoType>::
LocalElem(const nodeDataType t_graphNode)
{
	for (unsigned int cnt = 0; cnt < m_vecHead.size(); cnt++)//===> for each (auto l_vecElem in m_vecHead)
	{
		if (!memcmp(&m_vecHead[cnt]->nodeDat, &t_graphNode, sizeof(nodeDataType)))
			return cnt + 1;  //从 1 开始计算
	}
	return (-1);
}
//================================= 图的基本应用 ============================================//
//t_graph 为图结点，t_line 为图与其他结点的关系
template<typename nodeDataType, typename infoType>
template<typename...pack_infoType>
void usrGraph<nodeDataType, infoType>::
createGraph(const nodeDataType t_graphNode, pack_infoType...t_line)
{
	usrList<nodeDataType, infoType> *l_headVec = new(usrList<nodeDataType, infoType>);
	l_headVec->setHeadVal(t_graphNode);
	int cnt = 0;
	int sz = sizeof...(t_line);
	if (sizeof...(t_line) != 0)
	{
		int a[] = { (cnt+=usr_unpack_line(l_headVec,t_line), 0)... };  //解包
		m_numNode += 1;
	}
	m_vecHead.push_back(l_headVec->getHeadNode());
	m_numEdge += (sizeof...(t_line)-cnt);  //计算边数
}
//多态-----结点的边为空时的图结点构建
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
createGraph(const nodeDataType t_graphNode)
{
	usrList<nodeDataType, infoType> *l_headVec = new(usrList<nodeDataType, infoType>);
	l_headVec->setHeadVal(t_graphNode);  //设置表头结点数据
	m_vecHead.push_back(l_headVec->getHeadNode());
	m_numNode += 1;
}
//删除图中的结点以及相应以该结点为尾的弧
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
deleteGraphNode(const nodeDataType t_graphNode)
{
	int index = LocalElem(t_graphNode) - 1;
	int listLength = 0;
	//获取链表数据，并释放空间
	HeadNode<nodeDataType, infoType> *lheadPtr = m_vecHead[index];
	Node<infoType> *curPtr = lheadPtr->ptrNext;
	//获取更改的边数目
	while (curPtr)
	{
		curPtr = curPtr->ptrNext;
		++listLength;
	}
#if EN_OCCUPYIDE   //是否使用占位符
	//需要添加一个占位数据，以防止后面的遍历或是计算出现索引值不匹配
	m_vecHead[index] = OCCUPIED_POSITION_CHAR;  //占位符
#else
	//将数据从vecHead中删除
	m_vecHead.erase(m_vecHead.begin() + index);
#endif  //EN_OCCUPYIDE

	//更新结点数据与边信息
	m_numNode -= 1;
	if (m_numNode < 0)
		m_numNode = 0;
	m_numEdge -= listLength;
	if (m_numEdge < 0)
		m_numEdge = 0;
	//释放链表空间
	usrList<nodeDataType, infoType> l_tmpList;
	l_tmpList.clrLinerList(&lheadPtr);
	
}

//深度优先数据遍历
//t_searchMode默认为false---表示不忽略数据查找
template<typename nodeDataType, typename infoType>bool usrGraph<nodeDataType, infoType>::
deepFirstSearch(const nodeDataType &t_startElem, const nodeDataType &t_searchData, const bool t_searchMode)
{
	vector<bool>visitVec(m_numNode,false);  //初始化所有的值为 false
	usrStackUnique<HeadNode<nodeDataType, infoType>*>stkOrd;  //用于存储访问顺序
	HeadNode<nodeDataType, infoType>*curHeadPtr = nullptr;
	Node<nodeDataType>*curPtr = nullptr;
	int curIndex = LocalElem(t_startElem);  //索引值从 1 开始
	visitVec[curIndex - 1] = true;  //标记访问结点
	curHeadPtr = m_vecHead[curIndex - 1];
	//访问起始图结点数据
	if (visitNode(t_searchData, curHeadPtr, t_searchMode))
		return true;
	curPtr = curHeadPtr->ptrNext;
	stkOrd.push(curHeadPtr);
	while (true)
	{
		if (!curPtr)  //这个链表访问完了
		{
			stkOrd.pop(curHeadPtr);  //弹出数据
			if (stkOrd.isEmpty())
				break;   //查找完成
			curHeadPtr = stkOrd.getTopNode()->nodeDat;  //获取栈顶头结点
			curPtr = curHeadPtr->ptrNext;
			if (!curPtr)continue;
		}
		//获取inforType中的索引值
		curIndex = getIndex_InfoType(curPtr);
		//curIndex = curPtr->nodeDat;
		if (visitVec[curIndex-1])  //如果已经访问过了，都是头结点数据
		{
			//指向下一个结点
			curPtr = curPtr->ptrNext;
			continue;
		}
		//没有访问过当前数据
		visitVec[curIndex - 1] = true;  //标记访问结点
		//更新头结点
		curHeadPtr = m_vecHead[curIndex - 1];
		//访问图结点数据
		if (visitNode(t_searchData, curHeadPtr, t_searchMode))
			return true;
		stkOrd.push(curHeadPtr);
		curPtr = curHeadPtr->ptrNext;
	}
	return false;
}
//宽度遍历算法
//t_searchMode默认为false---表示不忽略数据查找
template<typename nodeDataType, typename infoType>bool usrGraph<nodeDataType, infoType>::
breadthFirstSearch(const nodeDataType &t_startElem, const nodeDataType &t_searchData, const bool t_searchMode)
{
	vector<bool>visitVec(m_numNode, false);  //初始化所有的值为 false，节点访问标志
	usrQueue<HeadNode<nodeDataType, infoType>*>queOrd;  //用于存储访问顺序
	HeadNode<nodeDataType, infoType>*curHeadPtr = nullptr;
	Node<nodeDataType>*curPtr = nullptr;
	int curIndex = LocalElem(t_startElem);  //索引值从 1 开始
	if (curIndex == -1)
		return false;
	curHeadPtr = m_vecHead[curIndex-1];
	//访问节点
	if (visitNode(t_searchData, curHeadPtr, t_searchMode))
		return true;
	visitVec[curIndex-1] = true;
	//将访问后的邻近节点压入队列中
	queOrd.enQueue(curHeadPtr);
	//visit all of the date pointed by the curHeadPtr
	while (!queOrd.isEmpty())
	{
		queOrd.deQueue(curHeadPtr); //出栈
		curPtr = curHeadPtr->ptrNext;
		while (curPtr)
		{
			//获取inforType中的索引值
			curIndex = m_getInfoIndex(curPtr);  //getIndexCurptr();
			curHeadPtr = m_vecHead[curIndex-1];
			if (!visitVec[curIndex-1])  //如果没有访问过
			{
				queOrd.enQueue(curHeadPtr);
				visitVec[curIndex-1] = true;//将其标志位置 1 
				//访问节点
				if (visitNode(t_searchData, curHeadPtr, t_searchMode))
					return true;
			}
			curPtr = curPtr->ptrNext;
		}
	}
	return false;
}
//最小代价生成树Prim算法实现---针对无向图，使用邻接矩阵实现
//只有类或是结构体类型的信息结点类型的边，权重或是代价才有含义
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
minCostPrim()
{  
	//使用邻接矩阵进行构建最小代价生成树
	vector<vector<int>>adjTable(m_numNode);  //邻接矩阵
	listInvertTable(adjTable);  //将当前邻接表转换为矩阵形式
	int *flag = new int[m_numNode];
	int tmp_m = 0, tmp_n = 0;
	int minDist = GRAPH_MAX_WEIGHT_LINE;
	memset(flag, 0, sizeof(int)*m_numNode);
	flag[0] = 1;
	for (int i = 0; i < m_numNode - 1; i++)
	{
		minDist = GRAPH_MAX_WEIGHT_LINE;
		for (int m = 0; m < m_numNode; m++)
		{
			for (int n = 0; n < m_numNode; n++)
			{
				if (flag[m] + flag[n] == 1 && adjTable[m][n] < minDist)
				{
					minDist = adjTable[m][n];
					tmp_m = m; tmp_n = n;
				}
			}
		}
		cout << tmp_m+1 << "---" << tmp_n+1 << endl;
		adjTable[tmp_m][tmp_n] = GRAPH_MAX_WEIGHT_LINE; //不再考虑找到的边
		flag[tmp_m] = 1; flag[tmp_n] = 1; //将边加入集合中
	}
	delete []flag; flag = nullptr;
}
//最短路径算法----针对有向图，起始点不一样，结果也有区别
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
minRoadLenDijksra(const nodeDataType &t_startElem)
{
	//使用邻接矩阵进行求解
	vector<vector<int>>adjTable(m_numNode);  //邻接矩阵
	listInvertTable(adjTable, true);  //将当前邻接表转换为矩阵形式，使用有向图
	int startIndex = LocalElem(t_startElem) - 1; //定位起始坐标，从 1 开始计数
	int minIndex = 0, minLength;
	int *indexCache = new int[m_numNode];  //用于存储满足条件的结点索引值
	int *distStart = new int[m_numNode];   //用于存储与起始结点距离值
	memset(indexCache, 0, sizeof(int)*m_numNode);  //初始化
	char **path, tmpCache[20];  //存储路径，用于显示
	path = new char*[m_numNode];
	for (int cnt = 0; cnt < m_numNode; cnt++)
	{
		path[cnt] = new char[100];
	}
	for (int loop = 0; loop < m_numNode; loop++)
	{
		distStart[loop] = adjTable[startIndex][loop];  //装载距离值
		if (distStart[loop] < GRAPH_MAX_WEIGHT_LINE) //装载路径值
			sprintf(path[loop], "%d ---> %d", startIndex + 1, loop + 1);
		else
			sprintf(path[loop], "");
	}
	indexCache[startIndex] = 1;
	//查找与其他结点的最短路径
	for (int loop = 0; loop < m_numNode; loop++)
	{
		minLength = GRAPH_MAX_WEIGHT_LINE;
		minIndex = 0;  //最小路径索引值
		//在与起始点直接连接中查找最短路径的值
		for (int i = 0; i < m_numNode; i++)
		{
			if (distStart[i] < minLength && (!indexCache[i]))  //最小，且没有在集合中
			{
				minLength = distStart[i];
				minIndex = i;
			}
		}
		indexCache[minIndex] = 1;  //将最小的结点放入集合中
		//在剩下的结点中查找最小值
		for (int j = 0; j < m_numNode; j++)
		{
			if ( (!indexCache[j]) && distStart[minIndex] + adjTable[minIndex][j] < distStart[j])  //在集合之外查找
			{
				//更新距离值，路径值
				distStart[j] = distStart[minIndex] + adjTable[minIndex][j];
				sprintf(tmpCache, " ---> %d", j+1);
				strcpy(path[j],path[minIndex]);
				strcat(path[j], tmpCache);
			}
		}
	}
	//输出数据
	for (int i = 0; i < m_numNode; i++)
	{
		if (i!=startIndex)
			cout << "Dist:" << distStart[i] << "\t" << path[i] << endl;
	}
	//释放空间
	delete[]distStart; distStart = nullptr;
	delete[]indexCache; indexCache = nullptr;
	for (int i = 0; i < m_numNode; i++)
	{	
		delete[]path[i]; path[i] = nullptr;
	}
	delete[]path; path = nullptr;
}

/** @Function:针对AOV网络，进行拓扑排序
    @Output：输出排序结果
*/
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
topSort_AOV()
{
	//1.找出任意的没有前继指针的结点，并访问
	//2.删除该结点，与相应的边之后，再次进行 1 操作
	//直到所有结点都有前继指针或是所有结点都访问完成
	//为了更加简单操作，可以在结点中，加入 结点的入度信息，以供判断是否存在前继指针
#if 0  //伪代码
	HeadNode<nodeDataType, infoType> *curNode, *tmpNode;
	vector<int>vecIndegree(m_numNode,0);  //用于存放各个结点的入度信息，默认为 0
	int tmpNode = m_numNode;  //用于保持没有更改前的结点数
	int curIndex = 0;
	for (int i = 0; i < tmpNode; i++)
	{
		//选择一个没有前继指针的结点
		findPrePtr(vecIndegree);
		if (vecIndegree.size() == 0)   //入度为 0 的结点已经全部查找完成
			break;
		curNode = m_vecHead[vecIndegree[0]];
		//访问数据
		visitNode(curNode);
		curIndex = vecFindElem(curNode->nodeDat);
		vecIndegree[curIndex] = -1;  //virtualDelNode(curNode);  这个并不会操作实际的图，只是虚拟删除
	}
	return true;

	void findPrePtr(vector<int>&vecRet)  //查找没有前继指针的结点，将其加入到vector中并返回
	{
		HeadNode<nodeDataType, infoType> *curHead = nullptr;
		Node<infoType> *curPtr = nullptr;
		int curIndex = 0;
		for (int i = 0; i < m_numNode; i++)
		{
			curHead = m_vecHead[i];
			if(vecRet[i]== -1)  //取出的数据是之前删除的数据的位置
				continue;	                        //OCCUPIED_POSITION_CHAR--虚拟删除数据之后放置的占位符
			curPtr = curHead->ptrNext;
			while (curPtr)
			{
				curIndex = m_getInfoIndex(curPtr);
				vecRet[curIndex]++;
				curPtr = curPtr->ptrNext;
			}
		}
	}

#endif //0

}

template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
AOE()
{

}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

#endif //__CPLUS_USRGRAPH_H__