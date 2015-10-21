

#include <iostream>
#include "KDTree.h"
#include "SrcPoint.h"

using namespace std;


void CreateCan(Container& can)
{
	double data[6][2] = { {2,3},{5,4}, {9,6}, {4,7}, {8,1}, {7,2} };
	can.clear();
	SrcPoint* s = NULL;
	Container::const_iterator itr = can.begin();

	for(int i=0;i<6;++i)
	{
		s = new SrcPoint;
		can.push_back(s);
		can.at(i)->x = data[i][0];
		can.at(i)->y = data[i][1];
	}

}

void PrintCan(const Container& can)
{
	if(can.empty())
	{
		return;
	}

	Container::const_iterator itr = can.begin();
	int i = 0;
	for(;itr!=can.end();++itr)
	{
		i++;
		cout<<" "<<i<<" x: "<<(*itr)->x<<" y: "<<(*itr)->y<<"\t"<<endl;
	}

}
void PrintTree(const KDNode* node)
{
	if(node == NULL)
	{
		cout<<"Node is NULL"<<endl;
		return;
	}
	if(node->sp == NULL)
	{
		return;
	}
	cout<<" node x: "<<node->sp->x<<" y: "<<node->sp->y<<endl;
	if(node->left != NULL)
	{
		cout<<"\t";
		cout<<"left:";
		PrintTree(node->left);
	}

	if(node->right != NULL)
	{
		cout<<"\t";
		cout<<"right:";
		PrintTree(node->right);
	}

}

int main()
{
	KDTree* tree = new KDTree();

	Container can;
	CreateCan(can);
//	PrintCan(can);

	Container nCan;

	tree->create(can);
	PrintTree(tree->getRoot());



//	tree->CopyContainer(can,nCan);
//	PrintCan(nCan);
//	cout<<" After Sort:"<<endl;
//	tree->QuickSort(nCan,0,(nCan.size()-1),2);
//	PrintCan(nCan);




	cout<<"node number: "<<tree->nodes_num<<endl;


	cout<<"The End"<<endl;

//	system("pause");
	return 0;

}

