/**
 * @file Request.cpp
 * @brief Implementation of the Request class
 *
 * @see Request.h
 * */
#include "../include/Request.h"

Request::Request(const StudentClasses &student, const Turma &desiredClass, const string &type) {
    if(type != "Changing" && type != "Removal" && type != "Enrollment") return;
    this->student = student;
    this->desiredUcClass = desiredClass;
    this->type = type;
}

void Request::printHeader() const{
    cout << "Student: " << student.getStudentName() << " - "<< student.getStudentCode()<<  "  |  ";
    if(type == "Removal") cout << "Requested Uc: " << desiredUcClass.getUcCode();
    else{
        cout << "Requested class: " << desiredUcClass.getClassCode() << " - " << desiredUcClass.getUcCode();
    }
}

void Request::print() const {
    printHeader();
    cout << "  |  " << "Type: " << type << endl;
}

StudentClasses Request::getStudent() const {
    return student;
}

Turma Request::getDesiredUcClass() const {
    return desiredUcClass;
}

string Request::getType() const {
    return type;
}
