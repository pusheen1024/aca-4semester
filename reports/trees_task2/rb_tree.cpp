const int R = 1; // красный узел
const int B = 2; // чёрный узел
struct tree { // узел красно-чёрного дерева
    int x;
    int color;
    tree *left;
    tree *right;
    tree *parent;
};
tree *node(tree *p, int x) { // создание узла, O(1)
    tree *nw = new tree;
    nw->x = x;
	nw->color = R;
    nw->left = NULL;
    nw->right = NULL;
    nw->parent = p;
    return nw;
}
tree *root(int x) { // создание корня, O(1)
    tree *nw = new tree();
    nw->x = x;
	nw->color = B;
    nw->left = NULL;
    nw->right = NULL;
    nw->parent = NULL;
	return nw;
}
void rot_left(tree *x, tree *&tr) { // левый поворот, O(1)
    auto y = x->right; // O(1)
    x->right = y->left; // O(1)
    if (y->left != NULL) { // O(1)
        y->left->parent = x; // O(1)
    }
    y->parent = x->parent; // O(1)
	if (x->parent) { // O(1)
    	if (x == x->parent->left) { // O(1)
        	x->parent->left = y; // O(1)
    	}
    	else x->parent->right = y; // O(1)
	}
    y->left = x; // O(1)
    x->parent = y; // O(1)
    if (y->parent == NULL) { // O(1)
        y->color = B; // O(1)
        tr = y; // O(1)
    }
}
void rot_right(tree *x, tree *&tr) { // правый поворот, O(1)
    auto y = x->left; // O(1)
    x->left = y->right; // O(1)
    if (y->right != NULL) { // O(1)
        y->right->parent = x; // O(1)
    }
    y->parent = x->parent; // O(1)
	if (x->parent) { // O(1)
    	if (x == x->parent->left) { // O(1)
        	x->parent->left = y; // O(1)
    	}
    	else x->parent->right = y; // O(1)
	}
    y->right = x; // O(1)
    x->parent = y; // O(1)
    if (y->parent == NULL) { // O(1)

        y->color = B; // O(1)
        tr = y; // O(1)
    }
}
tree *grandparent(tree *x) { // дед, O(1)
    if (x != NULL && x->parent != NULL) return x->parent->parent; // O(1)
    return NULL; // O(1)
}
tree *uncle(tree *x) { // дядя, O(1)
    auto g = grandparent(x); // O(1)
    if (g == NULL) return NULL; // O(1)
    if (x->parent == g->left) return g->right; // O(1)
    return g->left; // O(1)
}
tree *sibling(tree *x) { // брат, O(1)
    if (x != NULL && x->parent != NULL) { // O(1)
        if (x == x->parent->left) return x->parent->right; // O(1)
        else return x->parent->left; // O(1)
    }
    return NULL; // O(1)
}
// прототипы функций вставки
void insert_case1(tree *x, tree *&tr);
void insert_case2(tree *x, tree *&tr);
void insert_case3(tree *x, tree *&tr);
void insert_case4(tree *x, tree *&tr);
void insert_case5(tree *x, tree *&tr);

void insert_case1(tree *x, tree *&tr) { // корень
    if (x->parent == NULL) x->color = B; // O(1)
    else insert_case2(x, tr);
}
void insert_case2(tree *x, tree *&tr) { // родитель чёрный
    if (x->parent->color == R) // O(1)
		insert_case3(x, tr); // O(1)
}
void insert_case3(tree *x, tree *&tr) { // родитель и дядя красный
    auto u = uncle(x); // O(1)
    auto g = grandparent(x); // O(1)
    if (u != NULL && u->color == R && x->parent->color == R) { // O(1)
        x->parent->color = B; // O(1)
        u->color = B; // O(1)
        g->color = R; // O(1)
        insert_case1(g, tr); // O(1)
    }
    else insert_case4(x, tr); // O(1)
}
void insert_case4(tree *x, tree *&tr) { // родитель красный, дядя чёрный
    auto g = grandparent(x); // O(1)
    if (x == x->parent->right && x->parent == g->left) { // O(1)
        rot_left(x, tr); // O(1)
        x = x->left; // O(1)
    }
    else if (x == x->parent->left && x->parent == g->right) { // O(1)
        rot_right(x, tr); // O(1)
        x = x->right; // O(1)
    }
    insert_case5(x, tr); // O(1)
}
void insert_case5(tree *x, tree *&tr) {
    auto g = grandparent(x); // O(1)
    x->parent->color = B; // O(1)
    g->color = R; // O(1)
    if (x == x->parent->left && x->parent == g->left) rot_right(g, tr); // O(1)
    else rot_left(g, tr); // O(1)
}
void insert(int x, tree *&tr, tree *&prev) { // вставка элемента, O(h)
    if (tr == NULL) { // O(1)
        tr = root(x); // O(1)
        return;
    }
    if (x < prev->x && prev->left == NULL) { // O(1)
        prev->left = node(prev, x); // O(1)
        insert_case1(prev->left, tr);
    }
    else if (x > prev->x && prev->right == NULL) { // O(1)
    	prev->right = node(prev, x); // O(1)
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
    if (x->parent == NULL) { // O(1)
        if (x->left != NULL) tr = x->left; // O(1)
        else tr = x->right; // O(1)
		if (tr) tr->color = B; // O(1)
    }
    else delete_case2(x, tr); // O(1)
}
void delete_case2(tree *x, tree *&tr) {
    auto s = sibling(x); // O(1)
    if (s->color == R) { // O(1)
        x->parent->color = R; // O(1)
        s->color = B; // O(1)
        if (x == x->parent->left) rot_left(x->parent, tr); // O(1)
        else rot_right(x->parent, tr); // O(1)
    }
    delete_case3(x, tr); // O(1)
}
void delete_case3(tree *x, tree *&tr) {
    auto s = sibling(x); // O(1)
    if (x->parent->color == B && s->color == B &&
        (s->left == NULL || s->left->color == B) &&
        (s->right == NULL || s->right->color == B)) { // O(1)
            s->color = R; // O(1)
            delete_case1(x, tr); // O(1)
    }
    else delete_case4(x, tr); // O(1)
}
void delete_case4(tree *x, tree *&tr) {
    auto s = sibling(x); // O(1)
    if (x->parent->color == R && s->color == B &&
        (s->left == NULL || s->left->color == B) &&
        (s->right == NULL || s->right->color == B)) { // O(1)
            s->color = R; // O(1)
            x->parent->color = B; // O(1)
    }
    else delete_case5(x, tr); // O(1)
}
void delete_case5(tree *x, tree *&tr) {
    auto s = sibling(x); // O(1)
    if (s->color == B) { // O(1)
        if (x == x->parent->left &&
            (s->left != NULL && s->left->color == R) &&
            (s->right == NULL || s->right->color == B)) { // O(1)
                s->color = R; // O(1)
                s->left->color = B; // O(1)
                rot_right(s, tr); // O(1)
        }
        else {
            if (x == x->parent->right &&
                (s->right != NULL && s->right->color == R) &&
                (s->left == NULL || s->left->color == B)) { // O(1)
                    s->color = R; // O(1)
                    s->right->color = B; // O(1)
                    rot_left(s, tr); // O(1)
                }
        }
    }
    delete_case6(x, tr); // O(1)
}
void delete_case6(tree *x, tree *&tr) {
    auto s = sibling(x); // O(1)
    s->color = s->parent->color; // O(1)
    s->parent->color = B; // O(1)
    if (x == x->parent->left) { // O(1)
        s->right->color = B; // O(1)
        rot_left(x->parent, tr); // O(1)
    }
    else {
        s->left->color = B; // O(1)
        rot_right(x->parent, tr); // O(1)
    }
}
void replace(tree *&x, tree *&tr) { // замена, O(1)
    if (x->left != NULL) {
        auto ch = x->left; // O(1)
        ch->parent = x->parent; // O(1)
        if (x->parent != NULL) { // O(1)
            if (x == x->parent->left) x->parent->left = ch; // O(1)
            else x->parent->right = ch; // O(1)
        }
    }
    else {
        auto ch = x->right; // O(1)
        ch->parent = x->parent; // O(1)
        if (x->parent != NULL) { // O(1)
            if (x == x->parent->left) x->parent->left = ch; // O(1)
            else x->parent->right = ch; // O(1)
        }
    }
}
tree *max(tree *x) { // максимум, O(h)
    return ((x != NULL && x->right != NULL) ? max(x->right) : x);
}
tree *min(tree *x) { // минимум, O(h)
    return ((x != NULL && x->left != NULL) ? min(x->left) : x);
}
void delete_node(tree *x, tree *&tr) { // удаление элемента, O(h)
	if (x == NULL) return; // O(1)
	tree *buf = NULL; // O(1)
    if (x->left != NULL && x->right != NULL) { // O(1)
        if (x->x <= tr->x) buf = max(x->left); // O(h)
        else buf = min(x->right); // O(h)
        swap(x->x, buf->x); // O(1)
        x = buf; // O(1)
    }
    else if (x->left != NULL || x->right != NULL) { // O(1)
        tree *ch = NULL; // O(1)
        if (x->left != NULL) ch = x->left; // O(1)
        else ch = x->right; // O(1)
        replace(x, tr); // O(1)
        if (x->color == B) { // O(1)
            if (ch && ch->color == R) { // O(1)
				ch->color = B; // O(1)
            }
            else delete_case1(x, tr); // O(1)
        }
    }
    else {
		if (x->color == B) delete_case1(x, tr); // O(1)
		else {
			if (x == x->parent->left) x->parent->left = NULL; // O(1)
            else x->parent->right = NULL; // O(1)
        }
    }
	if (x->left == NULL && x->right == NULL) { // O(1)
		if (! x->parent) { // O(1)
			delete_case1(x, tr); // O(1)
			return;
		}
		if (x == x->parent->left) x->parent->left = NULL; // O(1)
		else if (x == x->parent->right) x->parent->right = NULL; // O(1)
	}
	delete x; // O(1)
}
string color(tree *tr) { // получение строки с цветом вершины
	if (tr->color == R) return "red";
	else return "black";
}
tree* find(tree *tr, int x) { // поиск элемента по значению, O(h)
	if (! tr || tr->x == x) return tr; // O(1)
	if (x < tr->x) return find(tr->left, x);
	return find(tr->right, x);
}
// вспомогательная функция для удаления элемента по значению, O(h)
bool delete_elem(int x, tree *&tr) {
	tree *node = find(tr, x); // O(h)
	if (node == NULL) return false; // O(1)
	delete_node(node, tr); // O(h)
	return true; // O(1)
}
void preorder(tree *tr) { // прямой обход, O(n)
    if (tr == NULL) return;
    cout << tr->x << ' ' << color(tr) << '\n';
	preorder(tr->left);
    preorder(tr->right);
}
void inorder(tree *tr) { // симметричный обход, O(n)
    if (tr == NULL) return;
    inorder(tr->left);
    cout << tr->x << ' ' << color(tr) << '\n';
    inorder(tr->right);
}
void postorder(tree *tr) { // обратный обход, O(n)
    if (tr == NULL) return;
	postorder(tr->left);
    postorder(tr->right);
    cout << tr->x << ' ' << color(tr) << '\n';
}
