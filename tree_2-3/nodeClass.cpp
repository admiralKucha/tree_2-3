#include "nodeClass.h"

Node::Node(int _L, int _M, Unit* _child[], Node* _father) {
	L = _L;
	M = _M;
	for (int i = 0; i < 3; i++) {
		child[i] = _child[i];
	}
	father = _father;
}

Node::Node(int _L, int _M, Unit* _child[]) {
	L = _L;
	M = _M;
	for (int i = 0; i < 3; i++) {
		child[i] = _child[i];
	}
	father = nullptr;
}

Node::Node(int _L, int _M) {
	L = _L;
	M = _M;
	for (int i = 0; i < 3; i++) {
		child[i] = nullptr;
	}
	father = nullptr;
}