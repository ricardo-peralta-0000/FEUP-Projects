#ifndef AED2324_PRJ1_G15_UC_H
#define AED2324_PRJ1_G15_UC_H

/**
 * @file UC.h
 * @brief Header file for the UC class
 * @details This file contains the declaration of the UC class
 * */
#include <set>
#include <iostream>

using namespace std;

/**
 * @class UC
 * @brief Represents a curricular unit (UC)
 */
class UC {
public:
    /**
     * @brief Default constructor for the UC class
     */
    UC();

    /**
     * @brief Constructor for the UC class
     * @param _ucCode UC code
     */
    UC(string _ucCode);

    /**
     * @brief Getter for the UC code
     * @return UC code
     * */
    const string &getUcCode() const;

    /**
     * @brief Setter for the UC code
     * @param ucCode UC code
     * */
    void setUcCode(const string &ucCode);

    /**
     * @brief Getter for the set of classes
     * @return Set of classes
     * */
    const set<string> &getClasses() const;

    /**
     * @brief Setter for the set of classes
     * @param classes Set of classes
     * */
    void setClasses(const set<string> &classes);

    /**
     * @brief Overload of the == operator for the UC class
     * @param uc UC to be compared with
     * @return True if the UCs are equal, false otherwise
     * */
    bool operator==(const UC &uc) const;

    /**
     * @brief
     * @details Insere o nome de uma turma (turma1, turma2, ...) no set de turmas da classe.\n
     * Time complexity: O(log (n)). \n
     * @param _class
     */
    void insertClass(string &_class);

    /**
     * @brief Overload of the < operator for the UC class
     * @param rhs Right hand side UC
     * @return True if the UC is less than the rhs, false otherwise
     * */
    bool operator<(const UC &rhs) const;


private:
    /** @brief UC code */
    string ucCode;
    /** @brief Set of classes */
    set<string> classes;
};

#endif //AED2324_PRJ1_G15_UC_H