/*
 * nnexceptions.h
 *
 *  Created on: May 2, 2013
 *      Author: Tony
 */

#ifndef NNEXCEPTIONS_H_
#define NNEXCEPTIONS_H_

#include <stdexcept>

namespace art2nn {

class dimension_error: public std::length_error {
public:
	explicit dimension_error(const std::string &what_arg): std::length_error(what_arg) {};
};

}

#endif /* NNEXCEPTIONS_H_ */
