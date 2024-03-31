/**
 * @file UC.cpp
 * @brief Code for the UC class
 * @see UC.h
 * */
#include "../include/UC.h"

const string &UC::getUcCode() const {
    return ucCode;
}

void UC::setUcCode(const string &ucCode) {
    UC::ucCode = ucCode;
}

const set<string> &UC::getClasses() const {
    return classes;
}

void UC::setClasses(const set<string> &classes) {
    UC::classes = classes;
}

UC::UC(string _ucCode) {
    this->ucCode = _ucCode;
}

void UC::insertClass(string &_class) {
    this->classes.insert(_class);

}

bool UC::operator==(const UC &uc) const {
    return ucCode == uc.getUcCode();
}

UC::UC() {
    this->ucCode = "-";
}

bool UC::operator<(const UC &rhs) const {
    return ucCode < rhs.ucCode;
}