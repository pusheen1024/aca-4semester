const int N = 26; // размер алфавита

vector<int> zf(string s) { // z-функция
	int n = s.size();
	int l = 0;
	int r = 0;
	vector<int> z(n);
	for (int i = 1; i < n; i++) {
		int j = max(0, min(z[i - l], r - i));
		while (i + j < n && s[j] == s[i + j]) j++;
		z[i] = j;
		if (i + j > r) {
			l = i;
			r = i + j;
		}
	}
	return z;
}

void boyer_moore(string s, string t) {
	int n = s.size(); // O(1)
	int m = t.size(); // O(1)
	vector<int> bad_char(N, m); // эвристика плохого символа
	for (int i = 0; i < m - 1; i++) { // O(m)
		bad_char[t[i] - 'A'] = m - i - 1; // O(1)
	}
	string t1 = t; // O(m)
	reverse(t1.begin(), t1.end()); // O(m)
	vector<int> z = zf(t1); // O(m)
	vector<int> good_suffix(m + 1, m); // эвристика хорошего суффикса
	for (int i = m - 1; i > 0; i--) good_suffix[m - z[i]] = i; // O(m)
	int r = 0; // O(1)
	for (int i = 1; i < m; i++) { // O(m)
		if (i + z[i] == m) { // O(1)
			while (r <= i) { // O(m) суммарно (метод двух указателей)
				if (good_suffix[r] == m) good_suffix[r] = i; // O(1)
				r++; // O(1)
			}
		}
	}
	int i = 0; // O(1)
	int lwb = 0; // O(1)
	vector<int> pos; // O(1)
	// O(n + m) - внешний и внутренний циклы по i и j
	while (i <= n - m) {
		int j = m - 1; // O(1)
		while (j >= lwb && t[j] == s[i + j]) j--;
		if (j < lwb) { // O(1)
			pos.pb(i); // O(1)
			lwb = m - good_suffix[0]; // O(1)
			j = -1; // O(1)
		}
		else lwb = 0; // O(1)
		if (j < lwb) i += good_suffix[j + 1]; // O(1)
		else i += max(good_suffix[j + 1], j - bad_char[s[i + j] - 'A']); // O(1)
	}
	cout << "Позиции вхождений:" << '\n';
	for (int x : pos) cout << x << ':' << x + m - 1 << '\n';
}
