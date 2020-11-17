#pragma once
#include <vector>
#include <iostream>

class Neuron;

class Layer {
	std::vector<Neuron> neurons;
public:
	Layer(int num_neurons, std::vector<double> initial_values);
	Layer(int num_neurons);
	std::vector<Neuron> get_neurons();
	void compute_neurons();
};