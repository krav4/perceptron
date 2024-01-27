#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <random>
#include <cmath>
#include <stdint.h>
#include "supportLib.hpp"
#include "pbPlots.hpp"
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
	Perceptron(int num_features) {
		m_num_features = num_features;
		weights = new double[num_features];
		std::default_random_engine generator;
		std::normal_distribution<double> dist(1, 0.1);
		std::cout << "Constructing perceptron. Initial weights: \n";
		for (int i = 0; i < num_features; i++) {
			double number = dist(generator);
			weights[i] = number / (double)std::sqrt(num_features);
			std::cout << weights[i] << "\n";
		} 
	}

	int fit(Matrix X, double learning_rate, int epochs) {
		double dot_res = 0;
		int d = 0;
		int i, j;
		while (epochs--)
		{
			// iterate over every input
			for (i = 0; i < X.get_num_rows(); i++) {
				// dot product weights and input row
				std::cout << "calculating dot product...\n";
				for (j = 0; j < m_num_features; j++) {
					std::cout << "X[i][j] = " << X[i][j] << "; weights[j] = " << weights[j] << "\n";
					dot_res += X[i][j] * weights[j];
				}
				std::cout << "dot product = " << dot_res << "\n";
				// if d is > 0 no weight update needed
				d = step(dot_res);
				std::cout << "d = " << d << "\n";
				// update weights
				for (j = 0; j < m_num_features; j++) {
					weights[j] += -learning_rate * d * X[i][j];
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

	void plot2D(Matrix X) {
		RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
		std::vector<double> xdots, ydots;
		std::vector<double> x_line, y_line, x_space, y_space;
		for (int i = 0; i < X.get_num_rows(); i++) {
			xdots.push_back(X[i][0]);
			ydots.push_back(X[i][1]);
		}

		double a = 0.1;

		double min_x = (double)*std::min_element(xdots.begin(), xdots.end());
		double max_x = (double)*std::max_element(xdots.begin(), xdots.end());

		x_line.push_back(min_x);
		x_line.push_back(max_x);

		y_line.push_back((-min_x * weights[0] - weights[2]) / weights[1]);
		y_line.push_back((-max_x * weights[0] - weights[2]) / weights[1]);

		StringReference* errorMessage = CreateStringReferenceLengthValue(0, L' ');
		std::cout << "drawing plot\n";


		ScatterPlotSeries* series = GetDefaultScatterPlotSeriesSettings();
		series->xs = &xdots;
		series->ys = &ydots;
		series->linearInterpolation = false;
		series->pointType = toVector(L"dots");
		series->color = CreateRGBColor(1, 0, 0);

		ScatterPlotSeries* series2 = GetDefaultScatterPlotSeriesSettings();
		series2->xs = &x_line;
		series2->ys = &y_line;
		series2->linearInterpolation = true;
		series2->lineType = toVector(L"solid");
		series2->lineThickness = 2;
		series2->color = CreateRGBColor(0, 0, 1);

		ScatterPlotSettings* settings = GetDefaultScatterPlotSettings();
		settings->width = 600;
		settings->height = 400;
		settings->autoBoundaries = true;
		settings->autoPadding = true;
		settings->title = toVector(L"");
		settings->xLabel = toVector(L"");
		settings->yLabel = toVector(L"");
		settings->scatterPlotSeries->push_back(series);
		settings->scatterPlotSeries->push_back(series2);

		bool success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

		if (success) {
			std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
			WriteToFile(pngdata, "example3.png");
			DeleteImage(imageReference->image);
		}
		else {
			std::cerr << "Error: ";
			for (wchar_t c : *errorMessage->string) {
				std::cerr << c;
			}
			std::cerr << std::endl;
		}

		FreeAllocations();
	}
private:
	double* weights;
	int m_num_features;
};
