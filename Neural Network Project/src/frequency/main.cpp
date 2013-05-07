/*
 * main.cpp
 *
 *  Created on: May 3, 2013
 *      Author: Tony
 */

#include <fstream>
#include <iostream>

#include "FrequencyTable.h"

using namespace std;
using namespace nnproject;

int main(int argc, char *argv[]) {
	FrequencyTable ft("files/");

	ofstream fout("input.ft");
	if (fout) {
		fout << ft;
		fout.close();
		cout << "input.ft written" << endl;
	}

	return 0;
}


