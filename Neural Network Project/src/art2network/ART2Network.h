/*
 * ART2Network.h
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#ifndef ART2NETWORK_H_
#define ART2NETWORK_H_

#include "nntypes.h"
#include "Maxnet.h"

namespace art2nn {

class ART2Network {
public:
	class Layer1;
	class Layer2;
	class Vigil;

	ART2Network(dimension input_dimension, param a, param b, param c, param d, param e, param theta, param rho);
	virtual ~ART2Network();

	index operator()(const input_vector &I);

	friend class Layer1;
	friend class Layer2;
	friend class Vigil;

	class Layer1 {
	public:
		Layer1(const ART2Network &parent);

		void zeroInput();

		signal_vector operator()(const input_vector I);

		friend class ART2Network;
		friend class Layer2;
		friend class Vigil;
	private:
		void initVectors();

		const ART2Network &parent;

		signal_vector p;
		signal_vector q;
		signal_vector u;
		signal_vector v;
		signal_vector w;
		signal_vector x;
	};

	class Layer2: public Maxnet {
	public:
		Layer2(const ART2Network &parent);

		index winner() const;
		signal winnerSignal() const;

		void resetWeights();
		void suppress(index j);
		void suppressWinner();
		unsigned int unsuppressedNodeCount();
		void addNode();

		friend class ART2Network;
		friend class Vigil;
	private:
		const ART2Network &parent;
	};

	class Vigil {
	public:
		Vigil(const ART2Network &parent);

		bool operator()();

	private:
		const ART2Network &parent;

		signal_vector r;
	};

protected:
	void commitNode();
	void learn();

	dimension input_dimension;

	param a;
	param b;
	param c;
	param d;
	param e;
	param theta;
	param rho;

	signal (*f)(param, signal);
	signal (*g)(param, signal);

	weight_matrix bottom_up_W;
	weight_matrix top_down_W;

	Layer1 F1;
	Layer2 F2;
	Vigil vigilance;
}; /* class ART2Network */

} /* namespace art2nn */

#endif /* ART2NETWORK_H_ */

