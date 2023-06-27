#pragma once
#include <iostream>
class Unit;
class Node;

class Unit {
public:
	Node* father;
	Unit* child[3];
	virtual  int get_L() const { return 0; };
	virtual inline int get_M() const { return 0; };
	virtual inline Unit* get_child(int i) const { return nullptr; };
	virtual inline bool isNode() const { return true; };
	virtual inline int get_value() const { return -5345345; };
	virtual inline void const print() { return; };
	inline void ch_father(Node* new_father) { father = new_father; };
};