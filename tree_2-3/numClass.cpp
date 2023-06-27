#include "numClass.h"

Num::Num(int _value, Node* _father) {
	value = _value;
	father = _father;
}

inline int Num::get_value() const
{
	return value;
}
