#include "matrix.h"
#include "vector.h"

using namespace linalg;

template <typename SecondOperClass>
void test_perfomance() {
  using std::array;
  using std::cout;
  using std::endl;

  array<size_t, 6> matrix_sizes = {500, 512, 1000, 1024, 2000, 2048};

  for (const auto& matrix_size : matrix_sizes) {
    Matrix a(matrix_size, matrix_size);
    SecondOperClass b(matrix_size);
    auto start = std::chrono::high_resolution_clock::now();
    Matrix c = a * static_cast<const Matrix&>(b);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    cout << "Size: " << matrix_size << " Time elapsed: " << diff.count() << " s"
         << endl;
  }
}

int main(int argc, char** argv) {
  using std::cout;
  using std::endl;

  cout << "Test matrices" << endl;
  test_perfomance<Matrix>();
  cout << "Test vectors" << endl;
  test_perfomance<Vector>();
}