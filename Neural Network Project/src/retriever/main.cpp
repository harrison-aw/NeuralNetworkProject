/*
 * main.cpp
 *
 *  Created on: May 4, 2013
 *      Author: Tony
 */

#include <iostream>

#include "GitHubLink.h"

using namespace std;
using namespace nnproject;

int main(int argc, char *argv[]) {

	GitHubLink link;

	try {
		link.downloadCode("lisp", 5000, 10000, "files/");
		link.downloadCode("cpp", 5000, 10000, "files/");
	} catch (GitHubLink::xml_parsing_exception &e) {
		cout << e.what() << endl;
	}

	return 0;
}


