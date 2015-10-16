

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
	nodes_num = can.size();
	KDNode* root = new KDNode();

//	int dims = contain.GetDimensions();
//	int val_size = contain.sp_vec.size();

	double variance_x = 0.0;
	double variance_y = 0.0;

	variance_x = computeVariance(can,0);//确定第一轴
	variance_y = computeVariance(can,1);

	if (variance_x >= variance_y )
	{
		root->setSplitDim(1);
	}else if (variance_y > variance_x)
	{
		root->setSplitDim(2);
	}
	int split = root->GetSplitDim();

	int s = 0;
	int e = can.size() - 1;
	CopyContainer(can,ownCan);
	cout<<"own can "<<ownCan.size()<<endl;

	QuickSort(ownCan,s,e,split);

	root->sp = evaluateMedian(ownCan,split);
	root->parent = NULL;

	KDNode* subLeft  = new KDNode;
	KDNode* subRight = new KDNode;

	subLeft->parent = root;
	subRight->parent = root;









}

void KDTree::buildTree(const Container& can,int dnum)
{
	if(!CheckContainer(can)){
		return;
	}
	dims_num = dnum; //in this case is 2;

	root = new KDNode;

	double variance_x = 0.0;
	double variance_y = 0.0;

//	double variance[dnum];
//
//	for(int i=0;i<dnum;++i){
//		variance[i] = computeVariance(can,i);
//	}

	if(variance_x == 0 || variance_y ==0){
		cout<<"The Variance equal to Zero"<<endl;
	}
	variance_x = computeVariance(can,0);
	variance_y = computeVariance(can,1);
	if (variance_x >= variance_y )
	{
		root->setSplitDim(0);

	}else if (variance_y > variance_x)
	{
		root->setSplitDim(1);

	}
	//sort then find the median

	if(root->GetSplitDim() == 0)//means sort x
	{

	}else if(root->GetSplitDim() == 1)// sort y
	{

	}else{
		cout<<"Split_dims neither x nor y,sth is wrong before."<<endl;
		return;
	}







}



void KDTree::buildSubTree(const Container& can, KDNode* node)
{



}


// 1.Variances at every dimension;
// 2. the max Variance Dimension is the split axis.
//3. sort the split dimension values. 
//4. select the mid as the root;
KDNode* KDTree::
	createKDSubTree(const Container& contain)
{
	cout<<"KDTree::createKDSubTree()."<<endl;
	KDNode* root = new KDNode();

//	int dims = contain.GetDimensions();
	int val_size = contain.size();



//	if (variance_x >= variance_y )
//	{
//		root->setSplitDim(0);
//	}else if (variance_y > variance_x)
//	{
//		root->setSplitDim(1);
//	}






	return root;
}


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

void KDTree::SetSubContainer(const Container& can,
		const SrcPoint* median,
		Container& subLeftCan,
		Container& subRightCan)
{
	if(!CheckContainer(can)){
		return;
	}

	Container::const_iterator itr = can.begin();
	while(itr!=can.end() && *itr != median)
	{
		subLeftCan.push_back(*itr);
	}
	while(itr!=can.end()){
		subRightCan.push_back(*itr);
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

