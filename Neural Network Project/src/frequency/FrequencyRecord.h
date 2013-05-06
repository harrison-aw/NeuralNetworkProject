/*
 * FrequencyTable.h
 *
 *  Created on: May 3, 2013
 *      Author: Tony
 */

#ifndef FREQUENCYRECORD_H_
#define FREQUENCYRECORD_H_

#include <iostream>
#include <map>
#include <string>

namespace nnproject {

class FrequencyRecord {
public:
	FrequencyRecord();
	FrequencyRecord(const FrequencyRecord &fr);
	explicit FrequencyRecord(const std::string &filename);
	virtual ~FrequencyRecord();

	friend std::ostream &operator<<(std::ostream &os, FrequencyRecord &fr);
	friend std::istream &operator>>(std::istream &is, FrequencyRecord &fr);

	void analyzeFile(const std::string &filename);

	unsigned int countOf(char c);
	double frequencyOf(char c);

private:
	unsigned int char_count;
	std::map<char, unsigned int> record;
};

} /* namespace cfanalyzer */
#endif /* FREQUENCYRECORD_H_ */
