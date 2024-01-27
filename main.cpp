#include "perceptron.h"
#include <iostream>
#include <string>
int main(int argc, char* argv[]) {

	Matrix inputs(10, 3);
	Matrix labels(10, 1);

	inputs[0][0] = 1;
	inputs[0][1] = 1;
	labels[0][0] = 1;

	inputs[1][0] = 2;
	inputs[1][1] = 1;
	labels[1][0] = 1;

	inputs[2][0] = 2;
	inputs[2][1] = 3;
	labels[2][0] = 1;

	inputs[3][0] = 3;
	inputs[3][1] = 2;
	labels[3][0] = 1;

	inputs[4][0] = 4;
	inputs[4][1] = 4;
	labels[4][0] = 1;

	inputs[5][0] = -1;
	inputs[5][1] = -1;
	labels[5][0] = -1;

	inputs[6][0] = -1;
	inputs[6][1] = -3;
	labels[6][0] = -1;

	inputs[7][0] = -2;
	inputs[7][1] = -2;
	labels[7][0] = -1;

	inputs[8][0] = -3;
	inputs[8][1] = -1;
	labels[8][0] = -1;

	inputs[9][0] = -4;
	inputs[9][1] = -4;
	labels[9][0] = -1;

	for (int i = 0; i < 10; i++) {
		inputs[i][2] = 1;
	}

	
	inputs.print();

	Perceptron perc;

	perc.fit(inputs, labels, 0.5, 10);
	perc.plot2D(inputs, labels, "perc1.png");

	inputs[0][0] = -1;
	inputs[0][1] = 1;
	labels[0][0] = 1;

	inputs[1][0] = -2;
	inputs[1][1] = 1;
	labels[1][0] = 1;

	inputs[2][0] = -2;
	inputs[2][1] = 3;
	labels[2][0] = 1;

	inputs[3][0] = -3;
	inputs[3][1] = 2;
	labels[3][0] = 1;

	inputs[4][0] = -4;
	inputs[4][1] = 4;
	labels[4][0] = 1;

	inputs[5][0] = 1;
	inputs[5][1] = -1;
	labels[5][0] = -1;

	inputs[6][0] = 1;
	inputs[6][1] = -3;
	labels[6][0] = -1;

	inputs[7][0] = 2;
	inputs[7][1] = -2;
	labels[7][0] = -1;

	inputs[8][0] = 3;
	inputs[8][1] = -1;
	labels[8][0] = -1;

	inputs[9][0] = 4;
	inputs[9][1] = -4;
	labels[9][0] = -1;

	perc.fit(inputs, labels, 0.5, 10);
	perc.plot2D(inputs, labels, "perc2.png");

}