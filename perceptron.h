#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <random>
#include <cmath>
#include <stdint.h>
#include "supportLib.hpp"
#include "pbPlots.hpp"
#include <string>

enum {
	COL_IDX_X = 0,
	COL_IDX_Y,
	COL_IDX_BIAS,
	NUM_COLS
};


struct Matrix {
	Matrix(int num_rows, int num_cols) {
		m_num_rows = num_rows;
		m_num_cols = num_cols;
		m_container = new int* [num_rows];

		for (int i = 0; i < num_rows; i++) {
			m_container[i] = new int[num_cols];
			memset(m_container[i], 0, num_cols * sizeof(int));
		}
	}

	~Matrix() {
	}

	int* operator[](int idx){
		if (idx > m_num_rows) {
			return nullptr;
		}
		return m_container[idx];
	}

	int get_num_rows() {
		return m_num_rows;
	}
	int get_num_cols() {
		return m_num_cols;
	}

	void print() {
		for (int i = 0; i < m_num_rows; i++) {
			for (int j = 0; j < m_num_cols; j++) {
				std::cout << m_container[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
	int m_num_rows;
	int m_num_cols;
	int ** m_container;
};

class Perceptron
{
public:
	Perceptron() {
		weights = new double[NUM_COLS];
		std::default_random_engine generator;
		std::normal_distribution<double> dist(1, 0.1);
		std::cout << "Constructing perceptron. Initial weights: \n";
		for (int i = 0; i < NUM_COLS; i++) {
			double number = dist(generator);
			weights[i] = number / (double)std::sqrt((double)NUM_COLS);
			std::cout << weights[i] << "\n";
		} 
	}

	int fit(Matrix X, Matrix labels, double learning_rate, int epochs) {
		double dot_res = 0;
		int d = 0;
		int i, j;
		while (epochs--)
		{
			// iterate over every input
			for (i = 0; i < X.get_num_rows(); i++) {
				// dot product weights and input row
				std::cout << "calculating dot product...\n";

				dot_res = X[i][COL_IDX_X] * weights[COL_IDX_X] + 
						  X[i][COL_IDX_Y] * weights[COL_IDX_Y] + 
					      X[i][COL_IDX_BIAS] * weights[COL_IDX_BIAS];

				std::cout << "dot product = " << dot_res << "\n";
				// if d is > 0 no weight update needed
				d = step(dot_res);
				std::cout << "d = " << d << "\n";
				// update weights
				for (j = 0; j < NUM_COLS; j++) {
					weights[j] += learning_rate * ((double)labels[i][0] - d)* X[i][j];
				}
				dot_res = 0;
			}

			std::cout << weights[0] << " " << weights[1] << " " << weights[2] << "\n";
		}
		return 0;
	}

	int step(double x) {
		int ret = (x > 0) ? 1 : 0;
		return ret;
	}

	void plot2D(Matrix X, Matrix labels, std::string name) {
		RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
		std::vector<double> xdots, ydots, xdots_1, ydots_1, xdots_2, ydots_2;
		std::vector<double> x_line, y_line, x_space, y_space;
		for (int i = 0; i < X.get_num_rows(); i++) {
			xdots.push_back(X[i][COL_IDX_X]);
			ydots.push_back(X[i][COL_IDX_Y]);
			if (*labels[i] > 0) {
				xdots_1.push_back(X[i][COL_IDX_X]);
				ydots_1.push_back(X[i][COL_IDX_Y]);
				std::cout << "class 1 point: " << X[i][COL_IDX_X] << "\n";

			}
			else {
				xdots_2.push_back(X[i][COL_IDX_X]);
				ydots_2.push_back(X[i][COL_IDX_Y]);
				std::cout << "class 2 point: " << X[i][COL_IDX_X] << "\n";
			}
		}

		double min_x = (double)*std::min_element(xdots.begin(), xdots.end());
		double max_x = (double)*std::max_element(xdots.begin(), xdots.end());

		x_line.push_back(min_x);
		x_line.push_back(max_x);

		y_line.push_back((-min_x * weights[0] - weights[2]) / weights[1]);
		y_line.push_back((-max_x * weights[0] - weights[2]) / weights[1]);

		StringReference* errorMessage = CreateStringReferenceLengthValue(0, L' ');
		std::cout << "drawing plot\n";

		for (auto coord : xdots_1) {
			std::cout << "xdots_1: " << coord << "\n";
		}
		for (auto coord : xdots_2) {
			std::cout << "xdots_2: " << coord << "\n";
		}
		for (auto coord : ydots_1) {
			std::cout << "ydots_1: " << coord << "\n";
		}
		for (auto coord : ydots_2) {
			std::cout << "ydots_2: " << coord << "\n";
		}
		ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
		settings->width = 600;
		settings->height = 400;
		settings->autoBoundaries = true;
		settings->autoPadding = true;
		settings->title = toVector(L"");
		settings->xLabel = toVector(L"");
		settings->yLabel = toVector(L"");

		ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
		series->xs = &xdots_1;
		series->ys = &ydots_1;
		series->linearInterpolation = false;
		series->pointType = toVector(L"dots");
		series->color = CreateRGBColor(1, 0, 0);
		settings->scatterPlotSeries->push_back(series);

		ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
		series2->xs = &xdots_2;
		series2->ys = &ydots_2;
		series2->linearInterpolation = false;
		series2->pointType = toVector(L"dots");
		series2->color = CreateRGBColor(0, 1, 0);
		settings->scatterPlotSeries->push_back(series2);

		ScatterPlotSeries* series3 = GetDefaultScatterPlotSeriesSettings();
		series3->xs = &x_line;
		series3->ys = &y_line;
		series3->linearInterpolation = true;
		series3->lineType = toVector(L"solid");
		series3->lineThickness = 2;
		series3->color = CreateRGBColor(0, 0, 1);

		settings->scatterPlotSeries->push_back(series3);

		bool success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

		if (success) {
			std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
			WriteToFile(pngdata, name);
			DeleteImage(imageReference->image);
		}
		else {
			std::cerr << "Error: ";
			for (char c : *errorMessage->string) {
				std::cout << c;
			}
			std::cerr << std::endl;
		}

		FreeAllocations();
	}
private:
	double* weights;
};
