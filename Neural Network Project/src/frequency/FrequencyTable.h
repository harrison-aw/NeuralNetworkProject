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
	FrequencyTable();
	explicit FrequencyTable(const std::string &directory_path);
	virtual ~FrequencyTable();

	friend std::ostream &operator<<(std::ostream &os, FrequencyTable &ft);
	friend std::istream &operator>>(std::istream &is, FrequencyTable &ft);

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
