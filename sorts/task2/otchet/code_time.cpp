void test(int n) {
	auto st = clock();
	vector<int> a(n);
	for (int i = 0; i < n; i++) a[i] = rnd();
	merge_sort(a, 0, n);
	auto end = clock();
	ld seconds = (ld)(end - st) / CLOCKS_PER_SEC;
	cout << seconds << '\n';
}
