#include "Student.h"

Student::Student(){
    m_studentId = 0;
    m_name = "";
    m_level = "";
    m_major = "";
    m_gpa = 0.0;
    m_advisorId = 0;
}

Student::Student(int m_studentId, std::string m_name, std::string m_level, std::string m_major, double m_gpa, int m_advisorId){
    this->m_studentId = m_studentId;
    this->m_name = m_name;
    this->m_level = m_level;
    this->m_major = m_major;
    this->m_gpa = m_gpa;
    this->m_advisorId = m_advisorId;
}


Student::~Student(){

}

int Student::getId(){
    return m_studentId;
}

void Student::setStudentId(int m_studentId){
    this->m_studentId = m_studentId;
}

std::string Student::getName(){
    return m_name;
}

void Student::setName(std::string m_name){
    this->m_name = m_name;
}

std::string Student::getLevel(){
    return m_level;
}

void Student::setLevel(std::string m_level){
    this->m_level = m_level;
}

std::string Student::getMajor(){
    return m_major;
}

void Student::setMajor(std::string m_major){
    this->m_major = m_major;
}

double Student::getGPA(){
    return m_gpa;
}

void Student::setGPA(double m_gpa){
    this->m_gpa = m_gpa;
}

int Student::getAdvisorId(){
    return m_advisorId;
}

void Student::setAdvisorId(int m_advisorId){
    this->m_advisorId = m_advisorId;
}

bool operator== (const Student& c1, const Student& c2){
    return c1.m_studentId == c2.m_studentId;
}

bool operator!= (const Student& c1, const Student& c2){
    return c1.m_studentId != c2.m_studentId;
}

bool operator< (const Student& c1, const Student& c2){
    return c1.m_studentId < c2.m_studentId;
}

bool operator<= (const Student& c1, const Student& c2){
    return c1.m_studentId <= c2.m_studentId;
}

bool operator> (const Student& c1, const Student& c2){
    return c1.m_studentId > c2.m_studentId;
}

bool operator>= (const Student& c1, const Student& c2){
    return c1.m_studentId >= c2.m_studentId;
}

ostream& operator<<(ostream& cout, const Student& c1){
    cout << "| Student Information |" << endl;
    cout << "Student Name: ";
    cout << c1.m_name << endl;
    cout << "Student ID: ";
    cout << c1.m_studentId << endl;
    cout << "Student Level: ";
    cout << c1.m_level << endl;
    cout << "Student Major: ";
    cout << c1.m_major << endl;
    cout << "Student GPA: ";
    cout << c1.m_gpa << endl;
    cout << "Student's Faculty Advisor ID: ";
    cout << c1.m_advisorId << endl;
    cout << "________________________________" << endl;
    return cout;
}