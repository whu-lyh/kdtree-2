

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

	map<int, double>  dims_Variances;

	dims_Variances.insert(make_pair(0,0.0));

	dims_Variances.insert(make_pair(1,30.0));
	dims_Variances.insert(make_pair(2,40.0));
	dims_Variances.insert(make_pair(3,20.0));
	dims_Variances.insert(make_pair(4,50.0));


	map<int,double>::const_iterator itr = dims_Variances.begin();


	int i = 0;
	for( ;itr!=dims_Variances.end();++itr)
	{

		cout<<"the "<<i<<" "<<itr->second<<endl;

		++i;
	}

	cout<<"hello"<<endl;

//	system("pause");
	return 0;

}

