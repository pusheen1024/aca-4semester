vector<int> zf(string s) {
	int n = s.size(); // O(1)
	int l = 0; // O(1)
	int r = 0; // O(1)
	vector<int> z(n); // O(n)
	for (int i = 1; i < n; i++) { // O(n)
		int j = max(0, min(z[i - l], r - i)); // O(1)
		while (i + j < n && s[j] == s[i + j]) j++; // O(n) суммарно для всех итераций внешнего цикла
		z[i] = j; // O(1)
		if (i + j > r) { // O(1)
			l = i; // O(1)
			r = i + j; // O(1)
		}
	}
	return z;
}
