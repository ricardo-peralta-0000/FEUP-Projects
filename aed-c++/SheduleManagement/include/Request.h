#ifndef AED2324_PRJ1_G15_REQUEST_H
#define AED2324_PRJ1_G15_REQUEST_H

/**
 * @file Request.h
 * @brief Header file for the Request class
 * @details This file contains the declaration of the Request class
 * */
#include "StudentClasses.h"
#include <iostream>

/**
 * @brief Class to store the information about a given request.
 * @details This class stores the information about a given request,
 * such as the student that made the request,
 * the class that the student wants to enroll in
 * and the type of the request.
 */
class Request{
public:

    /**
    * @brief Constructor of the Request class. If the type of Request is not valid, it type is set to be empty string.
    * @details Time complexity: O(1)
    * @param student Student that made the request
    * @param desiredClass Class that the student wants to enroll in
    */
    Request(const StudentClasses &student, const Turma &desiredClass, const string &type);

    /**
     * @brief Prints the header of the request (student name, student number, if type is removal -> Requested Uc, else requested class)
     * @details Time complexity: O(1)
     */
    void printHeader() const;

    /**
     * @brief Prints the request
     * @details calls printHeader() and then prints the type of the request
     * Time complexity: O(1)
     */
    void print() const;

    /**
    * @brief Returns the student that made the request
    * @details Time complexity: O(1)
    * @return Student that made the request
    */
    StudentClasses getStudent() const;

    /**
    * @brief Returns the UcClass that the student wants to enroll in
    * @details Time complexity: O(1)
    * @return Class that the student wants to enroll in
    */
    Turma getDesiredUcClass() const;

    string getType() const;

private:
    /** @brief Student that made the request */
    StudentClasses student;
    /** @brief Class that the student wants to enroll in */
    Turma desiredUcClass;
    /** @brief Type of the request: Changing, Removal, Enrollment */
    string type;
};

#endif //AED2324_PRJ1_G15_REQUEST_H
