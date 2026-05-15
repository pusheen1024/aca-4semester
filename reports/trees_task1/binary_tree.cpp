struct tree { // узел дерева
    int x;
    tree *left;
    tree *right;
    tree *parent;
};
tree *node(int x) { // создание узла, O(1)
    tree *nw = new tree;
    nw->x = x;
    nw->left = NULL;
    nw->right = NULL;
    nw->parent = NULL;
    return nw;
}
tree *Min(tree *tr) { // минимальный элемент, O(h)
	if (! tr->left) return tr; // O(1)
	return Min(tr->left);
}
void Insert(tree *&tr, int x) { // вставка узла, O(h)
    tree *nw = node(x); // O(1)
    if (! tr) { // O(1)
		tr = nw; // O(1)
		return;
	}
	tree *t = tr; // O(1)
	while (t) { // O(h)
		if (nw->x > t->x) { // O(1)
			if (t->right) // O(1)
				t = t->right; // O(1)
			else {
				nw->parent = t; // O(1)
				t->right = nw; // O(1)
				break;
			}
		}
		else if (nw->x < t->x) { // O(1)
			if (t->left) // O(1)
				t = t->left; // O(1)
			else {
				nw->parent = t; // O(1)
				t->left = nw; // O(1)
				break;
			}
		}
		else break;
	}
}
tree *Find(tree *tr, int x) { // поиск элемента по значению, O(h)
    if (! tr || tr->x == x) return tr; // O(1)
    if (x < tr->x) return Find(tr->left, x);
    return Find(tr->right, x);
}
tree *nxt(tree *tr, int x) { // следующий элемент (upper_bound), O(h)
    tree *t = Find(tr, x); // O(h)
	if (! t) return NULL; // O(1)
    if (t->right) return Min(t->right); // O(h)
    tree *y = t->parent; // O(1)
    while (y && t == y->right) { // O(h)
        t = y; // O(1)
        y = y->parent; // O(1)
    }
    return y;
}
void Delete(tree *&tr, tree *&d) { // удаление узла, O(h)
	if (! d) return; // O(1)
    tree *p = d->parent; // O(1)
    if (!p && ! d->left && ! d->right) { // O(1)
		d = NULL; // O(1)
		tr = NULL; // O(1)
	}
    else if (p && ! d->left && ! d->right) { // O(1)
        if (p->left == d) p->left = NULL; // O(1)
		else if (p->right == d) p->right = NULL; // O(1)
		d = NULL; // O(1)
    }
    else if (! d->left || ! d->right) { // O(1)
        if (! p) { // O(1)
            if (! d->left) { // O(1)
                tr = d->right; // O(1)
				d->right->parent = NULL; // O(1)
                d->parent = NULL; // O(1)
            }
            else {
                tr = d->left; // O(1)
				d->right->parent = NULL; // O(1)
                d->parent = NULL; // O(1)
            }
			d = NULL; // O(1)
        }
        else {
            if (! d->left) { // O(1)
                if (p->left == d) p->left = d->right; // O(1)
                else p->right = d->right; // O(1)
                d->right->parent = p; // O(1)
            }
            else {
                if (p->left == d) p->left = d->left; // O(1)
                else p->right = d->left; // O(1)
                d->left->parent = p; // O(1)
            }
        }
		d = NULL; // O(1)
    }
    else {
        tree *s = nxt(tr, d->x); // O(h)
		d->x = s->x; // O(1)
		if (s->parent->left == s) { // O(1)
			s->parent->left = s->right; // O(1)
			if (s->right) s->right->parent = s->parent; // O(1)
		}
		else {
			s->parent->right = s->right; // O(1)
			if (s->right) s->right->parent = s->parent; // O(1)
		}
		s = NULL; // O(1)
    }
}
void inorder(tree *tr) { // симметричный обход, O(n)
    if(! tr) return;
	inorder(tr->left);
    cout << tr->x << ' ';
    inorder(tr->right);
}
void preorder(tree *tr) { // прямой обход, O(n)
	if (! tr) return;
	cout << tr->x << ' ';
	preorder(tr->left);
	preorder(tr->right);
}
void postorder(tree *tr) { // обратный обход, O(n)
	if (! tr) return;
	postorder(tr->left);
	postorder(tr->right);
	cout << tr->x << ' ';
}
