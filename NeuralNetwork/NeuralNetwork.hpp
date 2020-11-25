#pragma once

#include <vector>
#include <time.h>
#include "Matrix.hpp"
#include <chrono>

class NeuralNetwork {
	std::vector<int> architecture;
	std::vector<Matrix> weights; // [0]=L1-L2 [1]=L2-L3 [2]=L3-L4 ...
public:
	void append_layer(int num_neurons, bool bias);
	void initialize_weights();
	double cost(Matrix X, Matrix y, int K, double lambda);
	static double sigmoid(double z);
	std::vector<Matrix> feedforward(Matrix X);
	std::vector<Matrix> backpropagation(Matrix X, Matrix y, int K, double lambda);
	void train(Matrix X, Matrix y, int K, double lambda, int iter, double alpha);
	//X must already have bias node 
};