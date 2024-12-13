
#include "test.h"
#include <iostream>
#include <string>
#include <cassert>
#include "NewFileSystem.h" 


using namespace std;

void testAddFileToFolder() {
    try {
        string rootFolder = "root";
        fileTree ft(rootFolder);

        string fileName = "file1.txt";
        ft.gethead()->addElm(fileName,true);

        assert(ft.gethead()->getColElmInFolder() == 1);
        assert(ft.gethead()->getFileInFolder(fileName)->isFile() == true);
        assert(ft.gethead()->getFileInFolder(fileName)->getname() == fileName);

        cout << "testAddFileToFolder complete!" << endl;
    }
    catch (const exception& e) {
        cout << "testAddFileToFolder failed: " << e.what() << endl;
    }
}

void testAddFolderToFolder() {
    try {
        string rootFolder = "root";
        fileTree ft(rootFolder);

        string folderName = "folder1";
        ft.gethead()->addElm(folderName,false);

        assert(ft.gethead()->getColElmInFolder() == 1);
        assert(!ft.gethead()->getFileInFolder(folderName)->isFile() == true);
        assert(ft.gethead()->getFileInFolder(folderName)->getname() == folderName);

        cout << "testAddFolderToFolder complete!" << endl;
    }
    catch (const exception& e) {
        cout << "testAddFolderToFolder failed: " << e.what() << endl;
    }
}

void testMoveFileToFolder() {
    try {
        string rootFolder = "root";
        fileTree ft(rootFolder);

        string fileName = "file1.txt";
        ft.gethead()->addElm(fileName,true);

        string folderName = "folder1";
        ft.gethead()->addElm(folderName, false);

        // Переместить file1.txt в folder1
        ft.gethead()->getFileInFolder(fileName)->move("root\\folder1", ft.gethead());

        assert(ft.gethead()->getFileInFolder(folderName)->getColElmInFolder() == 1);
        assert(ft.gethead()->getFileInFolder(folderName)->getFileInFolder(fileName)->getname() == fileName);

        cout << "testMoveFileToFolder complete!" << endl;
    }
    catch (const exception& e) {
        cout << "testMoveFileToFolder failed: " << e.what() << endl;
    }
}

void testCopyFileToFolder() {
    try {
        string rootFolder = "root";
        fileTree ft(rootFolder);

        string fileName = "file1.txt";
        ft.gethead()->addElm(fileName,true);

        string folderName = "folder1";
        ft.gethead()->addElm(folderName,false);

        // Скопировать file1.txt в folder1
        ft.gethead()->getFileInFolder(fileName)->copy("root\\folder1", ft.gethead());

        assert(ft.gethead()->getFileInFolder(folderName)->getColElmInFolder() == 1);
        assert(ft.gethead()->getFileInFolder(folderName)->getFileInFolder(fileName)->getname() == fileName);

        cout << "testCopyFileToFolder complete!" << endl;
    }
    catch (const exception& e) {
        cout << "testCopyFileToFolder failed: " << e.what() << endl;
    }
}

void testSearchFileInTree() {
    try {
        string rootFolder = "root";
        fileTree ft(rootFolder);

        string fileName = "file1.txt";
        ft.gethead()->addElm(fileName, true);

        string searchName = "file1.txt";
        auto result = ft.gethead()->search(*(ft.gethead()), searchName);

        assert(result->get_colElm() == 1);
        assert((*result)[0]->getname() == searchName);

        cout << "testSearchFileInTree complete!" << endl;
    }
    catch (const exception& e) {
        cout << "testSearchFileInTree failed: " << e.what() << endl;
    }
}
void testDeleteFile() {
    try {
        string rootFolder = "root";
        fileTree ft(rootFolder);

        string fileName = "file1.txt";
        ft.gethead()->addElm(fileName,true);

        ft.gethead()->deleteElm(fileName);

        assert(ft.gethead()->getColElmInFolder() == 0);

        cout << "testDeleteFile complete!" << endl;
    }
    catch (const exception& e) {
        cout << "testDeleteFile failed: " << e.what() << endl;
    }
}

