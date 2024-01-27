#include "perceptron.h"
#include <iostream>
#include <string>
int main(int argc, char* argv[]) {

	Matrix inputs(10, 3);

	inputs[0][0] = 1;
	inputs[0][1] = 1;

	inputs[1][0] = 2;
	inputs[1][1] = 1;

	inputs[2][0] = 2;
	inputs[2][1] = 3;

	inputs[3][0] = 3;
	inputs[3][1] = 2;

	inputs[4][0] = 4;
	inputs[4][1] = 4;

	inputs[5][0] = -1;
	inputs[5][1] = -1;

	inputs[6][0] = -1;
	inputs[6][1] = -3;

	inputs[7][0] = -2;
	inputs[7][1] = -2;

	inputs[8][0] = -3;
	inputs[8][1] = -1;

	inputs[9][0] = -4;
	inputs[9][1] = -4;

	for (int i = 0; i < 10; i++) {
		inputs[i][2] = 1;
	}

	
	inputs.print();

	Perceptron perc(3);

	perc.fit(inputs, 0.5, 100);
	perc.plot2D(inputs);

}