// построение двоичной кучи/пирамиды (каждый элемент больше своих детей)
void heapify(vector<int> &a, int n, int i) { // O(log n)
	int root = i; // O(1)
	int left = 2 * i + 1; // O(1)
	int right = 2 * i + 2; // O(1)
	if (left < n && a[left] > a[root]) root = left; // O(1)
	if (right < n && a[right] > a[root]) root = right; // O(1)
	if (root != i) { // O(1)
		swap(a[i], a[root]); // O(1)
		heapify(a, n, root); // root = 2 * i + 1 или 2 * i + 2
	}
}
void heap_sort(vector<int> &a) {
	int n = a.size(); // O(1)
	for (int i = n - 1; i >= 0; i--) // O(n)
		heapify(a, n, i); // O(log n)
	for (int i = n - 1; i >= 0; i--) { // O(n)
		swap(a[0], a[i]); // O(1)
		heapify(a, i, 0); // O(log n)
	}
}
