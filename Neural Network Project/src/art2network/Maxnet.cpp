/*
 * Maxnet.cpp
 *
 *  Created on: Apr 30, 2013
 *      Author: Tony
 */

#include "Maxnet.h"
#include "nnfunctions.h"

using namespace art2nn;

Maxnet::Maxnet():
	node_count(0), f(SIMPLE_SIGNAL_FUNCTION) {
	initW(1.0, 1.0);
}

Maxnet::Maxnet(const Maxnet &maxnet):
	node_count(maxnet.node_count), f(maxnet.f), signals(maxnet.signals), W(maxnet.W) {
}

Maxnet::Maxnet(size_t node_count):
	node_count(node_count), f(SIMPLE_SIGNAL_FUNCTION), signals(node_count), W(node_count, node_count) {
	initW(1.0/node_count, 1.0);
}

Maxnet::Maxnet(size_t node_count, param epsilon, param theta):
	node_count(node_count), f(SIMPLE_SIGNAL_FUNCTION), signals(node_count), W(node_count, node_count) {
	initW(epsilon, theta);
}

Maxnet::Maxnet(size_t node_count, param epsilon, param theta, signal (*f)(signal)):
	node_count(node_count), f(f), signals(node_count), W(node_count, node_count) {
	initW(epsilon, theta);
}

Maxnet::~Maxnet() {
}

Maxnet &Maxnet::operator=(const Maxnet &maxnet) {
	if (this != &maxnet) {
		node_count = maxnet.node_count;
		signals = maxnet.signals;
		W = maxnet.W;
		f = maxnet.f;
	}
	return *this;
}

const signal_vector &Maxnet::operator()(const input_vector &I) {
	unsigned int non_zero_count;

	setSignals(I);

	do {
		iterate();

		non_zero_count = 0;
		for (index j = 0; j < node_count; ++j) {
			if (signals[j] > 0)
				++non_zero_count;
		}
	} while (non_zero_count > 1);

	return signals;
}

void Maxnet::iterate() {
	input temp[node_count];
	for (index j = 0; j < node_count; ++j)
		temp[j] = f(net(j));
	for (index j = 0; j < node_count; ++j)
		signals[j] = temp[j];
}

void Maxnet::initW(param epsilon, param theta) {
	for (index i = 0; i < node_count; ++i) {
		for (index j = 0; j < node_count; ++j) {
			if (i != j)
				W(i, j, -epsilon);
			else
				W(i, j, theta);
		}
	}
}

void Maxnet::setSignals(const input_vector &I) {
	for (index i = 0; i < node_count; ++i)
		signals[i] = I[i];
}
