#pragma once
#include "nodeClass.h"
#include "numClass.h"

class Tree {
public:
	Unit* root;
	int f_s;
	Unit* find(int x);
	Tree();
	Node* search(int a, Unit* r);
	void add_son(Node* v, Unit* leaf);
	void insert(int a);
	void up_mark(Unit* v, Node* v_root, int i);
	void delet(int l);
	void deletNN(Node* l, int flag);
	void printTree();
};