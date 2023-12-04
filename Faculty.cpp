#include "Faculty.h"

Faculty::Faculty(){
    m_facultyId = 0;
    m_name = "";
    m_level = "";
    m_department = "";
}

Faculty::Faculty(int m_facultyId, std::string m_name, std::string m_level, std::string m_department, DblList<int>* m_advisees){
    this->m_facultyId = m_facultyId;
    this->m_name = m_name;
    this->m_level = m_level;
    this->m_department = m_department;
    this->m_advisees = m_advisees;
}

Faculty::~Faculty(){
    if(m_advisees != NULL){
        delete m_advisees;
    }
}

int Faculty::getId(){
    return m_facultyId;
}

void Faculty::setFacultyId(int m_facultyId){
    this->m_facultyId = m_facultyId;
}

std::string Faculty::getName(){
    return m_name;
}

void Faculty::setName(std::string m_name){
    this->m_name = m_name;
}

std::string Faculty::getLevel(){
    return m_level;
}

void Faculty::setLevel(std::string m_level){
    this->m_level = m_level;
}

std::string Faculty::getDepartment(){
    return m_department;
}

void Faculty::setDepartment(std::string m_department){
    this->m_department = m_department;
}

DblList<int>*& Faculty::getAdvisees(){
    return m_advisees;
}

void Faculty::addAdvisee(int id){
    m_advisees->addFront(id);
}

void Faculty::removeAdvisee(int id){
    m_advisees->removeSpecific(id);
}

bool operator== (const Faculty& c1, const Faculty& c2){
    return c1.m_facultyId == c2.m_facultyId;
}

bool operator!= (const Faculty& c1, const Faculty& c2){
    return c1.m_facultyId != c2.m_facultyId;
}

bool operator< (const Faculty& c1, const Faculty& c2){
    return c1.m_facultyId < c2.m_facultyId;
}

bool operator<= (const Faculty& c1, const Faculty& c2){
    return c1.m_facultyId <= c2.m_facultyId;
}

bool operator> (const Faculty& c1, const Faculty& c2){
    return c1.m_facultyId > c2.m_facultyId;
}

bool operator>= (const Faculty& c1, const Faculty& c2){
    return c1.m_facultyId >= c2.m_facultyId;
    
}

ostream& operator<<(ostream& cout, const Faculty& c1){
    cout << "| Faculty Information |" << endl;
    cout << "Faculty Name: ";
    cout << c1.m_name << endl;
    cout << "Faculty ID: ";
    cout << c1.m_facultyId << endl;
    cout << "Faculty Level: ";
    cout << c1.m_level << endl;
    cout << "Faculty Department: ";
    cout << c1.m_department << endl;
    cout << "Faculty's Advisees Id's: " << endl;
    c1.m_advisees->print();
    cout << "________________________________" << endl;
    return cout;
}