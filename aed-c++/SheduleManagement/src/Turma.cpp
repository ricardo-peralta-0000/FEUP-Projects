/**
 * @file Turma.cpp
 * @brief Implementation of the Turma class
 * @see Turma.h
 * */
#include "../include/Turma.h"

Turma::Turma() {
}

Turma::Turma(const std::string &class_code, const std::string &uc_code, int size) :  class_code_(class_code), uc_code_(uc_code), size(size){};

const string &Turma::getClassCode() const {
    return class_code_;
}

const string &Turma::getUcCode() const {
    return uc_code_;
}

bool Turma::operator<(const Turma &turma) const{
    if(this->uc_code_ == turma.uc_code_)
        return this->class_code_ < turma.class_code_;
    return this->uc_code_ < turma.uc_code_;
}

ostream &operator<<(ostream &os, const Turma &turma) {
    return os << turma.getClassCode() << "; " << turma.getUcCode() << ".";
}

bool Turma::operator==(const Turma &turma) const {
    return turma.uc_code_ == this->uc_code_ && turma.class_code_ == this->class_code_;
}

bool Turma::operator!=(const Turma &turma) const {
    return !(operator==(turma));
}

const unsigned int &Turma::getSize() const {
    return size;
}

void Turma::setSize(int s) {
    this->size = s;
}


