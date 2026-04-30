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

const int N = 26; // размер алфавита

vector<int> zf(string s) { // z-функция
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
	cout << "Введите текст, в котором Вы хотите найти вхождения подстроки: ";
	string s;
	cin >> s;
	int n = s.size();
	cout << "Введите подстроку, вхождения которой Вы хотите найти: ";
	string t;
	cin >> t;
	int m = t.size();
	vector<int> bad_char(N, m); // эвристика плохого символа
	for (int i = 0; i < m - 1; i++) {
		bad_char[t[i] - 'A'] = m - i - 1;
	}
	cout << "Плохой символ:" << '\n';
	for(int i = 0; i < N; i++) cout << bad_char[i] << ' ';
	cout << '\n';

	string t1 = t;
	reverse(t1.begin(), t1.end());
	vector<int> z = zf(t1);
	
	cout << "Z-функция:" << '\n';
	for (int i = 0; i < z.size(); i++) cout << z[i] << ' ';
	cout << '\n';
	
	vector<int> good_suffix(m + 1, m); // эвристика хорошего суффикса
	for (int i = m - 1; i > 0; i--) good_suffix[m - z[i]] = i;
	int r = 0;
	for (int i = 1; i < m; i++) {
		if (i + z[i] == m) {
			while (r <= i) {
				if (good_suffix[r] == m) good_suffix[r] = i;
				r++;
			}
		}
	}
	cout << "Хороший суффикс:" << '\n';
	for(int i = 0; i <= m; i++) cout << good_suffix[i] << ' ';
	cout << '\n';
	
	int i = 0;
	int lwb = 0;
	vector<int> pos;
	while (i <= n - m) {
		int j = m - 1;
		while (j >= lwb && t[j] == s[i + j]) j--;
		if (j < lwb) {
			pos.pb(i);
			lwb = m - good_suffix[0];
			j = -1;
		}
		else lwb = 0;
		if (j < lwb) i += good_suffix[j + 1];
		else i += max(good_suffix[j + 1], j - bad_char[s[i + j] - 'A']);
	}
	cout << "Позиции вхождений:" << '\n';
	for (int x : pos) cout << x << ':' << x + m - 1 << '\n';
}

int main() {
	int t = 1;
	//cin >> t;
	while (t--) solve();
}
