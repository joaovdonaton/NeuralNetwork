#include "Neuron.hpp"
#include "Layer.hpp"

Layer::Layer(int n, std::vector<double> initial_values) {
	if (n != initial_values.size()) std::cout << "Invalid size for initial_values" << std::endl;
	for (int i = 0; i < n; i++) {
		neurons.push_back(Neuron(initial_values[i]));
	}
}

Layer::Layer(int n) {
	for (int i = 0; i < n; i++) {
		neurons.push_back(Neuron());
	}
}

std::vector<Neuron> Layer::get_neurons() {
	return this->neurons;
}

void Layer::compute_neurons() {

}