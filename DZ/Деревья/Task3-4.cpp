#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
using namespace std;

ifstream in("input.txt");

struct tree {
	int inf;
	tree * right;
	tree * left;
	};

tree * node(int x) {
	tree * n = new tree;
	n->inf = x;
	n->left = n->right = NULL;
	return n;
}

void create(tree * &tr, int n) {
	int x;
	if (n > 0) {
		cin >> x;
		tr = node(x);
		int nl = n / 2;
		int nr = n - nl - 1;
		create(tr->left, nl);
		create(tr->right, nr);
	}
}

void preorder(tree * tr) {
	if (tr) {

		cout << tr->inf << " ";
		
		preorder(tr->left);
		preorder(tr->right);
	}
}

int lefth(tree * tr) {
	int k = 0;
	tree * x = tr;
	while (x) {
		k++;
		x = x->left;
	}
	return k - 1;
}
int righth(tree * tr) {
	int k = 0;
	tree * x = tr;
	while (x) {
		k++;
		x = x->right;
	}
	return k - 1;
}

void add(tree * &tr, int x) {
	tree * n = node(x);
	tree * y = tr;
	if (lefth(tr) == righth(tr)) {
		do {
			y = y->left;
		}
		while (y->left);
		if (!y->left) y->left = n;
		else y->right = n;
	}
	else {
		do {
			y = y->right;
		}
		while (y->right);
		if (!y->left) y->left = n;
		else y->right = n;
	}
}

void find(tree * tr, int x, tree * &res) {
	if (tr) {
		if (tr->inf == x) {
			res = tr;
		}
		else {
			find(tr->left, x, res);
			find(tr->right, x, res);
		}
	}
}


void find_vic(tree* tr, int x, int n, int &a) {
	if (tr) {
		if (tr->inf == x) {
			cout << "? " << n << " ?  ";
			a = n;
		}
		else {
			n++;
			find_vic(tr->left, x, n, a);
			find_vic(tr->right, x, n, a);
		}
	}
}

void del_n(tree * tr, int val) {
	tree * y;
	find(tr, val, y);
	if (y) {
		if (lefth(tr) == 0) tr = NULL;
			else if (lefth(tr) != righth(tr)) {
			tree * x = tr->left;
			do {
				x = x->left;
			}
			while (x->left->left);
			if (x->right) {
				if (x->right->inf == val) {
					x->right = NULL;
				}
				else {
					y->inf = x->right->inf;
					x->right = NULL;
				}
				delete x->right;
			}
			else {
				if (x->left->inf == val) {
					x->left = NULL;
				}
				else {
					y->inf = x->left->inf;
					x->left = NULL;
				}
				delete x->left;
			}
		}
		else {
			tree * x = tr->right;
			do {
				x = x->right;
			}
			while (x->right->right);
			if (x->right) {
				if (x->right->inf == val) {
					x->right = NULL;
				}
				else {
					y->inf = x->right->inf;
					x->right = NULL;
				}
				delete x->right;
			}
			else {
				if (x->left->inf == val) {
					x->left = NULL;
				}
				else {
					y->inf = x->left->inf;
					x->left = NULL;
				}
				delete x->left;
			}
		}
	}
}

void print(tree * tr, int k) {
	if (!tr) cout << "Empty tree\n";
	else {
		queue<tree*> cur, next;
		tree * r = tr;
		cur.push(r);
		int j = 0;
		while (cur.size()) {
			if (j == 0) {
				for (int i = 0; i < (int)pow(2.0, k) - 1; i++)
					cout << " ";
			}
			tree * buf = cur.front();
			cur.pop();
			j++;
			if (buf) {
				cout << buf->inf;
				next.push(buf->left);
				next.push(buf->right);
				for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
					cout << " ";
			}
				if (!buf) {
				for (int i = 0; i < (int)pow(2.0, k + 1) - 1; i++)
					cout << " ";
				cout << " ";
			}
			if (cur.empty()) {
				cout << endl;
				swap(cur, next);
				j = 0;
				k--;
			}
		
		}
	}
}

int countLeaves(tree* root) {
	if (root == nullptr) {
		return 0;
	}

	if (root->left == nullptr && root->right == nullptr) {
		return 1;
	}

	return countLeaves(root->left) + countLeaves(root->right);
}


int main() {
	tree * tr = NULL;
	int n, x;

	cout << "n: ";
	cin >> n;
	create(tr, n);

	int k = int(log((float)n) / log((float)2.0));
	print(tr, k);

	preorder(tr);
	cout << endl;

	cout << lefth(tr) << " " << righth(tr) << endl;

	cout << "Task 3: " << countLeaves(tr) << endl;

	int a;
	int y;
	cout << "y: ";
	cin >> y;
	find_vic(tr, y, 0, a);
	cout << "Task 4: " << a << endl;



	cout << "x=";
	cin >> x;
	add(tr, x);
	n++;
	k = int(log((float)n) / log((float)2.0));
	print(tr, k);
	preorder(tr);
	cout << endl;
	cout << " del node: ";
	cin >> x;
	del_n(tr, x);
	n--;
	k = int(log((float)n) / log((float)2.0));
	print(tr, k);
	preorder(tr);
	cout << endl;
	return 0;
}
