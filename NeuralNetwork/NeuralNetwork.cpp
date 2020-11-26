#include "NeuralNetwork.hpp"

void NeuralNetwork::append_layer(int num_neurons, bool bias) {
	this->architecture.push_back(num_neurons + bias);
}

void NeuralNetwork::initialize_weights() {
	srand((unsigned)time(NULL));

	for (int i = 0; i < this->architecture.size()-1; i++) {
		 int num_neurons = this->architecture[i]; //current layer
		 int num_neurons_next = this->architecture[i + 1]; //next layer

		 if (i + 1 != this->architecture.size()-1) //ignore bias node on layer l+1
			 num_neurons_next-=1; 

		 Matrix weights(num_neurons_next, num_neurons, 1);

		 for (int j = 0; j < num_neurons_next; j++) {
			 for (int k = 0; k < num_neurons; k++) {
				 weights.set_value(j, k, (double)rand() / RAND_MAX * 2 * 0.12 - 0.12);
			 }
		 }
		 this->weights.push_back(weights);
	}
	//debug 
	/*for (int i = 0; i < this->weights.size(); i++) {
		std::cout << this->weights[i].num_rows << "x" <<
			this->weights[i].num_columns << std::endl;
		weights[i].print();
	}*/
}

double NeuralNetwork::sigmoid(double z) {
	return 1/(1+exp(-z));
}

std::vector<Matrix> NeuralNetwork::feedforward(Matrix X) {
	std::vector<Matrix> a;
	a.push_back(X.transpose()); //100x785 a1(a[0]) is X training example per column after transposition
	for (int i = 0; i < this->weights.size(); i++) {
		Matrix prev_a = a[i];
		Matrix temp_a = this->weights[i]^prev_a; 
		
		if (i != this->weights.size() - 1) { //add bias to all layers except output
			std::vector<double> bias_col;
			for (int j = 0; j < temp_a.num_columns; j++) bias_col.push_back(1);
			temp_a.insert_row(bias_col, 0);
		}

		for (int j = 0; j < temp_a.num_rows; j++) { //apply activation function
			for (int k = 0; k < temp_a.num_columns; k++) {
				temp_a.set_value(j, k, NeuralNetwork::sigmoid(temp_a.get_value(j, k)));
			}
		}

		a.push_back(temp_a); 
	}
	// debug
	/*for (Matrix x : a) {
		std::cout << x.num_rows << "x" << x.num_columns << std::endl;
	}*/

	return a;
}

double NeuralNetwork::cost(Matrix X, Matrix y, int K, double lambda) {
	std::vector<Matrix> a = feedforward(X);
	int m = X.num_rows;
	double J = 1./m;

	Matrix Y(K, m, 1); // Y = KxM (col = [0 0 0 0 0 0 0 0 1 0])
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < m; j++) { 
			Y.set_value(i, j, (double)y.get_value(j, 0) == i);
		}
	}
	Matrix inv_Y = Y*Matrix(K, m, -1); // -Y
	Matrix output_layer = a.back();
	
	Matrix y1 = output_layer.log('n')*inv_Y; // ln(A[-1]).*-Y
	Matrix y0 = (Matrix(K, m, 1)-Y)*((Matrix(K, m, 1)-output_layer).log('n')); // (1-Y).*ln(1-A[-1])

	J = J * (y1-y0).sum(1).sum(2).get_value(0,0); // 1/m * sum(Y1-Y0)

	//regularization (lambda != 0)
	double reg_sum = 0;
	for (Matrix w : weights) { 
		//ignore first column (bias)
		w = w.transpose();
		w.remove_row(0);
		w = w * w;
		reg_sum += w.sum(1).sum(0).get_value(0, 0);
	}

	J = J + (lambda / (2 * (double)m)) * reg_sum;

	return J;
}

std::vector<Matrix> NeuralNetwork::backpropagation(Matrix X, Matrix y, int K, double lambda) {
	int m = X.num_rows;

	Matrix Y(K, m, 1); // Y = KxM (col = [0 0 0 0 0 0 0 0 1 0])
	for (int i = 0; i < K; i++) { 
		for (int j = 0; j < m; j++) {
			Y.set_value(i, j, (double)y.get_value(j, 0) == i);
		}
	}

	std::vector<Matrix> accum_errors;
	for (int i = 0; i < weights.size(); i++) { //initialize accum_errors
		accum_errors.push_back(Matrix(weights[i].num_rows, weights[i].num_columns, 0));
	}

	for (int i = 0; i < m; i++) {
		std::vector<Matrix> errors; //index 0 = output error, last index = L2 (L1 doesn't have an error)

		std::vector<Matrix> a = feedforward(X.get_row(i));
		for (int j = a.size()-1; j >= 1; j--) { //compute errors starting from the output layer
			if (j == a.size() - 1) { //output error (out_layer-Y)
				errors.push_back(a[j]-Y.get_column(i));
				continue;
			}

			//error for all other layers
			Matrix next_error = errors.back();
			if (j != a.size() - 2) { //remove bias from next error if next error isn't the output layer
				next_error.remove_row(0);
			}

			errors.push_back((this->weights[j].transpose()^next_error)*(a[j]
				*(Matrix(a[j].num_rows, a[j].num_columns, 1)-a[j])));
		}
		//update accum_errors
		for (int j = accum_errors.size()-1; j >= 0; j--) {
			if(accum_errors.size() - j - 1 != 0) errors[accum_errors.size() - j - 1].remove_row(0);

			accum_errors[j] = accum_errors[j]
				+(errors[accum_errors.size() - j - 1]^(a[j].transpose()));
		}
	}

	//compute gradients for weights
	std::vector<Matrix> gradient;
	for (int i = 0; i < accum_errors.size(); i++) {
		Matrix grad = Matrix(accum_errors[i].num_rows, accum_errors[i].num_columns, 1. / m) * accum_errors[i];

		//regularization
		for (int j = 0; j < grad.num_rows; j++) { 
			for (int k = 1; k < grad.num_columns; k++) { //skip bias
				grad.set_value(j, k, grad.get_value(j, k) + (lambda/m) * 
					weights[i].get_value(j, k));
			}
		}

		gradient.push_back(grad);
	}

	return gradient;
}

void NeuralNetwork::train(Matrix X, Matrix y, int K, double lambda, int iter, double alpha) {
	//perform gradient descent
	for (int i = 0; i < iter; i++) {
		std::vector<Matrix> gradient = backpropagation(X, y, K, lambda);
		for (int j = 0; j < weights.size(); j++) {
			weights[j] = weights[j]-(
				Matrix(weights[j].num_rows, weights[j].num_columns, alpha)*gradient[j]);
		}
		std::cout << "Current Iteration: " << i << "     Cost: "<< cost(X, y, K, lambda) << std::endl;;
	}
}