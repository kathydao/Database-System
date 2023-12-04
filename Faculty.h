#ifndef FACULTY_H
#define FACULTY_H

#include "DblList.cpp"
#include <string>
#include <ostream>

using namespace std;

class Faculty{
    public:
    Faculty();
    Faculty(int m_facultyId, std::string m_name, std::string m_level, std::string m_department, DblList<int>* m_advisees);
    virtual ~Faculty();
    int getId();
    void setFacultyId(int m_facultyId);
    std::string getName();
    void setName(std::string m_name);
    std::string getLevel();
    void setLevel(std::string m_level);
    std::string getDepartment();
    void setDepartment(std::string m_department);
    DblList<int>*& getAdvisees();
    void addAdvisee(int id);
    void removeAdvisee(int id);
    friend bool operator== (const Faculty& c1, const Faculty& c2);
    friend bool operator!= (const Faculty& c1, const Faculty& c2);
    friend bool operator< (const Faculty& c1, const Faculty& c2);
    friend bool operator<= (const Faculty& c1, const Faculty& c2);
    friend bool operator> (const Faculty& c1, const Faculty& c2);
    friend bool operator>= (const Faculty& c1, const Faculty& c2);
    friend ostream& operator<< (ostream& cout, const Faculty& c1);
    private:
    int m_facultyId;
    std::string m_name;
    std::string m_level;
    std::string m_department;
    DblList<int>* m_advisees;
};

#endif