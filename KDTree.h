
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

	bool isLeaf()
	{
		return (sp != NULL && parent != NULL
				&& left == NULL && right == NULL);
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

	unsigned  depth;

private:

	int   split_dim; //0 nothing 1:x, 2:y


};

class KDTree
{
public:


	KDTree():root(NULL),
			dims_num(0),
			nodes_num(0),
			maxDepth(0){

	}

	void setRoot(KDNode* n)
	{
		root = n;
	}

	void create(const Container& contain);

	void CreateVTwo(const Container& can);

	void setDimensionNumber(int n){
		dims_num = n;
	}

	KDNode* getRoot(){
		return root;
	}
	void destroy();

public:

	//锟斤拷锟筋：锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷平锟斤拷锟斤拷之锟斤拷锟狡斤拷锟斤拷锟狡斤拷锟斤拷锟�
	//锟斤拷锟斤拷应锟矫诧拷锟叫硷拷锟姐。
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

	void BuildSubTreeVT(Container& c,
			KDNode* n,
			unsigned d);

	void BuildSubTree(Container& can, KDNode* node, unsigned d);
	int nodes_num;
private:

	KDNode* root;

	int dims_num;

	unsigned  maxDepth;

	void traverse(KDNode* node, unsigned md);



};

#endif//KDTREE_H
