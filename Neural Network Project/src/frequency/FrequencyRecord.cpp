/*
 * FrequencyTable.cpp
 *
 *  Created on: May 3, 2013
 *      Author: Tony
 */

#include <fstream>

#include "FrequencyRecord.h"

using namespace std;

namespace nnproject {

FrequencyRecord::FrequencyRecord():
	char_count(0) {
}

FrequencyRecord::FrequencyRecord(const FrequencyRecord &fr):
	char_count(fr.char_count) {
	record = fr.record;
}

FrequencyRecord::FrequencyRecord(const string &filename):
	char_count(0) {
	analyzeFile(filename);
}

FrequencyRecord::~FrequencyRecord() {
}

ostream &operator<<(ostream &os, FrequencyRecord &fr) {
	os << fr.char_count;
	for (char c = 0; c < 127; ++c) {
		os << " " << fr.record[c];
	}
	return os;
}

istream &operator>>(istream &is, FrequencyRecord &fr) {
	is >> fr.char_count;
	for (char c = 0; c < 127; ++c) {
		is >> fr.record[c];
	}
	return is;
}

void FrequencyRecord::analyzeFile(const string &filename) {
	ifstream file(filename.c_str());
	while (file) {
		char c = file.get();
		if (file.good()) {
			++char_count;
			++record[c];
		}
	}
	file.close();
}

unsigned int FrequencyRecord::countOf(char c) {
	return record[c];
}

double FrequencyRecord::frequencyOf(char c) {
	return static_cast<double>(record[c]) / char_count;
}

} /* namespace cfanalyzer */
