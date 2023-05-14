#include <iostream>
#include <vector>

using namespace std;

template <typename T> class Matrix {
public:
  Matrix(T n, T m) { matrix = vector<vector<T>>(n, vector<T>(m, 0)); }
  Matrix(const vector<vector<T>> &vec) { matrix = vec; }

  void print(bool err_mode = true) const {
    for (auto row : matrix) {
      for (auto item : row) {
        if (err_mode) {
          cerr << item << " ";
        } else {
          cout << item << " ";
        }
      }
      if (err_mode) {
        cerr << endl;
      } else {
        cout << endl;
      }
    }
  }
  size_t numRows() const noexcept { return matrix.size(); }
  size_t numCols() const noexcept {
    return matrix.empty() ? 0 : matrix[0].size();
  }

  T get(int r, int c) const { return matrix[r][c]; }
  vector<T> &operator[](int r) { return matrix[r]; }

  Matrix operator*(const Matrix &rhs) const {
    if (matrix[0].size() != rhs.numRows()) {
      throw std::invalid_argument(
          "Incompatible dimensions for matrix multiplication");
    }
    Matrix ret = Matrix(this->numRows(), rhs.numCols());
    for (int i = 0; i < this->numRows(); ++i) {
      for (int j = 0; j < rhs.numCols(); ++j) {
        for (int k = 0; k < this->numCols(); ++k) {
          ret[i][j] += this->get(i, k) * rhs.get(k, j);
        }
      }
    }
    return ret;
  }
  Matrix mul(const Matrix &rhs, int mod) const {
    if (matrix[0].size() != rhs.numRows()) {
      throw std::invalid_argument(
          "Incompatible dimensions for matrix multiplication");
    }
    Matrix ret = Matrix(this->numRows(), rhs.numCols());
    for (int i = 0; i < this->numRows(); ++i) {
      for (int j = 0; j < rhs.numCols(); ++j) {
        for (int k = 0; k < this->numCols(); ++k) {
          ret[i][j] +=
              ((long long)this->get(i, k) % mod * rhs.get(k, j) % mod) % mod;
          if (ret[i][j] >= mod) {
            ret[i][j] -= mod;
          }
        }
      }
    }
    return ret;
  }
  Matrix bigPow(long long p, const int mod) const {
    if (!p) {
      return this->getUnitMatrix();
    };
    if (p % 2) {
      return bigPow(p - 1, mod).mul(*this, mod);
    } else {
      Matrix ret = this->bigPow(p / 2, mod);
      return ret.mul(ret, mod);
    }
  }
  static Matrix getUnitMatrix(int n) {
    vector<vector<T>> mat(n, vector<T>(n, 0));
    for (int i = 0; i < n; ++i) {
      mat[i][i] = 1;
    }
    return Matrix(mat);
  }

  Matrix getUnitMatrix() const {
    const int n = this->numRows();
    return getUnitMatrix(n);
  }

private:
  vector<vector<T>> matrix;
};

// driver
int main() {
  std::ios_base::sync_with_stdio(false);
  Matrix<int> lhs{{{2, 4, 6}, {8, 10, 12}}};
  Matrix<int> rhs{{{1, 2, 3}, {5, 6, 7}, {9, 10, 11}}};
  for (int i = 1; i < 10; i++) {
    auto ret = rhs.bigPow(i, 100000);
    ret.print();
    puts("------------------");
  }
  (lhs * rhs).print();
  return 0;
}
