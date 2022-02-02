#include "MatrixUtils.hpp"
#include <iostream>

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
MatrixUtils::Matrix::Matrix(const std::size_t S) : size(S){
	data = new int*[size];

	for(std::size_t i = 0; i < size; i++) {
		data[i] = new int[size];
	}
}

/**
 * @brief Construct a new Matrix object from a copy of another matrix
 * 
 * @param other 
 */
MatrixUtils::Matrix::Matrix(const MatrixUtils::Matrix &other) : size(other.size) {
	data = new int*[size];

	for(std::size_t i = 0; i < size; i++) {
		data[i] = new int[size];
	}

	for(std::size_t i = 0; i < size; i++) {
		for(std::size_t j = 0; j < size; j++) {
			data[i][j] = other.data[i][j];
		}
	}
}

/**
 * @brief Destroy the Matrix object
 */
MatrixUtils::Matrix::~Matrix() {
	for(std::size_t i = 0; i < size; i++) {
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
constexpr int MatrixUtils::Matrix::get(std::size_t row, std::size_t col) const {
	return data[row][col];
}

/**
 * @brief sets the passed value at row, col
 * 
 * @param row 0 indexed
 * @param col 0 indexed
 * @param value
 */
constexpr void MatrixUtils::Matrix::set(std::size_t row, std::size_t col, int value) {
	data[row][col] = value;
}

/**
 * @brief Fills the entire matrix with the passed value
 * 
 * @param value defaults to 0
 */
constexpr void MatrixUtils::Matrix::fill(int value) {
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
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
void MatrixUtils::Matrix::print(std::string title) const {
	std::cout << title << "\n";

	std::cout << "\t";
	for(std::size_t i = 0; i < size; i++) {
		std::cout << "v" << i+1 << "\t";
	}
	std::cout << "\n";
	for(std::size_t i = 0; i < size; i++) {
		std::cout << "v" << i+1 << "\t";
		for(int j = 0; j < size; j++) {
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
constexpr int MatrixUtils::Matrix::findInDegree(std::size_t col) const {
	col--; // this is so users can input col 1 instead of 0 when intending for 1
	int in = 0;
	for(std::size_t row = 0; row < size; row++) {
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
constexpr int MatrixUtils::Matrix::findOutDegree(std::size_t row) const {
	row--; // this is so users can input row 1 instead of 0 when intending for 1
	int out = 0;
	for(std::size_t col = 0; col < size; col++) {
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
constexpr int* MatrixUtils::Matrix::operator[](std::size_t idx) {
	return data[idx];
}

/* * * * * * * * * * 
*                 *
*   Algorithms    *
*                 *
* * * * * * * * * */
/**
 * @brief Finds the optimal path beween all points using floyds algorithm. 
 * Outputs a path Matrix to the passed in Matrix obj.
 * 
 * @param P_Matrix 
 */
constexpr void MatrixUtils::Matrix::floyds(MatrixUtils::Matrix &P) { 
	for(std::size_t k = 0; k < size; k++) {
		for(std::size_t i = 0; i < size; i++) {
			for(std::size_t j = 0; j < size; j++) {
				if(data[i][k] + data[k][j] < data[i][j]) {
					P.data[i][j] = k+1;
					data[i][j] = data[i][k] + data[k][j];
				}
			}
		}
	}
}

/**
 * @brief Takes in a start and end vertex and finds all points in between to connect those two points. 
 * Will fail if no path is possible. 
 * Only prints out the inbetween vertexes not the start and end 
 * 
 * @param start_vertex 0 indexed
 * @param end_vertex  0 indexed
 */
void MatrixUtils::Matrix::path(std::size_t start_vertex, std::size_t end_vertex) const {


	if (data[start_vertex][end_vertex] != 0) {
		path(start_vertex, data[start_vertex][end_vertex]-1);
		std::cout << 'v' << data[start_vertex][end_vertex] << ' ';
		path(data[start_vertex][end_vertex]-1, end_vertex);
	}
}
