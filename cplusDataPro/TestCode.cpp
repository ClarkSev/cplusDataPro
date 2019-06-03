//该文件包含--数据结构的一些测试代码


#ifdef EN_MAPCOLOR_SOLVER  //地图染色问题

//地图中区域与区域的相邻关系矩阵，相邻为 1 否则为 0
const int areaRelate[AREANUMBER][AREANUMBER] =
{ { 0, 1, 1, 1, 1, 1, 0 }, \
{1,0,0,0,0,1,0},\
{1,0,0,1,1,0,0},\
{1,0,1,0,1,1,0},\
{1,0,1,1,0,1,0},\
{1,1,0,1,1,0,0},\
{0,0,0,0,0,0,0} };

//地图的区域索引从0开始计算
mapElementType map[AREANUMBER] =
{ {0,"a",0}, {1,"b",0}, {2,"c",0},\
{3, "d", 0}, { 4, "e", 0 }, { 5, "f", 0 }, { 6, "g", 0 } };

usrStack<mapStackType>stkMap;
mapSolver(areaRelate, stkMap, map); //策划染色方法，则是多种染色组合
//printSolver(map, stkMap);        //将空白地图进行填充颜色，并将其打印出来

#endif //EN_MAPCOLOR_SOLVER

#ifdef EN_BAG_SOLVER  //背包问题

ElementType ele[6] = { { "1000", "aaa", "place01", 20 }, \
{"1001", "bbb", "place02", 10}, \
{"1002", "ccc", "place03", 30}, \
{"1003", "ddd", "place04", 80}, \
{"1004","eee","place05",50},\
{"1005","fff","place06",40} };
knapSack(ele,6,40);

#endif  //EN_BAG_SOLVER

//在使用结构体类型堆栈会出现异常，但是可以将结构体改写为类
//实现相应的功能，那么该程序就能完成相关操作
#ifdef EN_STRUCTURE_STACK  //结构体类型的堆栈


template<class dataType>
void printStu(const usrStack<dataType> &tlink)
{
	Node<dataType>* l_ptrNode = tlink.getTopNode(); //用于遍历
	for (int pos = 1; pos <= tlink.size(); pos++)
	{
		cout << "第" << pos << "个元素 : " << l_ptrNode->nodeDat.name << "  "\
			<< l_ptrNode->nodeDat.sex << " " << l_ptrNode->nodeDat.number;
		if (pos % 4 == 0)
			cout << endl;
		l_ptrNode = l_ptrNode->ptrNext;
	}
	cout << endl;
}
struct student
{
	string name;
	string sex;
	string number;
	int  score;
	int    age;
};

#endif //EN_STRUCTURE_STACK

#ifdef EN_STRUCTURE_BT

usrBinaryTree<int>usrtree;
DblNode<int> *myroot = usrtree.creatBinaryTreeNode(5);
DblNode<int> *tmpNode[6];
for (int loop = 0; loop < 6; loop++)
{
	tmpNode[loop] = usrtree.creatBinaryTreeNode(loop + 10);
}
//连接结点
usrtree.connectTree(myroot, tmpNode[2], tmpNode[0]);
usrtree.connectTree(tmpNode[2], tmpNode[1], tmpNode[4]);
usrtree.connectTree(tmpNode[1], tmpNode[3], nullptr);
usrtree.connectTree(tmpNode[0], nullptr, tmpNode[5]);
usrtree.printTree();
usrtree.searchDataUpToDn_LToR(13, nullptr, false);

#endif  //EN_STRUCTURE_BT

#ifdef  EN_CLASSIFYBT

usrClassifyBT<int>usrCBT(20);
//DblNode<int> *myroot = usrtree.creatBinaryTreeNode(5);

usrCBT.insertNodeDat(10);
usrCBT.insertNodeDat(30);
usrCBT.insertNodeDat(5);
usrCBT.insertNodeDat(15);
usrCBT.insertNodeDat(25);
usrCBT.insertNodeDat(35);
usrCBT.insertNodeDat(3);
usrCBT.insertNodeDat(7);
usrCBT.insertNodeDat(17);
usrCBT.insertNodeDat(27);
usrCBT.insertNodeDat(40);
usrCBT.printTree();
usrCBT.deleteNodeDat(20);
usrCBT.printTree();


#endif //EN_CLASSIFYBT


#ifdef EN_TEST_VARYPARA

void printx()
{
	cout << "test function pointer!" << endl;
}
template<class T1, class ...T2>
void printArgs(T1 p, T2...args)
{
	cout << "parameters:" << p << endl;
	printArgs(args...);
}
void printArgs()
{
	cout << "function end!" << endl;
}


template<class ...T2>
void printArgs_md2(T2...args)
{
	//逗号表达式解包
	//其实质就是使用initializer_list进行初始化数组
	int a[] = { (cout << args << endl, 0)... };
	//sizeof前的 ... 用于计算参数的个数
	cout << "参数个数为：" << sizeof...(args) << endl;
}


#endif  //EN_TEST_VARYPARA

#ifdef   EN_TEST_MAXSTACKTREE

usrBinaryTree<int>usrbt;
usrMaxStackTree<int>usrStack;
vector<int>lvect;
lvect.push_back(52); lvect.push_back(6); lvect.push_back(5); lvect.push_back(79);
lvect.push_back(55); lvect.push_back(24); lvect.push_back(15); lvect.push_back(36);
lvect.push_back(16); lvect.push_back(62); lvect.push_back(7); lvect.push_back(38);
usrStack.initMaxStackTree(lvect,usrbt);
usrbt.searchDataUpToDn_LToR(0,nullptr,false);

#endif //EN_TEST_MAXSTACKTREE

#ifdef EN_TEST_USRLIST

class nodetype
{
	string m_str;
public:
	nodetype(string t_str = "") :m_str(t_str){};
	~nodetype(){};
};
struct node
{
	string m_str;
};
int main()
{
	usrList<int, int>usr(12);
	//nodetype n1, n2, n3;
	//usr.insertAfter(n1);
	//usr.insertAfter(n2);
	//cout << memcmp(&n1, &n3, sizeof(n3)) << endl;
	usr.insertAfter(11);
	usr.insertAfter(1);
	usr.insertAfter(24);
	usr.insertPosAfter(1, 23);
	cout<<usr.findData(n1)<<endl;
	cout << usr.getPosData(1)<<endl;
	usr.printLinerList();
	usr.moveNodeToPos(1, 4);
	usr.printLinerList();
	usr.clrLinerList();
	ur.printLinerList();
	cout << usr.isEmpty()<<endl;
	system("pause");
	return 0;
}

#endif //EN_TEST_USRLIST
