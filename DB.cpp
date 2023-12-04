#include "DB.h"
#include "Faculty.h"
#include "Student.h"
#include "DblList.h"
#include <iostream>
#include <string>

using namespace std;

DB::DB(){
    StudentRecords = new LBST<Student*>();
    FacultyRecords = new LBST<Faculty*>();
}

DB::~DB(){
    if(StudentRecords != NULL){
        delete StudentRecords;
    }
    if(FacultyRecords != NULL){
        delete FacultyRecords;
    }
}

void DB::MainLoop(){

    DblList<int>* preloadFaculty1Advisees = new DblList<int>();
    preloadFaculty1Advisees->addFront(1);
    preloadFaculty1Advisees->addFront(2);
    DblList<int>* preloadFaculty2Advisees = new DblList<int>();
    preloadFaculty2Advisees->addFront(3);
    preloadFaculty2Advisees->addFront(4);
    Faculty* preloadFaculty1 = new Faculty(1, "Eddard Stark", "Senior Associate Dean", "Fowler School of Engineering", preloadFaculty1Advisees);
    Faculty* preloadFaculty2 = new Faculty(2, "Daenerys Targaryen", "Program Director for the Faculty of Engineering", "Fowler School Of Engineering", preloadFaculty2Advisees);
    Student* preloadStudent1 = new Student(1, "Tywin Lannister", "Junior", "Mechanical Engineering", 4.0, 1);
    Student* preloadStudent2 = new Student(2, "Margaery Tyrell", "Senior", "Data Science", 3.75, 1);
    Student* preloadStudent3 = new Student(3, "Jon Snow ", "Freshman", "Computer Science", 2.0, 2);
    Student* preloadStudent4 = new Student(4, "Robert Arryn", "Sophomore", "Electrical Engineering", 3.5, 2);
    FacultyRecords->insert(preloadFaculty1);
    FacultyRecords->insert(preloadFaculty2);
    StudentRecords->insert(preloadStudent1);
    StudentRecords->insert(preloadStudent3);
    StudentRecords->insert(preloadStudent2);
    StudentRecords->insert(preloadStudent4);

    bool dbOpen = true;

    std::ofstream file;
    file.open("runLog.txt", std::ios_base::out);
    file << "";
    file.close();

    while(dbOpen){
        int choice;
        showMenu();
        while(!(cin >> choice)){ 
            cout << "Error! Non integer value entered! Please try again. " << endl;
            cin.clear();
            cin.ignore(40,'\n');
        }
        switch(choice){
            case 1:
                StudentRecords->printInfo();
                break;
            case 2:
                FacultyRecords->printInfo();
                break;
            case 3:
            {
                int sId;
                cout << "| FIND STUDENT BY ID |" << endl;
                cout << "Please enter a students id: ";
                while(!(cin >> sId) || !StudentRecords->existingId(sId)){
                    if(sId == -1){
                        break;
                    }
                    cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                    cin.clear();
                }
                if(sId != -1){
                    cout << endl;
                    StudentRecords->getWithIdThenPrint(sId);
                }
                break;
            }
            case 4:
            {
                int facultyId;
                cout << "| FIND FACULTY MEMBER BY ID |" << endl;
                cout << "Please enter a faculty member's id: ";
                while(!(cin >> facultyId) || !FacultyRecords->existingId(facultyId)){
                    if(facultyId == -1){
                        break;
                    }
                    cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                    cin.clear();
                }
                if(facultyId != -1){
                    cout << endl;
                    FacultyRecords->getWithIdThenPrint(facultyId);
                }
                break;
            }
            case 5:
            {
                if(FacultyRecords->getSize() == 0){ 
                    cout << "Please add a faculty member before adding a student. Current faculty size is 0." << endl;
                }else{
                    int newStudentId;
                    std::string newStudentName, newStudentLevel, newStudentMajor;
                    double newStudentGPA;
                    int newStudentAdvisorId;
                    cout << "| ADD STUDENT |" << endl;
                    cout << "Please enter a new students unique id number: ";
                    while(!(cin >> newStudentId) || StudentRecords->existingId(newStudentId)){ 
                        if(newStudentId == -1){
                            break;
                        }
                        cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                        cin.clear();
                        cin.ignore(40,'\n');
                    }
                    if(newStudentId == -1){
                        break;
                    }
                    cout << endl;
                    cout << "Please enter the new student's name: ";
                    getline(cin.ignore(1, '\n'), newStudentName); 
                    cout << endl;
                    cout << "Please enter the new student's school standing: ";
                    getline(cin, newStudentLevel);
                    cout << endl;
                    cout << "Please enter the new student's major: ";
                    getline(cin, newStudentMajor);
                    cout << endl;
                    cout << "Please enter the new student's gpa: ";
                    while(!(cin >> newStudentGPA)){
                        cout << "Error! Non decimal value entered! Please try again. " << endl;
                        cin.clear();
                        cin.ignore(40,'\n');
                    }
                    cout << endl;
                    cout << "Please enter the new students advisors id number or type -1 to cancel: ";
                    while(!(cin >> newStudentAdvisorId) || !FacultyRecords->existingId(newStudentAdvisorId)){
                        if(newStudentAdvisorId == -1){
                            break;
                        }
                        cout << "Error! Non integer value entered or Faculty ID does not exist, please try again! " << endl;
                        cin.clear();
                        cin.ignore(40,'\n');
                    }
                    if(newStudentAdvisorId == -1){
                            break;
                    }
                    cout << endl;
                    FacultyRecords->getWithId(newStudentAdvisorId)->addAdvisee(newStudentId);
                    Student* stud = new Student(newStudentId, newStudentName, newStudentLevel, newStudentMajor, newStudentGPA, newStudentAdvisorId);
                    StudentRecords->insert(stud);
                    cout << "Student successfully added to database!" << endl;   
                }
                break;
            }
            case 6:
            {
                int deleteStudentId;
                cout << "| DELETE STUDENT |" << endl;
                cout << "Please enter the id of the student you would like to delete or -1 to exit: ";
                while(!(cin >> deleteStudentId) || !StudentRecords->existingId(deleteStudentId)){
                    if(deleteStudentId == -1){
                        break;
                    }
                    cout << "Error! Non integer value entered or Student ID does not exist! Please try again or type -1 to cancel. " << endl;
                    cin.clear();
                    cin.ignore(40,'\n');
                }
                if(deleteStudentId != -1){
                    int advisorId = StudentRecords->getWithId(deleteStudentId)->getAdvisorId();
                    if(FacultyRecords->getWithId(advisorId)->getAdvisees()->contains(deleteStudentId)){ 
                        FacultyRecords->getWithId(advisorId)->getAdvisees()->removeSpecific(deleteStudentId);
                    }
                    StudentRecords->remove(StudentRecords->getWithId(deleteStudentId));
                }
                break;
            }
            case 7:
            {
                int newFacultyId;
                std::string newFacultyName, newFacultyLevel, newFacultyDepartment;
                DblList<int>* newFacultyAdvisees = new DblList<int>();
                cout << "| ADD FACULTY MEMBER |" << endl;
                cout << "Please enter a new faculty members unique id number: ";
                while(!(cin >> newFacultyId) || FacultyRecords->existingId(newFacultyId)){
                    cout << "Error! Non integer value entered OR id already exists! Please try again or type -1 to exit. " << endl;
                    cin.clear();
                    cin.ignore(40,'\n');
                }
                cout << endl;
                cout << "Please enter the new faculty member's name: ";
                getline(cin.ignore(1, '\n'), newFacultyName);
                cout << endl;
                cout << "Please enter the new faculty member's level: ";
                getline(cin.ignore(1, '\n'), newFacultyLevel);
                cout << endl;
                cout << "Please enter the new faculty member's department: ";
                getline(cin.ignore(1, '\n'), newFacultyDepartment);
                cout << endl;
                bool isDoneAddingAdvisees = false;
                while(isDoneAddingAdvisees == false){
                    cout << "Please enter the id number of a advisee for this faculty member or type -1 to stop: ";
                    int temp;
                    while(!(cin >> temp) || !StudentRecords->existingId(temp)){
                        if(temp == -1){
                            break;
                        }
                        cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                        cin.clear();
                        cin.ignore(40,'\n');
                    }
                    if(temp == -1){
                        isDoneAddingAdvisees = true;
                        break;
                    }
                    cout << "You are attempting to override student: " << StudentRecords->getWithId(temp)->getName(); 
                    cout << "Please type 1 to confirm and -1 to cancel: ";
                    int confirm;
                    while(!(cin >> confirm)){
                        cout << "Error! Non integer value entered! Please try again or type -1 to exit. " << endl;
                        cin.clear();
                        cin.ignore(40,'\n');
                    }
                    if(confirm == 1){
                        FacultyRecords->getWithId(StudentRecords->getWithId(temp)->getAdvisorId())->removeAdvisee(temp);
                        StudentRecords->getWithId(temp)->setAdvisorId(newFacultyId);
                        newFacultyAdvisees->addFront(temp);
                    }else{
                        continue;
                    }
                    cout << endl;
                }
                Faculty* fac = new Faculty(newFacultyId, newFacultyName, newFacultyLevel, newFacultyDepartment, newFacultyAdvisees);
                FacultyRecords->insert(fac);
                cout << "Faculty member successfully added to database!" << endl;
                break;
            }
            case 8:
            {
                int deleteFacultyId;
                cout << "| DELETE FACULTY MEMBER |" << endl;
                cout << "Please enter the id of the faculty member you would like to delete or type -1 to exit: ";
                while(!(cin >> deleteFacultyId) || !FacultyRecords->existingId(deleteFacultyId)){
                    if(deleteFacultyId == -1){
                        break;
                    }
                    cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                    cin.clear();
                    cin.ignore(40,'\n');
                }
                if(deleteFacultyId == -1){
                    break;
                }else if(FacultyRecords->getWithId(deleteFacultyId)->getAdvisees()->getSize() == 0){
                    
                    FacultyRecords->remove(FacultyRecords->getWithId(deleteFacultyId));
                    cout << "Successfully removed faculty member!" << endl;
                }else{
                    cout << "You are attempting to remove a faculty member ";
                    cout << "that has advisees, please enter a new faculty member ";
                    cout << "id to transfer advisees or type -1 to cancel: ";
                    int newDeleteFacultyId;
                    while(!(cin >> newDeleteFacultyId) || !FacultyRecords->existingId(newDeleteFacultyId)){
                        if(newDeleteFacultyId == -1){
                            break;
                        }
                        cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                        cin.clear();
                        cin.ignore(40,'\n');
                    }
                        if(newDeleteFacultyId != -1){
                            while(FacultyRecords->getWithId(deleteFacultyId)->getAdvisees()->getSize() != 0){
                                FacultyRecords->getWithId(newDeleteFacultyId)->addAdvisee(FacultyRecords->getWithId(deleteFacultyId)->getAdvisees()->removeFront());
                            }
                            FacultyRecords->remove(FacultyRecords->getWithId(deleteFacultyId));
                        }
                }
                break;
            }
            case 9:
            {
                int studentsId;
                int advisorsId;
                cout << "|  CHANGE STUDENTS ADVISOR |" << endl;
                cout << "Please type the student id of the student that will be updated: ";
                while(!(cin >> studentsId) || !StudentRecords->existingId(studentsId)){
                    if(studentsId == -1){
                        break;
                    }
                    cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                    cin.clear();
                    cin.ignore(40,'\n');
                }
                if(studentsId == -1){
                    break;
                }
                cout << endl;
                cout << "Please type the faculty members id that will be the new students advisor: ";
                while(!(cin >> advisorsId) || !FacultyRecords->existingId(advisorsId)){
                    if(advisorsId == -1){
                        break;
                    }
                    cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                    cin.clear();
                    cin.ignore(40,'\n');
                }
                if(advisorsId == -1){
                    break;
                }
                cout << endl;
                FacultyRecords->getWithId(StudentRecords->getWithId(studentsId)->getAdvisorId())->removeAdvisee(studentsId);
                StudentRecords->getWithId(studentsId)->setAdvisorId(advisorsId);
                FacultyRecords->getWithId(advisorsId)->addAdvisee(studentsId);
                cout << "Successfully updated students advisor!" << endl;
                break;
            }
            case 10:
            {
                if(FacultyRecords->getSize() > 1){
                    int facultyToEdit;
                    int adviseeToRemove;
                    int newFaculty;
                    cout << "| REMOVE ADVISEE FROM FACULTY |" << endl;
                    cout << "Please enter the id of the faculty member you would like to edit: ";
                    while(!(cin >> facultyToEdit) || !FacultyRecords->existingId(facultyToEdit)){
                        if(facultyToEdit == -1){
                            break;
                        }
                        cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                        cin.clear();
                        cin.ignore(40,'\n');
                    }
                    if(facultyToEdit == -1){
                            break;
                        }
                    cout << endl;
                    cout << "Please enter the id of the advisee you would like to remove: ";
                    while(!(cin >> adviseeToRemove) || !StudentRecords->existingId(adviseeToRemove) || !FacultyRecords->getWithId(facultyToEdit)->getAdvisees()->contains(adviseeToRemove)){
                        if(adviseeToRemove == -1){
                            break;
                        }
                        cout << "Error! Non integer value entered OR id does not exist! Please try again or type -1 to exit. " << endl;
                        cin.clear();
                        cin.ignore(40,'\n');
                    }
                    if(adviseeToRemove == -1){
                            break;
                        }
                    cout << endl;
                    cout << "Please enter the id of the new faculty member you would like to assign to the advisee: ";
                    while(!(cin >> newFaculty) || !FacultyRecords->existingId(newFaculty)){
                        if(newFaculty == -1){
                            break;
                        }
                        cout << "Error! Non integer value entered OR id does not exist OR id already entered! Please try again or type -1 to exit. " << endl;
                        cin.clear();
                        cin.ignore(40,'\n');
                    }
                    if(newFaculty == -1){
                            break;
                        }
                    cout << endl;
                    StudentRecords->getWithId(adviseeToRemove)->setAdvisorId(newFaculty);
                    FacultyRecords->getWithId(newFaculty)->addAdvisee(adviseeToRemove);
                    FacultyRecords->getWithId(facultyToEdit)->getAdvisees()->removeSpecific(adviseeToRemove);
                    cout << "Successfully removed advisee from faculty member!" << endl;
                }else{
                    cout << "Sorry that action is not possible with only 1 faculty member." << endl;
                }
                break;
            }
            case 11:
            {
                StudentRecords->outputInfo();
                FacultyRecords->outputInfo();
                cout << "| Program Closing |" << endl;
                dbOpen = false;
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void DB::showMenu(){
    cout << "| University Database |" << endl;
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the students id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Add a new student" << endl;
    cout << "6. Delete a student given the id" << endl;
    cout << "7. Add a new faculty member" << endl;
    cout << "8. Delete a faculty member given the id." << endl;
    cout << "9. Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "10. Remove an advisee from a faculty member given the ids" << endl;
    cout << "11. Exit" << endl;
    cout << "Please enter the number of the action you would like to take: " << endl;
}