/*
 * FrequencyTable.cpp
 *
 *  Created on: May 5, 2013
 *      Author: Tony
 */

#include <dirent.h>

#include "FrequencyTable.h"

using namespace std;

namespace nnproject {

FrequencyTable::FrequencyTable() {
}

FrequencyTable::FrequencyTable(const string &directory_path) {
	buildFromDirectory(directory_path);
}

FrequencyTable::~FrequencyTable() {
}

ostream &operator<<(ostream &os, FrequencyTable &ft) {
	os << ft.table.size();
	for (map<string,FrequencyRecord>::iterator it = ft.table.begin(); it != ft.table.end(); ++it) {
		os << " " << it->first << " " << it->second;
	}

	return os;
}

istream &operator>>(istream &is, FrequencyTable &ft) {
	unsigned int size;
	is >> size;
	for (unsigned int i = 0; i < size; ++i) {
		std::string filename;
		is >> filename;
		is >> ft.table[filename];
	}
	return is;
}

void FrequencyTable::buildFromDirectory(const string &directory_path) {
	vector<string> filenames(getFilenames(directory_path));

	for (vector<string>::iterator it = filenames.begin(); it != filenames.end(); ++it) {
		table[*it] = FrequencyRecord(directory_path + *it);
	}
}

vector<string> FrequencyTable::getFilenames(string directory_path) {
	vector<string> filenames;

	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(directory_path.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name[0] != '.')
				filenames.push_back(ent->d_name);
		}
		closedir(dir);
	} else {
		throw directory_exception("Unable to open directory: " + directory_path);
	}
	return filenames;
}

} /* namespace nnproject */
