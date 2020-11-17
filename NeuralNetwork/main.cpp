#include "Matrix.hpp"
#include "NeuralNetwork.hpp"
#include "load_data.hpp"

int main() {
	NeuralNetwork NN;
	NN.append_layer(784, true);
	NN.append_layer(30, true);
	NN.append_layer(10, false);
	
	NN.initialize_weights();

	/*
	std::vector<std::string> a = split("7 33 222 2 333 2 1 ");
	for (int i = 0; i < a.size(); i++) {
		std::cout << a[i] << std::endl;
	}*/

	Matrix X = load_data("x_train.txt", 100);
	Matrix y = load_labels("y_train.txt", 100); 

	std::vector<double> bias_col;
	for (int i = 0; i < X.num_rows; i++) bias_col.push_back(1);

	X.insert_column(bias_col, 0);
	
	std::cout << NN.cost(X, y, 10, 0.) << std::endl;

	/*Matrix test(100, 2);
	test.insert_column(bias_col, 0);
	test.print();*/

	//X.print();
	//std::cout << X.num_rows << " " << X.num_columns << std::endl;
	//y.print();*/

	return 0;
}