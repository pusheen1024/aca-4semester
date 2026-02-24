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
#include <unordered_map>
#include <complex>

#define pb push_back
#define mp make_pair
#define x first
#define y second

using namespace std;

typedef long long li;
typedef long double ld;
typedef pair<int, int> ptt;
typedef pair<li, li> pll;

mt19937 rnd(time(NULL));

struct tree { // узел дерева
    int x;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x) { // создание узла
    tree *nw = new tree;
    nw->x = x;
    nw->left = NULL;
    nw->right = NULL;
    nw->parent = NULL;
    return nw;
}

tree *Min(tree *tr) { // минимальный элемент
	if (! tr->left) return tr;
	return Min(tr->left);
}

void Insert(tree *&tr, int x) { // вставка узла
    tree *nw = node(x);
    if (! tr) {
		tr = nw;
		return;
	}
	tree *t = tr;
	while (t) {
		if (nw->x > t->x) {
			if (t->right)
				t = t->right;
			else {
				nw->parent = t;
				t->right = nw;
				break;
			}
		}
		else if (nw->x < t->x) {
			if (t->left)
				t = t->left;
			else {
				nw->parent = t;
				t->left = nw;
				break;
			}
		}
		else break;
	}
}

tree *Find(tree *tr, int x) { // поиск элемента по значению
    if (! tr || tr->x == x) return tr;
    if (x < tr->x) return Find(tr->left, x);
    return Find(tr->right, x);
}

tree *nxt(tree *tr, int x) { // следующий элемент (upper_bound)
    tree *t = Find(tr, x);
	if (! t) return NULL;
    if (t->right) return Min(t->right);
    tree *y = t->parent;
    while (y && t == y->right) {
        t = y;
        y = y->parent;
    }
    return y;
}

void Delete(tree *&tr, tree *&d) { // удаление узла
	if (! d) return;
    tree *p = d->parent;
    if (!p && ! d->left && ! d->right) {
		d = NULL;
		tr = NULL;
	}
    else if (p && ! d->left && ! d->right) {
        if (p->left == d) p->left = NULL;
		else if (p->right == d) p->right = NULL;
		d = NULL;
    }
    else if (! d->left || ! d->right) {
        if (! p) {
            if (! d->left) {
                tr = d->right;
				d->right->parent = NULL;
                d->parent = NULL;
            }
            else {
                tr = d->left;
				d->right->parent = NULL;
                d->parent = NULL;
            }
			d = NULL;
        }
        else {
            if (! d->left) {
                if (p->left == d) p->left = d->right;
                else p->right = d->right;
                d->right->parent = p;
            }
            else {
                if (p->left == d) p->left = d->left;
                else p->right = d->left;
                d->left->parent = p;
            }
        }
		d = NULL;
    }
    else {
        tree *s = nxt(tr, d->x);
		d->x = s->x;
		if (s->parent->left == s) {
			s->parent->left = s->right;
			if (s->right) s->right->parent = s->parent;
		}
		else {
			s->parent->right = s->right;
			if (s->right) s->right->parent = s->parent;
		}
		s = NULL;
    }
}

void inorder(tree *tr) { // симметричный обход
    if(! tr) return;
	inorder(tr->left);
    cout << tr->x << ' ';
    inorder(tr->right);
}

void preorder(tree *tr) { // прямой обход
	if (! tr) return;
	cout << tr->x << ' ';
	preorder(tr->left);
	preorder(tr->right);
}

void postorder(tree *tr) { // обратный обход
	if (! tr) return;
	postorder(tr->left);
	postorder(tr->right);
	cout << tr->x << ' ';
}

tree *tr = NULL;

void solve(bool &finish) {
	cout << "Что Вы хотите сделать?" << '\n';
	cout << "1) Вставить узел в дерево;" << '\n';
	cout << "2) Удалить узел из дерева;" << '\n';
	cout << "3) Проверить, есть ли узел в дереве;" << '\n';
	cout << "4) Вывести прямой обход дерева;" << '\n';
	cout << "5) Вывести симметричный обход дерева;" << '\n';
	cout << "6) Вывести обратный обход дерева." << '\n';
	cout << "0) Завершить работу с деревом." << '\n';
	int choice;
	cin >> choice;
	switch(choice) {
		case 1: {
			int val;
			cout << "Введите элемент, который хотите вставить: ";
			cin >> val;
			Insert(tr, val);
			break;
		}
		case 2: {
			int val;
			cout << "Введите элемент, который хотите удалить: ";
			cin >> val;
			tree *node = Find(tr, val);
			if (node == NULL) cout << "Такого элемента не существует в дереве." << '\n';
			else {
				Delete(tr, node);
				cout << "Элемент успешно удалён." << '\n';
			}
			break;
		}
		case 3: {
			int val;
			cout << "Введите элемент, который хотите найти: ";
			cin >> val;
			if (Find(tr, val)) cout << "Узел с таким значением есть в дереве." << '\n';
			else cout << "Узла с таким значением нет в дереве." << '\n';
			break;
		}
		case 4: {
			cout << "Прямой обход: ";
			preorder(tr);
			cout << '\n';
			break;
		}
		case 5: {
			cout << "Симметричный обход: ";
			inorder(tr);
			cout << '\n';
			break;
		}
		case 6: {
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
