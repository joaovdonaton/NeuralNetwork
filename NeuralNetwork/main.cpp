#include "Matrix.hpp"
#include "NeuralNetwork.hpp"
#include "load_data.hpp"

int main() {
	NeuralNetwork NN;
	NN.append_layer(784, true);
	NN.append_layer(30, true);
	NN.append_layer(10, false);
	
	NN.initialize_weights();

	double lamb = 5;

	//load training set and train weights
	Matrix X = load_data("./data/MNIST digits/x_train.txt", 1000);
	Matrix y = load_labels("./data/MNIST digits/y_train.txt", 1000); 

	std::vector<double> bias_col;
	for (int i = 0; i < X.num_rows; i++) bias_col.push_back(1);
	X.insert_column(bias_col, 0);
	
	NN.train(X, y, 10, lamb, 400, 0.1);

	//load test set and measure accuracy
	Matrix test_X = load_data("./data/MNIST digits/x_test.txt", 2500);
	Matrix test_y = load_labels("./data/MNIST digits/y_test.txt", 2500);

	bias_col.clear();
	for (int i = 0; i < test_X.num_rows; i++) bias_col.push_back(1);
	test_X.insert_column(bias_col, 0);

	Matrix out = NN.feedforward(test_X).back().transpose();
	double correct = 0.;

	for (int i = 0; i < test_X.num_rows; i++) {
		Matrix out_layer = out.get_row(i);
		int max_ind = out_layer.get_value(0, 0);
		for (int j = 0; j < 10; j++) {
			if (out_layer.get_value(0, j) > out_layer.get_value(0, max_ind)) {
				max_ind = j;
			}
		}
		if (max_ind == test_y.get_value(i, 0)) correct++;
		//std::cout << "Prediction: " << max_ind << "     Answer:" << test_y.get_value(i, 0) << std::endl;
	}

	std::cout << "Test set accuracy: " << 100 * correct / test_X.num_rows << std::endl;
	std::cout << "Training set cost: " << NN.cost(X, y, 10, 0.) << std::endl;
	std::cout << "Test set cost: " << NN.cost(test_X, test_y, 10, 0.) << std::endl;

	return 0;
}