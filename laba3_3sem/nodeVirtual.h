#pragma once
#include <memory>
#include <string> 
#include "DynamicArrSequence.h"
#include <filesystem> 
using namespace std;

class node {
public:
	string name;
	string folder;
	node* parent;
	DynamicArrSequence<node*> children;

	virtual ~node() {}
	virtual bool isFile() = 0;

	virtual node& operator=(const node& right) {
		name = right.name;
		folder = right.folder;
		parent = right.parent;
		children = right.children;
		return *this;
	}

	string copy(string folder, node* head) {
		string h = folder.substr(0, folder.find('\\'));
		int i = h.size() + 1;
		node* ptr = head;
		if (h != head->name) {
			return "not copy";
		}
		string zagl = folder.substr(0, folder.find('\\'));
		folder = folder.substr(zagl.size() + 1);
		while (folder.find('\\') != string::npos) {
			string temp = folder.substr(0, folder.find('\\'));
			folder = folder.substr(temp.size() + 1);
			ptr = ptr->getFileInFolder(temp);
			if (ptr == nullptr) {
				return "not copy";
			}
		}
		ptr = ptr->getFileInFolder(folder);
		if (ptr == nullptr) {
			return "not copy";
		}
		if (ptr->isFile()) {
			return "this is not folder";
		}
		ptr->addElm(name,isFile());
		ptr->children[ptr->children.get_colElm() - 1]->children = this->children;
		return "copy";
	}

	string move(string folder, node* head) {
		string str = this->copy(folder, head);
		if (str != "copy") {
			return "not move";
		}
		if (this->parent != nullptr) {
			this->parent->deleteElm(this->name);
		}
		else {
			if (this->isFile() == false) {
				this->children.clearArr();
			}
			delete this;
		}
		return "move";
	}

	virtual bool addElm(string& name1,bool flag) = 0;

	virtual bool deleteElm(string& name1) = 0;

	virtual node* getFileInFolder(string& name1) = 0;

	string& getname() {
		return name;
	}

	shared_ptr<Dynamic_Array<node*>> search(node& current, string& name1) {
		Dynamic_Array<node*> queue;
		queue.push_back(&current);
		std::shared_ptr<Dynamic_Array<node*>> arr = std::make_shared<Dynamic_Array<node*>>();
		while (queue.get_colElm()) {
			if (queue[queue.get_colElm() - 1]->getname() == name1) {
				arr->push_back(queue[queue.get_colElm() - 1]);
			}
			int colElmOld = queue.get_colElm();
			for (int i = 0; i < queue[queue.get_colElm() - 1]->children.get_colElm(); ++i) {
				queue.push_back(queue[queue.get_colElm() - 1]->children[i]);
			}
			queue.pop_index(colElmOld - 1);
		}
		return arr;
	}
	virtual bool print() = 0;
	virtual bool print(node* node) = 0;

	node* getParent() {
		return parent;
	}

	virtual int getColElmInFolder() = 0;

	virtual bool traverse(string& str) = 0;

	struct Elm {
		string link;
		node* Node;
	};
	virtual void adder(Elm& elm) {};
	virtual void print(node& node, int colStar) = 0;

};