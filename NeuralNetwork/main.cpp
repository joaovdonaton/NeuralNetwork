#include "Matrix.hpp"
#include "NeuralNetwork.hpp"
#include "load_data.hpp"

int main() {
	NeuralNetwork NN;
	NN.append_layer(784, true);
	NN.append_layer(30, true);
	NN.append_layer(10, false);
	
	NN.initialize_weights();

	Matrix pop(3, 4, -5);
	(pop^Matrix(4, 3, -2)).print();

	/*
	std::vector<std::string> a = split("7 33 222 2 333 2 1 ");
	for (int i = 0; i < a.size(); i++) {
		std::cout << a[i] << std::endl;
	}*/

	Matrix X = load_data("x_train.txt", 20);
	Matrix y = load_labels("y_train.txt", 20); 

	std::vector<double> bias_col;
	for (int i = 0; i < X.num_rows; i++) bias_col.push_back(1);

	X.insert_column(bias_col, 0);
	
	NN.train(X, y, 10, 0., 500, 0.1);

	Matrix out = NN.feedforward(X).back().transpose();
	double correct = 0.;

	for (int i = 0; i < X.num_rows; i++) {
		Matrix out_layer = out.get_row(i);
		int max_ind = out_layer.get_value(0, 0);
		for (int j = 0; j < 10; j++) {
			if (out_layer.get_value(0, j) > out_layer.get_value(0, max_ind)) {
				max_ind = j;
			}
		}
		if (max_ind == y.get_value(i, 0)) correct++;
		std::cout << "Prediction: " << max_ind << "     Answer:" << y.get_value(i, 0) << std::endl;
	}

	std::cout << "Accuracy: " << 100 * correct / X.num_rows << std::endl;

	/*Matrix test(100, 2);
	test.insert_column(bias_col, 0);
	test.print();*/

	//X.print();
	//std::cout << X.num_rows << " " << X.num_columns << std::endl;
	//y.print();*/

	return 0;
}