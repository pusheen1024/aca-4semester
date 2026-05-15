struct tree { // узел AVL-дерева
    int x;
    int height;
    tree *left;
    tree *right;
};
tree *node(int x) { // создание узла, O(1)
    tree *nw = new tree;
    nw->x = x;
    nw->left = NULL;
    nw->right = NULL;
    nw->height = 1;
    return nw;
}
int height(tree *x) { // высота поддерева, O(1)
    return (x != NULL ? x->height : 0); // O(1)
}
int bal(tree *x) { // баланс, O(1)
    if (x == NULL) return 0; // O(1)
    return height(x->right) - height(x->left); // O(1)
}
void fix(tree *x) { // пересчёт высоты после изменений, O(1)
    int hl = height(x->left); // O(1)
    int hr = height(x->right); // O(1)
    x->height = max(hl, hr) + 1; // O(1)
}
tree *rot_left(tree *x) { // левый поворот, O(1)
    tree *y = x->right; // O(1)
    x->right = y->left; // O(1)
    y->left = x; // O(1)
    fix(x); // O(1)
    fix(y); // O(1)
    return y; // O(1)
}
tree *rot_right(tree *x) { // правый поворот, O(1)
    tree *y = x->left; // O(1)
    x->left = y->right; // O(1)
    y->right = x; // O(1)
    fix(x); // O(1)
    fix(y); // O(1)
    return y; // O(1)
}
tree *balance(tree *x) { // перебалансировка, O(1)
    fix(x); // O(1)
    if (bal(x) == 2) { // O(1)
        if (bal(x->right) < 0) x->right = rot_right(x->right); // O(1)
        return rot_left(x); // O(1)
    }
    if (bal(x) == -2) { // O(1)
        if (bal(x->left) > 0) x->left = rot_left(x->left); // O(1)
        return rot_right(x); // O(1)
    }
    return x; // O(1)
}
tree *insert(tree *tr, int x) { // вставка элемента, O(h)
    if (! tr) return node(x); // O(1)
    if (x < tr->x) tr->left = insert(tr->left, x);
    else tr->right = insert(tr->right, x);
    return balance(tr); // O(1)
}
tree *find_min(tree *tr) { // поиск минимума, O(h)
    return (tr->left != NULL ? find_min(tr->left) : tr);
}
tree *delete_min(tree *tr) { // удаление минимума, O(h)
    if (tr->left == NULL) return tr->right; // O(1)
    tr->left = delete_min(tr->left);
    return balance(tr); // O(1)
}
tree *delete_node(tree *tr, int x) { // удаление вершины, O(h)
    if (tr == NULL) return NULL; // O(1)
    if (x < tr->x) tr->left = delete_node(tr->left, x);
    else if (x > tr->x) tr->right = delete_node(tr->right, x);
    else {
        tree *l = tr->left; // O(1)
        tree *r = tr->right; // O(1)
        delete tr; // O(1)
        if (r == NULL) return l; // O(1)
        tree *mn = find_min(r); // O(h)
        mn->right = delete_min(r); // O(h)
        mn->left = l; // O(1)
        return balance(mn); // O(1)
    }
    return balance(tr); // O(1)
}
tree *find(tree *tr, int x) { // поиск элемента, O(h)
	if (tr == NULL || tr->x == x) return tr; // O(1)
	if (x < tr->x) return find(tr->left, x);
	return find(tr->right, x);
}
void preorder(tree *tr) { // прямой обход, O(n)
	if (tr == NULL) return;
	cout << tr->x << ' ';
	preorder(tr->left);
	preorder(tr->right);
}
void inorder(tree *tr) { // симметричный обход, O(n)
    if (tr == NULL) return;
    inorder(tr->left);
    cout << tr->x << ' ';
    inorder(tr->right);
}
void postorder(tree *tr) { // обратный обход, O(n)
	if (tr == NULL) return;
	postorder(tr->left);
	postorder(tr->right);
	cout << tr->x << ' ';
}
