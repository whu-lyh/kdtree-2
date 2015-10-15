
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

	void SetValue(SrcPoint* s)
	{
		if(s == NULL){
			cout<<"SrcPoint is pointing to NULL"<<endl;
			return;
		}
		sp = s;
	}

	SrcPoint*  sp;
	KDNode* parent;
	KDNode* left;
	KDNode* right;

private:

	int   split_dim;


};

class KDTree
{
public:
	KDNode* root;

	KDTree():root(NULL),axis(0),dims_num(0),
			nodes_num(0){	}

	void create(const Container& contain);

	void destroy();

	void buildTree(const Container& can, int dnumber);
private:
	KDNode* createKDSubTree(const Container& cont);

	void buildSubTree(const Container& can, KDNode* node);

	//方差：各个数据与平均数之差的平方的平均数
	//方差应该并行计算。
	//if column = 0, compute x variance, 
	//if column = 1, compute y variance
	double computeVariance(const Container& con, int column);

	void QuickSort(Container& con,int sort_dim, int s, int e);

public:

	bool CheckContainer(const Container& can);

	double ComputeDvalue(const list<double>& elts);

private:

	int nodes_num;
	int dims_num;

	int axis;


};

#endif//KDTREE_H
