vector<int> prf(string s) {
	int n = s.size(); // O(1)
	vector<int> pr(n); // O(n)
	for (int i = 1; i < n; i++) { // O(n)
		int j = pr[i - 1]; // O(1)
		while (j > 0 && s[i] != s[j]) // O(n) суммарно для всех итераций внешнего цикла
			j = pr[j - 1]; // O(1)
		if (s[i] == s[j]) j++; // O(1)
		pr[i] = j; // O(1)
	}
	return pr;
}
