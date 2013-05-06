/*
 * Maxnet.h
 *
 *  Created on: Apr 29, 2013
 *      Author: ah1411
 */

#ifndef MAXNET_H_
#define MAXNET_H_

#include "Matrix.h"
#include "nntypes.h"

namespace art2nn {

class Maxnet {
public:
	Maxnet();
	Maxnet(const Maxnet &maxnet);
	Maxnet(size_t node_count);
	Maxnet(size_t node_count, param epsilon, param theta);
	Maxnet(size_t node_count, param epsilon, param theta, signal (*f)(signal));
	virtual ~Maxnet();

	Maxnet &operator=(const Maxnet &maxnet);
	const signal_vector &operator()(const input_vector &I);  // iterates until winner chosen

	const signal_vector &output() const { return signals; }
	size_t getNodeCount() const { return node_count; }

protected:
	signal net(index j) const { return W.column(j) * signals; }
	void iterate();

	size_t node_count;
	signal (*f)(signal);
	signal_vector signals;
	weight_matrix W;  // connection weights
private:
	void initW(param epsilon, param theta);
	void setSignals(const input_vector &I);
};

} /* namespace art2nn */

#endif /* MAXNET_H_ */

