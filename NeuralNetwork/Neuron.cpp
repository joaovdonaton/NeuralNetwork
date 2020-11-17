#include "Layer.hpp"
#include "Neuron.hpp"

void Neuron::compute(Layer prev_l, double theta[]) {
	int sum = 0;
	/*for (auto neuron : prev_l.get_neurons()) {
		sum +=
	}*/
	this->value = sum;
}

Neuron::Neuron() {
	this->value = 0.;
}

Neuron::Neuron(double value) {
	this->value = value;
}