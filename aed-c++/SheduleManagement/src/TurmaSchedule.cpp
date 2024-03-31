/**
 * @file TurmaSchedule.cpp
 * @brief Code for the TurmaSchedule class
 * @see TurmaSchedule.h
 */
#include "../include/TurmaSchedule.h"

using namespace std;

TurmaSchedule::TurmaSchedule() {
    this->t = Turma();
    this->slots = vector<TimeSlot>();
}

TurmaSchedule::TurmaSchedule(const Turma &t) {
    this->t = t;
    this->slots = vector<TimeSlot>();
}

TurmaSchedule::TurmaSchedule(const string &ucId, const string &classId) {
    this->t = Turma(ucId, classId);
    this->slots = vector<TimeSlot>();
}

void TurmaSchedule::addSlot(const TimeSlot &slot) {
    slots.push_back(slot);
}

void TurmaSchedule::addStudent(const StudentClasses &student) {
    students.insert(student);
}

void TurmaSchedule::removeStudent(const StudentClasses &student) {
    students.erase(student);
}


bool TurmaSchedule::sameUcId(const TurmaSchedule &other) const {
    return this->t.getUcCode() == other.t.getUcCode();
}

void TurmaSchedule::printHeader() const {
    cout << ">> UC:" << t.getUcCode() << " " << t.getClassCode() << endl;
}

void TurmaSchedule::printSlots() const {
    cout << ">> Slots:" << endl;
    for (const TimeSlot &slot : slots) {
        cout << "   " << slot.getWeekDay() << "   " << slot.getStartHour() << " - " << slot.getEndHour() << "   " << slot.getType() << endl;
    }
}

void TurmaSchedule::printStudents(const string &sortType) const{
    vector<StudentClasses> studentsVector(students.begin(), students.end()); //O(q)
    if (sortType == "By name ascending") {
        sort(studentsVector.begin(), studentsVector.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() < b.getStudentName(); }); //O(q logQ)
    } else if (sortType == "By name descending") {
        sort(studentsVector.rbegin(), studentsVector.rend(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() < b.getStudentName(); }); //O(q logQ)
    } else if (sortType == "By UPcode ascending") {
        sort(studentsVector.begin(), studentsVector.end());
    } else if (sortType == "By UPcode descending") {
        sort(studentsVector.rbegin(), studentsVector.rend());
    } else {
        cout << "Invalid sortType" << endl;
        return;
    }
    cout << ">> Number of students: " << students.size() << endl;
    cout << ">> Students:" << endl;
    for(StudentClasses student: studentsVector){   //O(q)
        cout << "   "; cout << "Student: " << student.getStudentName() << ", " << student.getStudentCode() << endl;
    }
}

void TurmaSchedule::print() const {
    printHeader();  //O(1)
    printSlots();   //O(l)
    printStudents();    //O(q log q)
    cout << endl;
}

Turma TurmaSchedule::getUcTurmas() const {
    return t;
}

int TurmaSchedule::getNumStudents() const {
    return students.size();
}

const vector<TimeSlot> &TurmaSchedule::getSlots() const {
    return slots;
}

set<StudentClasses> TurmaSchedule::getStudents() const {
    return students;
}

bool TurmaSchedule::operator < (const TurmaSchedule &other) const {
    return this->getUcTurmas() < other.getUcTurmas();
}

bool TurmaSchedule::operator == (const TurmaSchedule &other) const {
    return this->getUcTurmas() == other.getUcTurmas();
}