#include "treeClass.h"

int main() {
	Tree a = Tree();
	a.insert(5);
	a.insert(10);
	a.insert(1);
	a.insert(3);
	a.insert(20);
	a.insert(4);
	a.insert(25);
	a.insert(0);
	a.insert(15);
	a.insert(11);
	a.delet(4);
	a.delet(3);
	a.printTree();
	return 0;
}

int main1() {
	Tree a = Tree();
	a.insert(-2);
	a.insert(23);
	a.insert(345);
	a.insert(645);
	a.insert(-123);
	a.insert(56);
	a.insert(76);
	a.insert(1);
	a.insert(10);
	a.insert(45);
	a.delet(-123);
	a.delet(-2);
	a.delet(23);
	a.delet(76);
	a.delet(45);
	a.delet(345);
	a.delet(56);
	a.delet(645);
	a.delet(10);
	a.printTree();
	return 0;
}