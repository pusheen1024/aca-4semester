// сортировка подсчётом для массива, где числа лежат в диапазоне [k1, k2],
// где k1, k2 - любые целые числа, в т.ч. отрицательные

void counting_sort(vector<int> &a) { 
	int n = a.size(); // O(1)
	int mn = *min_element(a.begin(), a.end()); // O(n)
	int mx = *max_element(a.begin(), a.end()); // O(n)
	vector<int> cnt(mx - mn + 1); // O(k)
	for (int i = 0; i < n; i++) { // O(n)
		cnt[a[i] - mn]++; // O(1)
	}
	int idx = 0; // O(1)
	for (int num = 0; num <= mx - mn; num++) { // O(k)
		for (int c = 0; c < cnt[num]; c++) { // O(n) суммарно
			a[idx] = num + mn; // O(1)
			idx++; // O(1)
		}
	}
}
