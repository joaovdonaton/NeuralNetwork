#pragma once

class Layer;

class Neuron {
	double value;
public:
	Neuron();
	Neuron(double value);
	void compute(Layer prev_l, double weights[]);
};