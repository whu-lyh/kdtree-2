

#include <iostream>
#include "KDTree.h"


using namespace std;

int main()
{
	KDTree* tree = new KDTree();

	list<double> list_t;
	list_t.push_back(4);
	list_t.push_back(9);
	list_t.push_back(6);
	list_t.push_back(7);
	list_t.push_back(2);
	list_t.push_back(8);

	double d = tree->ComputeDvalue(list_t);

	cout<<"d: "<<d<<endl;

	cout<<"hello"<<endl;

	system("pause");
	return 0;

}

