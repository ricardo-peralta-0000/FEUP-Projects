#ifndef AED2324_PRJ1_G15_STUDENTCLASSES_H
#define AED2324_PRJ1_G15_STUDENTCLASSES_H

/**
 * @file StudentClasses.h
 * @brief Header file for the StudentClasses class
 * @details This file contains the declaration of the StudentClasses class and required structures
 * */
#include "Turma.h"
#include <list>
#include <algorithm>

/**
 * @struct StudentID
 * @brief Structure representing a student's unique
 * identification information - the student code and the student name.
 * */
struct StudentID{
    string StudentCode;
    string StudentName;
};
/**
 * @class StudentClasses
 * @brief Represents a student's enrollment information and related operations.
 * */
class StudentClasses {
public:
    /**
     * @brief Default constructor for the StudentClasses class.
     * */
    StudentClasses();

    /**
     * @brief Constructor for the StudentClasses class.
     *
     * @param id The student's ID.
     * @param name The student's name.
     * */
    StudentClasses(const string &id, const string &name);

    /**
     * @brief Constructor for the StudentClasses class.
     * @param id The student's ID.
     * @param name The student's name.
     * @param l The list of classes the student is enrolled in.
     * */
    StudentClasses(const string &id, const string &name, list<Turma> l);
    /**
     * @brief Adds a class (Turma) to the student's list of classes.
     *
     * @param t The Turma to add.
     * */
    void addTurma(const Turma &t);

    /*!@brief Changes UC of the student.
     *
     * @details Time complexity: O(log(n)) where:
     * - n is the number of classes the student is enrolled
     *
     * @param t The new Turma to change to.
     * @return The class removed if the student was enrolled, if not it returns am empty class
     */
    Turma changeTurma(const Turma &t);
    //void removeUc(const string &UcCode);
    //void addUc(const Turma &t);

    /**
     * @brief Checks if the student is enrolled in a specific class (Turma).
     * @param UcCode The curricular unit code to search for.
     * @return True if the student is enrolled in the class, false otherwise.
     * */
    bool isEnrolled(const string &UcCode) const;

    /**
     * @brief Removes a class (Turma) from the student's list of classes.
     *
     * @param t The Turma to remove.
     * */
    void removeTurma(const Turma &t);

    /**
     * @brief Finds a specific Turma by its code.
     * @note Time complexity  O(n)
     * @param UcCode The curricular unit code to search for.
     * @return The Turma if found, or an empty Turma if not found.
     * */
    Turma findTurma(const string &UcCode) const;

    /**
     * @brief Gets the academic year of the student based on their enrolled classes.
     * @return The academic year of the student.
     * */
    unsigned int getYear() const;

    /**
     * @brief Overloaded stream insertion operator to display StudentClasses.
     *
     * @param os The output stream.
     * @param Sc The StudentClasses object to display.
     * @return The output stream.
     * */
    friend ostream &operator <<(ostream &os, const StudentClasses &Sc);

    /**
     * @brief Gets the StudentID associated with the StudentClasses object.
     * @return The StudentID.
     * */
    StudentID getSID() const;

    /**
     * @brief Gets the student's UP number (student code).
     * @return The student's UP number as a string.
     * */
    string getStudentCode() const;

    /**
     * @brief Gets the student's name.
     * @return The student's name as a string.
     * */
    string getStudentName() const;

    /**
     * @brief Gets the list of classes the student is enrolled in.
     * @return The list of Turmas.
     * */
    list<Turma> getTurmas() const;

    /**
     * @brief Equality operator to compare StudentClasses objects by student code.
     * @param rhs The right-hand side StudentClasses object to compare with.
     * @return True if the student codes are equal, false otherwise.
     * */
    bool operator == (const StudentClasses &rhs) const;

    /**
     * @brief Less than operator to compare StudentClasses objects by student code.
     * @param rhs The right-hand side StudentClasses object to compare with.
     * @return True if the student code is less than that of the right-hand side, false otherwise.
     * */
    bool operator < (const StudentClasses &rhs) const;

private:

    StudentID SID; /**< The student's unique identification information. */
    list<Turma> turmas; /**< The list of classes (Turma) the student is enrolled in. */
};

#endif //AED2324_PRJ1_G15_STUDENTCLASSES_H
