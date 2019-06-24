#include "usrList.h"
//#include "linerList.cpp"  //模板函数，需要引入cpp实现函数，用于链接编译
#include "usrStack.h"
#include "usrQueue.h"
#include "usrBinaryTree.h"
#include "usrClassifyBT.h"
#include "usrMaxStackTree.h"
#include "usrGraph.h"
#include "usrAlgorithm.h"

#include <Windows.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace nmspace_usr_datastructure;
using namespace std;


#if  1

int main()
{
	int arry[] = { 5,4,2,3,21,12,6,13,9,10 };
	int szArry = sizeof(arry) / sizeof(int);
	int ret = 0;
	//usrInsertSort(arry, szArry,1,3);
	usrRadixSort(arry, szArry,2);
	//usrHeapSort(arry, szArry);
	//usrInitMaxHeap(arry,szArry);
	//usrDelHeapNode(arry, szArry,ret);
	//usrBubSort(arry, szArry);
	//cout<<usrBinSearch(arry, szArry, 2)<<endl;
	for (auto elem : arry)
	{
		cout << elem << ",";
	}
	cout << endl;
	system("pause");
	return 0;
}

#endif  //1




