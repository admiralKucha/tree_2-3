#include "treeClass.h"

Unit* Tree::find(int x) {
	Unit* cur_node = root;
	while (cur_node->isNode()) {
		if (x <= cur_node->get_L()) {
			cur_node = cur_node->get_child(0);
		}
		else if (x <= cur_node->get_M() || cur_node->get_child(2) == nullptr) {
			cur_node = cur_node->get_child(1);
		}
		else {
			cur_node = cur_node->get_child(2);
		}
	}
	if (x == cur_node->get_value()) {
		return cur_node;
	}
	else {
		return nullptr;
	}
}

Tree::Tree() {
	root = nullptr;
}

Node* Tree::search(int a, Unit* r) {
	Unit* cur_node = r;
	while (cur_node->isNode()) {
		if (a <= cur_node->get_L()) {
			cur_node = cur_node->get_child(0);
			f_s = 0;
		}
		else if (a <= cur_node->get_M()) {
			cur_node = cur_node->get_child(1);
			f_s = 1;
		}
		else if (cur_node->get_child(2) == nullptr){
			cur_node = cur_node->get_child(1);
			f_s = 2;
		}
		else {
			cur_node = cur_node->get_child(2);
			f_s = 2;
		}
	}
	return cur_node->father;
}

void Tree::add_son(Node* v, Unit* leaf) {
	Unit* buf_v[3] = { v->get_child(2), leaf, nullptr };
	Node* v_new = new Node(v->get_child(2)->get_M(), leaf->get_M(), buf_v, nullptr);
	v->right_dis();

	leaf->ch_father(v_new);
	v_new->child[0]->ch_father(v_new);

	if (v == root) {
		Unit* buf_v[3] = { v, v_new, nullptr };
		Node* root_new = new Node(v->get_M(), leaf->get_M(), buf_v, nullptr);
		v_new->ch_father(root_new);
		v->ch_father(root_new);
		root = root_new;
	}
	else {
		Node* v_father = v->father;
		v_new->ch_father(v_father);
		Unit* first = v_father->get_child(1);
		int _M[2] = { v_new->get_M(), v_father->get_M() };

		if (v_father->get_child(2) == nullptr) {
			if (_M[0] < _M[1]) {
				v_father->ch_child(2, first);
				v_father->ch_child(1, v_new);
				v_father->ch_L(v->get_M());
				v_father->ch_M(v_new->get_M());
			}
			else {
				v_father->ch_child(2, v_new);
				v_father->ch_M(v->get_M());
				up_mark(v_new, v_father, v_new->get_M());
			}
		}
		else {
			if (_M[0] < _M[1]) {
				Unit* last = v_father->child[2];
				v_father->ch_child(2, v_father->child[1]);
				v_father->ch_child(1, v_new);

				v_father->ch_M(v_new->get_M());
				v_father->ch_L(v->get_M());
				
				add_son(v_father, last);

			}
			else if (_M[0] < v_father->child[2]->get_M()) {
				Unit* last = v_father->child[2];
				v_father->ch_child(2, v_new);
				v_father->ch_M(v->get_M());
				up_mark(v_new, v_father, v_new->get_M());
				add_son(v_father, last);
			}
			else {
				up_mark(v_father->child[2], v_father, v_father->child[2]->get_M());
				add_son(v_father, v_new);
			}
		}
	}
}

void Tree::insert(int a) {
	if (root == nullptr) {
		Num* new_v =  new Num(a, nullptr);
		root = new_v;
	}

	else if (!root->isNode()) {
		Node* new_root;
		Num* new_v;
		if (a > root->get_value()) {
			new_v = new Num(a, nullptr);
			Unit* buf_v[3] = { root, new_v, nullptr };
			new_root = new Node(root->get_value(), a, buf_v, nullptr);
		}
		else{
			new_v = new Num(a, nullptr);
			Unit* buf_v[3] = { new_v, root, nullptr };
			new_root = new Node(a, root->get_value(), buf_v, nullptr);
		}
		root->ch_father(new_root);
		new_v->ch_father(new_root);
		root = new_root;
	}

	else {
		Node* f = search(a, root);
		Num* new_v = new Num(a, f);
		if (f->get_child(2) == nullptr) {
			if (f_s == 0) {
				int sec = f->get_L();
				f->ch_child(2, f->get_child(1));
				f->ch_child(1, f->get_child(0));
				f->ch_child(0, new_v);
				f->ch_L(new_v->get_value());
				f->ch_M(sec);
			}
			else if (f_s == 1) {
				f->ch_child(2, f->get_child(1));
				f->ch_child(1, new_v);
				f->ch_M(new_v->get_value());
			}
			else {
				f->ch_child(2, new_v);
				up_mark(new_v, f, a);
			}
		}
		else {
			if (f_s == 0) {
				Unit* first = f->get_child(0);
				f->ch_M(first->get_M());
				Unit* fourth = f->get_child(2);
				f->ch_child(2, f->get_child(1));
				f->ch_child(1, first);
				f->ch_child(0, new_v);
				f->ch_L(a);
				add_son(f, fourth);
			}
			else if (f_s == 1) {
				f->ch_M(a);
				Unit* fourth = f->get_child(2);
				f->ch_child(2, f->get_child(1));
				f->ch_child(1, new_v);
				add_son(f, fourth);
			}
			else {
				Unit* third = f->get_child(2);
				if (third->get_value() > new_v->get_value()) {
					f->ch_child(2, new_v);
					add_son(f, third);
				}
				else {
					add_son(f, new_v);
				}
			}
		}
	}
}

void Tree::up_mark(Unit* v, Node* v_root, int i) {
	if (v_root == nullptr) {
		return;
	}
	if (v == v_root->get_child(0)) {
		v_root->ch_L(i);
	}
	else if (v == v_root->get_child(1)) {
		if (v_root->get_child(2) == nullptr) { //странно
			up_mark(v_root, v_root->father, i);
		}
		v_root->ch_M(i);
	}
	else {
		up_mark(v_root, v_root->father, i);
	}
}

void Tree::delet(int l) {
	if (l == root->get_value()) {
		root = nullptr;
		return;
	}
	Node* l_node = search(l, root);
	Unit* third = l_node->child[2];
	Unit* second = l_node->child[1];
	Unit* first = l_node->child[0];
	if (f_s == 0 && l != l_node->child[0]->get_value()) {
		return;
	}

	if (f_s == 1 && l != l_node->child[1]->get_value()) {
		return;
	}

	if (f_s == 2 && l != third->get_value()) {
		return;
	}

	if (third != nullptr) {
		if (f_s == 2) {
			up_mark(l_node, l_node->father, second->get_value());
			
			l_node->ch_child(2, nullptr);
		}
		else if(f_s == 1) {
			l_node->ch_child(1, third);
			l_node->ch_child(2, nullptr);
			up_mark(third, l_node, third->get_value()); // l_node->ch_M(third->get_value());
		}
		else {
			l_node->ch_child(0, second);
			l_node->ch_child(1, third);
			l_node->ch_child(2, nullptr);
			l_node->ch_L(second->get_value());
			l_node->ch_M(third->get_value());
		}

	}
	else {
		if (l_node == root) {
			if (f_s == 1) {
				root = first;
			}
			else {
				root = second;
			}
		}
		else {

			if (l_node->father->child[0] == l_node) { //правый брат
				Unit* smth = l_node->father->child[1]->get_child(2);
				Node* buf = dynamic_cast<Node*>(l_node->father->get_child(1));
				if (smth == nullptr) {
					if (f_s == 0) {
						smth = l_node->child[1];
						l_node->child[1]->ch_father(buf);
					}
					else {
						smth = l_node->child[0];
						l_node->child[0]->ch_father(buf);
					}
					buf->child[2] = buf->child[1];
					buf->child[1] = buf->child[0];
					buf->child[0] = smth;
					deletNN(l_node, 0);
					buf->ch_L(buf->child[0]->get_M());
					if (buf->child[1]->child[2] == nullptr) {
						up_mark(buf->child[1], buf, buf->child[1]->get_M());
					}
					else {
						up_mark(buf->child[1], buf, buf->child[1]->child[2]->get_M());
					}
				}
				else {
					smth = buf->child[0];
					buf->child[0] = buf->child[1];
					buf->child[1] = buf->child[2];
					buf->child[2] = nullptr;
					buf->ch_L(buf->child[0]->get_M());
					buf->ch_M(buf->child[1]->get_M());
					if (f_s == 0) {
						l_node->child[0] = l_node->child[1];
						l_node->child[1] = smth;
						smth->ch_father(l_node);
					}
					else {
						l_node->child[1] = smth;
						smth->ch_father(l_node);
					}
					l_node->ch_L(l_node->get_child(0)->get_M());
					up_mark(l_node->get_child(1), l_node, l_node->get_child(1)->get_M());
				}
			}
			else if (l_node->father->child[1] == l_node) { //левый брат
				Unit* smth = l_node->father->child[0]->child[2];
				Node * buf = dynamic_cast<Node*>(l_node->father->get_child(0));
				if (buf->child[2] == nullptr) {
					if (f_s == 0) {
						buf->ch_child(2, l_node->child[1]);
						l_node->child[1]->ch_father(buf);
					}
					else {
						buf->ch_child(2, l_node->child[0]);
						l_node->child[0]->ch_father(buf);
					}
					
					deletNN(l_node, 1);
					up_mark(buf->child[2], buf, buf->child[2]->get_M());
				}
				else {
					buf->child[2] = nullptr;
					up_mark(buf->child[1], buf, buf->child[1]->get_M()); //
					if (f_s == 0) {
						l_node->child[0] = smth;
						smth->ch_father(l_node);
					}
					else {
						l_node->child[1] = l_node->child[0];
						l_node->child[0] = smth;
						smth->ch_father(l_node);
					}
					l_node->ch_L(l_node->get_child(0)->get_M());
					l_node->ch_M(l_node->get_child(1)->get_M());
					up_mark(l_node, l_node->father, l_node->get_M());
				}
			}
			else { 
				Unit* smth = l_node->father->child[1]->child[2];
				Node* buf = dynamic_cast<Node*>(l_node->father->get_child(1));
				if (buf->child[2] == nullptr) {
					if (f_s == 0) {
						buf->ch_child(2, l_node->child[1]);
						l_node->child[1]->ch_father(buf);
					}
					else {
						buf->ch_child(2, l_node->child[0]);
						l_node->child[0]->ch_father(buf);
					}				
					deletNN(l_node, 2);
					up_mark(buf->child[2], buf, buf->child[2]->get_M());
				}
				else {
					buf->child[2] = nullptr;
					up_mark(buf->child[1], buf, buf->child[1]->get_M());
					if (f_s == 0) {
						l_node->child[0] = smth;
						smth->ch_father(l_node);
					}
					else {
						l_node->child[1] = l_node->child[0];
						l_node->child[0] = smth;
						smth->ch_father(l_node);
					}
					l_node->ch_L(l_node->get_child(0)->get_M());
					l_node->ch_M(l_node->get_child(1)->get_M());
					up_mark(l_node, l_node->father, l_node->get_M());
				}
			}

		}
	}
}

void Tree::deletNN(Node* l, int flag) {
	Node* l_node = l->father;
	if (l_node == root) {
		if (root->child[2] == nullptr) {
			if (l_node->child[0] == l) {
				root = l_node->child[1];
				return;
			}
			else {
				root = l_node->child[0];
				return;
			}
		}
		else {
			if (l == root->child[2]) {
				root->child[2] = nullptr;
			}
			else if (l == root->child[1]) {
				root->child[1] = root->child[2];
				root->child[2] = nullptr;
			}
			else {

				root->child[0] = root->child[1];
				root->child[1] = root->child[2];
				root->child[2] = nullptr;
			}
			l_node->ch_M(root->child[1]->get_M());
			return;
		}
	}

	Unit* third = l_node->child[2];
	Unit* second = l_node->child[1];
	Unit* first = l_node->child[0];
	if (third != nullptr) {
		if (flag == 2) {
			up_mark(l_node, l_node->father, second->get_value());
			l_node->ch_child(2, nullptr);
		}
		else if (flag == 1) {
			l_node->ch_child(1, third);
			l_node->ch_child(2, nullptr);
			up_mark(third, l_node, third->get_value()); // l_node->ch_M(third->get_value());
		}
		else {
			l_node->ch_child(0, second);
			l_node->ch_child(1, third);
			l_node->ch_child(2, nullptr);
			l_node->ch_L(second->get_value());
			l_node->ch_M(third->get_value());
		}

	}
	else {
		if (l_node == root) {
			if (flag == 1) {
				root = first;
			}
			else {
				root = second;
			}
		}
		else {

			if (l_node->father->child[0] == l_node) { //правый брат
				Unit* smth = l_node->father->child[1]->get_child(2);
				Node* buf = dynamic_cast<Node*>(l_node->father->get_child(1));
				if (smth == nullptr) {
					if (flag == 0) {
						smth = l_node->child[1];
						l_node->child[1]->ch_father(buf);
					}
					else {
						smth = l_node->child[0];
						l_node->child[0]->ch_father(buf);
					}
					buf->child[2] = buf->child[1];
					buf->child[1] = buf->child[0];
					buf->child[0] = smth;
					deletNN(l_node, 0);
					buf->ch_L(buf->child[0]->get_M());
					if (buf->child[1]->child[2] == nullptr) {
						up_mark(buf->child[1], buf, buf->child[1]->get_M());
					}
					else {
						up_mark(buf->child[1], buf, buf->child[1]->child[2]->get_M());
					}
				}
				else {
					smth = buf->child[0];
					buf->child[0] = buf->child[1];
					buf->child[1] = buf->child[2];
					buf->child[2] = nullptr;
					buf->ch_L(buf->child[0]->get_M());
					buf->ch_M(buf->child[1]->get_M());
					if (flag == 0) {
						l_node->child[0] = l_node->child[1];
						l_node->child[1] = smth;
						smth->ch_father(l_node);
					}
					else {
						l_node->child[1] = smth;
						smth->ch_father(l_node);
					}
					l_node->ch_L(l_node->get_child(0)->get_M());
					up_mark(l_node->get_child(1), l_node, l_node->get_child(1)->get_M());
				}
			}
			else if (l_node->father->child[1] == l_node) { //левый брат
				Unit* smth = l_node->father->child[0]->child[2];
				Node* buf = dynamic_cast<Node*>(l_node->father->get_child(0));
				if (buf->child[2] == nullptr) {
					if (flag == 0) {
						buf->ch_child(2, l_node->child[1]);
						l_node->child[1]->ch_father(buf);
					}
					else {
						buf->ch_child(2, l_node->child[0]);
						l_node->child[0]->ch_father(buf);
					}
					deletNN(l_node, 1);
					up_mark(buf->child[2], buf, buf->child[2]->get_M());
				}
				else {
					buf->child[2] = nullptr;
					up_mark(buf->child[1], buf, buf->child[1]->get_M()); //
					if (flag == 0) {
						l_node->child[0] = smth;
						smth->ch_father(l_node);
					}
					else {
						l_node->child[1] = l_node->child[0];
						l_node->child[0] = smth;
						smth->ch_father(l_node);
					}
					l_node->ch_L(l_node->get_child(0)->get_M());
					l_node->ch_M(l_node->get_child(1)->get_M());
					up_mark(l_node, l_node->father, l_node->get_M());
				}
			}
			else {
				Unit* smth = l_node->father->child[1]->child[2];
				Node* buf = dynamic_cast<Node*>(l_node->father->get_child(1));
				if (buf->child[2] == nullptr) {
					if (flag == 0) {
						buf->ch_child(2, l_node->child[1]);
						l_node->child[1]->ch_father(buf);
					}
					else {
						buf->ch_child(2, l_node->child[0]);
						l_node->child[0]->ch_father(buf);
					}
					l_node;
					deletNN(l_node, 2);
					up_mark(buf->child[2], buf, buf->child[2]->get_M());
				}
				else {
					buf->child[2] = nullptr;
					up_mark(buf->child[1], buf, buf->child[1]->get_M());
					if (f_s == 0) {
						l_node->child[0] = smth;
						smth->ch_father(l_node);
					}
					else {
						l_node->child[1] = l_node->child[0];
						l_node->child[0] = smth;
						smth->ch_father(l_node);
					}
					l_node->ch_L(l_node->get_child(0)->get_M());
					l_node->ch_M(l_node->get_child(1)->get_M());
					up_mark(l_node, l_node->father, l_node->get_M());
				}
			}

		}
	}
}

void Tree::printTree() {
	if (root == nullptr) {
		return;
	}
	int size = 1;  // Максимальный размер массива
	Unit** ptr = new Unit *[size];

	int front;
	int rear = 1;

	int le;
	ptr[0] = root;
	while (ptr[0]->isNode()) {
		size = size * 3;
		Unit** next_queue = new Unit* [size];
		le = rear;
		front = 0;
		rear = 0;
		while (front < le) {
			if (ptr[front] == nullptr) {
				front++;
			}
			else{
				Unit* curr = ptr[front];
				curr->print();
				next_queue[rear++] = curr->get_child(0);
				next_queue[rear++] = curr->get_child(1);
				next_queue[rear++] = curr->get_child(2);
				front++;
			}
			std::cout << "  ";
		}
		std::cout << std::endl;
		ptr = next_queue;
	}
	for (int i = 0; i < rear; i++) {
		if (ptr[i] == nullptr) {
			std::cout << "  ";
		}
		else {
			ptr[i]->print();
		}
	}

}