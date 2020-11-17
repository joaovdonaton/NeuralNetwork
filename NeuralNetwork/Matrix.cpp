#include "Matrix.hpp"

Matrix::Matrix(int num_rows, int num_columns, double initial_value) {
	this->num_rows = num_rows, this->num_columns = num_columns;
	for (int i = 0; i < num_rows; i++) {
		std::vector<double> r;
		for (int j = 0; j < num_columns; j++) {
			r.push_back(initial_value);
		}
		mat.push_back(r);
	}
}

Matrix Matrix::matrix_log(char b) {
	Matrix new_m(this->num_rows, this->num_columns, 1);
	//temporary fix
	switch (b) {
	case 't': //base 10 logarithm
		for (int i = 0; i < this->num_rows; i++) {
			for (int j = 0; j < this->num_columns; j++) {
				new_m.set_value(i, j, log10(this->get_value(i, j)));
			}
		}
		break;
	case 'n': //natural logarithm
		for (int i = 0; i < this->num_rows; i++) {
			for (int j = 0; j < this->num_columns; j++) {
				new_m.set_value(i, j, log(this->get_value(i, j)));
			}
		}
		break;
	default:
		std::cout << "Invalid logarithm base" << std::endl;
	}
	return new_m;
}

Matrix Matrix::matrix_op(Matrix mat, char op) {
	if (this->num_rows != mat.num_rows || this->num_columns != mat.num_columns) {
		std::cout << "Element wise matrix multiplication failed: " << num_rows << "x" << num_columns
			<< " " << mat.num_rows << "x" << mat.num_columns << std::endl;
		return Matrix(1, 1, 1);
	}

	Matrix new_m(this->num_rows, this->num_columns, 1);
	for (int i = 0; i < this->num_rows; i++) {
		for (int j = 0; j < this->num_columns; j++) {
			//temporary fix
			switch (op) {
			case '*':
				new_m.set_value(i, j, this->get_value(i, j) * mat.get_value(i, j));
				break;
			case '-':
				new_m.set_value(i, j, this->get_value(i, j) - mat.get_value(i, j));
				break;
			default:
				std::cout << "Invalid element wise operation" << std::endl;
				return Matrix(1, 1, 1);
			}
		}
	}

	return new_m;
}

void Matrix::set_value(int row, int column, double x) {
	mat[row][column] = x;
}

double Matrix::get_value(int row, int column) {
	return mat[row][column];
}

Matrix Matrix::multiply(Matrix mat) {
	if (num_columns != mat.num_rows) {
		std::cout << "Matrices can't be multiplied: " << num_rows << "x" << num_columns
			<< " " << mat.num_rows << "x" << mat.num_columns << std::endl;
		return Matrix(1,1, 1);
	}
	
	Matrix new_m(num_rows, mat.num_columns, 1);
	for (int i = 0; i < new_m.num_rows; i++) {
		for (int j = 0; j < new_m.num_columns; j++) {
			double sum = 0;
			for (int k = 0; k < num_columns; k++) {
				sum += this->mat[i][k] * mat.get_value(k, j);
			}
			new_m.set_value(i, j, sum);
		}
	}

	return new_m;
}

void Matrix::insert_row(std::vector<double> row, int position){
	if (row.size() == this->num_columns && !(position > this->num_rows)) {
		this->mat.insert(this->mat.begin() + position, row);
		this->num_rows++;
	}
	else {
		std::cout << "Could not append row" << std::endl;
	}
}

void Matrix::insert_column(std::vector<double> column, int position){
	if (column.size() == this->num_rows && !(position > this->num_columns)) {
		for (int i = 0; i < this->num_rows; i++) {
			this->mat[i].insert(this->mat[i].begin()+position, column[i]);
		}
		this->num_columns++;
	}
	else {
		std::cout << "Could not append column" << std::endl;
	}
}

Matrix Matrix::transpose() {
	Matrix new_m(num_columns, num_rows, 1);
	for (int i = 0; i < new_m.num_rows; i++) {
		for (int j = 0; j < new_m.num_columns; j++) {
			new_m.set_value(i, j, mat[j][i]);
		}
	}
	return new_m;
}

Matrix Matrix::matrix_sum(int axis) {
	if (axis==1) { 
		Matrix mat(1, this->num_columns, 1);
		for (int i = 0; i < this->num_columns; i++) {
			int accum = 0;
			for (int j = 0; j < this->num_rows; j++) {
				accum += this->mat[j][i];
			}
			mat.set_value(0, i, accum);
		}
		return mat;
	}
	else {
		Matrix mat(this->num_rows, 1, 1);
		for (int i = 0; i < this->num_rows; i++) {
			int accum = 0;
			for (int j = 0; j < this->num_columns; j++) {
				accum += this->mat[i][j];
			}
			mat.set_value(i, 0, accum);
		}
		return mat;
	}
}

void Matrix::print() {
	std::cout << this->num_rows << "x" << this->num_columns << std::endl;
	for (auto row: mat) {
		for (double value: row) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
}