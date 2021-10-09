#include <cassert>

#include "cblas.h"
#include "matrix.h"
#include "stdafx.h"
#include "utils.h"

int main(int argc, char** argv) {
  using std::array;
  using std::cout;
  using std::endl;
  using namespace linalg;

  array<size_t, 3> matrix_sizes = {500, 512, 1024};

  for (const auto& size : matrix_sizes) {
    Matrix a(size, size), b(size, size);
    Matrix c(a.rowCount(), b.columnCount());

    fill_matrix(a);
    fill_matrix(b);

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, c.rowCount(),
                c.columnCount(), a.columnCount(), 1.0, a.getRawData(),
                a.columnCount(), b.getRawData(), b.columnCount(), 0.0,
                c.getRawData(), c.columnCount());

    Matrix d = a * b;

    assert(c == d);
  }

  return 0;
}