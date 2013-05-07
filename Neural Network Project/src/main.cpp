/*
 * main.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Tony
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "art2network/ART2Network.h"
#include "frequency/FrequencyTable.h"

using namespace std;
using namespace art2nn;
using namespace nnproject;

input_vector makeInput(FrequencyRecord &fr);

int main() {
	FrequencyTable ft;
	ifstream fin("input.ft");
	if (fin) {
		fin >> ft;
		fin.close();
		cout << "input read" << endl;
	} else {
		cout << "unable to read input" << endl;
		return 1;
	}

	param a = 10;
	param b = 10;
	param c = 4;
	param d = .2;
	param e = 0;
	param theta = .005;
	param rho = .99999;

	ART2Network network(127, a, b, c, d, e, theta, rho);
	cout << "Network built." << endl << endl;

	for (int i = 0; i < 10; ++i) {
		cout << "Shuffling inputs" << endl << endl;
		vector<string> inputs;
		for (FrequencyTable::iterator it = ft.begin(); it != ft.end(); ++it)
			inputs.push_back(it->first);
		std::random_shuffle(inputs.begin(), inputs.end());

		map<string, index> classification;
		for (vector<string>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
			try {
				cout << "processing " << *it << endl;
				classification[*it] = network(ft[*it]);
				cout << endl;
			} catch (exception &e) {
				cout << "Error: " << e.what() << endl;
				return 1;
			}
		}
	}

	cout << endl << endl;
	cout << "Printing results: " << endl;

	for (map<string, index>::iterator it = classification.begin(); it != classification.end(); ++it) {
		cout << it->first << " -> " << it->second << endl;
	}

	return 0;
}

input_vector makeInput(FrequencyRecord &fr) {
	input_vector input(127);
	for (char c = 0; c < 127; ++c) {
		input[c] = fr.frequencyOf(c);
	}
	return input;
}

