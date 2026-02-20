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

// быстрая сортировка

void quick_sort(vector<int> &a, int l, int r) {
	if (l == r - 1) return;
	int i = l;
	int j = r - 1;
	int q = l + rnd() % (r - l); // случайный выбор опорного элемента
	while (i <= j) {
		while (a[i] < a[q]) i++;
		while (a[j] > a[q]) j--;
		if (i <= j) swap(a[i++], a[j--]);
	}
	if (j > l) quick_sort(a, l, j + 1);
	if (i < r) quick_sort(a, i, r);
}

void test(int n) {
	auto st = clock();
	vector<int> a(n);
	for (int i = 0; i < n; i++) a[i] = rnd();
	quick_sort(a, 0, n);
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
	quick_sort(a, 0, n);
	cout << "Отсортированный с помощью быстрой сортировки массив: ";
	for (int x : a) cout << x << ' ';
	cout << '\n';
}

int main() {
	int t = 1;
	//cin >> t;
	test(1000000);
}
