#include "usrList.h"
//#include "linerList.cpp"  //ģ�庯������Ҫ����cppʵ�ֺ������������ӱ���
#include "usrStack.h"
#include "usrQueue.h"
#include "usrBinaryTree.h"
#include "usrClassifyBT.h"
#include "usrMaxStackTree.h"
#include "usrGraph.h"


#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace nmspace_usr_datastructure;
using namespace std;

struct info
{
public:
	int Index; int Weight;
};

#if  1

int main()
{
	//����ͼ ��β��ʾ
	usrGraph<int, int>usrDirect;
	//vector<int>usrVec = { 1,2,3,4,5 };
	info i1 = { 2, 10 }, i2 = { 3, 2 };
	//usrVec.erase(usrVec.begin()+3);
	usrDirect.createGraph(1, 2, 3);
	usrDirect.createGraph(2, 4, 5);
	usrDirect.createGraph(3, 2);
	usrDirect.createGraph(4, 1, 3);
	usrDirect.createGraph(5, 1);
	//usrDirect.deepFirstSearch(2, 0);
	usrDirect.breadthFirstSearch(2, 0);
	usrDirect.deleteGraphNode(1);
	//usrDirect.createGraph(1, i1, i2);
	//i1 = { 4, 12 }; i2 = { 5, 5 };
	//usrDirect.createGraph(2, i1, i2);
	//i1 = { 2, 10 };
	//usrDirect.createGraph(3, i1);
	//i1 = { 1, 21 }; i2 = { 3, 15 };
	//usrDirect.createGraph(4, i1, i2);
	//i1 = { 1, 2 };
	//usrDirect.createGraph(5, i1);

	//usrDirect.minCostPrim();
	//usrDirect.minRoadLenDijksra(3);
	system("pause");
	return 0;
}

#endif  //1




