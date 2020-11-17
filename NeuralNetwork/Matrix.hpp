#pragma once

#include <vector>
#include <iostream>

class Matrix {
	std::vector<std::vector<double>> mat;
public:
	int num_rows = 0, num_columns = 0;
	Matrix(int num_rows, int num_columns, double initial_value);
	Matrix transpose();
	Matrix multiply(Matrix mat);
	void set_value(int row, int column, double x);
	double get_value(int row, int column);
	void insert_row(std::vector<double> row, int position);
	void insert_column(std::vector<double> column, int position);
	void print();
	Matrix matrix_sum(int axis); // 1 = row, 2 = column
	Matrix matrix_mult(Matrix mat); //element wise multiplication
}; 