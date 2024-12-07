#include "fileSystem3.h"
#include <string>
#include "DynamicArrSequence.h"
#include <filesystem> 
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	//string namepapka1 = "papka1";
	//fileTree folder(namepapka1);
	//fileTree::node* papka1 = folder.gethead();
	//for (int i = 0; i < 1e7; i++) {
	//	string namepapka2 = "papka2";
	//	papka1->addfolder(namepapka2);
	//	fileTree::node* papka2 = papka1->getFileInFolder(namepapka2);
	//	for (int i = 0; i < 100; i++) {	
	//		papka2->addfolder(namepapka2);
	//	}
	//	papka1->deleteElm(namepapka2);
	//}
	
	//string str = "C:\\Users\\razil\\OneDrive\\Desktop\\����� �����";
	//fileTree folder ;
	//fileTree::node* papka = folder.traverse(str);
	//papka->print();

	std::cout << "whrite folder name\n";
	string name;
	std::cin >> name;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	fileTree folder(name);
	fileTree::node* headFolder = folder.gethead();

	fileTree::node* YouInF = headFolder;
	int choise;

	do
	{
		try {
			if (YouInF->get_isFile()) {
				std::cout << "\nYou in file: \n" << YouInF->getname();
			}
			else {
				std::cout << "You in folder: " << YouInF->getname();
				std::cout << "\n\n1) addFolder\n";
				std::cout << "2) addFile\n";
				std::cout << "3) print your folder\n";
				std::cout << "6) go to the folder item\n";
			}
			std::cout << "4) print full folder\n";
			std::cout << "5) go to the parent folder\n";
			
			std::cin >> choise;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			switch (choise)
			{
			case 1:
			{
				if (YouInF->get_isFile()) {
					break;
				}
				std::cout << "whrite folder name\n";
				string nameFolder;
				std::cin >> nameFolder;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				YouInF->addfolder(nameFolder);
				break;
			}

			case 2:
			{
				if (YouInF->get_isFile()) {
					break;
				}
				std::cout << "whrite file name\n";
				string nameFile;
				std::cin >> nameFile;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				YouInF->addfile(nameFile);
				break;
			}

			case 3:
			{
				if (YouInF->get_isFile()) {
					break;
				}
				YouInF->print();
				std::cout << "\n";
				break;
			}

			case 4:
			{
				folder.print();
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
				if (YouInF->get_isFile()) {
					break;
				}
				YouInF->print();
				if (YouInF->getColElmInFolder() == 0) {
					std::cout << "\nin folder 0 elm\n";
					break;
				}
				fileTree::node* temp = nullptr;
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

			default:
				break;
			}
		}
		catch (std::exception& e) {
			std::cout << "\nthe operation failed, try again" << std::endl;
		}
	} while (choise);
	return 0;
}