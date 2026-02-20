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

// сортировка слиянием

vector<int> merge_sort(vector<int> &a, int l, int r) {
	if (l == r - 1) return {a[l]};
	int m = (l + r) / 2;
	auto left = merge_sort(a, l, m);
	auto right = merge_sort(a, m, r);
	vector<int> res;
	int i = 0;
	int j = 0;
	while(i < left.size() && j < right.size()) {
		if (left[i] < right[j]) res.pb(left[i++]);
		else res.pb(right[j++]);
	}
	while (i < left.size()) res.pb(left[i++]);
	while (j < right.size()) res.pb(right[j++]);
	return res;
}

void test(int n) {
	auto st = clock();
	vector<int> a(n);
	for (int i = 0; i < n; i++) a[i] = rnd();
	merge_sort(a, 0, n);
	auto end = clock();
	ld seconds = (ld)(end - st) / CLOCKS_PER_SEC;
	cout << seconds << '\n';
}

void solve() {
	int n;
	cout << "Введите размер массива: ";
	cin >> n;
	cout << "Введите элементы массива: ";
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	a = merge_sort(a, 0, n);
	cout << "Отсортированный с помощью сортировки слиянием массив: ";
	for (int x : a) cout << x << ' ';
	cout << '\n';
}

int main() {
	int t = 1;
	//cin >> t;
	test(50000);
}
