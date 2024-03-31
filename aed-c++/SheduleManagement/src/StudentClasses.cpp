/**
 * @file StudentClasses.cpp
 * @brief Implementation of the StudentClasses class
 * @see StudentClasses.h
 * */
#include "../include/StudentClasses.h"

StudentClasses::StudentClasses() : SID({"", ""}){
}

StudentClasses::StudentClasses(const string &id, const string &name) : SID({id, name}), turmas(){
}

StudentClasses::StudentClasses(const string &id, const string &name, list<Turma> l) : SID({id, name}), turmas(l){

}

void StudentClasses::addTurma(const Turma &t) {
    turmas.push_back(t);
}

void StudentClasses::removeTurma(const Turma &t) {
    turmas.remove(t);
}

Turma StudentClasses::changeTurma(const Turma &t) {
    for (auto it = turmas.begin(); it != turmas.end(); it++) {
        Turma cur = *it;
        if (cur.getUcCode() == t.getUcCode()) {
            Turma oldClass = cur;
            *it = t;
            return oldClass;
        }
    }
    return {};
}

Turma StudentClasses::findTurma(const string &UcCode) const {
    for(const Turma &t : turmas){
        if(t.getUcCode() == UcCode)
            return t;
    }
    return {};
}

ostream &operator<<(ostream &os, const StudentClasses &Sc) {
    //os << "Student: ";
    os << Sc.SID.StudentName << ", " << "(" << Sc.SID.StudentCode << ")" <<endl;

    /*
    os << "Turmas: ";
    for(const auto & turma : Sc.turmas){
        os << turma.getUcCode() << " " << turma.getClassCode() << " | ";
    }
    os << endl;
    */
    return os;
}

StudentID StudentClasses::getSID() const {
    return SID;
}

string StudentClasses::getStudentCode() const {
    return SID.StudentCode;
}

string StudentClasses::getStudentName() const {
    return SID.StudentName;
}

list<Turma> StudentClasses::getTurmas() const {
    return turmas;
}

bool StudentClasses::operator==(const StudentClasses &rhs) const {
    return this->SID.StudentCode == rhs.SID.StudentCode;
}

bool StudentClasses::operator<(const StudentClasses &rhs) const {
    return this->SID.StudentCode < rhs.SID.StudentCode;
}

unsigned int StudentClasses::getYear() const {
    return max_element(turmas.begin(), turmas.end(),
                       [](const Turma &a, const Turma &b) {
                                    return a.getClassCode()[0] - '0' < b.getClassCode()[0] - '0';
                                }
                       )->getClassCode()[0] - '0';
}

bool StudentClasses::isEnrolled(const string &UcCode) const {
    return findTurma(UcCode) != Turma();
}