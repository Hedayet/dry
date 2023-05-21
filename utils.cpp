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

int main() {
  std::ios_base::sync_with_stdio(false);
  for (string s; cin >> s;) {
    cout << s << " " << isPal(s) << endl;
  }
  return 0;
}