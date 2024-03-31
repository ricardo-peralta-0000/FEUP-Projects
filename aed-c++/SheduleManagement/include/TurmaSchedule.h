#ifndef AED2324_PRJ1_G15_TURMASCHEDULE_H
#define AED2324_PRJ1_G15_TURMASCHEDULE_H

/**
 * @file TurmaSchedule.h
 * @brief Header file for the TurmaSchedule class
 * @details This file contains the declaration of the TurmaSchedule class
 * */
#include <vector>
#include <set>
#include "TimeSlot.h"
#include "Turma.h"
#include "StudentClasses.h"

/**
 * @class TurmaSchedule
 * @brief Represents a schedule for a class composed of a vector of TimeSlots and a set of students
 */
class TurmaSchedule {
public:
    /** @brief Default Constructor, calls the UcClass default constructor and initializes the slots vector as empty
     * @details Time complexity: O(1)
     */
    TurmaSchedule();

    /** @brief Constructor, sets ucClass to the given one. The vector of slots is initialized as empty.
     * @details Time complexity: O(1)
     * @param UcClass the UcClass of the schedule
     */
    TurmaSchedule(const Turma &t);

    /** @brief Constructor, given a ucId and a classId, creates a UcClass and  the vector of slots is initialized as empty
     * @details Time complexity: O(1)
     * @param ucId
     * @param classId
     */
    TurmaSchedule(const string &ucId, const string &TurmasId);

    /** @brief Add a slot to the vector of slots
     * @details Time complexity: O(1)
     * @param slot the slot to be added
     */
    void addSlot(const TimeSlot &slot);

    /** @brief Inserts a student in the set of students
     * @details Time complexity: O(log * q), where: \n
     * - q is the number of students in the ClassSchedules set of students
     * @param student the student to add
     */
    void addStudent(const StudentClasses &student);

    /** @brief Removes a student from the set of students
     * @details Time complexity: O(log q), where:\n
     * - q is the number of students in the ClassSchedules set of students
     * @param student the student to remove
     */
    void removeStudent(const StudentClasses &student);

    /** @brief Boolean function that returns true if the ClassSchedules have the same UcId, false otherwise
     * @details Time complexity: O(1)
     * @param other the other ClassSchedule
     */
    bool sameUcId(const TurmaSchedule &other) const;

    /** @brief Prints the ucId and classId
     * @details Time complexity: O(1)
     */
    void printHeader() const;

    /** @brief Prints each slot in the vector of slots (Weekday, Start time, End time, Type)
     * @details Time complexity: O(l), where: \n
     * - l is the number of slots in the ClassSchedule
     */
    void printSlots() const;

    /**@brief Prints the students in a given sortType
     * @details Prints the number of students, then the students in the given sortType\n
     * Time complexity: O(q log q), where: \n
     * - q is the number of students in the ClassSchedule
     * @param sortType the type of sort, it can be alphabetical, reverse alphabetical, numerical, reverse numerical
     */
    void printStudents(const string &sortType = "alphabetical") const;

    /**@brief Prints the ClassSchedule (calls printHeader(), printSlots() and printStudents())
     * @details Time complexity: O(l) + O(q log q), where l is the number of slots in the ClassSchedule and q is the number of students in the ClassSchedule
     * @see printHeader()
     * @see printSlots()
     * @see printStudents()
    */
    void print() const;

    /**@brief Returns the UcClass of the ClassSchedule
     * @details Time complexity: O(1)
     */
    Turma getUcTurmas() const;

    /** @brief Returns the number of students enrolled in the class
     * @details Time complexity: O(1)
     * @return the number of students
     */
    int getNumStudents() const;

    /**
     * @brief Returns a reference to the vector of slots
     * @details Time complexity: O(1)
    */
    const vector<TimeSlot> &getSlots() const;

    /**@brief Returns the set of students
     * @details Time complexity: O(1)
     */
    set<StudentClasses> getStudents() const;

    /** @brief Minor operator overload. Compares two ClassSchedules by their UcId, then by their classId
     * @details Time complexity: O(1)
     * @param other The ClassSchedule to compare to
     * @return true if the UcClass is smaller, false otherwise
     */
    bool operator < (const TurmaSchedule &other) const;

    /** @brief Equality operator overload
     * @details Time complexity: O(1)
     * @param other The ClassSchedule to compare to
     * @return true if the UcClass is equal, false otherwise
     */
    bool operator == (const TurmaSchedule &other) const;
private:
    /** @brief Information about the Turmas and UC that the schedule is for */
    Turma t;
    /** @brief Vector of slots that constitutes the schedule */
    vector<TimeSlot> slots;
    /** @brief Set of students that are enrolled in the Turmas in this UC */
    set<StudentClasses> students;
};

#endif //AED2324_PRJ1_G15_TURMASCHEDULE_H