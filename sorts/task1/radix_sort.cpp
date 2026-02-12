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

const int base = 10;

// поразрядная сортировка LSD (least significant digit)

void radix_sort_lsd(vector<int> &a) {
	int n = a.size();
	vector<int> a1(n);
	vector<int> cnt(base);
	vector<int> pr(base + 1);
	int pw = 1;
	for (int digit = 0; digit < 10; digit++) {
		for (int j = 0; j < base; j++) cnt[j] = 0;
		for (int j = 0; j <= base; j++) pr[j] = 0;
		for (int i = 0; i < n; i++) {
			int d = (a[i] / pw) % 10;
			cnt[d]++;
		}
		for (int j = 0; j < base; j++) pr[j + 1] = pr[j] + cnt[j];
		int idx = 0;
		for (int i = 0; i < n; i++) {
			int d = (a[i] / pw) % 10;
			a1[pr[d]++] = a[i];
		}
		a = a1;
		pw *= 10;
	}
}

void solve() {
	int n;
	cout << "Введите размер массива: ";
	cin >> n;
	cout << "Введите элементы массива: ";
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] < 0) {
			cout << "Элементы массива должны быть положительными!" << '\n';
			return;
		}
	}
	radix_sort_lsd(a);
	cout << "Отсортированный с помощью поразрядной сортировки (LSD) массив: ";
	for (int x : a) cout << x << ' ';
	cout << '\n';
}

int main() {
	int t = 1;
	//cin >> t;
	while (t--) solve();
}
