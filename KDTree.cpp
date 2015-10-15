

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


void KDTree::create(const Container& contain)
{
	cout<<"KDTree::create()."<<endl;
	KDNode* root = new KDNode();

//	int dims = contain.GetDimensions();
//	int val_size = contain.sp_vec.size();

	double variance_x = 0.0;
	double variance_y = 0.0;

	variance_x = computeVariance(contain,0);//»∑∂®µ⁄“ª÷·
	variance_y = computeVariance(contain,1);

	if (variance_x >= variance_y )
	{
		root->setSplitDim(0);
		axis = 0;
	}else if (variance_y > variance_x)
	{
		root->setSplitDim(1);
		axis = 1;
	}
	//≈≈–Ú axis == 0 x÷·≈≈–Ú  axis ==1 y÷·≈≈–Ú
	if(0==axis){



	}else if(1==axis){


	}








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
		axis = 0;
	}else if (variance_y > variance_x)
	{
		root->setSplitDim(1);
		axis = 1;
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


void KDTree::QuickSort(Container& can, int sort_dim,int s, int e)
{

	SrcPoint* pivot = NULL;
	int r = e; //
	int l = s; ///start from left side


	if(can.empty()){
		cout<<"The src point vec is empty()"<<endl;
		return ;
	}

	if(sort_dim == 0)//sort x values
	{
		if(s>e){
			return;
		}

		pivot = can[s];

		while(l!=r){

			while(pivot->x <= can[r]->x && l<r){
				r--;
			}
			while(pivot->x >= can[l]->x && l<r){
				l++;
			}

			if(l<r){
				//switch the positions
				SrcPoint* sp_temp = can[l];
				can[l] = can[r];
				can[r] = sp_temp;
			}

		}

		can[s] = can[l];
		can[l] = pivot;

//		QuickSort()

	}

	if(sort_dim == 1)//sort y values
	{
		if(s>e){
			return;
		}

		pivot = can[s];

		while(l!=r){

			while(pivot->y <= can[r]->y && l<r){
				r--;
			}
			while(pivot->y >= can[l]->y && l<r){
				l++;
			}

			if(l<r){
				//switch the positions
				SrcPoint* sp_temp = can[l];
				can[l] = can[r];
				can[r] = sp_temp;
			}

		}

		can[s] = can[l];
		can[l] = pivot;
	}



}

double KDTree::computeVariance(const Container& can,int column)
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
	if (0 == column)
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
		
		return variance;
	}

	if (1 == column)
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

