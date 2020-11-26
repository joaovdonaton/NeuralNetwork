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

Matrix Matrix::log(char b) {
	Matrix new_m(num_rows, num_columns, 1);
	switch (b) {
	case 't': //base 10 logarithm
		for (int i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_columns; j++) {
				new_m.set_value(i, j, log10(this->get_value(i, j)));
			}
		}
		break;
	case 'n': //natural logarithm
		for (int i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_columns; j++) {
				new_m.set_value(i, j, std::log(this->get_value(i, j)));
			}
		}
		break;
	default:
		std::cout << "Invalid logarithm base" << std::endl;
	}
	return new_m;
}

Matrix Matrix::operator+(Matrix mat) {
	if (num_rows != mat.num_rows || num_columns != mat.num_columns) {
		std::cout << "Element wise matrix addition failed: " << num_rows << "x" << num_columns
			<< " " << mat.num_rows << "x" << mat.num_columns << std::endl;
		return Matrix(1, 1, 1);
	}

	Matrix new_m(num_rows, num_columns, 1);
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			new_m.set_value(i, j, this->get_value(i, j) + mat.get_value(i, j));
		}
	}

	return new_m;
}

Matrix Matrix::operator-(Matrix mat) {
	if (num_rows != mat.num_rows || num_columns != mat.num_columns) {
		std::cout << "Element wise matrix subtraction failed: " << num_rows << "x" << num_columns
			<< " " << mat.num_rows << "x" << mat.num_columns << std::endl;
		return Matrix(1, 1, 1);
	}

	Matrix new_m(num_rows, num_columns, 1);
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			new_m.set_value(i, j, this->get_value(i, j) - mat.get_value(i, j));
		}
	}

	return new_m;
}

Matrix Matrix::operator*(Matrix mat) {
	if (num_rows != mat.num_rows || num_columns != mat.num_columns) {
		std::cout << "Element wise matrix multiplication failed: " << num_rows << "x" << num_columns
			<< " " << mat.num_rows << "x" << mat.num_columns << std::endl;
		return Matrix(1, 1, 1);
	}

	Matrix new_m(num_rows, num_columns, 1);
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_columns; j++) {
			new_m.set_value(i, j, this->get_value(i, j) * mat.get_value(i, j));
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

Matrix Matrix::get_row(int row) {
	if (row >= num_rows) {
		std::cout << "Row index out of range: " << row << "(Max: " << num_rows-1 << ")"<< std::endl;
		return Matrix(1, 1, 1);
	}

	Matrix r(1, num_columns, 0);
	for (int i = 0; i < num_columns; i++) {
		r.set_value(0, i, this->get_value(row, i));
	}
	return r;
}

Matrix Matrix::get_column(int column) {
	if (column >= num_columns) {
		std::cout << "Column index out of range: " << column << "(Max: " << num_columns-1 << ")" << std::endl;
		return Matrix(1, 1, 1);
	}

	Matrix col(num_rows, 1, 0);
	for (int i = 0; i < num_rows; i++) {
		col.set_value(i, 0, this->get_value(i, column));
	}
	return col;
}

void Matrix::remove_row(int row) {
	mat.erase(mat.begin()+row);
	num_rows--;
}

Matrix Matrix::operator^(Matrix mat) {
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
	if (row.size() == num_columns && !(position > num_rows)) {
		mat.insert(mat.begin() + position, row);
		num_rows++;
	}
	else {
		std::cout << "Could not insert row" << std::endl;
	}
}

void Matrix::insert_column(std::vector<double> column, int position){
	if (column.size() == num_rows && !(position > num_columns)) {
		for (int i = 0; i < num_rows; i++) {
			mat[i].insert(mat[i].begin()+position, column[i]);
		}
		num_columns++;
	}
	else {
		std::cout << "Could not insert column" << std::endl;
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

Matrix Matrix::sum(int axis) {
	if (axis==1) { 
		Matrix mat(1, num_columns, 1);
		for (int i = 0; i < num_columns; i++) {
			double accum = 0;
			for (int j = 0; j < num_rows; j++) {
				accum += this->mat[j][i];
			}
			mat.set_value(0, i, accum);
		}
		return mat;
	}
	else {
		Matrix mat(num_rows, 1, 1);
		for (int i = 0; i < num_rows; i++) {
			double accum = 0;
			for (int j = 0; j < num_columns; j++) {
				accum += this->mat[i][j];
			}
			mat.set_value(i, 0, accum);
		}
		return mat;
	}
}

void Matrix::print() {
	std::cout << num_rows << "x" << num_columns << std::endl;
	for (auto row: mat) {
		for (double value: row) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
}