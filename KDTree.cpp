

#include "KDTree.h"


KDNode::KDNode()
	:split_dim(0),
	sp(NULL),
	parent(NULL),
	left(NULL),
	right(NULL)
{

}

KDNode::KDNode(SrcPoint* s,int split,
	KDNode* p,KDNode* l,KDNode* r)
{
	cout<<"This is the KDNode initation"<<endl;
	if (s == NULL || s->id == 0)
	{
		cout<<"the Src point's id is Zero"<<endl;
	}else{

		sp = s;
		split_dim = split;
		parent    = p;
		left      = l;
		right     = r;

	}
}

KDNode::KDNode(const KDNode& rhs)
{


}

KDNode& KDNode::operator=(const KDNode& rhs)
{

	if (this == &rhs)
	{
		return *this;
	}


	return *this;
}


void KDTree::create(const Container& can)
{
	cout<<"KDTree::create()."<<endl;
	if(can.empty()){
		cout<<"Container is empty"<<endl;
		return;
	}
	KDNode* root = new KDNode();

	setRoot(root);
	nodes_num = can.size();
	if(can.size() == 1)
	{
		root->sp = can.at(0);
		cout<<"Can only has one element"<<endl;
		return;
	}
	Container newCan; // use for sort and split;
	CopyContainer(can,newCan);

	root->parent = NULL;
	BuildSubTree(newCan,root);






}

void KDTree::BuildSubTree(Container& can,
		KDNode* node)
{
	if(can.empty()){
		cout<<"Container is empty"<<endl;
		return;
	}
	if(can.size() == 1)
	{
		node->sp = can.at(0);
		return;
	}
	double variance_x = 0.0;
	double variance_y = 0.0;

	int s = 0;
	int e = can.size() - 1;

	SrcPoint* median = NULL;
	KDNode* subLeft = NULL;
	KDNode* subRight = NULL;

	variance_x = computeVariance(can,1);
	variance_y = computeVariance(can,2);

	if(variance_x == 0 || variance_y ==0){
		cout<<"The Variance equal to Zero"<<endl;
	}

	if (variance_x >= variance_y )
	{
		node->setSplitDim(1);

	}else if (variance_y > variance_x)
	{
		node->setSplitDim(2);
	}

	QuickSort(can,s,e,node->GetSplitDim());

	median = evaluateMedian(can,node->GetSplitDim());
	if(median == NULL)
	{
		node = NULL;
		return;
	}
	node->sp = median;

	subLeft  = new KDNode;
	subRight = new KDNode;

	Container leftCan;
	Container rightCan;

	SetSubContainer(can,median,
			node->GetSplitDim(),
			leftCan,
			rightCan);

	node->left  = subLeft;
	node->right = subRight;

	subLeft->parent  = node;
	subRight->parent = node;

	BuildSubTree(leftCan, subLeft);
	BuildSubTree(rightCan,subRight);

}

// 1.Variances at every dimension;
// 2. the max Variance Dimension is the split axis.
//3. sort the split dimension values. 
//4. select the mid as the root;
void KDTree::QuickSort(Container& can, int s,int e, int sort_dim)
{
	if(can.empty()){
		cout<<"The src point vec is empty()"<<endl;
		return ;
	}

	if(s>e){
		return;
	}

	SrcPoint* pivot = NULL;
	int r = e; //
	int l = s; ///start from left side
	pivot = can.at(s);

	while(l != r)
	{
		if(sort_dim == 1)
		{
			while(pivot->x <= can.at(r)->x && l<r){
				r--;
			}
			while(pivot->x >= can.at(l)->x && l<r){
				l++;
			}
		}
		if(sort_dim == 2)
		{
			while(pivot->y <= can.at(r)->y && l<r){
				r--;
			}
			while(pivot->y >= can.at(l)->y && l<r){
				l++;
			}
		}

		if(l<r)
		{
			SrcPoint* t = can.at(l);
			can.at(l) = can.at(r);
			can.at(r) = t;
		}

	}
	can.at(s) = can.at(l);
	can.at(l) = pivot;

	QuickSort(can, s, l-1, sort_dim);
	QuickSort(can, l+1, e, sort_dim);


}

SrcPoint* KDTree::evaluateMedian(const Container& can, int sort_d)
{
	if(!CheckContainer(can))
	{
		return NULL;
	}

	SrcPoint* median = NULL;
	int mid   = 0;
	int num   = can.size();

	if(num % 2 != 0)//not even
	{
		mid = (num+1) /2 ;
		median = can.at(mid - 1); //start from 0;
	}
	if(num % 2 == 0){
		//num is even  tricky part
		mid = num/2 -1;
		median = can.at(mid);
	}

	return median;
}


double KDTree::computeVariance(const Container& can,int sort_d)
{
	if (can.empty())
	{
		cout<<"The container is empty."<<endl;
		return 0.0;
	}
	double variance = 0.0;
	double average  = 0.0;
	double sum      = 0.0;
	int    num      = can.size();

	Container::const_iterator iter;
//	vector<SrcPoint*>::const_iterator  iter;
	iter = can.begin();
	if (1 == sort_d)
	{
		for ( ;iter!=can.end();++iter)
		{
			sum += (*iter)->x;
		}
		average = sum / (double) num;
		double t = 0.0;
		iter = can.begin();//reset the iterator;

		while (iter!=can.end())
		{
			t = (*iter)->x - average;
			t = pow(t,2);
			variance +=t;
			++iter;
		}
	}

	if (2 == sort_d)
	{
		for ( ;iter!=can.end();++iter)
		{
			sum += (*iter)->y;
		}
		average = sum / (double) num;
		double t = 0.0;
		iter = can.begin();//reset the iterator;

		while (iter!=can.end())
		{
			t = (*iter)->y - average;
			t = pow(t,2);
			variance +=t;
			++iter;
		}
	}
	return variance;
}

//consider the number
void KDTree::SetSubContainer(const Container& can,
		const SrcPoint* median,
		const int split_d,
		Container& subLeftCan,
		Container& subRightCan)
{
	if(can.empty())
	{
		return;
	}
	if(can.size() ==  1)
	{
		return;
	}
	Container::const_iterator itr = can.begin();
	for(;itr!=can.end();++itr)
	{
		if(split_d == 1)
		{
			if((*itr)->x < median->x)
			{
				subLeftCan.push_back(*itr);
			}
			if((*itr)->x > median->x)
			{
				subRightCan.push_back(*itr);
			}
		}

		if(split_d == 2)
		{
			if((*itr)->y < median->y)
			{
				subLeftCan.push_back(*itr);
			}
			if((*itr)->y > median->y)
			{
				subRightCan.push_back(*itr);
			}
		}
	}

}

void KDTree::CopyContainer(const Container& can, Container& newCan)
{
	if(can.empty()){
		return;
	}
	newCan.clear();
	Container::const_iterator itr = can.begin();
	for(;itr!=can.end();++itr)
	{
		newCan.push_back(*itr);
	}
	cout<<"Copy's done."<<endl;
}


void KDTree::destroy()
{


}

bool KDTree::CheckContainer(const Container& can)
{
	cout<<"Checking the Cantainer..."<<endl;
	if(can.empty()){
		cout<<"The container is empty."<<endl;
		return false;
	}else
	{
		return true;
	}

}

