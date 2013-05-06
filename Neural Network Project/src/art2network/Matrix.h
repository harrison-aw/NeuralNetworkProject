/*
 * Matrix.h
 *
 *  Created on: May 1, 2013
 *      Author: Tony
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "indextypes.h"
#include "nnexceptions.h"
#include "Vector.h"

namespace art2nn {

template<class T> class Matrix;
template<class T> Matrix<T> operator+(const Matrix<T>&, const Matrix<T>&);
template<class T> Matrix<T> operator-(const Matrix<T>&, const Matrix<T>&);
template<class T> Matrix<T> operator*(T, const Matrix<T>&);
template<class T> Matrix<T> operator*(const Matrix<T>&, T);
template<class T> Vector<T> operator*(const Matrix<T>&, const Vector<T>&);
template<class T> Vector<T> operator*(const Vector<T>&, const Matrix<T>&);
template<class T> Matrix<T> operator*(const Matrix<T>&, const Matrix<T>&);
template<class T> bool operator==(const Matrix<T>&, const Matrix<T>&);
template<class T> bool operator!=(const Matrix<T>&, const Matrix<T>&);

template<class T>
class Matrix {
public:
	Matrix();
	Matrix(const Matrix<T> &matrix);
	Matrix(dimension n, dimension m);
	virtual ~Matrix();

	friend Matrix<T> operator+<>(const Matrix<T> &left, const Matrix<T> &right);
	friend Matrix<T> operator-<>(const Matrix<T> &left, const Matrix<T> &right);
	friend Matrix<T> operator*<>(T left, const Matrix<T> &right);
	friend Matrix<T> operator*<>(const Matrix<T> &left, T right);
	friend Vector<T> operator*<>(const Matrix<T>&, const Vector<T>&);
	friend Vector<T> operator*<>(const Vector<T>&, const Matrix<T>&);
	friend Matrix<T> operator*<>(const Matrix<T>&, const Matrix<T>&);

	friend bool operator==<>(const Matrix<T> &left, const Matrix<T> &right);
	friend bool operator!=<>(const Matrix<T> &left, const Matrix<T> &right);

	Matrix<T> &operator=(const Matrix &matrix);
	Matrix<T> &operator+=(const Matrix &matrix);
	Matrix<T> &operator-=(const Matrix &matrix);
	Matrix<T> operator-() const;

	T operator()(index i, index j) const;
	T operator()(index i, index j, T entry);

	Matrix<T> transpose() const;
	void resize(dimension new_n, dimension new_m);

	Vector<T> row(index i) const { return Vector<T>(m, entries[i]); }
	Vector<T> column(index j) const { return Vector<T>(n, transposed_entries[j]); }

	dimension row_dim() const { return m; };
	dimension col_dim() const { return n; };

private:
	void buildTransposedEntries();

	dimension n;
	dimension m;
	T **entries;
	T **transposed_entries;
};

template<class T>
Matrix<T>::Matrix():
	n(0), m(0), entries(NULL), transposed_entries(NULL) {
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &matrix):
	n(matrix.n), m(matrix.m), entries(NULL), transposed_entries(NULL) {
	if (n > 0 && m > 0) {
		entries = new T*[n];
		for (index i = 0; i < n; ++i) {
			entries[i] = new T[m];
			for (index j = 0; j < m; ++j)
				entries[i][j] = matrix.entries[i][j];
		}
		buildTransposedEntries();
	}
}

template<class T>
Matrix<T>::Matrix(dimension n, dimension m):
	n(n), m(m), entries(NULL), transposed_entries(NULL) {
	if (n > 0 && m > 0) {
		entries = new T*[n];
		for (index i = 0; i < n; ++i) {
			entries[i] = new T[m];
			for (index j = 0; j < m; ++j)
				entries[i][j] = 0;
		}
		buildTransposedEntries();
	}
}

template<class T>
Matrix<T>::~Matrix() {
	if (n > 0 && m > 0) {
		for (index i = 0; i < n; ++i)
			delete entries[i];
		delete entries;
		for (index j = 0; j < m; ++j)
			delete transposed_entries[j];
		delete transposed_entries;
	}
}

template<class T>
Matrix<T> operator+(const Matrix<T> &left, const Matrix<T> &right) {
	Matrix<T> sum(left);
	return sum += right;
}

template<class T>
Matrix<T> operator-(const Matrix<T> &left, const Matrix<T> &right) {
	Matrix<T> difference(left);
	return difference -= right;
}

template<class T>
Matrix<T> operator*(T left, const Matrix<T> &right) {
	Matrix<T> product(right);
	for (index i = 0; i < right.n; ++i) {
		for (index j = 0; j < right.m; ++j) {
			right.entries[i][j] *= left;
			right.transposed_entries[j][i] *= left;
		}
	}
	return product;
}

template<class T>
Matrix<T> operator*(const Matrix<T> &left, T right) {
	return right * left;
}

template<class T>
Vector<T> operator*(const Matrix<T> &left, const Vector<T> &right) {
	if (left.m != right.dim())
		throw dimension_error("number of columns in matrix and dimension of vector must match to multiply");

	Vector<T> product(left.m);
	for (index j = 0; j < left.m; ++j)
		product[j] = left.column(j) * right;
	return product;
}

template<class T>
Vector<T> operator*(const Vector<T> &left, const Matrix<T> &right) {
	if (left.dim() != right.n)
		throw dimension_error("dimension of vector and number of rows in matrix must match to multiply");

	Vector<T> product(right.n);
	for (index i = 0; i < right.n; ++i)
		product[i] = left * right.row(i);
	return product;
}

template<class T>
Matrix<T> operator*(const Matrix<T> &left, const Matrix<T> &right) {
	if (left.m != left.n)
		throw dimension_error("number of columns in left matrix must match number of rows in right matrix");

	Matrix<T> product(left.n, right.m);
	for (index i = 0; i < left.n; ++i) {
		for (index j = 0; j < right.m; ++j)
			product.transposed_entries[j][i] = product.entries[i][j] = left.row(i) * right.column(j);
	}
	return product;
}

template<class T>
bool operator==(const Matrix<T> &left, const Matrix<T> &right) {
	if (left.n != right.n || left.m != right.m)
		return false;
	for (index i = 0; i < left.n; ++i) {
		for (index j = 0; j < left.m; ++j) {
			if (left.entries[i][j] != right.entries[i][j])
				return false;
		}
	}
	return true;
}

template<class T>
bool operator!=(const Matrix<T> &left, const Matrix<T> &right) {
	return !(left == right);
}

template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix) {
	if (this != &matrix) {
		if (n > 0 && m > 0 && n != matrix.n && m != matrix.m) {
			for (index i = 0; i < n; ++i)
				delete entries[i];
			delete entries;
			for (index j = 0; j < m; ++j)
				delete transposed_entries[j];
			delete transposed_entries;
		}

		n = matrix.n;
		m = matrix.m;
		entries = new T*[n];
		for (index i = 0; i < n; ++i) {
			entries[i] = new T[m];
			for (index j = 0; j < m; ++j)
				entries[i][j] = matrix.entries[i][j];
		}
		buildTransposedEntries();
	}
	return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &matrix) {
	if (n != matrix.n || m != matrix.m)
		throw dimension_error("cannot add matrices of different sizes");
	for (index i = 0; i < n; ++i) {
		for (index j = 0; j < m; ++j) {
			entries[i][j] += matrix.entries[i][j];
			transposed_entries[j][i] += matrix.transposed_entries[j][i];
		}
	}
	return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &matrix) {
	if (n != matrix.n || m != matrix.m)
		throw dimension_error("cannot subtract matrices of different sizes");
	for (index i = 0; i < n; ++i) {
		for (index j = 0; j < m; ++j) {
			entries[i][j] -= matrix.entries[i][j];
			transposed_entries[j][i] -= matrix.transposed_entries[j][i];
		}
	}
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::operator-() const {
	Matrix<T> negation(*this);
	for (index i = 0; i < n; ++i) {
		for (index j = 0; j < m; ++j)
			transposed_entries[j][i] = entries[i][j] = -entries[i][j];
	}
	return negation;
}

template<class T>
T Matrix<T>::operator()(index i, index j) const {
	return entries[i][j];
}

template<class T>
T Matrix<T>::operator()(index i, index j, T entry) {
	return transposed_entries[j][i] = entries[i][j] = entry;
}

template<class T>
void Matrix<T>::buildTransposedEntries() {
	transposed_entries = new T*[m];
	for (index j = 0; j < m; ++j) {
		transposed_entries[j] = new T[n];
		for (index i = 0; i < n; ++i)
			transposed_entries[j][i] = entries[i][j];
	}
}

template<class T>
Matrix<T> Matrix<T>::transpose() const {
	Matrix<T> transpose(*this);
	T **temp;
	temp = transpose.transposed_entries;
	transpose.transposed_entries = transpose.entries;
	transpose.entries = temp;
	return transpose;
}

template<class T>
void Matrix<T>::resize(dimension new_n, dimension new_m) {
	if (new_n != n || new_m != m) {
		T **new_entries, **new_transposed_entries;

		index min_n = (n < new_n) ? n : new_n;
		index min_m = (m < new_m) ? m : new_m;

		new_entries = new T*[new_n];
		for (index i = 0; i < new_n; ++i) {
			new_entries[i] = new T[new_m];
			for (index j = 0; j < min_m; ++j) {
				if (i < n)
					new_entries[i][j] = entries[i][j];
			}
			if (i < n)
				delete entries[i];
		}
		delete entries;
		entries = new_entries;

		new_transposed_entries = new T*[new_m];
		for (index j = 0; j < new_m; ++j) {
			new_transposed_entries[j] = new T[new_m];
			for (index i = 0; i < min_n; ++i) {
				if (j < m)
					new_transposed_entries[j][i] = transposed_entries[j][i];
			}
			if (j < m)
				delete transposed_entries[j];
		}
		delete transposed_entries;
		transposed_entries = new_transposed_entries;

		n = new_n;
		m = new_m;
	}
}

} /* namespace art2nn */
#endif /* MATRIX_H_ */
