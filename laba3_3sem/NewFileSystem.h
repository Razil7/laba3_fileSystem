#pragma once
#include "folder.h"

class fileTree {
	node* head;
public:


	fileTree(string& folder2) {
		string str = "";
		head = new Folder(folder2, str, nullptr);
	}
	fileTree() {
		string str = "";
		head = new Folder(str, str, nullptr);
	}

	~fileTree() {
		delete head;
	}
	void print() {
		head->print(head);
	}
	node* gethead() {
		return head;
	}
	node* traverse(string link) {
		head->traverse(link);
		return head;
	}
};
