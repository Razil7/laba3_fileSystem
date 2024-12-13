#pragma once

#include "nodeVirtual.h"
#include "file.h"
#include "DynamicArrSequence.h"
#include <filesystem> 
#include <string> 

using namespace std;
class Folder : public node {
public:

	Folder() {
		name = "";
		folder = " ";
		parent = nullptr;
	}
	Folder(string& name1, string& folder1, Folder* parent1)   {
		name = name1;
		folder = folder1;
		parent = parent1;
	
	}
	Folder(const Folder& right)   {
		name = right.name;
		folder = right.folder;
		parent = right.parent;
		children = right.children;
	}


	Folder& operator=(const Folder& right) {
		name = right.name;
		folder = right.folder;
		parent = right.parent;
		children = right.children;
		return *this;
	}

	bool isFile() override {
		return false;
	}
	bool addElm(string& name1, bool flag) override {
		string str = folder + "\\" + name;
		if (flag) {
			file* file2 = new file(name1, str, this);
			children.push_back(file2);
			return true;
		}
		else {
			Folder* file2 = new Folder(name1, str, this);
			children.push_back(file2);
			return true;
		}
	}

	bool deleteElm(string& name1) override {
		if (children.get_colElm() == 0) {
			return false;
		}

		for (int i = 0; i < children.get_colElm(); i++) {
			if (name1 == children[i]->getname()) {
				if (!children[i]->isFile()) {
					children[i]->children.clearArr();
				}
				children.pop_index(i);
				break;
			}
		}
		return true;
	}

	node* getFileInFolder(string& name1) override {
		for (int i = 0; i < children.get_colElm(); i++) {
			if (name1 == children[i]->getname()) {
				return children[i];
			}
		}
		return nullptr;
	}
	bool print() override {
		this->print(*this, 0);
		return true;
		
	}
	bool print(node* node) override {
		this->print(*node, 0);
		return true;
	}
	int getColElmInFolder() override {
		return children.get_colElm();
	}
	bool traverse(string& str) override {
		filesystem::path p(str);
		name = p.filename().string();
		Dynamic_Array<Elm> arr;
		arr.push_back(Elm{ str,this });
		while (arr.get_colElm() > 0) {
			int colElm = arr.get_colElm();
			for (int i = 0; i < colElm; i++) {
				arr[i].Node->adder(arr[i]);
			}
			for (int i = 0; i < colElm; i++) {
				for (int q = 0; q < arr[0].Node->getColElmInFolder(); q++) {

					if (!arr[0].Node->isFile()) {
						arr[0].Node->children[q];
						arr.push_back(Elm{ arr[0].link + '\\' + arr[0].Node->children[q]->getname() , arr[0].Node->children[q] });
					}

				}
				arr.pop_index(0);
			}
		}
		return true;
	}

private:
	void adder(Elm& elm) override {
		if (elm.Node->isFile()) {
			return;
		}
		for (auto& folder : filesystem::directory_iterator(elm.link)) {
			string Name = folder.path().filename().string();
			elm.Node->addElm(Name, !(folder.is_directory()));
		}
	}
	void print(node& node, int colStar) override {

		cout << "\n";
		for (int i = 0; i < colStar; i++) {
			cout << "*";
		}
		cout << node.name;

		if (node.children.get_colElm() == 0) {
			return;
		}

		for (int i = 0; i < node.children.get_colElm(); i++) {
			print(*node.children[i], colStar + 1);
		}
	}
};