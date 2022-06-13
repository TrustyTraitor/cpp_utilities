#include "MatrixUtils.cpp"
#include <string>
int main() {

	MatrixUtils::Matrix<int> m1(4,3);
	m1.fill(1);

	m1*=2.5;

	m1.print();

	return 0;
}