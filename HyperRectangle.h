/*
 * HyperRectangle.h
 *
 *  Created on: 2015Äê10ÔÂ13ÈÕ
 *      Author: wubian
 */

#ifndef HYPERRECTANGLE_H_
#define HYPERRECTANGLE_H_

#include <utility>

using namespace std;

class HyperRectangle
{
public:

	HyperRectangle()
    {
		min = make_pair(0.0, 0.0);
		max = make_pair(0.0, 0.0);
    }

	HyperRectangle(const double xmin,
			const double ymin,
			const double xmax,
			const double ymax){

		min.first = xmin;
		min.second = ymin;

		max.first = xmax;
		max.second = ymax;
	}

	pair<double, double> min;
	pair<double, double> max;


};

#endif /* HYPERRECTANGLE_H_ */
