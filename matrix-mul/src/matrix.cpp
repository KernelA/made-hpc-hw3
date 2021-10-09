#include "matrix.h"

using namespace linalg;

void Matrix::fill(double fill_value) {
  for (size_t i{}; i < elements.size(); ++i) {
    elements[i] = fill_value;
  }
}

Matrix::Matrix(size_t rows, size_t columns)
    : rows(rows), columns(columns), elements(rows * columns, 0.0) {}

Matrix::Matrix(size_t size) : Matrix(size, size) {}

double& Matrix::get(size_t row, size_t col) {
  return this->elements.at(getLinearIndex(row, col));
}

size_t Matrix::getLinearIndex(size_t row, size_t column) const {
  return row * columnCount() + column;
}

const double& Matrix::get(size_t row, size_t col) const {
  return this->elements.at(getLinearIndex(row, col));
}

void Matrix::set(size_t row, size_t col, const double& value) {
  this->elements.at(getLinearIndex(row, col)) = value;
}

void Matrix::checkShapeEquality(const Matrix& other) const {
  if (rows != other.rows || columns != other.columns) {
    throw SizeMismatchException();
  }
}

Matrix& Matrix::operator*=(const Matrix& a) {
  if (columns != a.rows) {
    throw SizeMismatchException();
  }

  Matrix temp(*this);

  this->resize(rows, a.columns);
  fill(0.0);

  for (size_t i{}; i < temp.columnCount(); ++i) {
    for (size_t row{}; row < rowCount(); ++row) {
      for (size_t col{}; col < a.columnCount(); ++col) {
        this->get(row, col) += temp.get(row, i) * a.get(i, col);
      }
    }
  }

  return *this;
}

Matrix Matrix::operator*(const Matrix& a) const {
  Matrix matrix_mult(*this);

  return matrix_mult *= a;
}

void Matrix::resize(size_t new_rows, size_t new_cols) {
  if (new_rows == rowCount() && new_cols == columnCount()) {
    return;
  }

  elements.resize(new_rows * new_cols);
  rows = new_rows;
  columns = new_cols;
}

bool Matrix::operator==(const Matrix& a) const {
  if (rows != a.rows || columns != a.columns) {
    return false;
  }

  for (size_t i{}; i < rows; ++i) {
    for (size_t j{}; j < columns; ++j) {
      if (std::abs(this->get(i, j) - a.get(i, j)) > EPS) {
        return false;
      }
    }
  }

  return true;
}

bool Matrix::operator!=(const Matrix& a) const { return !(*this == a); }

size_t Matrix::rowCount() const { return rows; }

size_t Matrix::columnCount() const { return columns; }

const double* Matrix::getRawData() const { return elements.data(); }

double* Matrix::getRawData() { return elements.data(); }

std::ostream& linalg::operator<<(std::ostream& output, const Matrix& matrix) {
  for (size_t row{}; row < matrix.rowCount(); ++row) {
    size_t column{};
    for (; column < matrix.columnCount() - 1; ++column) {
      output << matrix.get(row, column) << ' ';
    }

    output << matrix.get(row, column) << '\n';
  }

  return output;
}

std::istream& linalg::operator>>(std::istream& input, Matrix& matrix) {
  size_t new_rows{}, new_columns{};
  double elem{};

  input >> new_rows >> new_columns;

  matrix.resize(new_rows, new_columns);

  for (size_t row{}; row < matrix.rowCount(); ++row) {
    for (size_t column{}; column < matrix.columnCount(); ++column) {
      input >> matrix.get(row, column);
    }
  }

  return input;
}