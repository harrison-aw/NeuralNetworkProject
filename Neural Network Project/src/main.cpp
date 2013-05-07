/*
 * main.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Tony
 */

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
	param theta = .01;
	param rho = .99;

	ART2Network network(127, a, b, c, d, e, theta, rho);
	cout << "Network built." << endl;

	cout << "Inputs: " << endl;
	for (FrequencyTable::iterator it = ft.begin(); it != ft.end(); ++it) {
		cout << makeInput(it->second).project(20) << endl;
	}

	cout << endl;
	map<string, index> classification;
	for (FrequencyTable::iterator it = ft.begin(); it != ft.end(); ++it) {
		try {
			cout << "processing " << it->first << endl;
			classification[it->first] = network(makeInput(it->second));
			cout << endl;
		} catch (exception &e) {
			cout << "Error: " << e.what() << endl;
			return 1;
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

