/*
 * types.h
 *
 *  Created on: May 1, 2013
 *      Author: ah1411
 */

#ifndef TYPES_H_
#define TYPES_H_

#include "indextypes.h"
#include "Vector.h"
#include "Matrix.h"

namespace art2nn {

typedef double param;
typedef double signal;
typedef double weight;
typedef double input;

typedef Vector<signal> signal_vector;
typedef Vector<weight> weight_vector;
typedef Vector<input> input_vector;

typedef Matrix<weight> weight_matrix;

} /* namespace art2nn */

#endif /* TYPES_H_ */
