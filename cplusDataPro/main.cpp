#include "usrList.h"
//#include "linerList.cpp"  //模板函数，需要引入cpp实现函数，用于链接编译
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
	//有向图 弧尾表示
	usrGraph<int, int>usrDirect;
	info i1 = { 2, 10 }, i2 = { 3, 2 };

	usrDirect.createGraph(1, 2, 3);
	usrDirect.createGraph(2, 4, 5);
	usrDirect.createGraph(3, 2);
	usrDirect.createGraph(4, 1, 3);
	usrDirect.createGraph(5, 1);

	//usrDirect.createGraph(1, i1, i2);
	//i1 = { 4, 12 }; i2 = { 5, 5 };
	//usrDirect.createGraph(2, i1, i2);
	//i1 = { 2, 10 };
	//usrDirect.createGraph(3, i1);
	//i1 = { 1, 21 }; i2 = { 3, 15 };
	//usrDirect.createGraph(4, i1, i2);
	//i1 = { 1, 2 };
	//usrDirect.createGraph(5, i1);

	//usrDirect.deepFirstSearch(2, 0);
	//usrDirect.minCostPrim();
	usrDirect.breadthFirstSearch(2,0);
	//usrDirect.minRoadLenDijksra(3);
	system("pause");
	return 0;
}

#endif  //1




