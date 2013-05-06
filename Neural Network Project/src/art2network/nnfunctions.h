/*
 * functions.h
 *
 *  Created on: May 2, 2013
 *      Author: Tony
 */

#ifndef NNFUNCTIONS_H_
#define NNFUNCTIONS_H_

#include "nntypes.h"

namespace art2nn {

signal SIMPLE_SIGNAL_FUNCTION(signal x);
signal NONLINEAR_SIGNAL_FUNCTION(param theta, signal x);
signal LINEAR_SIGNAL_FUNCTION(param theta, signal x);
signal HEAVISIDE_SIGNAL_FUNCTION(param d, signal x);

signal_vector vectorApply(signal_vector vector, signal (*f)(signal));
signal_vector vectorApply(signal_vector vector, signal (*f)(param, signal), param p);

} /* namespace art2nn */

#endif /* NNFUNCTIONS_H_ */
