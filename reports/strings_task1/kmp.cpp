void kmp(string s, string t) {
	int n = s.size(); // O(1)
	int m = t.size(); // O(1)
	string nw = t + '#' + s; // O(m)
	vector<int> pr = prf(nw); // O(n + m) - построение префикс-функции
	vector<int> pos; // O(1)
	for (int i = m + 1; i + m - 1 < pr.size(); i++) { // O(n)
		if (pr[i + m - 1] == m) pos.pb(i - m - 1); // O(1)
	}
	cout << "Позиции вхождений:" << '\n';
	for (int x : pos) cout << x << ':' << x + m - 1 << '\n';
}
