#pragma once

#include <string>
#include <cstddef>

namespace MatrixUtils {

	enum CONSTANTS { INFINITE = 2000 };

	class Matrix {
		public:
			const std::size_t size;

			/* * * * * * * * * * 
			 *                 *
			 * Read and Write  *
			 *                 *
			 * * * * * * * * * */
			constexpr int get(std::size_t row, std::size_t col) const;
			constexpr void set(std::size_t row, std::size_t col, int value);
			constexpr void fill(int value = 0);

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
			constexpr void floyds(Matrix &P_Matrix);
			void path(std::size_t start_vertex, std::size_t end_vertex) const;

			/* * * * * * * * * * 
			 *                 *
			 *    Overloads    *
			 *                 *
			 * * * * * * * * * */
			constexpr int* operator[](std::size_t col);

			/* * * * * * * * * * 
			 *   Constuctors   *
			 *       and       *
			 *   Destructors   *
			 * * * * * * * * * */
			Matrix(const std::size_t size);
			Matrix(const Matrix &other);
			~Matrix();

		private:
			int** data;
	};

}
