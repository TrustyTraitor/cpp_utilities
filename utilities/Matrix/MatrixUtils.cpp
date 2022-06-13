#include "MatrixUtils.hpp"
#include <iostream>

using MatrixUtils::IsNumeric;

/* * * * * * * * * * 
*   Constuctors   *
*       and       *
*   Destructors   *
* * * * * * * * * */
/**
 * @brief Construct a new Matrix object with a size
 * 
 * @param size This cannot be changed after initialization
 */
template<IsNumeric T>
MatrixUtils::Matrix<T>::Matrix(const std::size_t S) : rowSize(S), colSize(S){
	data = new T*[rowSize];

	for(std::size_t i = 0; i < rowSize; i++) {
		data[i] = new T[colSize];
	}
}

template<IsNumeric T>
MatrixUtils::Matrix<T>::Matrix(const std::size_t Sr, const std::size_t Sc) : rowSize(Sr), colSize(Sc){
	data = new T*[rowSize];

	for(std::size_t i = 0; i < rowSize; i++) {
		data[i] = new T[colSize];
	}
}

/**
 * @brief Construct a new Matrix object from a copy of another matrix
 * 
 * @param other 
 */
template<IsNumeric TT>
MatrixUtils::Matrix<TT>::Matrix(const Matrix<TT> &other) : rowSize(other.rowSize), colSize(other.colSize) {
	data = new TT*[rowSize];

	for(std::size_t i = 0; i < rowSize; i++) {
		data[i] = new TT[colSize];
	}

	for(std::size_t i = 0; i < rowSize; i++) {
		for(std::size_t j = 0; j < colSize; j++) {
			data[i][j] = other.data[i][j];
		}
	}
}

/**
 * @brief Destroy the Matrix object
 */
template<IsNumeric T>
MatrixUtils::Matrix<T>::~Matrix() {
	for(std::size_t i = 0; i < rowSize; i++) {
		delete[] data[i];
	}
	delete[] data;
}

/* * * * * * * * * * 
*                 *
* Read and Write  *
*                 *
* * * * * * * * * */
/**
 * @brief returns the value at location row, col
 * 
 * @param row 0 indexed
 * @param col 0 indexed
 * @return int 
 */
template<IsNumeric T>
constexpr T MatrixUtils::Matrix<T>::get(std::size_t row, std::size_t col) const {
	return data[row][col];
}

/**
 * @brief sets the passed value at row, col
 * 
 * @param row 0 indexed
 * @param col 0 indexed
 * @param value
 */
template<IsNumeric T>
constexpr void MatrixUtils::Matrix<T>::set(std::size_t row, std::size_t col, T value) {
	data[row][col] = value;
}

/**
 * @brief Fills the entire matrix with the passed value
 * 
 * @param value defaults to 0
 */
template<IsNumeric T>
constexpr void MatrixUtils::Matrix<T>::fill(T value) {
	for(int i = 0; i < rowSize; i++) {
		for(int j = 0; j < colSize; j++) {
			data[i][j] = value;
		}
	}
}

/* * * * * * * * * * 
*                 *
*   Matrix Info   *
*                 *
* * * * * * * * * */
/**
 * @brief Prints the matrix values
 * 
 * @param title optional param that is printed before the matrix
 */
template<IsNumeric T>
void MatrixUtils::Matrix<T>::print(std::string title) const {
	std::cout << title << "\n";

	std::cout << "\t";
	for(std::size_t i = 0; i < colSize; i++) {
		std::cout << "v" << i+1 << "\t";
	}
	std::cout << "\n";
	for(std::size_t i = 0; i < rowSize; i++) {
		std::cout << "v" << i+1 << "\t";
		for(int j = 0; j < colSize; j++) {
			if(data[i][j] == INFINITE)
				std::cout << "INF" << "\t";
			else
				std::cout << data[i][j] << "\t";
		}
		std::cout << '\n';
	}
}

/**
 * @brief Finds the in degree of a vertex and returns it
 * 
 * @param vertex 0 indexed
 * @return int
 */
template<IsNumeric T>
constexpr int MatrixUtils::Matrix<T>::findInDegree(std::size_t col) const {
	col--; // this is so users can input col 1 instead of 0 when intending for 1
	int in = 0;
	for(std::size_t row = 0; row < rowSize; row++) {
		if( row != col ) {
			if (data[row][col] != INFINITE)
				in++;
		} 
	}
	return in;
}

/**
 * @brief Finds the out degree of a vertex and returns it
 * 
 * @param vertex 0 indexed
 * @return int 
 */
template<IsNumeric T>
constexpr int MatrixUtils::Matrix<T>::findOutDegree(std::size_t row) const {
	row--; // this is so users can input row 1 instead of 0 when intending for 1
	int out = 0;
	for(std::size_t col = 0; col < rowSize; col++) {
		if( row != col ) {
			if (data[row][col] != INFINITE)
				out++;
		} 
	}
	return out;
}

/* * * * * * * * * * 
*                 *
*    Overloads    *
*                 *
* * * * * * * * * */
/**
 * @brief Overloads the [] operator to return the array at data[col] but adding the second [row] gives the value
 * 
 * @param col 
 * @return int* 
 */
template<IsNumeric T>
 int* MatrixUtils::Matrix<T>::operator[](std::size_t idx) {
	return data[idx];
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param mult 
 */
template<IsNumeric T>
void MatrixUtils::Matrix<T>::operator*=(const MatrixUtils::IsNumeric auto& mult) {
	for(std::size_t i = 0; i < rowSize; i++) {
		for(std::size_t j = 0; j < colSize; j++) {
			data[i][j] *= mult;
		}
	}
}

/**
 * @brief 
 * 
 * @param multiplier 
 * @return Matrix 
 */
template<IsNumeric T>
MatrixUtils::Matrix<T> operator*(const MatrixUtils::Matrix<T> mat, const MatrixUtils::IsNumeric auto& mult) {

	MatrixUtils::Matrix newMat(mat);

	for(std::size_t i = 0; i < mat.rowSize; i++) {
		for(std::size_t j = 0; j < mat.colSize; j++) {
			newMat[i][j] *= mult;
		}
	}

	return newMat;
}

/**
 * @brief 
 * 
 * @param other 
 * @return Matrix 
 */
template<IsNumeric T>
MatrixUtils::Matrix<T> operator*(const MatrixUtils::Matrix<T>& left, const MatrixUtils::Matrix<T>& right) {
	MatrixUtils::Matrix<T> Matrix<T> newMat(left.rowSize, left.colSize);

	return newMat;
}

/**
 * @brief 
 * 
 * @param other 
 * @return Matrix 
 */
template<IsNumeric T>
MatrixUtils::Matrix<T> operator+(const MatrixUtils::Matrix<T>& left, const MatrixUtils::Matrix<T>& right) {
	MatrixUtils::Matrix<T> Matrix<T> newMat(left.rowSize, left.colSize);

	for (std::size_t i = 0; i < left.rowSize; i++) {
		for (std::size_t j = 0; j < left.colSize; j++) {
			newMat[i][j] = left[i][j] + right[i][j];
		}
	}

	return newMat;
}

/**
 * @brief 
 * 
 * @param other 
 * @return Matrix 
 */
template<IsNumeric T>
MatrixUtils::Matrix<T> operator-(const MatrixUtils::Matrix<T>& left, const MatrixUtils::Matrix<T>& right) {
	MatrixUtils::Matrix<T> Matrix<T> newMat(left.rowSize, left.colSize);

	for (std::size_t i = 0; i < left.rowSize; i++) {
		for (std::size_t j = 0; j < left.colSize; j++) {
			newMat[i][j] = left[i][j] - right[i][j];
		}
	}

	return newMat;
}

/* * * * * * * * * * 
*                 *
*   Algorithms    *
*                 *
* * * * * * * * * */
/**
 * @brief Finds the optimal path beween all points using floyds algorithm. 
 * Outputs a path Matrix.
 * 
 * @param P_Matrix 
 */
template<IsNumeric T>
MatrixUtils::Matrix<T> MatrixUtils::Matrix<T>::floyds() {
	MatrixUtils::Matrix<T> P(rowSize, colSize);

	for(std::size_t k = 0; k < rowSize; k++) {
		for(std::size_t i = 0; i < rowSize; i++) {
			for(std::size_t j = 0; j < rowSize; j++) {
				if(data[i][k] + data[k][j] < data[i][j]) {
					P.data[i][j] = k+1;
					data[i][j] = data[i][k] + data[k][j];
				}
			}
		}
	}

	return P;
}

/**
 * @brief Takes in a start and end vertex and finds all points in between to connect those two points. 
 * Will fail if no path is possible. 
 * Only prints out the inbetween vertexes not the start and end 
 * 
 * @param start_vertex 0 indexed
 * @param end_vertex  0 indexed
 */
template<IsNumeric T>
void MatrixUtils::Matrix<T>::path(std::size_t start_vertex, std::size_t end_vertex) const {
	if (data[start_vertex][end_vertex] != 0) {
		path(start_vertex, data[start_vertex][end_vertex]-1);
		std::cout << 'v' << data[start_vertex][end_vertex] << ' ';
		path(data[start_vertex][end_vertex]-1, end_vertex);
	}
}
