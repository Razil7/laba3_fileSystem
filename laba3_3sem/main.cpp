#include "test.h"
#include"NewFileSystem.h"
#include "folder.h"
#include "file.h"
#include <string>
#include "DynamicArrSequence.h"
#include <filesystem> 
using namespace std;



void interface(node* headFolder) {
	node* YouInF = headFolder;
	int choise;

	do 
	{
		try {
			if (YouInF->isFile()) {
				std::cout << "\nYou in file: \n" << YouInF->getname();
			}
			else {
				std::cout << "You in folder: " << YouInF->getname();
				std::cout << "\n\n1) addFolder\n";
				std::cout << "2) addFile\n";
				std::cout << "3) print your folder\n";
				std::cout << "6) go to the folder item\n";
				std::cout << "7) delete an item from the folder where you are located";
			}
			std::cout << "\n4) print full folder\n";
			std::cout << "5) go to the parent folder\n";

			std::cin >> choise;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (choise)
			{
			case 1:
			{
				if (YouInF->isFile()) {
					break;
				}
				std::cout << "whrite folder name\n";
				string nameFolder;
				std::cin >> nameFolder;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				YouInF->addElm(nameFolder, false);
				break;
			}

			case 2:
			{
				if (YouInF->isFile()) {
					break;
				}
				std::cout << "whrite file name\n";
				string nameFile;
				std::cin >> nameFile;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				YouInF->addElm(nameFile, true);
				break;
			}

			case 3:
			{
				if (YouInF->isFile()) {
					break;
				}
				YouInF->print();
				std::cout << "\n";
				break;
			}

			case 4:
			{
				headFolder->print();
				std::cout << "\n";
				break;
			}

			case 5:
			{
				if (YouInF == headFolder) {
					break;
				}
				YouInF = YouInF->getParent();
				break;
			}
			case 6:
			{
				if (YouInF->isFile()) {
					break;
				}
				YouInF->print();
				if (YouInF->getColElmInFolder() == 0) {
					std::cout << "\nin folder 0 elm\n";
					break;
				}
				node* temp = nullptr;
				while (temp == nullptr)
				{
					std::cout << "\nwrite the name of the desired item\n";
					string name;
					std::cin >> name;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					temp = YouInF->getFileInFolder(name);
				}
				YouInF = temp;
				break;
			}

			case 7:
			{
				if (YouInF->isFile()) {
					break;
				}
				YouInF->print();
				std::cout << "\nwhrite file name\n";
				string nameFile;
				std::cin >> nameFile;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				node* temp = YouInF->getFileInFolder(nameFile);
				if (temp == nullptr) {
					std::cout << "name not found , deletion failed\n";
					break;
				}
				YouInF->deleteElm(nameFile);
				break;
			}

			default:
				break;
			}
		}
		catch (std::exception& e) {
			std::cout << "\nthe operation failed, try again" << std::endl;
		}
	} while (choise);
}




int main() {
	setlocale(LC_ALL, "RU");

	testAddFileToFolder();
	testAddFolderToFolder();
	testMoveFileToFolder();
	testCopyFileToFolder();
	testSearchFileInTree();
	testDeleteFile();


	std::cout << "\n\n1) create folder\n";
	std::cout << "2) add a folder from windows\n";
	int q;
	std::cin >> q;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch (q)
	{
	case 1:
	{
		std::cout << "whrite folder name\n";
		string name;
		std::cin >> name;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		fileTree folder(name);
		node* headFolder = folder.gethead();
		interface(headFolder);
		break;
	}

	case 2:
	{
		string str = "C:\\Users\\razil\\OneDrive\\Desktop\\����� �����";
		fileTree folder;
		node* headFolder = folder.traverse(str);
		interface(headFolder);
		break;
	}
	}

	return 0;
}
