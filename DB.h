#ifndef DB_H
#define DB_H

#include "LazyBST.cpp"
#include "Student.h"
#include "Faculty.h"
#include "TreeNode.h"
#include "DblList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DB{
    public:
    DB();
    virtual ~DB();
    void MainLoop();
    private:
    LBST<Student*>* StudentRecords;
    LBST<Faculty*>* FacultyRecords;
    void showMenu();
};

#endif