#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Workaround para definid operator>> e operator<< com template
template <class Tvalor>
class Matrix;

template <class Tvalor>
ostream &operator<<(ostream &os, const Matrix<Tvalor> &mat);

template <class Tvalor>
istream &operator>>(istream &is, Matrix<Tvalor> &mat);
// Fim do workaround

template <class Tvalor = double>
class Matrix {
 private:
  Tvalor *m;
  int rows;
  int cols;
  friend ostream &operator<<<>(ostream &os, const Matrix<Tvalor> &mat);
  friend istream &operator>><>(istream &is, Matrix<Tvalor> &mat);

 public:
  // Construtor default
  Matrix() : rows(0), cols(0), m(new Tvalor(0)){};
  // Construtor de matriz cujos elementos sao todos iguais a <val>
  Matrix(int t_rows, int t_cols, const Tvalor &val = 0.0)
      : rows(t_rows), cols(t_cols), m(new Tvalor[t_rows * t_cols]) {
    for (int i = 0; i < t_rows * t_cols; i++) {
      m[i] = val;
    }
  };
  // Construtor de matriz cujos elementos sao dados por um ponteiro
  Matrix(int t_rows, int t_cols, const Tvalor *vec)
      : rows(t_rows), cols(t_cols), m(new Tvalor[t_rows * t_cols]) {
    for (int i = 0; i < t_rows * t_cols; i++) {
      m[i] = vec[i];
    }
  };
  // Construtor de matriz cujos elementos sao dados por um vetor
  Matrix(int t_rows, int t_cols, const vector<Tvalor> &vec)
      : rows(t_rows), cols(t_cols), m(new Tvalor[t_rows * t_cols]) {
    for (int i = 0; i < t_rows * t_cols; i++) {
      if (i < vec.size())
        m[i] = vec.at(i);
      else
        m[i] = 0;
    }
  };
  // Construtor por copia
  Matrix(const Matrix<Tvalor> &mat)
      : rows(mat.rows), cols(mat.cols), m(new Tvalor[mat.rows * mat.cols]) {
    for (int i = 0; i < mat.cols * mat.rows; i++) {
      m[i] = mat.m[i];
    }
  };
  // Construtor por arquivo
  Matrix(ifstream &myFile);
  // Destrutor
  ~Matrix() {
    cout << "~Matrix()" << endl;
    delete[] m;
  };

  // Getters
  //  Retorna o numero de linhas da matriz
  int getRows() const;
  // Retorna o numero de colunas da matriz
  int getCols() const;
  // Retorna o elemento da posicao (row, col) da matriz
  Tvalor get(int row, int col) const;

  // Setters
  //  Trocar as dimensoes da matriz.
  void reshape(int row, int col);

  // Operators
  //  Acesso a elementos, com primeiro indice = 1
  Tvalor &operator()(int row, int col);
  //  Atribuicao
  Matrix &operator=(const Matrix &mat);
  // Soma de matrizes
  Matrix operator+(const Matrix &mat) const;
  // Soma de matrizes com atribuicao
  Matrix operator+=(const Matrix &mat);
  // Subtracao de matrizes
  Matrix operator-(const Matrix &mat) const;
  // Subtracao de matrizes com atribuicao
  Matrix operator-=(const Matrix &mat);
  // Multiplicao de matriz por constante
  Matrix operator*(const Tvalor &val) const;
  // Multiplicao de matriz por constante, com atribuicao
  Matrix operator*=(const Tvalor &val);
  // Multiplicao de matrizes
  Matrix operator*(const Matrix &mat) const;
  // Multiplicao de matrizes com atribuicao
  Matrix operator*=(const Matrix &mat);
  // Transposicao de matriz
  Matrix operator~() const;
  // Comparacao de matrizes
  bool operator==(const Matrix &mat) const;
  bool operator!=(const Matrix &mat) const;
};

template <class Tvalor>
Matrix<Tvalor>::Matrix(ifstream &myFile) {
  Tvalor *m_tmp = new Tvalor[0];
  Tvalor tmp;
  int r = 1, c = 0, last = 0, counter = 0;

  while (myFile >> tmp) {
    counter++;
    c++;
    if (myFile.peek() == '\n') {
      r++;
      if (last == 0 || c == last)
        last = c;
      else if (last != 0 && c != last)
        throw invalid_argument(
            "Inconsistent number of columns. The file must contain column "
            "elements separated by white spaces and row elements separated by "
            "line breaks.");
      c = 0;
    }
    Tvalor *aux = new Tvalor[counter];
    copy(m_tmp, m_tmp + counter - 1, aux);
    aux[counter - 1] = tmp;
    delete[] m_tmp;
    m_tmp = aux;
    aux = nullptr;
  }
  if (counter != c * r) {
    throw invalid_argument(
        "Inconsistent number of columns. The file must contain column elements "
        "separated by white spaces and row elements separated by line breaks.");
  }
  rows = r;
  cols = last;
  m = m_tmp;
  m_tmp = nullptr;
}

template <class Tvalor>
inline int Matrix<Tvalor>::getRows() const {
  return rows;
}

template <class Tvalor>
inline int Matrix<Tvalor>::getCols() const {
  return cols;
}

template <class Tvalor>
inline Tvalor Matrix<Tvalor>::get(int row, int col) const {
  if (rows < row || cols < col || col < 1 || row < 1)
    throw invalid_argument("Index out of bounds.");
  return m[(cols * (row - 1) + (col - 1))];
}

template <class Tvalor>
inline void Matrix<Tvalor>::reshape(int row, int col) {
  if (col < 1 || row < 1)
    throw invalid_argument("Matrix must have positive dimensions");
  else if (row * col != rows * cols && (rows != 0 && cols != 0))
    throw invalid_argument(
        "Incompatible dimensions. New shape should retain the number of "
        "elements");
  else {
    rows = row;
    cols = col;
  }
}

template <class Tvalor>
ostream &operator<<(ostream &os, const Matrix<Tvalor> &mat) {
  for (int counter = 0; counter < mat.rows * mat.cols; counter++) {
    Tvalor i = mat.m[counter];
    if (!(counter % mat.cols)) {
      os << " | ";
    }
    if (!((counter + 1) % mat.cols)) {
      os << i << " |\n";
    } else {
      os << i << "    ";
    }
  }
  return os;
}

template <class Tvalor>
istream &operator>>(istream &is, Matrix<Tvalor> &mat) {
  Tvalor *m_tmp = new Tvalor[0];
  Tvalor tmp;
  int elements = 0;
  while (is >> tmp) {
    elements++;
    Tvalor *aux = new Tvalor[elements];
    copy(m_tmp, m_tmp + elements - 1, aux);
    aux[elements - 1] = tmp;
    delete[] m_tmp;
    m_tmp = aux;
    aux = nullptr;
    if (cin.peek() == '\n') {
      cin.clear(ios::eofbit);
    }
  }
  if (mat.cols == 0 or mat.rows == 0) {
    cout << "WARNING: current <rows> and/or <cols> of Matrix are set to 0. "
            "Creating a "
         << elements << " x 1 matrix." << endl;
    mat.cols = elements;
    mat.rows = 1;
  } else if (elements != (mat.rows * mat.cols)) {
    throw invalid_argument("Number of elements should be equal to rows * cols");
  }
  mat.m = m_tmp;
  m_tmp = nullptr;
  return is;
}

template <class Tvalor>
inline Tvalor &Matrix<Tvalor>::operator()(int row, int col) {
  if (rows < row || cols < col || col < 1 || row < 1)
    throw invalid_argument("Index out of bounds.");
  return m[(cols * (row - 1) + (col - 1))];
}

template <class Tvalor>
Matrix<Tvalor> &Matrix<Tvalor>::operator=(const Matrix &mat) {
  if (this != &mat) {
    rows = mat.rows;
    cols = mat.cols;
    m = nullptr;
    m = new Tvalor[mat.cols * mat.rows];
    copy(mat.m, mat.m + (mat.cols * mat.rows), m);
  }
  return *this;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator+(const Matrix<Tvalor> &mat) const {
  if (this->cols != mat.cols || this->rows != mat.rows)
    throw invalid_argument("Matrices must have equal dimensions");
  Tvalor *tmp = new Tvalor[this->cols * this->rows];
  for (int i = 0; i < (this->cols * this->rows); i++) {
    tmp[i] = this->m[i] + mat.m[i];
  }
  return Matrix(rows, cols, tmp);
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator+=(const Matrix<Tvalor> &mat) {
  if (this->cols != mat.cols || this->rows != mat.rows)
    throw invalid_argument("Matrices must have equal dimensions");
  for (int i = 0; i < (this->cols * this->rows); i++) {
    this->m[i] += mat.m[i];
  }
  return *this;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator-(const Matrix<Tvalor> &mat) const {
  if (this->cols != mat.cols || this->rows != mat.rows)
    throw invalid_argument("Matrices must have equal dimensions");
  Tvalor *tmp = new Tvalor[this->cols * this->rows];
  for (int i = 0; i < (this->cols * this->rows); i++) {
    tmp[i] = this->m[i] - mat.m[i];
  }
  return Matrix(rows, cols, tmp);
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator-=(const Matrix<Tvalor> &mat) {
  if (this->cols != mat.cols || this->rows != mat.rows)
    throw invalid_argument("Matrices must have equal dimensions");
  for (int i = 0; i < (this->cols * this->rows); i++) {
    this->m[i] -= mat.m[i];
  }
  return *this;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator*(const Tvalor &val) const {
  Tvalor *tmp = new Tvalor[cols * rows];
  for (int i = 0; i < (cols * rows); i++) {
    tmp[i] = val * this->m[i];
  }
  return Matrix<Tvalor>(rows, cols, tmp);
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator*=(const Tvalor &val) {
  for (int i = 0; i < (cols * rows); i++) {
    this->m[i] *= val;
  }
  return *this;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator*(const Matrix &mat) const {
  if (cols != mat.rows) {
    throw invalid_argument(
        "The number of columns in the first matrix must be equal to the number "
        "of rows in the second matrix.");
  }
  Matrix m3(rows, mat.cols, 0.0);
  for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= mat.cols; j++) {
      for (int k = 1; k <= mat.rows; k++) {
        m3(i, j) += mat.get(k, j) * get(i, k);
      }
    }
  }
  return m3;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator*=(const Matrix &mat) {
  if (cols != mat.rows) {
    throw invalid_argument(
        "The number of columns in the first matrix must be equal to the number "
        "of rows in the second matrix.");
  }
  Matrix m3(rows, mat.cols, 0.0);
  for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= mat.cols; j++) {
      for (int k = 1; k <= mat.rows; k++) {
        m3(i, j) += mat.get(k, j) * get(i, k);
      }
    }
  }
  m = m3.m;
  cols = mat.cols;
  return *this;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator~() const {
  Tvalor *aux = new Tvalor[cols * rows];
  for (int counter = 0; counter < cols * rows; counter++) {
    int k = counter / cols;
    int j = (counter - (k * cols)) * (rows) + k;
    aux[j] = m[counter];
  }
  return Matrix<Tvalor>(cols, rows, aux);
}

template <class Tvalor>
bool Matrix<Tvalor>::operator==(const Matrix<Tvalor> &mat) const {
  bool tmp = (rows == mat.rows && cols == mat.cols);
  bool ret = true;
  if (tmp) {
    for (int i = 0; i < cols * rows; i++) {
      ret = ret && (m[i] == mat.m[i]);
    }
  }
  ret = ret && tmp;
  return ret;
}

template <class Tvalor>
bool Matrix<Tvalor>::operator!=(const Matrix<Tvalor> &mat) const {
  bool tmp = (rows != mat.rows || cols != mat.cols);
  bool ret = true;
  if (!tmp) {
    for (int i = 0; i < cols * rows; i++) {
      ret = ret && (m[i] != mat.m[i]);
    }
  }
  ret = ret || tmp;
  return ret;
}

#endif