/*
 * MSSI.h
 *
 *  Created on: 19/2/2015
 *      Author: oscar
 */

#ifndef MSSI_H_
#define MSSI_H_

#include "SEG.h"
#include "Metric.h"
#include <vector>
#include <algorithm>

using namespace std;
/*
 * Métrica de similaridade para segmentação de imagens
 * Oscar
 *
 *
 */

typedef vector<vector<float> > matrix_t;

class MSSI: public Metric
{
	public:

		MSSI()
		{
		}
		;

		float operator()(SEG* __seg_1, SEG* __seg_2);

		void print_matrix();

	private:
		matrix_t _intersections;
		void fill_matrix(SEG* __seg_1, SEG* __seg_2);
		void find_largest_intersections();
		void fill_largest(int __i, int __j);

};

void MSSI::print_matrix()
{
	for (unsigned i = 0; i < _intersections.size(); i++)
	{

		for (unsigned j = 0; j < _intersections[i].size(); j++)
		{
			cout << _intersections[i][j] << " ";
		}
		cout << endl;

	}

}

void MSSI::fill_largest(int __i, int __j)
{
	float &col = _intersections[_intersections.size() - 1][__j];

	float &row = _intersections[__i][_intersections[0].size() - 1];

	float value = 0;

	value = _intersections[__i][__j];

	if (value > row && value > col)
	{
		col = value;
		row = value;
	}
}

void MSSI::fill_matrix(SEG* __seg_1, SEG* __seg_2)
{

	_intersections.resize(__seg_1->size() + 1); // position[size] to store the largest element

	for (int i = 0; i < __seg_1->size() + 1; i++)
	{
		_intersections[i].resize(__seg_2->size() + 1, 0.f);
	}

	for (int i = 0; i < __seg_1->size(); i++)
	{
		for (int j = 0; j < __seg_2->size(); j++)
		{

			_intersections[i][j] = I((*__seg_1)[i], (*__seg_2)[j]);

			fill_largest(i, j);

		}

	}

}

float MSSI::operator()(SEG* __seg_1, SEG* __seg_2)
{

	fill_matrix(__seg_1, __seg_2);

	print_matrix();

}

#endif /* MSSI_H_ */
