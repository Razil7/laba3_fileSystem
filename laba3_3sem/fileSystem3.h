#pragma once
#include <string> 
#include "DynamicArrSequence.h"
#include <filesystem> 


using namespace std;
class fileTree {
public:
	class node {
		string name;
		string folder;
		node* parent;
		DynamicArrSequence<node> children;
		bool isFile;


	public:

		node() : name(""), isFile(true), folder(""), parent(nullptr) {}
		node(string& name1, bool flag, string& folder1, node* parent1) : name(name1), isFile(flag), folder(folder1), parent(parent1) {}
		node(const node& right): name(right.name), folder(right.folder) , parent(right.parent), children(right.children) , isFile(right.isFile){}
		//node(node&& right): name(move(right.name)) , folder(move(right.folder)), parent(move(right.parent)), 
		//										children(move(right.children)), isFile(move(right.isFile)) {}
		node& operator=(const node& right) {
			name = right.name;
			folder = right.folder;
			parent = right.parent;
			children = right.children;
			isFile = right.isFile;
			return *this;
		}

		/*node& operator=(node&& right) {
			name = move(right.name);
			folder = move(right.folder);
			parent = move(right.parent);
			parent = nullptr;
			children = move(right.children);
			isFile = move(right.isFile);
			return *this;
		}*/

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
			if (ptr->isFile) {
				return "this is not folder";
			}
			ptr->addElm(name, isFile);
			ptr->children[ptr->children.get_colElm() - 1].children = this->children;
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
				if (this->isFile == false) {
					this->children.clearArr();
				}
				delete this;
			}
			return "move";
		}

		void addfile(string& name1) {
			addElm(name1, true);
		}
		void addfolder(string& name1) {
			addElm(name1, false);
		}
		void addElm(string& name1, bool flag) {
			if (isFile) {
				return;
			}
			string str = folder + "\\" + name;
			node file(name1, flag, str, this);
			children.push_back(file);
		}
		void deleteElm(string& name1) {
			if (isFile) {
				return;
			}
			if (children.get_colElm() == 0) {
				return;
			}

			for (int i = 0; i < children.get_colElm(); i++) {
				if (name1 == children[i].getname()) {
					if (!children[i].get_isFile()) {
						children[i].children.clearArr();
					}
					children.pop_index(i);
					break;
				}
			}
		}

		node* getFileInFolder(string& name1) {
			if (isFile) {
				return nullptr;
			}
			for (int i = 0; i < children.get_colElm(); i++) {
				if (name1 == children[i].getname()) {
					return &children[i];
				}
			}
			return nullptr;
		}
		string& getname() {
			return name;
		}
		bool get_isFile() {
			return isFile;
		}

		DynamicArrSequence<node*>* search(node& current, string& name1) {
			DynamicArrSequence<node*> queue;
			queue.push_back(&current);
			DynamicArrSequence<node*>* arr = new DynamicArrSequence<node*>;
			while (queue.get_colElm()) {
				if (queue[queue.get_colElm() - 1]->getname() == name1) {
					arr->push_back(queue[queue.get_colElm() - 1]);
				}
				int colElmOld = queue.get_colElm();
				for (int i = 0; i < queue[queue.get_colElm() - 1]->children.get_colElm(); ++i) {
					queue.push_back(&queue[queue.get_colElm() - 1]->children[i]);
				}
				queue.pop_index(colElmOld -1);
			}
			return arr;
		}
		void print() {
			this->print(*this, 0);
		}
		void print(node& node) {
			this->print(node, 0);
		}

		node* getParent() {
			return parent;
		}

		int getColElmInFolder() {
			return children.get_colElm();
		}

		void traverse(string& str) {
			filesystem::path p(str);
			name = p.filename().string();
			DynamicArray<Elm> arr;
			arr.push_back(Elm{ str,this });
			while (arr.get_colElm() > 0) {
				int colElm = arr.get_colElm();
				for (int i = 0; i < colElm; i++) {
					arr[i].Node->adder(arr[i]);
				}
				for (int i = 0; i < colElm; i++) {
					for (int q = 0; q < arr[0].Node->getColElmInFolder(); q++) {

						if (!arr[0].Node->get_isFile()) {
						    arr[0].Node->children[q];
							arr.push_back(Elm{ arr[0].link + '\\' + arr[0].Node->children[q].getname() , &arr[0].Node->children[q] });
						}

					}
					arr.pop_index(0);
				}
			}
		}

	private:
		struct Elm {
			string link;
			node* Node;
		};
		void adder(Elm& elm) {
			if (elm.Node->get_isFile()) {
				return;
			}
			for (auto& folder : filesystem::directory_iterator(elm.link)) {
				string Name = folder.path().filename().string();
				elm.Node->addElm(Name, !(folder.is_directory()));
			}
		}
		void print(node& node, int colStar) {

			cout << "\n";
			for (int i = 0; i < colStar; i++) {
				cout << "*";
			}
			cout << node.name;

			if (node.children.get_colElm() == 0) {
				return;
			}

			for (int i = 0; i < node.children.get_colElm(); i++) {
				print(node.children[i], colStar + 1);
			}
		}
	};

	fileTree(string& folder) {
		string str = "";
		node node2(folder, false, str, nullptr);
		head  = node2;
	}
	fileTree() {
		string str = "";
		node node2(str, false, str, nullptr);
		head = node2;
	}
	void print() {
		head.print(head);
	}
	node* gethead() {
		return &head;
	}

	node* traverse(string link) {
		head.traverse(link);
		return &head;
	}

private:
	node head;
};