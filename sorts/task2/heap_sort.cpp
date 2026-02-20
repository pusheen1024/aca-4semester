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

// построение двоичной кучи/пирамиды (каждый элемент больше своих детей)

void heapify(vector<int> &a, int n, int i) {
	int root = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n && a[left] > a[root]) root = left;
	if (right < n && a[right] > a[root]) root = right;
	if (root != i) {
		swap(a[i], a[root]);
		heapify(a, n, root);
	}
}

// пирамидальная сортировка

void heap_sort(vector<int> &a) {
	int n = a.size();
	for (int i = n - 1; i >= 0; i--) heapify(a, n, i);
	for (int i = n - 1; i >= 0; i--) {
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}
}

void solve() {
	int n;
	cout << "Введите размер массива: ";
	cin >> n;
	cout << "Введите элементы массива: ";
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	heap_sort(a);
	cout << "Отсортированный с помощью сортировки слиянием массив: ";
	for (int x : a) cout << x << ' ';
	cout << '\n';
}

int main() {
	int t = 1;
	//cin >> t;
	while (t--) solve();
}
