#include <iostream>
#include <vector>

using namespace std;

class Matrix {
public:
  template <typename T> Matrix(T n, T m) {
    matrix = vector<vector<int>>(n, vector<int>(m, 0));
  }
  Matrix(const vector<vector<int>> &vec) { matrix = vec; }

  void print(bool err_mode = true) {
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

  template <typename T> int get(T r, T c) const { return matrix[r][c]; }
  vector<int> &operator[](int r) { return matrix[r]; }

  Matrix operator*(const Matrix &rhs) {
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

  Matrix bigPow(int p, int mod) const {
    if (p == 0) {
      return *this;
    }
    if (p % 2) {
      return bigPow(p - 1, mod).mul(*this, mod);
    } else {
      Matrix ret = this->bigPow(p / 2, mod);
      return ret.mul(ret, mod);
    }
  }

private:
  vector<vector<int>> matrix;
};

// driver
int main() {
  std::ios_base::sync_with_stdio(false);
  Matrix lhs = Matrix({{2, 4, 6}, {8, 10, 12}});
  Matrix rhs = Matrix({{1, 2, 3}, {5, 6, 7}, {9, 10, 11}});
  for (int i = 1; i < 10; i++) {
    auto ret = rhs.bigPow(i, 100000);
    ret.print();
    puts("------------------");
  }
  (lhs * rhs).print();
  return 0;
}
