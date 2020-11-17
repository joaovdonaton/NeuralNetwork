#include "Matrix.hpp"

Matrix::Matrix(int num_rows, int num_columns) {
	this->num_rows = num_rows, this->num_columns = num_columns;
	for (int i = 0; i < num_rows; i++) {
		std::vector<double> r;
		for (int j = 0; j < num_columns; j++) {
			r.push_back(4);
		}
		mat.push_back(r);
	}
}

void Matrix::set_value(int row, int column, double x) {
	mat[row][column] = x;
}

double Matrix::get_value(int row, int column) {
	return mat[row][column];
}

Matrix* Matrix::multiply(Matrix *mat) {
	if (num_columns != mat->num_rows) return nullptr; //return nullptr if matrices can't be multiplied
	
	Matrix *new_m = new Matrix(num_rows, mat->num_columns);
	for (int i = 0; i < new_m->num_rows; i++) {
		for (int j = 0; j < new_m->num_columns; j++) {
			double sum = 0;
			for (int k = 0; k < num_columns; k++) {
				sum += this->mat[i][k] * mat->get_value(k, j);
			}
			new_m->set_value(i, j, sum);
		}
	}

	return new_m;
}

void Matrix::append_row(std::vector<double> row) {
	if (row.size() == this->num_columns) {
		this->mat.push_back(row);
		this->num_rows++;
	}
	else {
		std::cout << "Could not append row" << std::endl;
	}
}

void Matrix::append_column(std::vector<double> column) {
	if (column.size() == this->num_rows) {
		for (int i = 0; i < this->num_rows; i++) {
			this->mat[i].insert(this->mat[i].begin(), column[i]);
		}
		this->num_columns++;
	}
	else {
		std::cout << "Could not append column" << std::endl;
	}
}

Matrix* Matrix::transpose() {
	Matrix *new_m = new Matrix(num_columns, num_rows);
	for (int i = 0; i < new_m->num_rows; i++) {
		for (int j = 0; j < new_m->num_columns; j++) {
			new_m->set_value(i, j, mat[j][i]);
		}
	}
	return new_m;
}

void Matrix::print() {
	for (auto row: mat) {
		for (double value: row) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
}