#pragma once
#include "unitClass.h"


class Num : public Unit {
public:
	int value = 0;
	Num(int _value, Node* _father);

	virtual inline bool isNode() const override { return false; };
	virtual inline int get_value() const override;
	virtual  int get_L() const override { return value; };
	virtual inline int get_M() const override { return value; };
	virtual inline void const print() override { std::cout << value << " "; };
};