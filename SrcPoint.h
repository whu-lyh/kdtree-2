
#include <iostream>
#include <vector>
using namespace std;

class SrcPoint
{
public:

	SrcPoint():
	  x(0.0),
	  y(0.0),
	  id(0)
	  {/*.do nothing.*/}

	SrcPoint(double dx,double dy,unsigned i):
	  x(dx),y(dy),id(i)
	{/*..	*/}

	~SrcPoint(){
		x = 0.0;
		y = 0.0;
		id = 0;
	}

	SrcPoint(const SrcPoint& rhs)
	{
		if (rhs.id == 0)
		{
			cout<<"The rhs id is 0"<<endl;
		}
		x = rhs.x;
		y = rhs.y;
		id = rhs.id;
	}
	SrcPoint& operator=(const SrcPoint& rhs)
	{
		if (rhs.id == 0)
		{
			cout<<"The rhs.id is 0"<<endl;
		}else{
			x = rhs.x;
			y = rhs.y;
			id = rhs.id;
		}

		x = rhs.x;
		y = rhs.y;
		id = rhs.id;

		return *this;
	}

	double x;
	double y;

	unsigned id;

};

class Container
{
public:

	Container()
	{
		sp_vec.clear();
		dim = 0;
	}

	~Container();

	int GetDimensions()const{
		return dim;
	}

	void AddSrcPoint(SrcPoint* sp)
	{
		if (NULL == sp)
		{
			cout<<"The SrcPoint is null"<<endl;
			return;
		}
		sp_vec.push_back(sp);
	}

	vector<SrcPoint*> sp_vec;

private:
	int dim;

};

