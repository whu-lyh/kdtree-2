/*
 * Tools.h
 *
 *  Created on: 2015骞�10鏈�25鏃�
 *      Author: wb-mac
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include "SrcPoint.h"
#include "KDTree.h"

class Tools
{

public:
	Tools(){

	}

	double MeasureDistance(SrcPoint* s1, SrcPoint* s2)
	{
		double dis = 0.0;
		if(s1 == NULL || s2 == NULL || s1==s2)
		{
			return 0.0;
		}

		dis = sqrt(pow((s1->x - s2->x),2) + pow((s1->y - s2->y),2));


		return dis;
	}

	SrcPoint* SearchNearestNeighbor(SrcPoint* tar, KDTree* tree)
	{
		SrcPoint* nearest = NULL;
		if(tar == NULL || tree == NULL)
		{
			return NULL;
		}

//		KDTree* currentTree = tree;
//		nearest = currentTree->root;

		KDNode* currentNode = tree->getRoot();
		nearest = currentNode->sp;

		KDNode* tNode = tree->getRoot();
		while(!tNode->isLeaf())
		{

			if(tNode->GetSplitDim() == 1)
			{
				if(tNode->right->sp == NULL || tar->x < tNode->sp->x)
				{
					tNode = tNode->left;
				}else
				{
					tNode = tNode->right;
				}

			}
			if(tNode->GetSplitDim() == 2)
			{
				if(tNode->right->sp == NULL || tar->x < tNode->sp->x)
				{
					tNode = tNode->left;
				}else
				{
					tNode = tNode->right;
				}

			}

		}
		nearest = tNode->sp;
		double dis = MeasureDistance(tNode->sp,tar);
		cout<<"Distance is "<<dis<<endl;

		return nearest;


	}






};




#endif /* TOOLS_H_ */
