#include "NeuralNetwork.hpp"

void NeuralNetwork::append_layer(int num_neurons, bool bias) {
	this->layers.push_back(Layer(num_neurons+bias));
	//for(auto l: layers) std::cout << l.get_neurons().size() << std::endl;
}

void NeuralNetwork::initialize_weights() {
	srand((unsigned)time(NULL));

	for (int i = 0; i < this->layers.size()-1; i++) {
		 int num_neurons = this->layers[i].get_neurons().size(); //current layer
		 int num_neurons_next = this->layers[i + 1].get_neurons().size(); //next layer

		 if (i + 1 != this->layers.size()-1) //ignore bias node
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
	a.push_back(X.transpose()); //100x785 a1(a[0]) is X
	for (int i = 0; i < this->weights.size(); i++) {
		Matrix prev_a = a[i];
		Matrix temp_a = this->weights[i].multiply(prev_a); 
		
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
	Matrix inv_Y = Y.op(Matrix(K, m, -1), '*'); // -Y
	Matrix output_layer = a.back();
	
	Matrix y1 = output_layer.log('n').op(inv_Y, '*'); //A[-1].*-Y
	Matrix y0 = Matrix(K, m, 1).op(Y, '-').op(Matrix(K, m, 1).op(output_layer, '-').log('n'), '*'); // (1-Y).*ln(1-A[-1])

	J = J * y1.op(y0, '-').sum(1).sum(2).get_value(0,0); // 1/m * sum(sum(Y1-Y0))

	return J;
}

/*std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;*/