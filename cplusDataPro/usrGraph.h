/**@file:     �û�ͼ��Ķ�����ʵ���ļ�
  *@Author��  T.H.
  *@Version�� V1.0
  *@Note:     Ŀǰ��������ʱ��û�н��ڽӱ������������ȫ��
			  ֻ��ʹ�õ�vector���ڽӱ�ͷָ�������������û���ͷź��ָ�������

			  ��ͼ��ʵ�֣���Ϊ�����㣬���ںܶ�ľ����ԣ�ֻ������ѧϰͼ������㷨
			  �������ձ���
*/

#pragma once

#pragma warning(disable:4996)

#ifndef __CPLUS_USRGRAPH_H__
#define __CPLUS_USRGRAPH_H__

/** �����ļ�----------------------------------------------------------------------*/
#include "usrList.h"
#include "usrStack.h"
#include "usrQueue.h"
#include <math.h>
#include <list>
#include <vector>
#include <map>
#include <cstring>
#include <memory>  //��������ָ���
/** ˽�к�------------------------------------------------------------------------*/
#if !defined EN_USR_GRAPH_CLASS
	#define EN_USR_GRAPH_CLASS       (1)      //ʹ���û���ջ��
#endif  //EN_USR_GRAPH_CLASS

#if EN_USR_GRAPH_CLASS
	#define macroGpStkTmp     usrStackUnique  //û���ظ�����
	#define macroGpDeqTmp     usrQueue
#else
	#define macroGpStkTmp     stack
	#define macroGpDeqTmp     deque
#endif //EN_USR_GRAPH_CLASS

#define GRAPH_MAX_WEIGHT_LINE           (65535)   //���Ȩ��ֵ

/** �ඨ��------------------------------------------------------------------------*/
#if EN_NMSPACE_USR_DATASTRUCTURE
namespace nmspace_usr_datastructure
{
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

//ʹ���ڽӱ����ʽ���д洢ͼ���Ĺ�ϵ//

//---------------------------------ͼ�ķ�������------------------------------------//
template<typename nodeDataType,typename infoType>
class usrGraph
{
private:
	//usrList<nodeDataType, infoType>adjList;
	int m_numNode;
	int m_numEdge;
	vector< HeadNode<nodeDataType,infoType>* >m_vecHead;  //����װ��ͷ���
protected:
	//������ݷ���
	bool visitNode(const nodeDataType &tdat, HeadNode<nodeDataType,infoType> *tptr_Node, bool tbMode = false)
	{
		if (tbMode)
		{
			if (!memcmp(&tptr_Node->nodeDat, &tdat, sizeof(nodeDataType)))
				return true;
		}
		else
			cout << "������ݣ�" << tptr_Node->nodeDat << endl;
		return false;
	}
	int m_getInfoIndex(const Node<infoType>* tptr_Node)
	{
		//���infoType�ǽṹ������� ���ͣ���Ҫ���Ĵ˴�����
		//tptr_Node->nodeDat;
		return  tptr_Node->nodeDat;// tptr_Node->nodeDat.Index;  
	}
	//���ڽӱ�ת��Ϊ�ڽӾ�������ֵ��0��ʼ
	//graphMode--��ʾͼ��ģʽ��Ĭ��Ϊ����ͼ  true��ʾ����ͼ
	void listInvertTable(vector< vector<int> >&t_table, bool graphMode=false)const;   
public:
	usrGraph();
	~usrGraph();
	//����ͼ
	template<typename ...pack_infoType>
	void createGraph(const nodeDataType t_graphNode, pack_infoType...t_line);
	void createGraph(const nodeDataType t_graphNode);  //��̬---���ı�Ϊ��ʱ��ͼ��㹹��

	//���ñߵ�Ȩֵ
	bool m_setLineWeight(HeadNode<nodeDataType, infoType>* tHeadPtr, int tLineIndex, int tLineWeight);
	//�ҳ�ͷ�����ָ�������СȨ�رߵĽ������ֵ
	int m_findMinLine(HeadNode<nodeDataType, infoType>* tHeadPtr);
	//��λԪ������ �� 1 ��ʼ����
	int LocalElem(const nodeDataType t_graphNode);

	//=========================== ͼ�Ļ���Ӧ�� ===========================//
	//������ȱ���
	//t_searchMode  ��ʾ����ģʽ��false---��ʾ�������ݣ�ֱ��ȫ������
	bool deepFirstSearch(const nodeDataType &t_startElem, const nodeDataType &t_searchData,\
		const bool t_searchMode = false);
	//������ȱ���
	bool breadthFirstSearch(const nodeDataType &t_startElem, const nodeDataType &t_searchData, \
		const bool t_searchMode = false);
	
	void minCostPrim();//��С����������----�������ͼ
	void minRoadLenDijksra(const nodeDataType &t_startElem);   //���·���㷨---�������ͼ
};

//---------------------------------ͼ�ķ���ʵ��------------------------------------//
template<typename nodeDataType, typename infoType>
usrGraph<nodeDataType, infoType>::usrGraph() :m_numNode(0), m_numEdge(0)
{
	//��ʼ��˽�б���
}
template<typename nodeDataType, typename infoType>
usrGraph<nodeDataType, infoType>::~usrGraph()
{
	//HeadNode<nodeDataType, infoType> *l_ptrHead = nullptr;
	////����Vector�����������
	//while (m_vecHead.size())
	//{

	//}
}
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
listInvertTable(vector< vector<int> >&t_table,bool graphMode)const   //���ڽӱ�ת��Ϊ�ڽӾ���
{
	//����Ĳ���t_table��Ҫ��һ��m_numNode��С���������
	//��������t_table����Ϊm_numNode*m_numNode�ľ���
	for (auto &vecElem:t_table)
	{
		//vecElem.resize(m_numNode);
		//�����б�Ԥ��Ϊ���Ȩ��
		vecElem.assign(m_numNode, GRAPH_MAX_WEIGHT_LINE);  //��������Ĵ�С���ֵ
	}
	int curIndex = 0;
	Node<infoType>* curPtr = nullptr;
	for (auto elem : m_vecHead)
	{
		curPtr = elem->ptrNext;
		while (curPtr)
		{
			//�Գƾ���
			t_table[curIndex][(curPtr->nodeDat.Index)-1] = curPtr->nodeDat.Weight;//t_table[curIndex][Index] = Weight;
			if (!graphMode)  //��������ͼ graphMode=true ��ʱ�ڽӾ���Ͳ�һ�����ǶԳƾ���
				t_table[(curPtr->nodeDat.Index) - 1][curIndex] = t_table[curIndex][(curPtr->nodeDat.Index) - 1];
			curPtr = curPtr->ptrNext;
		}
		curIndex++;
	}
}
//================================= ͼ������ط��� ============================================//
//function���ڽ��ʱ���ã��ж��������Ƿ�����ظ����ݣ������ڣ��򲻲�����Ϣ
//return�������Ƿ�����ظ�����
template<typename nodeDataType,typename infoType>
int usr_unpack_line(usrList<nodeDataType, infoType>*t_headVec, infoType t_elem)
{
	if ((t_headVec->findData(t_elem) != -1) && (!t_headVec->isEmpty()))
	{
		return 1;
	}
	t_headVec->insertAfter(t_elem); return 0;
}
//������СȨ�صı�����ֵ
template<typename nodeDataType, typename infoType>int usrGraph<nodeDataType, infoType>::
m_findMinLine(HeadNode<nodeDataType, infoType>* tHeadPtr)
{
	int minWeight = GRAPH_MAX_WEIGHT_LINE;
	int minIndex = 0;
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
	return minIndex;
}
//���ñߵ�Ȩ��
template<typename nodeDataType, typename infoType>bool usrGraph<nodeDataType, infoType>::
m_setLineWeight(HeadNode<nodeDataType, infoType>* tHeadPtr, int tLineIndex, int tLineWeight)
{
	Node<infoType>* lPtr = tHeadPtr->ptrNext;
	while (lPtr)
	{
		if (lPtr->nodeDat.Index == tLineIndex)
		{
			lPtr->nodeDat.Weight = tLineWeight; return true;
		}
		lPtr = lPtr->ptrNext;
	}
	return false;
}

//����Ԫ���ڱ���λ��--�� 1 ��ʼ����
template<typename nodeDataType, typename infoType>int usrGraph<nodeDataType, infoType>::
LocalElem(const nodeDataType t_graphNode)
{
	for (unsigned int cnt = 0; cnt < m_vecHead.size(); cnt++)//===> for each (auto l_vecElem in m_vecHead)
	{
		if (!memcmp(&m_vecHead[cnt]->nodeDat, &t_graphNode, sizeof(nodeDataType)))
			return cnt + 1;  //�� 1 ��ʼ����
	}
	return (-1);
}
//================================= ͼ�Ļ���Ӧ�� ============================================//
//t_graph Ϊͼ��㣬t_line Ϊͼ���������Ĺ�ϵ
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
		int a[] = { (cnt+=usr_unpack_line(l_headVec,t_line), 0)... };  //���
		m_numNode += 1;
	}
	m_vecHead.push_back(l_headVec->getHeadNode());
	m_numEdge += (sizeof...(t_line)-cnt);  //�������
}
//��̬-----���ı�Ϊ��ʱ��ͼ��㹹��
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
createGraph(const nodeDataType t_graphNode)
{
	usrList<nodeDataType, infoType> *l_headVec = new(usrList<nodeDataType, infoType>);
	l_headVec->setHeadVal(t_graphNode);  //���ñ�ͷ�������
	m_vecHead.push_back(l_headVec->getHeadNode());
	m_numNode += 1;
}

//����������ݱ���
//t_searchModeĬ��Ϊfalse---��ʾ���������ݲ���
template<typename nodeDataType, typename infoType>bool usrGraph<nodeDataType, infoType>::
deepFirstSearch(const nodeDataType &t_startElem, const nodeDataType &t_searchData, const bool t_searchMode)
{
	vector<bool>visitVec(m_numNode,false);  //��ʼ�����е�ֵΪ false
	usrStackUnique<HeadNode<nodeDataType, infoType>*>stkOrd;  //���ڴ洢����˳��
	HeadNode<nodeDataType, infoType>*curHeadPtr = nullptr;
	Node<nodeDataType>*curPtr = nullptr;
	int curIndex = LocalElem(t_startElem);  //����ֵ�� 1 ��ʼ
	visitVec[curIndex - 1] = true;  //��Ƿ��ʽ��
	curHeadPtr = m_vecHead[curIndex - 1];
	//������ʼͼ�������
	if (visitNode(t_searchData, curHeadPtr, t_searchMode))
		return true;
	curPtr = curHeadPtr->ptrNext;
	stkOrd.push(curHeadPtr);
	while (true)
	{
		if (!curPtr)  //��������������
		{
			stkOrd.pop(curHeadPtr);  //��������
			if (stkOrd.isEmpty())
				break;   //�������
			curHeadPtr = stkOrd.getTopNode()->nodeDat;  //��ȡջ��ͷ���
			curPtr = curHeadPtr->ptrNext;
			if (!curPtr)continue;
		}
		//��ȡinforType�е�����ֵ
		curIndex = getIndex_InfoType(curPtr);
		//curIndex = curPtr->nodeDat;
		if (visitVec[curIndex-1])  //����Ѿ����ʹ��ˣ�����ͷ�������
		{
			//ָ����һ�����
			curPtr = curPtr->ptrNext;
			continue;
		}
		//û�з��ʹ���ǰ����
		visitVec[curIndex - 1] = true;  //��Ƿ��ʽ��
		//����ͷ���
		curHeadPtr = m_vecHead[curIndex - 1];
		//����ͼ�������
		if (visitNode(t_searchData, curHeadPtr, t_searchMode))
			return true;
		stkOrd.push(curHeadPtr);
		curPtr = curHeadPtr->ptrNext;
	}
	return false;
}
//��ȱ����㷨
//t_searchModeĬ��Ϊfalse---��ʾ���������ݲ���
template<typename nodeDataType, typename infoType>bool usrGraph<nodeDataType, infoType>::
breadthFirstSearch(const nodeDataType &t_startElem, const nodeDataType &t_searchData, const bool t_searchMode)
{
	vector<bool>visitVec(m_numNode, false);  //��ʼ�����е�ֵΪ false���ڵ���ʱ�־
	usrQueue<HeadNode<nodeDataType, infoType>*>queOrd;  //���ڴ洢����˳��
	HeadNode<nodeDataType, infoType>*curHeadPtr = nullptr;
	Node<nodeDataType>*curPtr = nullptr;
	int curIndex = LocalElem(t_startElem);  //����ֵ�� 1 ��ʼ
	if (curIndex == -1)
		return false;
	curHeadPtr = m_vecHead[curIndex-1];
	//���ʽڵ�
	if (visitNode(t_searchData, curHeadPtr, t_searchMode))
		return true;
	visitVec[curIndex-1] = true;
	//�����ʺ���ڽ��ڵ�ѹ�������
	queOrd.enQueue(curHeadPtr);
	//visit all of the date pointed by the curHeadPtr
	while (!queOrd.isEmpty())
	{
		queOrd.deQueue(curHeadPtr); //��ջ
		curPtr = curHeadPtr->ptrNext;
		while (curPtr)
		{
			//��ȡinforType�е�����ֵ
			curIndex = m_getInfoIndex(curPtr);  //getIndexCurptr();
			curHeadPtr = m_vecHead[curIndex-1];
			if (!visitVec[curIndex-1])  //���û�з��ʹ�
			{
				queOrd.enQueue(curHeadPtr);
				visitVec[curIndex-1] = true;//�����־λ�� 1 
				//���ʽڵ�
				if (visitNode(t_searchData, curHeadPtr, t_searchMode))
					return true;
			}
			curPtr = curPtr->ptrNext;
		}
	}
	return false;
}
//��С����������Prim�㷨ʵ��---�������ͼ��ʹ���ڽӾ���ʵ��
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
minCostPrim()
{
#if 0
	//vector<bool>vecLineState(m_numNode,false);  //���ڱ�־���Ƿ��Ѿ�����
	HeadNode<nodeDataType, infoType>*curHeadPtr = nullptr;
	int curIndex = 0, minLineIndex = 0;
	//������СȨ�صı�
	int minWeightLine = GRAPH_MAX_WEIGHT_LINE;
	vector<vector<int>>vecIndexCache(m_numNode);  //���ڴ洢��С�����ߵĽ������ֵ
	for (int loop = 0; loop < m_numNode; loop++)
	{
		for (curIndex = 0; curIndex < m_numNode; curIndex++)   //��ѭ��ʹ�ÿ�����ȱ�����������СȨ�صı�
		{
			curHeadPtr = m_vecHead[curIndex];
			//ʹ�ÿ�����ȱ�����һ�㣬Ҳ���Ǳ������ڽӱ��е�һ��������������С�ߵ�ͷ�������ֵ
			minLineIndex = m_findMinLine(curHeadPtr);
			//����С�����������ֵ��Ӧ��һ��
			vecIndexCache[curIndex].push_back(minLineIndex);
			//��֮ǰ�ҵ�����С������ΪȨ�������
			m_setLineWeight(curHeadPtr, minLineIndex, GRAPH_MAX_WEIGHT_LINE);
		}
	}
	//�����µ�ͼ��������
	for (int loop = 0; loop < m_numNode; loop++)
	{
		//��Ҫ�ж��Ƿ�����Ѿ����ӹ��Ľ��----������ͼ�в����ڸ�����
		//createGraph(loop,vecIndexCache[loop])
		for (int line : vecIndexCache[loop])
		{
			cout << loop << "---" << line << endl;
		}
	}
#endif //0
	//ʹ���ڽӾ�����й�����С����������
	vector<vector<int>>adjTable(m_numNode);  //�ڽӾ���
	listInvertTable(adjTable);  //����ǰ�ڽӱ�ת��Ϊ������ʽ
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
		adjTable[tmp_m][tmp_n] = GRAPH_MAX_WEIGHT_LINE; //���ٿ����ҵ��ı�
		flag[tmp_m] = 1; flag[tmp_n] = 1; //���߼��뼯����
	}
	delete []flag; flag = nullptr;
}
//���·���㷨----�������ͼ����ʼ�㲻һ�������Ҳ������
template<typename nodeDataType, typename infoType>void usrGraph<nodeDataType, infoType>::
minRoadLenDijksra(const nodeDataType &t_startElem)
{
	//ʹ���ڽӾ���������
	vector<vector<int>>adjTable(m_numNode);  //�ڽӾ���
	listInvertTable(adjTable, true);  //����ǰ�ڽӱ�ת��Ϊ������ʽ��ʹ������ͼ
	int startIndex = LocalElem(t_startElem) - 1; //��λ��ʼ���꣬�� 1 ��ʼ����
	int minIndex = 0, minLength;
	int *indexCache = new int[m_numNode];  //���ڴ洢���������Ľ������ֵ
	int *distStart = new int[m_numNode];   //���ڴ洢����ʼ������ֵ
	memset(indexCache, 0, sizeof(int)*m_numNode);  //��ʼ��
	char **path, tmpCache[20];  //�洢·����������ʾ
	path = new char*[m_numNode];
	for (int cnt = 0; cnt < m_numNode; cnt++)
	{
		path[cnt] = new char[100];
	}
	for (int loop = 0; loop < m_numNode; loop++)
	{
		distStart[loop] = adjTable[startIndex][loop];  //װ�ؾ���ֵ
		if (distStart[loop] < GRAPH_MAX_WEIGHT_LINE) //װ��·��ֵ
			sprintf(path[loop], "%d ---> %d", startIndex + 1, loop + 1);
		else
			sprintf(path[loop], "");
	}
	indexCache[startIndex] = 1;
	//�����������������·������
	for (int loop = 0; loop < m_numNode; loop++)
	{
		minLength = GRAPH_MAX_WEIGHT_LINE;
		minIndex = 0;  //��С·������ֵ
		//������ʼ��ֱ�������в������·����ֵ
		for (int i = 0; i < m_numNode; i++)
		{
			if (distStart[i] < minLength && (!indexCache[i]))  //��С����û���ڼ�����
			{
				minLength = distStart[i];
				minIndex = i;
			}
		}
		indexCache[minIndex] = 1;  //����С�Ľ����뼯����
		//��ʣ�µĽ���в�����Сֵ
		for (int j = 0; j < m_numNode; j++)
		{
			if ( (!indexCache[j]) && distStart[minIndex] + adjTable[minIndex][j] < distStart[j])  //�ڼ���֮�����
			{
				//���¾���ֵ��·��ֵ
				distStart[j] = distStart[minIndex] + adjTable[minIndex][j];
				sprintf(tmpCache, " ---> %d", j+1);
				strcpy(path[j],path[minIndex]);
				strcat(path[j], tmpCache);
			}
		}
	}
	//�������
	for (int i = 0; i < m_numNode; i++)
	{
		if (i!=startIndex)
			cout << "Dist:" << distStart[i] << "\t" << path[i] << endl;
	}
	delete[]distStart; distStart = nullptr;
	delete[]indexCache; indexCache = nullptr;
	for (int i = 0; i < m_numNode; i++)
	{	
		delete[]path[i]; path[i] = nullptr;
	}
	delete[]path; path = nullptr;
}

#if EN_NMSPACE_USR_DATASTRUCTURE
}
#endif  //EN_NMSPACE_USR_DATASTRUCTURE

#endif //__CPLUS_USRGRAPH_H__