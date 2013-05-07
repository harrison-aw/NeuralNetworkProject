/*
 * ART2Network.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#include "ART2Network.h"
#include "nnfunctions.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace art2nn {

ART2Network::ART2Network(dimension input_dimension, param a, param b, param c, param d, param e, param theta, param rho):
	input_dimension(input_dimension),
	a(a), b(b), c(c), d(d), e(e), theta(theta), rho(rho),
	f(LINEAR_SIGNAL_FUNCTION), g(HEAVISIDE_SIGNAL_FUNCTION),
	bottom_up_W(input_dimension, 0), top_down_W(0, input_dimension),
	F1(*this), F2(*this), vigilance(*this) {
}

ART2Network::~ART2Network() {
}

art2nn::index ART2Network::operator()(const input_vector &I) {
	F1.zeroInput();
	F2.resetWeights();

	input_vector normedI = I / I.norm();

	int nodes_committed = 0;

	bool stable = false;
	do {
		if (F2.getNodeCount() == 0 || F2.unsuppressedNodeCount() == 0) {
			commitNode(normedI);
			++nodes_committed;
		}

		signal_vector F2nets = F1(normedI) * bottom_up_W;
		cout << "F2 nets: " << F2nets << endl;
		F2(F2nets);  // feed forward
		cout << "Winning index: " << F2.winner() << endl;
		F1(normedI);      // feed backward
		F1(normedI);      // feed backward

		if (vigilance()) {  // if vigilance test is passed
			cout << "network is stable" << endl;
			stable = true;
		} else {
			cout << "suppressing winner" << endl;
			F2.suppressWinner();
			/*
			if (F2.unsuppressedNodeCount() > 0) {
				cout << "suppressing winner" << endl;
				F2.suppressWinner();
			} else {
				cout << "committing node" << endl;
				commitNode(normedI);
				++nodes_committed;
			}
			*/
		}

		cout << "learning" << endl;
		learn();

		if (nodes_committed > 1) {
			cout << "too many nodes committed" << endl;
			throw new runtime_error("too many nodes committed");
		}
	} while (!stable);

	return F2.winner();
}

void ART2Network::commitNode(const input_vector &I) {
	F2.addNode();
	dimension category_count = F2.getNodeCount();

	const signal_vector &p = F1.p;
	const signal_vector &u = F1.u;

	bottom_up_W.resize(input_dimension, category_count);
	top_down_W.resize(category_count, input_dimension);

	// add connection weights to new node
	index J = category_count - 1;
	for (index i = 0; i < input_dimension; ++i) {
		bottom_up_W(i, J, p[i]);
		top_down_W(J, i, 0);
	}
}

void ART2Network::learn() {
	index J = F2.winner();
	const signal_vector &u = F1.u;

	for (index i = 0; i < input_dimension; ++i) {
		weight bottom_up_delta = d * (u[i]/(1-d) - bottom_up_W(i, J));
		weight top_down_delta = d * (u[i]/(1-d) - top_down_W(J, i));

		bottom_up_W(i, J, bottom_up_W(i, J) + bottom_up_delta);
		top_down_W(J, i, top_down_W(J, i) + top_down_delta);
	}
}


/* Layer1 */

ART2Network::Layer1::Layer1(const ART2Network &parent):
	parent(parent),
	p(parent.input_dimension),
	q(parent.input_dimension),
	u(parent.input_dimension),
	v(parent.input_dimension),
	w(parent.input_dimension),
	x(parent.input_dimension) {
}

signal_vector ART2Network::Layer1::operator()(const input_vector &I) {
	param a = parent.a;
	param b = parent.b;
	param d = parent.d;
	param e = parent.e;
	param theta = parent.theta;

	signal (*f)(param, signal) = parent.f;
	signal (*g)(param, signal) = parent.g;

	const weight_matrix &top_down_W = parent.top_down_W;

	signal_vector y = parent.F2.output();

	signal_vector old_p, old_u;

	w = I + a * u;
	x = w / (e + w.norm());
	v = vectorApply(x, f, theta) + b * vectorApply(q, f, theta);
	u = v / (e + v.norm());
	p = u + (vectorApply(y, g, d) * top_down_W).project(u.dim());
	q = p  - u;

	return p;
}

void ART2Network::Layer1::zeroInput() {
	dimension m = parent.input_dimension;
	for (index i = 0; i < m; ++i)
		p[i] = q[i] = u[i] = v[i] = w[i] = x[i] = 0.0;
}


/* Layer 2 */

ART2Network::Layer2::Layer2(const ART2Network &parent):
	Maxnet(0), parent(parent) {
}

art2nn::index ART2Network::Layer2::winner() const {
	art2nn::index J = 0;
	for (index j = 0; j < node_count; ++j) {
		if (signals[j] > 0) {
			J = j;
			break;
		}
	}
	return J;
}

art2nn::signal ART2Network::Layer2::winnerSignal() const {
	return signals[winner()];
}

void ART2Network::Layer2::resetWeights() {
	param epsilon = 1.0 / node_count;
	param theta = 1.0;

	for (index i = 0; i < node_count; ++i) {
		for (index j = 0; j < node_count; ++j) {
			if (i != j)
				W(i, j, -epsilon);
			else
				W(i, j, theta);
		}
	}
}

void ART2Network::Layer2::suppress(index j) {
	for (index i = 0; i < node_count; ++i)
		W(i, j, 0.0);
}

void ART2Network::Layer2::suppressWinner() {
	suppress(winner());
}

unsigned int ART2Network::Layer2::unsuppressedNodeCount() {
	unsigned int count = 0;
	for (index i = 0; i < node_count; ++i) {
		if (W(i, 0) != 0.0)
			++count;
	}
	return count;
}

void ART2Network::Layer2::addNode() {
	++node_count;
	signals = signals.project(node_count);

	weight_matrix newW(node_count, node_count);
	W = newW;
	resetWeights();
}


/* Vigil */

ART2Network::Vigil::Vigil(const ART2Network &parent):
	parent(parent), r(parent.input_dimension) {
}

bool ART2Network::Vigil::operator()() {
	param c = parent.c;
	param e = parent.e;
	param rho = parent.rho;

	const signal_vector &u = parent.F1.u;
	const signal_vector &q = parent.F1.q;

	r = (u + c*q) / (e + u.norm() + c * q.norm());

	cout << "|r| = " << r.norm() << endl;

	if (r.norm() != r.norm()) {
		throw new runtime_error("r is nan");
	}

	return (rho / (e + r.norm())) <= 1;
}

} /* namespace art2nn */
