#pragma once

#include <vector>
#include <iostream>

class Matrix {
	std::vector<std::vector<double>> mat;
public:
	int num_rows = 0, num_columns = 0;
	Matrix(int num_rows, int num_columns);
	Matrix transpose();
	Matrix multiply(Matrix mat);
	void set_value(int row, int column, double x);
	double get_value(int row, int column);
	void append_row(std::vector<double> row);
	void append_column(std::vector<double> column);
	void print();
}; 