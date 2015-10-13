
#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <list>
#include <math.h>
#include <map>

#include "SrcPoint.h"

using namespace std;

class KDNode
{

public:
	KDNode();

	KDNode(SrcPoint* s,
		int sp_dim,
		KDNode* p,
		KDNode* l,
		KDNode* r);

	KDNode(const KDNode& rhs);

	KDNode& operator=(const KDNode& rhs);

	void setSplitDim(int sm)
	{
		split_dim = sm;
	}

	int GetSplitDim(){
		return split_dim;
	}

private:

	int   split_dim;
	SrcPoint*  sp;
	KDNode* parent;
	KDNode* left;
	KDNode* right;

};

class KDTree
{
public:
	KDNode* root;

	KDTree():root(NULL),axis(0){
		for(int i=0; i!=3;++i)
		{
			dim_vari.insert(make_pair(i,0.0));

		}
	}

	void create(const Container& contain);

	void destroy();

private:
	KDNode* createKDSubTree(const Container& cont);

	//方差：各个数据与平均数之差的平方的平均数
	//方差应该并行计算。
	//if column = 0, compute x variance, 
	//if column = 1, compute y variance
	double computeVariance(const Container& con, int column);

	void QuickSort(Container& con,int sort_dim);

public:

	double ComputeDvalue(const list<double>& elts);

private:

	map<int, double>  dim_vari;
	int axis;


};

#endif//KDTREE_H
