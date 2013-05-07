/*
 * FrequencyTable.h
 *
 *  Created on: May 5, 2013
 *      Author: Tony
 */

#ifndef FREQUENCYTABLE_H_
#define FREQUENCYTABLE_H_

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "FrequencyRecord.h"

namespace nnproject {

class FrequencyTable {
public:
	typedef std::map<std::string, FrequencyRecord>::iterator iterator;

	FrequencyTable();
	explicit FrequencyTable(const std::string &directory_path);
	virtual ~FrequencyTable();

	friend std::ostream &operator<<(std::ostream &os, FrequencyTable &ft);
	friend std::istream &operator>>(std::istream &is, FrequencyTable &ft);
	FrequencyRecord &operator[](const std::string &key);

	iterator begin() { return table.begin(); };
	iterator end() { return table.end(); };

	void buildFromDirectory(const std::string &directory_path);

	class directory_exception: public std::runtime_error {
	public:
		explicit directory_exception(const std::string &what_arg): std::runtime_error(what_arg) {};
	};

protected:
	static std::vector<std::string> getFilenames(std::string directory_path);

	std::map<std::string, FrequencyRecord> table;
};

} /* namespace nnproject */
#endif /* FREQUENCYTABLE_H_ */
