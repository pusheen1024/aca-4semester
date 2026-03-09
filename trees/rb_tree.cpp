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

const int R = 1; // красный узел
const int B = 2; // чёрный узел

struct tree { // узел красно-чёрного дерева
    int x;
    int color;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(tree *p, int x) { // создание узла
    tree *nw = new tree;
    nw->x = x;
	nw->color = R;
    nw->left = NULL;
    nw->right = NULL;
    nw->parent = p;
    return nw;
}

tree *root(int x) { // создание корня
    tree *nw = new tree();
    nw->x = x;
	nw->color = B;
    nw->left = NULL;
    nw->right = NULL;
    nw->parent = NULL;
	return nw;
}

void rot_left(tree *x, tree *&tr) { // левый поворот
    auto y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
	if (x->parent) {
    	if (x == x->parent->left) {
        	x->parent->left = y;
    	}
    	else x->parent->right = y;
	}
    y->left = x;
    x->parent = y;
    if (y->parent == NULL) {
        y->color = B;
        tr = y;
    }
}

void rot_right(tree *x, tree *&tr) { // правый поворот
    auto y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
	if (x->parent) {
    	if (x == x->parent->left) {
        	x->parent->left = y;
    	}
    	else x->parent->right = y;
	}
    y->right = x;
    x->parent = y;
    if (y->parent == NULL) {
        y->color = B;
        tr = y;
    }
}

tree *grandparent(tree *x) { // дед
    if (x != NULL && x->parent != NULL) return x->parent->parent;
    return NULL;
}

tree *uncle(tree *x) { // дядя
    auto g = grandparent(x);
    if (g == NULL) return NULL;
    if (x->parent == g->left) return g->right;
    return g->left;
}

tree *sibling(tree *x) { // брат
    if (x != NULL && x->parent != NULL) {
        if (x == x->parent->left) return x->parent->right;
        else return x->parent->left;
    }
    return NULL;
}

// прототипы функций вставки
void insert_case1(tree *x, tree *&tr);
void insert_case2(tree *x, tree *&tr);
void insert_case3(tree *x, tree *&tr);
void insert_case4(tree *x, tree *&tr);
void insert_case5(tree *x, tree *&tr);

void insert_case1(tree *x, tree *&tr) { // корень
    if (x->parent == NULL) x->color = B;
    else insert_case2(x, tr);
}

void insert_case2(tree *x, tree *&tr) { // родитель чёрный
    if (x->parent->color == R) insert_case3(x, tr);
}

void insert_case3(tree *x, tree *&tr) { // родитель и дядя красный
    auto u = uncle(x);
    auto g = grandparent(x);
    if (u != NULL && u->color == R && x->parent->color == R) {
        x->parent->color = B;
        u->color = B;
        g->color = R;
        insert_case1(g, tr);
    }
    else insert_case4(x, tr);
}

void insert_case4(tree *x, tree *&tr) { // родитель красный, дядя чёрный
    auto g = grandparent(x);
    if (x == x->parent->right && x->parent == g->left) {
        rot_left(x, tr);
        x = x->left;
    }
    else if (x == x->parent->left && x->parent == g->right) {
        rot_right(x, tr);
        x = x->right;
    }
    insert_case5(x, tr);
}

void insert_case5(tree *x, tree *&tr) {
    auto g = grandparent(x);
    x->parent->color = B;
    g->color = R;
    if (x == x->parent->left && x->parent == g->left) rot_right(g, tr);
    else rot_left(g, tr);
}

void insert(int x, tree *&tr, tree *&prev) { // вставка элемента
    if (tr == NULL) {
        tr = root(x);
        return;
    }
    if (x < prev->x && prev->left == NULL) {
        prev->left = node(prev, x);
        insert_case1(prev->left, tr);
    }
    else if (x > prev->x && prev->right == NULL) {
    	prev->right = node(prev, x);
        insert_case1(prev->right, tr);
    }
    else {
    	if (x < prev->x && prev->left) insert(x, tr, prev->left);
        else if (x > prev->x && prev->right) insert(x, tr, prev->right);
    }
}

// прототипы функций удаления
void delete_case1(tree *x, tree *&tr);
void delete_case2(tree *x, tree *&tr);
void delete_case3(tree *x, tree *&tr);
void delete_case4(tree *x, tree *&tr);
void delete_case5(tree *x, tree *&tr);
void delete_case6(tree *x, tree *&tr);

void delete_case1(tree *x, tree *&tr) { // корень
    if (x->parent == NULL) {
        if (x->left != NULL) tr = x->left;
        else tr = x->right;
		if (tr) tr->color = B;
    }
    else delete_case2(x, tr);
}

void delete_case2(tree *x, tree *&tr) {
    auto s = sibling(x);
    if (s->color == R) {
        x->parent->color = R;
        s->color = B;
        if (x == x->parent->left) rot_left(x->parent, tr);
        else rot_right(x->parent, tr);
    }
    delete_case3(x, tr);
}

void delete_case3(tree *x, tree *&tr) {
    auto s = sibling(x);
    if (x->parent->color == B && s->color == B &&
        (s->left == NULL || s->left->color == B) &&
        (s->right == NULL || s->right->color == B)) {
            s->color = R;
            delete_case1(x, tr);
    }
    else delete_case4(x, tr);
}

void delete_case4(tree *x, tree *&tr) {
    auto s = sibling(x);
    if (x->parent->color == R && s->color == B &&
        (s->left == NULL || s->left->color == B) &&
        (s->right == NULL || s->right->color == B)) {
            s->color = R;
            x->parent->color = B;
    }
    else delete_case5(x, tr);
}

void delete_case5(tree *x, tree *&tr) {
    auto s = sibling(x);
    if (s->color == B) {
        if (x == x->parent->left &&
            (s->left != NULL && s->left->color == R) &&
            (s->right == NULL || s->right->color == B)) {
                s->color = R;
                s->left->color = B;
                rot_right(s, tr);
        }
        else {
            if (x == x->parent->right &&
                (s->right != NULL && s->right->color == R) &&
                (s->left == NULL || s->left->color == B)) {
                    s->color = R;
                    s->right->color = B;
                    rot_left(s, tr);
                }
        }
    }
    delete_case6(x, tr);
}

void delete_case6(tree *x, tree *&tr) {
    auto s = sibling(x);
    s->color = s->parent->color;
    s->parent->color = B;
    if (x == x->parent->left) {
        s->right->color = B;
        rot_left(x->parent, tr);
    }
    else {
        s->left->color = B;
        rot_right(x->parent, tr);
    }
}

void replace(tree *&x, tree *&tr) {
    if (x->left != NULL) {
        auto ch = x->left;
        ch->parent = x->parent;
        if (x->parent != NULL) {
            if (x == x->parent->left) x->parent->left = ch;
            else x->parent->right = ch;
        }
    }
    else {
        auto ch = x->right;
        ch->parent = x->parent;
        if (x->parent != NULL) {
            if (x == x->parent->left) x->parent->left = ch;
            else x->parent->right = ch;
        }
    }
}

tree *max(tree *x) {
    return ((x != NULL && x->right != NULL) ? max(x->right) : x);
}

tree *min(tree *x) {
    return ((x != NULL && x->left != NULL) ? min(x->left) : x);
}

void delete_node(tree *x, tree *&tr) { // удаление элемента
	if (x == NULL) return;
	tree *buf = NULL;
    if (x->left != NULL && x->right != NULL) {
        if (x->x <= tr->x) buf = max(x->left);
        else buf = min(x->right);
        swap(x->x, buf->x);
        x = buf;
    }
    else if (x->left != NULL || x->right != NULL) {
        tree *ch = NULL;
        if (x->left != NULL) ch = x->left;
        else ch = x->right;
        replace(x, tr);
        if (x->color == B) {
            if (ch && ch->color == R) {
				ch->color = B;
            }
            else delete_case1(x, tr);
        }
    }
    else {
		if (x->color == B) delete_case1(x, tr);
		else {
			if (x == x->parent->left) x->parent->left = NULL;
            else x->parent->right = NULL;
        }
    }
	if (x->left == NULL && x->right == NULL) {
		if (! x->parent) {
			delete_case1(x, tr);
			return;
		}
		if (x == x->parent->left) x->parent->left = NULL;
		else if (x == x->parent->right) x->parent->right = NULL;
	}
	delete x;
}

string color(tree *tr) {
	if (tr->color == R) return "red";
	else return "black";
}

tree* find(tree *tr, int x) { // поиск элемента по значению
	if (! tr || tr->x == x) return tr;
	if (x < tr->x) return find(tr->left, x);
	return find(tr->right, x);
}

bool delete_elem(int x, tree *&tr) {
	tree *node = find(tr, x);
	if (node == NULL) return false;
	delete_node(node, tr);
	return true;
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

void postorder(tree *tr) { // обратный обход
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
			insert(val, tr, tr);
			cout << "Прямой обход: ";
			preorder(tr);
			cout << '\n';
			break;
		}
		case 2: {
			int val;
			cout << "Введите элемент, который хотите удалить: ";
			cin >> val;
			if (! delete_elem(val, tr))
				cout << "Такого элемента не существует в дереве." << '\n';
			else cout << "Элемент успешно удалён." << '\n';
			cout << "Прямой обход: ";
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
