#pragma once

#include <string>
#include <cstddef>
#include <concepts>

namespace MatrixUtils {

	enum CONSTANTS { INFINITE = 2000 };

	template<typename T>
	concept IsNumeric = std::integral<T> || std::floating_point<T>;

	template<IsNumeric T>
	class Matrix {
		public:
			const std::size_t rowSize;
			const std::size_t colSize;

			/* * * * * * * * * * 
			 *                 *
			 * Read and Write  *
			 *                 *
			 * * * * * * * * * */
			constexpr T get(std::size_t row, std::size_t col) const;
			constexpr void set(std::size_t row, std::size_t col, T value);
			constexpr void fill(T value = 0);

			/* * * * * * * * * * 
			 *                 *
			 *   Matrix Info   *
			 *                 *
			 * * * * * * * * * */
			constexpr int findInDegree(std::size_t vertex) const;
			constexpr int findOutDegree(std::size_t vertex) const;
			void print(std::string title = "") const;

			/* * * * * * * * * * 
			 *                 *
			 *   Algorithms    *
			 *                 *
			 * * * * * * * * * */
			Matrix<T> floyds();
			void path(std::size_t start_vertex, std::size_t end_vertex) const;

			/* * * * * * * * * * 
			 *                 *
			 *    Overloads    *
			 *                 *
			 * * * * * * * * * */
			int* operator[](std::size_t col);
			void operator*=(const IsNumeric auto& mult);
			// Matrix operator*(const int& multiplier) const;
			// Matrix operator*(const Matrix other) const;
			// Matrix operator+(const Matrix other) const;
			// Matrix operator-(const Matrix other) const;

			/* * * * * * * * * * 
			 *   Constuctors   *
			 *       and       *
			 *   Destructors   *
			 * * * * * * * * * */
			Matrix(const std::size_t size);
			Matrix(const std::size_t sizeRow, const std::size_t sizeCol);
			Matrix(const Matrix<T> &other);
			~Matrix();

		private:
			T** data;
	};

}
