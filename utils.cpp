#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

bool isPal(const string &s) {
  for (int i = 0; i < s.size() / 2; ++i) {
    if (s[i] != s[s.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

long long calcFastPow(int n, int p) {
  if (p == 0) {
    return 1;
  }
  if (p & 1) {
    return (long long)n * calcFastPow(n, p - 1);
  }
  long long ret = calcFastPow(n, p / 2);
  return ret * ret;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  for (string s; cin >> s;) {
    cout << s << " " << isPal(s) << endl;
  }
  return 0;
}