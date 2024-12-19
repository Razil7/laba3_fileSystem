#pragma once
#include <string> 
#include "nodeVirtual.h"

class file : public node {
public:
	file()  {
		name = "";
		folder = "";
		parent = nullptr;
	
	}
	file(string& name1, string& folder1, node* parent1)  {
		name = name1;
		folder = folder1;
		parent = parent1;
	}
	file(const file& right)  {
		name = right.name;
		folder = right.folder;
		parent = right.parent;
		children = right.children;
	}

	file& operator=(const file& right) {
		name = right.name;
		folder = right.folder;
		parent = right.parent;
		children = right.children;
		return *this;
	}

	bool isFile() override {
		return true;
	}
	bool addElm(string& name1, bool flag) override {
		return false;
	}

	bool deleteElm(string& name1) override {
		return false;
	}

	node* getFileInFolder(string& name1) override {
		return nullptr;
	}
	bool print() override {
		return false;
	}
	bool print(node* node) override {
		return false;
	}
	int getColElmInFolder() override {
		return -1;
	}
	bool traverse(string& str) override {
		return false;
	}

private :
	 void adder(Elm& elm) override {}
	 void print(node& node, int colStar) override {}
};