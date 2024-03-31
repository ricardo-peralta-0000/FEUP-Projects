#ifndef AED2324_PRJ1_G15_TURMA_H
#define AED2324_PRJ1_G15_TURMA_H
/**
 * @file Turma.h
 * @brief Header file for the Turma class
 * @details This file contains the declaration of the Turma class
 * */
#include <string>
#include <iostream>

using namespace std;

/**
 * @class Turma
 * @brief Represents a class by its code and the code of the UC it belongs to.
 */
class Turma{
public:
    /**
     * @brief Default constructor for the Turma class
     * */
    Turma();

    /**
     * @brief Constructor for the Turma class
     * @details This constructor initializes the class with the given parameters
     * @param class_code The code of the class
     * @param uc_code The code of the UC
     * */
    Turma(const string &class_code, const string &uc_code, int size = 1);

    /**
     * @brief Getter for the class code
     * @return The class code
     * */
    const string &getClassCode() const;

    /**
     * @brief Getter for the UC code
     * @return The UC code
     * */
    const string &getUcCode() const;
    const unsigned int &getSize() const;

    void setSize(int s);

    /**
     * @brief Operator overload for the Turma class
     * @details This operator overload is used to sort the Turma objects in a set by the UC code
     * in spite of the main changes of the data struct (UC code based)
     * @return True if the first Turma object is less than the second, false otherwise. \n
     * It starts by comparing the UC codes, if they are equal, it compares the class codes
     * */
    bool operator < (const Turma & rhs) const;

    /**
     * @brief Operator overload for the Turma class
     * @details This operator overload is used to compare two Turma objects
     * @return True if the two Turma objects are equal, false otherwise
     * */
    bool operator == (const Turma &turma) const;

    /**
     * @brief Operator overload for the Turma class
     * @details This operator overload is used to compare two Turma objects
     * @return True if the two Turma objects are not equal, false otherwise
     * */
    bool operator != (const Turma &turma) const;

    /**
     * @brief Operator overload for the Turma class
     * @details This operator overload is used to print a Turma object instance
     * */
    friend ostream &operator <<(ostream &os, const Turma &turma);

    struct TurmaHash {
        size_t operator()(const Turma& t) const {
            // Combine the hash codes of class_code_ and uc_code_ using hash
            hash<string> stringHash;
            size_t class_code_hash = stringHash(t.getClassCode());
            size_t uc_code_hash = stringHash(t.getUcCode());

            // Combine the two hash codes to create a unique hash for Turma
            return class_code_hash ^ (uc_code_hash << 1);
        }
    };
private:

    string class_code_; /*< The code of the class*/

    string uc_code_; /*< The code of the UC*/

    unsigned int size;/* The size of a Turma*/

};

#endif //AED2324_PRJ1_G15_TURMA_H
