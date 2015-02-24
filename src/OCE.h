/*
 * OCE.h
 *
 *  Created on: 13/2/2015
 *      Author: oscar
 */

#include <vector>
#include <cmath>
#include "SEG.h"
#include "Metric.h"

using namespace std;

#ifndef OCE_H_
#define OCE_H_

typedef vector<vector<int> > reg_t; //seg row

/*
 *  An evaluation metric for image segmentation of multiple objects
 *	Mark Polak - 2009
 *	Implemented by: Oscar
 *
 * */

class OCE: public Metric
{
	public:
		float operator()(SEG* __seg_1, SEG* __seg_2);

	private:

		int bar_delta(int __input); //bar delta: see the paper (equation 6)
		float E(SEG* __seg_1, SEG* __seg_2); //error function: equation 6

};

float OCE::operator ()(SEG* __seg_1, SEG* __seg_2)
{
	return Util::min(E(__seg_1, __seg_2), E(__seg_2, __seg_1));
}

int OCE::bar_delta(int __input)
{
	return (__input == 0) ? 0 : 1;

}

float OCE::E(SEG* __seg_1, SEG* __seg_2)
{

	float error = 0;

	for (int j = 0; j < __seg_1->size(); j++)
	{

		float jacc = 0;
		for (int i = 0; i < __seg_2->size(); i++)
		{

			float den = 0;
			float num = 0;

			for (int k = 0; k < __seg_2->size(); k++)
			{
				den += bar_delta(I((*__seg_1)[j], (*__seg_2)[k])) * size((*__seg_2)[k]);
			}

			num = bar_delta(I((*__seg_1)[j], (*__seg_2)[i])) * size((*__seg_2)[i]);

			float w_ij = num / den;

			jacc += (jaccard((*__seg_1)[j], (*__seg_2)[i]) * w_ij);

		}

		jacc = 1 - jacc;

		float den = 0;
		for (int k = 0; k < __seg_1->size(); k++)
		{
			den += size((*__seg_1)[k]);
		}

		float w_j = size((*__seg_1)[j]) / den;

		error = error + (jacc * w_j);

	}

	return error;
}

#endif /* OCE_H_ */
