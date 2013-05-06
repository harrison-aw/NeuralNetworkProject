/*
 * main.cpp
 *
 *  Created on: May 6, 2013
 *      Author: Tony
 */

#include <iostream>

#include "art2network/ART2Network.h"
#include "frequency/FrequencyTable.h"

using namespace std;
using namespace art2nn;
using namespace nnproject;

int main() {
	ART2Network network(127, .2, 0, 0, .2, .001, .4, .3);

	cout << "Network built." << endl;

	return 0;
}

