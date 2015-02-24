//============================================================================
// Name        : Segmentation_metrics.cpp
// Author      : Oscar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SEG.h"

#include "OCE.h"
#include "MSSI.h"
#include "Metric.h"
using namespace std;


void foo(Metric* __m, SEG* __seg_1, SEG* __seg_2)
{
	cout<<(*__m)(__seg_1, __seg_2)<<endl;

}

int main()
{
	SEG seg_1, seg_2;
	seg_1.read("frutas_1.seg");
	seg_2.read("frutas_2.seg");

	//seg_2.print();

	//Metric *oce = new OCE();
	MSSI mssi;


	foo(new MSSI(), &seg_1, &seg_2);
	foo(new OCE(), &seg_1, &seg_2);

	return 0;
}
