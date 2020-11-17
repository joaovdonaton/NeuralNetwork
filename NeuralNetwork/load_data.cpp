#include "load_data.hpp"

//only works if elements are separated by single spaces
//final character must be a single space 
std::vector<std::string> split(std::string str) {
	//if (str[-1] != ' ') str.append(" ");
	std::vector<std::string> split_str;
	int last_space = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			split_str.push_back(str.substr(last_space, i-last_space));
			last_space = i;
		}
	}
	//split_str.push_back(str.substr(last_space, str.size()-last_space));
	return split_str;
}

Matrix load_data(std::string filename, int n_samples) {
	std::string line_str;
	std::ifstream cfile(filename);
	int columns = 0;
	getline(cfile, line_str);
	columns = split(line_str).size();

	// debug std::cout << rows << " " << columns << std::endl;

	std::cout << "Loading dataset into matrix(" << n_samples << "x" << columns
		<< ")..." << std::endl;

	Matrix mat(n_samples, columns);

	std::ifstream file(filename);
	int current_line = 0;
	while (std::getline(file, line_str)) {
		std::vector<std::string> nums = split(line_str);
		for (int i = 0; i < nums.size(); i++) {
			mat.set_value(current_line, i, std::stoi(nums[i]));
		}
		current_line++;
		if (current_line == n_samples) break;
	}
	file.close();
	return mat;
}

Matrix load_labels(std::string filename, int n_labels) {
	std::cout << "Loading labels into matrix(" << n_labels << "x" << 1
		<< ")..." << std::endl;

	std::ifstream file(filename);
	std::string line;
	Matrix mat(n_labels, 1);
	int i = 0;
	while (std::getline(file, line)) {
		mat.set_value(i, 0, std::stoi(line));
		i++;
		if (i == n_labels) break;
	}

	return mat;
}