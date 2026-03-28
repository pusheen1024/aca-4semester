#include <iostream>
#include <fstream>
#include <cstdio>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <array>
#include <climits>
#include <cassert>
#include <unordered_map>
#include <complex>

#define pb push_back
#define mp make_pair
#define x first
#define y second

using namespace std;

typedef long long li;
typedef long double ld;
typedef pair<int, int> ptt;
typedef pair<li, li> pll;

mt19937 rnd(time(NULL));

vector<int> zf(string s) {
	int n = s.size();
	int l = 0;
	int r = 0;
	vector<int> z(n);
	for (int i = 1; i < n; i++) {
		int j = max(0, min(z[i - l], r - i));
		while (i + j < n && s[j] == s[i + j]) j++;
		z[i] = j;
		if (i + j > r) {
			l = i;
			r = i + j;
		}
	}
	return z;
}

void solve() {
	cout << "Введите строку, от которой хотите посчитать z-функцию: ";
	string s;
	cin >> s;
	cout << "z-функция: ";
	vector<int> z = zf(s);
	for (int x : z) cout << x << ' ';
	cout << '\n';
}

int main() {
	int t = 1;
	//cin >> t;
	while (t--) solve();
}

