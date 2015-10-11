

#include "KDTree.h"


KDNode::KDNode()
	:split_dim(0),
	sp(nullptr),
	parent(nullptr),
	left(nullptr),
	right(nullptr)
{


}

KDNode::KDNode(SrcPoint* s,int split,
	KDNode* p,KDNode* l,KDNode* r)
{
	cout<<"This is the KDNode initation"<<endl;
	if (s == nullptr || s->id == 0)
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


void KDTree::create(const Container& contain)
{
	cout<<"KDTree::create()."<<endl;
	KDNode* root = new KDNode();

	int dims = contain.GetDimensions();
	int val_size = contain.sp_vec.size();

	double variance_x = 0.0;
	double variance_y = 0.0;

	variance_x = computeVariance(contain,0);
	variance_y = computeVariance(contain,1);

	if (variance_x >= variance_y )
	{
		root->setSplitDim(0);
	}else if (variance_y > variance_x)
	{
		root->setSplitDim(1);
	}



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

	int dims = contain.GetDimensions();
	int val_size = contain.sp_vec.size();



	if (variance_x >= variance_y )
	{
		root->setSplitDim(0);
	}else if (variance_y > variance_x)
	{
		root->setSplitDim(1);
	}






	return node;
}

double KDTree::computeVariance(const Container& con,int column)
{
	if (con.sp_vec.empty())
	{
		cout<<"The container is empty."<<endl;
		return 0.0;
	}
	double variance = 0.0;
	double average  = 0.0;
	double sum      = 0.0;
	int    num      = con.sp_vec.size();
	vector<SrcPoint*>::const_iterator  iter;
	iter = con.sp_vec.begin();
	if (0 == column)
	{
		for ( ;iter!=con.sp_vec.end();++iter)
		{
			sum += (*iter)->x;
		}
		average = sum / (double) num;
		double t = 0.0;
		iter = con.sp_vec.begin();//reset the iterator;

		while (iter!=con.sp_vec.end())
		{
			t = (*iter)->x - average;
			t = pow(t,2);
			variance +=t;
			++iter;
		}
		
		return variance;
	}

	if (1 == column)
	{
		for ( ;iter!=con.sp_vec.end();++iter)
		{
			sum += (*iter)->y;
		}
		average = sum / (double) num;
		double t = 0.0;
		iter = con.sp_vec.begin();//reset the iterator;

		while (iter!=con.sp_vec.end())
		{
			t = (*iter)->y - average;
			t = pow(t,2);
			variance +=t;
			++iter;
		}
		return variance;
	}

	return 0.0;
}


double KDTree::ComputeDvalue(const list<double>& elts)
{
	if (elts.empty())
	{
		cout<<"The list is empty."<<endl;
		return 0.0;
	}

	double d_val = 0.0;
	double ave   = 0.0;
	double sum   = 0.0;
	
	int num = elts.size();
	std::list<double>::const_iterator it = elts.begin();
	for( ; it != elts.end(); ++it)
	{
		sum += *it;
	}
	ave = sum / num;

	double t = 0.0;

	it = elts.begin();
	for(;it!=elts.end();++it)
	{
		t = *it - ave;
		t = pow(t,2);
		d_val += t;
	}

	d_val /= num;
	return d_val;

}

void KDTree::destroy()
{


}