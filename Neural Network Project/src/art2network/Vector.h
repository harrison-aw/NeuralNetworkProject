/*
 * Vector.h
 *
 *  Created on: May 1, 2013
 *      Author: ah1411
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>

#include "indextypes.h"
#include "nnexceptions.h"

namespace art2nn {

template<class T> class Vector;
template<class T> Vector<T> operator+(const Vector<T>&, const Vector<T>&);
template<class T> Vector<T> operator-(const Vector<T>&, const Vector<T>&);
template<class T> Vector<T> operator*(T, const Vector<T>&);
template<class T> Vector<T> operator*(const Vector<T>&, T);
template<class T> Vector<T> operator/(const Vector <T>&, T);
template<class T> T operator*(const Vector<T>&, const Vector<T>&);
template<class T> bool operator==(const Vector<T>&, const Vector<T>&);
template<class T> bool operator!=(const Vector<T>&, const Vector<T>&);

template<class T>
class Vector {
public:
	Vector();
	Vector(const Vector<T> &vector);
	explicit Vector(dimension n);
	Vector(dimension n, T *array);
	virtual ~Vector();

	friend Vector<T> operator-<>(const Vector<T> &left, const Vector<T> &right);
	friend Vector<T> operator+<>(const Vector<T> &left, const Vector<T> &right);
	friend Vector<T> operator*<>(T left, const Vector<T> &right);
	friend Vector<T> operator*<>(const Vector<T> &left, T right);
	friend Vector<T> operator/<>(const Vector<T> &left, T right);
	friend T operator*<>(const Vector<T> &left, const Vector<T> &right);
	friend bool operator==<>(const Vector<T> &left, const Vector<T> &right);
	friend bool operator!=<>(const Vector<T> &left, const Vector<T> &right);

	Vector<T> &operator=(const Vector<T> &vector);
	Vector<T> &operator+=(const Vector<T> &vector);
	Vector<T> &operator-=(const Vector<T> &vector);
	Vector<T> &operator*=(T scalar);
	Vector<T> &operator/=(T scalar);
	Vector<T> operator-() const;
	T &operator[](index i);
	const T &operator[](index i) const;

	T norm() const;
	Vector<T> project(dimension m) const;

	dimension dim() const { return n; };

private:
	dimension n;
	T *coords;
};

template<class T>
Vector<T>::Vector():
	n(0), coords(NULL) {
}

template<class T>
Vector<T>::Vector(const Vector<T> &vector):
	n(vector.n), coords(NULL) {
	if (n > 0) {
		coords = new T[n];
		for (index i = 0; i < n; ++i)
			coords[i] = vector.coords[i];
	}
}

template<class T>
Vector<T>::Vector(dimension n):
	n(n), coords(NULL) {
	if (n > 0) {
		coords = new T[n];
		for (index i = 0; i < n; ++i)
			coords[i] = 0;
	}
}

template<class T>
Vector<T>::Vector(dimension n, T *array):
	n(n), coords(NULL) {
	if (n > 0) {
		coords = new T[n];
		for (index i = 0; i < n; ++i)
			coords[i] = array[i];
	}
}

template<class T>
Vector<T>::~Vector() {
	if (coords != NULL)
		delete coords;
}

template<class T>
Vector<T> operator+(const Vector<T> &left, const Vector<T> &right) {
	if (left.n != right.n)
		throw dimension_error("cannot add vectors of different dimensions");
	Vector<T> sum(left);
	return sum += right;
}

template<class T>
Vector<T> operator-(const Vector<T> &left, const Vector<T> &right) {
	if (left.n != right.n)
		throw dimension_error("cannot subtract vectors of different dimensions");
	Vector<T> difference(left);
	return difference -= right;
}

template<class T>
Vector<T> operator*(T left, const Vector<T> &right) {
	Vector<T> product(right);
	return product *= left;
}

template<class T>
Vector<T> operator*(const Vector<T> &left, T right) {
	return right * left;
}

template<class T>
Vector<T> operator/(const Vector<T> &left, T right) {
	return left * (1/right);
}

template<class T>
T operator*(const Vector<T> &left, const Vector<T> &right) {
	if (left.n != right.n)
		throw dimension_error("cannot take the dot product of vectors of different dimensions");
	T product = 0.0;
	for (index i = 0; i < left.n; ++i)
		product += left.coords[i] * right.coords[i];
	return product;
}

template<class T>
bool operator==(const Vector<T> &left, const Vector<T> &right) {
	if (left.n != right.n)
		return false;
	for (index i = 0; i < left.n; ++i) {
		if (left.coords[i] != right.coords[i])
			return false;
	}
	return true;
}

template<class T>
bool operator!=(const Vector<T> &left, const Vector<T> &right) {
	return !(left == right);
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vector) {
	if (this != &vector) {
		if (n != vector.n) {
			n = vector.n;
			delete coords;
			coords = new T[n];
		}
		for (index i = 0; i < n; ++i)
			coords[i] = vector.coords[i];
	}
	return *this;
}

template<class T>
Vector<T> &Vector<T>::operator+=(const Vector<T> &vector) {
	if (n != vector.n)
		throw dimension_error("vector dimensions must be equal to add");

	for (index i = 0; i < n; ++i)
		coords[i] += vector.coords[i];
	return *this;
}

template<class T>
Vector<T> &Vector<T>::operator-=(const Vector<T> &vector) {
	if (n != vector.n)
		throw dimension_error("vector dimensions must be equal to subtract");

	for (index i = 0; i < n; ++i)
		coords[i] -= vector.coords[i];
	return *this;
}

template<class T>
Vector<T> &Vector<T>::operator*=(T scalar) {
	for (index i = 0; i < n; ++i)
		coords[i] *= scalar;
	return *this;
}

template<class T>
Vector<T> &Vector<T>::operator/=(T scalar) {
	for (index i = 0; i < n; ++i)
		coords[i] /= scalar;
	return *this;
}

template<class T>
Vector<T> Vector<T>::operator-() const {
	Vector negation(n);
	for (index i = 0; i < n; ++i)
		negation.coords[i] = -coords[i];
	return negation;
}

template<class T>
T &Vector<T>::operator[](index i) {
	if (i >= n)
		throw dimension_error("index beyond vector dimensions");
	return coords[i];
}

template<class T>
const T &Vector<T>::operator[](index i) const {
	if (i >= n)
		throw dimension_error("index beyond vector dimensions");
	return coords[i];
}

template<class T>
T Vector<T>::norm() const {
	T norm = 0;
	for (index i = 0; i < n; ++i)
		norm += coords[i] * coords[i];
	return sqrt(norm);
}

template<class T>
Vector<T> Vector<T>::project(dimension m) const {
	if (m != n) {
		Vector projection(m);
		dimension min = (n > m) ? m : n;

		for (index i = 0; i < min; ++i)
			projection.coords[i] = coords[i];
		return projection;
	}
	return *this;
}

} /* namespace art2nn */

#endif /* VECTOR_H_ */
