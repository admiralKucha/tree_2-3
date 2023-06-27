#pragma once
#include "unitClass.h"


class Node: public Unit {
public:
	int L = 0;
	int M = 0;
	Node(int _L, int _M, Unit* _child[], Node* _father);
	Node(int _L, int _M, Unit* _child[]);
	Node(int _L, int _M);
	virtual inline int get_L() const override { return L; };
	virtual int get_M() const override { return M; };
	virtual inline Unit* get_child(int i) const override{ return child[i]; };
	inline void ch_L(int i) { L = i; };
	inline void ch_M(int i) { M = i; };
	virtual inline bool isNode() const override { return true; };
	inline void right_dis() { child[2] = nullptr; };
	inline void ch_child(int i, Unit* _child) { child[i] = _child; };
	virtual inline void const print() override { std::cout << L << ":" << M << " "; };
};