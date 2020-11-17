#include <fstream>
#include "Matrix.hpp"
#include <string>
#include <vector>

Matrix load_data(std::string filename, int n_samples);
Matrix load_labels(std::string filename, int n_labels);
std::vector<std::string> split(std::string str);