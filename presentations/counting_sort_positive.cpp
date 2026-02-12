// сортировка подсчётом для массива, где числа лежат в диапазоне [0, k]

void counting_sort_positive(vector<int> &a) { 
	int n = a.size();
	int mx = *max_element(a.begin(), a.end());
	vector<int> cnt(mx + 1);
	for (int i = 0; i < n; i++) {
		cnt[a[i]]++;
	}
	int idx = 0;
	for (int num = 0; num <= mx; num++) {
		for (int c = 0; c < cnt[num]; c++) {
			a[idx] = num;
			idx++;
		}
	}
}


