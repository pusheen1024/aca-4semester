#include <iostream>
#include <fstream>
#include <cstdio>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <array>
#include <climits>
#include <cassert>
#include <climits>

#define pb push_back

using namespace std;

typedef long long li;
typedef long double ld;
typedef pair<int, int> ptt;

const int INF = 1e9;
const int M = 1e9 + 7;

struct tree { // узел AVL-дерева
    int x;
    int height;
    tree *left;
    tree *right;
};

tree *node(int x) { // создание узла
    tree *nw = new tree;
    nw->x = x;
    nw->left = NULL;
    nw->right = NULL;
    nw->height = 1;
    return nw;
}

int height(tree *x) { // высота поддерева
    return (x != NULL ? x->height : 0);
}

int bal(tree *x) { // баланс
    if (x == NULL) return 0;
    return height(x->right) - height(x->left);
}

void fix(tree *x) {
    int hl = height(x->left);
    int hr = height(x->right);
    x->height = max(hl, hr) + 1;
}

tree *rot_left(tree *x) { // левый поворот
    tree *y = x->right;
    x->right = y->left;
    y->left = x;
    fix(x);
    fix(y);
    return y;
}

tree *rot_right(tree *x) { // правый поворот
    tree *y = x->left;
    x->left = y->right;
    y->right = x;
    fix(x);
    fix(y);
    return y;
}

tree *balance(tree *x) { // перебалансировка
    fix(x);
    if (bal(x) == 2) {
        if (bal(x->right) < 0) x->right = rot_right(x->right);
        return rot_left(x);
    }
    if (bal(x) == -2) {
        if (bal(x->left) > 0) x->left = rot_left(x->left);
        return rot_right(x);
    }
    return x;
}

tree *insert(tree *tr, int x) { // вставка элемента
    if (! tr) return node(x);
    if (x < tr->x) tr->left = insert(tr->left, x);
    else tr->right = insert(tr->right, x);
    return balance(tr);
}

tree *find_min(tree *tr) {
    return (tr->left != NULL ? find_min(tr->left) : tr);
}

tree *delete_min(tree *tr) {
    if (tr->left == NULL) return tr->right;
    tr->left = delete_min(tr->left);
    return balance(tr);
}

tree *delete_node(tree *tr, int x) { // удаление вершины
    if (tr == NULL) return NULL;
    if (x < tr->x) tr->left = delete_node(tr->left, x);
    else if (x > tr->x) tr->right = delete_node(tr->right, x);
    else {
        tree *l = tr->left;
        tree *r = tr->right;
        delete tr;
        if (r == NULL) return l;
        tree *mn = find_min(r);
        mn->right = delete_min(r);
        mn->left = l;
        return balance(mn);
    }
    return balance(tr);
}

tree *find(tree *tr, int x) { // поиск элемента
	if (tr == NULL || tr->x == x) return tr;
	if (x < tr->x) return find(tr->left, x);
	return find(tr->right, x);
}

void preorder(tree *tr) { // прямой обход
	if (tr == NULL) return;
	cout << tr->x << ' ';
	preorder(tr->left);
	preorder(tr->right);
}

void inorder(tree *tr) { // симметричный обход
    if (tr == NULL) return;
    inorder(tr->left);
    cout << tr->x << ' ';
    inorder(tr->right);
}

void postorder(tree *tr) {
	if (tr == NULL) return;
	postorder(tr->left);
	postorder(tr->right);
	cout << tr->x << ' ';
}

tree *tr = NULL;

void solve(bool &finish) {
	cout << "Что Вы хотите сделать?" << '\n';
	cout << "1) Вставить узел в дерево;" << '\n';
	cout << "2) Удалить узел из дерева;" << '\n';
	cout << "3) Вывести прямой обход дерева;" << '\n';
	cout << "4) Вывести симметричный обход дерева;" << '\n';
	cout << "5) Вывести обратный обход дерева." << '\n';
	cout << "0) Завершить работу с деревом." << '\n';
	int choice;
	cin >> choice;
	switch(choice) {
		case 1: {
			int val;
			cout << "Введите элемент, который хотите вставить: ";
			cin >> val;
			tr = insert(tr, val);
			cout << "Изменённое дерево: ";
			preorder(tr);
			cout << '\n';
			break;
		}
		case 2: {
			int val;
			cout << "Введите элемент, который хотите удалить: ";
			cin >> val;
			tr = delete_node(tr, val);
			cout << "Изменённое дерево: ";
			preorder(tr);
			cout << '\n';
			break;
		}
		case 3: {
			cout << "Прямой обход: ";
			preorder(tr);
			cout << '\n';
			break;
		}
		case 4: {
			cout << "Симметричный обход: ";
			inorder(tr);
			cout << '\n';
			break;
		}
		case 5: {
			cout << "Обратный обход: ";
			postorder(tr);
			cout << '\n';
			break;
		}
		case 0: {
			finish = 1;
			break;
		}
		default: {
			cout << "Некорректный выбор!" << '\n';
			break;
		}
	}
}

int main() {
	bool finish = 0;
	cout << "Добро пожаловать!" << '\n';
	while (! finish) solve(finish);
	cout << "До свидания!" << '\n';
}
