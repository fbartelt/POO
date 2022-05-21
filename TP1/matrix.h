#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

template <class Tvalor>
class Matrix;

template <class Tvalor>
ostream &operator<<(ostream &os, const Matrix<Tvalor> &mat);

template <class Tvalor>
istream &operator>>(istream &is, Matrix<Tvalor> &mat);

template <class Tvalor = double>
class Matrix {
 private:
  vector<Tvalor> m;
  int rows;
  int cols;
  friend ostream &operator<<<>(ostream &os, const Matrix<Tvalor> &mat);
  friend istream &operator>><>(istream &is, Matrix<Tvalor> &mat);

 public:
  // Construtor default
  Matrix() : rows(0), cols(0), m(vector<Tvalor>(0, 0)){};
  // Construtor de matriz cujos elementos sao todos iguais a <val>
  Matrix(int t_rows, int t_cols, const Tvalor &val = 0.0)
      : rows(t_rows), cols(t_cols), m(vector<Tvalor>(t_rows * t_cols, val)){};
  // Construtor de matriz cujos elementos sao dados por um vetor 1D
  Matrix(int t_rows, int t_cols, const vector<Tvalor> &vec)
      : rows(t_rows), cols(t_cols), m(vec) {
    while (m.size() < rows * cols) {
      m.push_back(0.0);
    }
  };
  // Construtor por copia
  Matrix(const Matrix<Tvalor> &mat)
      : rows(mat.rows), cols(mat.cols), m(mat.m){};
  // Construtor por arquivo
  Matrix(ifstream &myFile);
  // Destrutor
  ~Matrix(){};

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
  vector<Tvalor> m_tmp;
  Tvalor tmp;
  int r = 1, c = 0, last = -1;

  while (myFile >> tmp) {
    c++;
    if (myFile.peek() == '\n') {
      r++;
      if (last == -1 || c == last)
        last = c;
      else if (last != -1 && c != last)
        throw invalid_argument(
            "Inconsistent number of columns. The file must contain column "
            "elements separated by white spaces and row elements separated by "
            "line breaks.");
      c = 0;
    }
    m_tmp.push_back(tmp);
  }
  if (m_tmp.size() != last * r)
    throw invalid_argument(
        "Inconsistent number of columns. The file must contain column elements "
        "separated by white spaces and row elements separated by line breaks.");
  // cout << "r: " << r << endl;
  // cout << "c: " << last << endl;
  rows = r;
  cols = last;
  m = m_tmp;
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
  return m.at(cols * (row - 1) + (col - 1));
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
  int counter = 0;

  for (Tvalor i : mat.m) {
    if (!(counter % mat.cols)) {
      os << " | ";
    }

    counter++;
    //    os << "" << i << "\t";

    if (!(counter % mat.cols) && counter != 0) {
      os << i << " |\n";
    } else {
      // os << "";
      os << i << "    ";
    }
  }
  return os;
}

template <class Tvalor>
istream &operator>>(istream &is, Matrix<Tvalor> &mat) {
  Tvalor tmp;
  vector<Tvalor> tmp_vec;
  int elements = 0;
  while (is >> tmp) {
    tmp_vec.push_back(tmp);
    elements++;
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
  mat.m.swap(tmp_vec);
  return is;
}

template <class Tvalor>
inline Tvalor &Matrix<Tvalor>::operator()(int row, int col) {
  if (rows < row || cols < col || col < 1 || row < 1)
    throw invalid_argument("Index out of bounds.");
  return m.at(cols * (row - 1) + (col - 1));
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator+(const Matrix<Tvalor> &mat) const {
  Matrix<Tvalor> tmp(*this);
  transform(tmp.m.begin(), tmp.m.end(), mat.m.begin(), tmp.m.begin(),
            plus<Tvalor>());
  return tmp;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator+=(const Matrix<Tvalor> &mat) {
  transform(m.begin(), m.end(), mat.m.begin(), m.begin(), plus<Tvalor>());
  return *this;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator-(const Matrix<Tvalor> &mat) const {
  Matrix<Tvalor> tmp(*this);
  transform(tmp.m.begin(), tmp.m.end(), mat.m.begin(), tmp.m.begin(),
            minus<Tvalor>());
  return tmp;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator~() const {
  vector<Tvalor> vec(cols * rows, 0);
  int counter = 0;
  for (auto i : m) {
    int k = counter / cols;
    int j = (counter - (k * cols)) * (rows) + k;
    // cout << counter << "  " << k << "  " << j << endl;
    vec[j] = i;
    counter++;
  }
  Matrix<Tvalor> transposed(cols, rows, vec);
  return transposed;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator-=(const Matrix<Tvalor> &mat) {
  transform(m.begin(), m.end(), mat.m.begin(), m.begin(), minus<Tvalor>());
  return *this;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator*(const Tvalor &val) const {
  Matrix<Tvalor> m2(*this);
  vector<Tvalor> vec(rows * cols, val);
  transform(m2.m.begin(), m2.m.end(), vec.begin(), m2.m.begin(),
            multiplies<Tvalor>());
  return m2;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator*=(const Tvalor &val) {
  vector<Tvalor> vec(rows * cols, val);
  transform(m.begin(), m.end(), vec.begin(), m.begin(), multiplies<Tvalor>());
  return *this;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator*(const Matrix &mat) const {
  if (cols != mat.rows)
    throw invalid_argument(
        "The number of columns in the first matrix must be equal to the number "
        "of rows in the second matrix.");
  Matrix m3(rows, mat.cols, 0.0);
  for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= mat.cols; j++) {
      for (int k = 1; k <= mat.rows; k++) {
        // m3(i, j) += mat(k, j) * this->operator()(i, k);
        m3(i, j) += mat.get(k, j) * get(i, k);
        // cout << "A[" << i << ", " << j << "] = " <<"x[" << i << ", " << k <<
        // "] * y[" << k << ", " << j << "]" << endl; cout << " " << m3(i, j) <<
        // " =\t " << this->operator()(i, k) << "  " << mat(k, j) << endl;
      }
    }
  }
  return m3;
}

template <class Tvalor>
Matrix<Tvalor> Matrix<Tvalor>::operator*=(const Matrix &mat) {
  if (cols != mat.rows)
    throw invalid_argument(
        "The number of columns in the first matrix must be equal to the number "
        "of rows in the second matrix.");
  Matrix m3(rows, mat.cols, 0.0);
  for (int i = 1; i <= rows; i++) {
    for (int j = 1; j <= mat.cols; j++) {
      for (int k = 1; k <= mat.rows; k++) {
        // m3(i, j) += mat(k, j) * this->operator()(i, k);
        m3(i, j) += mat.get(k, j) * get(i, k);
      }
    }
  }
  m = m3.m;
  cols = mat.cols;
  return *this;
}

template <class Tvalor>
bool Matrix<Tvalor>::operator==(const Matrix<Tvalor> &mat) const {
  bool ret = (m == mat.m);
  bool tmp = (rows == mat.rows && cols == mat.cols);
  ret = ret && tmp;
  return ret;
}

template <class Tvalor>
bool Matrix<Tvalor>::operator!=(const Matrix<Tvalor> &mat) const {
  bool ret = (m != mat.m);
  bool tmp = (rows != mat.rows || cols != mat.cols);
  ret = ret || tmp;
  return ret;
}

#endif