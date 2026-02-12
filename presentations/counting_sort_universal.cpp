// сортировка подсчётом для массива, где числа лежат в диапазоне [k1, k2], 
// где k1, k2 - любые целые числа, в т.ч. отрицательные

void counting_sort_universal(vector<int> &a) { 
	int n = a.size();
	int mn = *min_element(a.begin(), a.end());
	int mx = *max_element(a.begin(), a.end());
	vector<int> cnt(mx - mn + 1);
	for (int i = 0; i < n; i++) {
		cnt[a[i] - mn]++;
	}
	int idx = 0;
	for (int num = 0; num <= mx - mn; num++) {
		for (int c = 0; c < cnt[num]; c++) {
			a[idx] = num + mn;
			idx++;
		}
	}
}
