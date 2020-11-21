#pragma once

#include <vector>
#include <iostream>
#include <math.h>

class Matrix {
	std::vector<std::vector<double>> mat;
public:
	int num_rows = 0, num_columns = 0;
	Matrix(int num_rows, int num_columns, double initial_value);
	Matrix transpose(); 
	Matrix multiply(Matrix mat); // matrix multiplication
	void set_value(int row, int column, double x);
	double get_value(int row, int column);
	void insert_row(std::vector<double> row, int position);
	void insert_column(std::vector<double> column, int position);
	Matrix get_row(int row);
	Matrix get_column(int column);
	void remove_row(int row);
	void print();
	Matrix sum(int axis); // 1 = row, 2 = column, sum across axis
	Matrix op(Matrix mat, char op); // element wise operations
	Matrix log(char b); //apply logarithm of base "b" to every element
}; 