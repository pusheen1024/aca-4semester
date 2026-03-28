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

vector<int> prf(string s) {
	int n = s.size();
	vector<int> pr(n);
	for (int i = 1; i < n; i++) {
		int j = pr[i - 1];
		while (j > 0 && s[i] != s[j]) 
			j = pr[j - 1];
		if (s[i] == s[j]) j++;
		pr[i] = j;
	}
	return pr;
}

void solve() {
	cout << "Введите строку, от которой хотите посчитать префикс-функцию: ";
	string s;
	cin >> s;
	cout << "Префикс-функция: ";
	vector<int> pr = prf(s);
	for (int x : pr) cout << x << ' ';
	cout << '\n';
}

int main() {
	int t = 1;
	//cin >> t;
	while (t--) solve();
}
