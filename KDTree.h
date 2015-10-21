
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

	bool operator==(const KDNode& rhs)
	{
		return false;
	}

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
	SrcPoint* getValue()
	{
		return sp;
	}

	SrcPoint*  sp;
	KDNode* parent;
	KDNode* left;
	KDNode* right;

private:

	int   split_dim; //0 nothing 1:x, 2:y


};

class KDTree
{
public:


	KDTree():root(NULL),
			dims_num(0),
			nodes_num(0){

	}

	void setRoot(KDNode* n)
	{
		root = n;
	}

	void create(const Container& contain);

	void setDimensionNumber(int n){
		dims_num = n;
	}

	KDNode* getRoot(){
		return root;
	}
	void destroy();

public:

	//方差：各个数据与平均数之差的平方的平均数
	//方差应该并行计算。
	//if column = 0, compute x variance, 
	//if column = 1, compute y variance
	double computeVariance(const Container& con, int sort_d);

	void QuickSort(Container& con,int s, int e, int sort_d);

	SrcPoint* evaluateMedian(const Container& can, int sort_d);

	void CopyContainer(const Container& can, Container& newCan);

	void SetSubContainer(const Container& can,
			const SrcPoint* median,
			const int split_d,
			Container& subLeftCan,
			Container& subRightCan);
public:

	bool CheckContainer(const Container& can);

	void BuildSubTree(Container& can, KDNode* node);
	int nodes_num;
private:

	KDNode* root;

	int dims_num;




};

#endif//KDTREE_H
