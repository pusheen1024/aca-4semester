const int base = 10; // десятичная система счисления

// поразрядная сортировка LSD (least significant digit)

void radix_sort_lsd(vector<int> &a) {
	int n = a.size(); // O(1)
	vector<int> a1(n); // O(n)
	vector<int> cnt(base); // O(b)
	vector<int> pr(base + 1); // O(b)
	int pw = 1; // O(1)
	for (int digit = 0; digit < 10; digit++) { // O(len)
		for (int j = 0; j < base; j++) cnt[j] = 0; // O(b)
		for (int j = 0; j <= base; j++) pr[j] = 0; // O(b)
		for (int i = 0; i < n; i++) { // O(n)
			int d = (a[i] / pw) % 10; // O(1)
			cnt[d]++; // O(1)
		}
		for (int j = 0; j < base; j++) pr[j + 1] = pr[j] + cnt[j]; // O(b)
		int idx = 0; // O(1)
		for (int i = 0; i < n; i++) { // O(n)
			int d = (a[i] / pw) % 10; // O(1)
			a1[pr[d]++] = a[i]; // O(1)
		}
		a = a1; // O(n)
		pw *= 10; // O(1)
	}
}
