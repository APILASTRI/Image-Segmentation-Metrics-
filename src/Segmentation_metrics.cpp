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
using namespace std;

int main()
{
	SEG seg_1, seg_2;
	seg_1.read("frutas_2.seg");
	seg_2.read("frutas_1.seg");

	//seg_2.print();


	OCE oce;

	cout <<  oce(&seg_1, &seg_2) << endl;

	return 0;
}