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

// сортировка подсчётом для массива, где числа лежат в диапазоне [k1, k2], где k1, k2 - любые целые числа, в т.ч. отрицательные

void counting_sort(vector<int> &a) { 
	int n = a.size();
	int mn = *min_element(a.begin(), a.end());
	int mx = *max_element(a.begin(), a.end());
	vector<int> cnt(mx - mn + 1);
	for (int i = 0; i < n; i++) {
		cnt[a[i] - mn]++;
	}
	int idx = 0;
	for (int num = 0; num <= mx - mn; num++) {
		for (int c = 0; c < cnt[num]; c++) {
			a[idx] = num + mn;
			idx++;
		}
	}
}

void solve() {
	int n;
	cout << "Введите размер массива: ";
	cin >> n;
	cout << "Введите элементы массива: ";
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	counting_sort(a);
	cout << "Отсортированный с помощью сортировки подсчётом массив: ";
	for (int x : a) cout << x << ' ';
	cout << '\n';
}

int main() {
	int t = 1;
	//cin >> t;
	while (t--) solve();
}
