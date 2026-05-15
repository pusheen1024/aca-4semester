void quick_sort(vector<int> &a, int l, int r) {
	if (l == r - 1) return; // O(1)
	int i = l; // O(1)
	int j = r - 1; // O(1)
	int q = l + rnd() % (r - l); // случайный выбор опорного элемента, O(1)
	while (i <= j) { // O(n) (метод 2 указателей)
		while (a[i] < a[q]) i++; // O(n) суммарно
		while (a[j] > a[q]) j--; // O(n) суммарно
		if (i <= j) swap(a[i++], a[j--]); // O(1)
	}
	if (j > l) quick_sort(a, l, j + 1);
	if (i < r) quick_sort(a, i, r);
}
