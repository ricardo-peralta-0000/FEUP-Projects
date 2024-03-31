#ifndef AED2324_PRJ1_G15_PARSE_H
#define AED2324_PRJ1_G15_PARSE_H

/**
 * @file Parse.h
 * @brief This file contains the definition of the Parse class for handling class schedules and student information.
 */

#include <set>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <queue>
#include <stack>
#include <functional>
#include "TurmaSchedule.h"
#include "StudentClasses.h"
#include "Request.h"



/**
 * @struct studentByNUCS
 * @brief A comparator struct for sorting StudentClasses by the number of classes they are enrolled in.
 */
struct studentByNUCS {
    bool operator()(const StudentClasses& s1, const StudentClasses& s2) const {
        return s1.getTurmas().size() < s2.getTurmas().size();
    }
};


/**
 * @brief Handles parsing and processing of class schedules and student information.
 * */
class Parse {
public:

    /**
     * @brief Default constructor.
     * */
    Parse();

    /**
     * @brief Reads and processes schedule and student information from files.
     *
     * This function calls for 3 other methods, which read the files
     * */
    void readFiles();

    /**
     * @brief Creates schedules based on class information from a CSV file.
     *
     * This function reads class information from a CSV file and creates schedules for each class.
     *
     * @details Time complexity: O(n), where n is the number of lines in the file classes_per_uc.csv.
     * */
    void createSchedules();

    /**
     * @brief Sets schedules by reading class information from a CSV file.
     *
     * This function reads class information from a CSV file and assigns time slots to the corresponding schedules.
     *
     * @details Time complexity:
     * */
    void setSchedules();

    /**
     * @brief Reads the file "students.csv" and creates/updates the student information and a set of students
     *
     * @details Reads the students_classes.csv file, adds/updates the student information by adding the UcClass read in the file.
     * It also inserts/updates the student in the set of students\n
     * @details Time complexity: O(p * log s), being:\n
     * - p the number of lines in the file students_classes.csv\n
     * - s the number of students
     */
    void createStudents();

    /**
     * @brief Binary search for schedules based on a desired class.
     *
     * This function performs a binary search to find the index of a schedule based on a desired class.
     *
     * @details Time complexity: O(log(n)) where n is the number of schedules.
     *
     * @param desiredTurma The desired class to search for.
     *
     * @return The index of the schedule or -1 if not found.
     * */
    unsigned long int binarySearchSchedules(const Turma &desiredTurma) const;

    /**
     * @brief Finds and returns a class schedule based on a given class.
     * @param turma The class to search for.
     * @return A pointer to the class schedule or nullptr if not found.
     * */
    TurmaSchedule* findSchedule(const Turma &turma) const;

    /**
     * @brief Function that returns a vector with the ClassSchedules of a given class
     * @details Time complexity: O(n) where n is the number of schedules(lines in the classes_per_uc.csv file)
     * @param ucId The ID of the UC
     * @return A vector with all the classes of a given uc
     */
    vector<TurmaSchedule> classesOfUc(const string &ucId) const;

    /**
    * @brief Function that returns a vector with the students of a given class
     * @param ucId The ID of the UC
     * @details Time Complexity: O(n) + O(jq) where:\n
     * - n is the number of schedules(lines in classes_per_uc.csv file)\n
     * - j the number of ClassSchedules with a given ucId\n
     * - q the number of students in a given ClassSchedule ts\n
     * @return A vector with all the students of a given uc
     */
    vector<StudentClasses> studentsOfUc(const string &ucId) const;

    /**
     * @brief Prints a list of students grouped by academic year.
     */
    void printStudentsByYear(const string& SortingType) const;

    /**
     * @brief Prints a list of students grouped by course.
     */
    void printCourseStudents(const string& SortingType) const;

    /**
     * @brief Prints the schedule of a specific student.
     */
    void printStudentSchedule(const string &studentId) const;

    //void printClasses(const string SortingType) const;

    //TODO RESOLVE SHORTING THE CODE
    //void sortTypeStudents(vector<StudentClasses> &v) const;

    /**
     * @details O(nlog(n))
     * @brief sort the vector based on the sorting type
     *
     * */

    static void sortTypeUCs(vector<Turma> &v, const string& sortingType) ;

    /**
     * @details O(nlog(n))
     * @brief sort the vector based on the sorting type
     *
     * */
    static void sortTypeClasses(vector<Turma> &v, const string& SortingType) ;


    /**
     * @brief returns the turmasTable
     */
    unordered_set<Turma, Turma::TurmaHash> getTurmasTable() const;

    /**
     * @details O(n^2) [chama uma funçao dentro do loop O(n)]
     * @return vetor de pares, numero de alunos por ano(1ºano, 2º, 3º)
     *
     * */

    vector<pair<int, string>> getOcupationYear() const;

    void writeRejectedRequest();


    /**
     * @brief Function that prints the schedule of a given class
     * @details Time complexity: O(n*l*log(r*log(c)) + O(cd) where:\n
     * - n is the number of schedules\n
     * - l is the number of slots in a schedule\n
     * - c is the number of slots in a weekday\n
     * - r is the number of weekdays\n
     * - d is the number of classes in a slot\n
     * @param classCode The code of the class\n
     */
    void printClassSchedule(const string &classCode) const;

    /**
     * @brief Function that print the schedule of a given uc
     * @details Time complexity: O(n*l*log(r*log(c)) + O(cd) where:\n
     * - n is the number of schedules\n
     * - l is the number of slots in a schedule\n
     * - c is the number of slots in a weekday\n
     * - r is the number of weekdays\n
     * - d is the number of classes in a slot\n
     * @param ucCode The code of the UC
     */
    void printUcSchedule(const string &ucCode) const;

    /**
     * @brief Function that prints the students of a given class
     * @details Time complexity: O(log n) + O(q log q) where:\n
     * - n is the number of schedules(lines classes_per_uc.csv)\n
     * - q is the number of students in the ClassSchedule\n
     */
    void printClassStudents(const Turma &turma, const string &orderType) const;

    /**
     * @brief Function that prints the students enrolled a given uc
     * @details Time complexity O(n)+ O(jq) + O(d log d) where:\n
     * - n is the number of schedules(lines in classes_per_uc.csv file)\n
     * - j the number of ClassSchedules with a given ucId\n
     * - q the number of students in a given ClassSchedule cs \n
     * - d is the number of students in a given uc\n
     * @param ucId The Id of the UC\n
     * @param sortType The type of sorting to be used
     */
    void printUcStudents(const string &ucId,  const string &sortType) const;

    /**
     * @brief Function that prints the students of a given year
     * @param year The year of the students to be printed
     */
    set<StudentClasses> getStudentsByYear(unsigned int year) const;

    /**
     * @brief Function that returns a set of students sorted by the number of classes they are enrolled in
     * @details This function returns a multiset of student classes sorted by the count of classes they are enrolled in. The "studentByNUCS" comparison is used to sort the students.
     * @return A multiset of student classes sorted by class count.
     */
    multiset<StudentClasses, studentByNUCS> getStudentsByNUCS();
    //set<CourseUnit> Managing::getUcs(char year)

    /**
     * @brief Finds a student by their ID.
     * This function searches for a student based on their ID and returns a pointer. If no student is found, it returns a nullptr.
     *
     * @param studentId The unique identifier of the student to find.
     *
     * @return A pointer to the student or nullptr if not found.
     */
    StudentClasses* findStudent(const string &studentId) const;

    /**
     * @brief Function that returns the UcClass that the student is currently enrolled in
     * @details Time complexity: O(h) where:\n
     * - h is the number of classes the student is enrolled in
     * @see Student::findUcClass()
     */
    Turma getFormerClass(const Request &request) const;

    /**
     * @brief Function that returns the number of students in a given uc
     * @details Returns the size of the vector studentsOfUc
     * Time complexity: O(n) + O(jq), where:\n
     * - n is the number of schedules(lines in classes_per_uc.csv file)\n
     * - j the number of ClassSchedules with a given ucId \n
     * - q the number of students in a given ClassSchedule\n
     */
    int getNumberOfStudentsUc(const string &ucId) const;

    /**
     * @brief Function that gets the number of students in a given class of a given UC
     * @details Time complexity: O(log n) being:\n
     * - n the number of schedules.
     * @see findSchedule()
     */
    int getNumberOfStudentsUcClass(const Turma &t) const;

    /**
     * @brief Function that returns the number of pending requests
     * @details Time complexity: O(1)
     */
    int getNumberOfPendingRequests() const;

    /**
     * @brief Function that given a student and the ucClass he wants to change to, adds the request to the queue of changingRequests
     * @details Time complexity: O(1)
     */
    void addChangingRequest(const StudentClasses &student, const Turma &turma);

    /**
     * @brief Function that given a student and the ucClass he wants to enroll in, adds the request to the queue of enrollmentRequests
     * @details Time complexity: O(1)
     */
    void addEnrollmentRequest(const StudentClasses &student, const Turma &turma);

    /**
     * @brief Function that given a student and the ucClass he wants to withdraw from, adds the request to the queue of removalRequests
     * @details Time complexity: O(1)
     */
    void addRemovalRequest(const StudentClasses &student, const Turma &turma);

    /**
    * @brief Function that verifies if the schedule of two given classes have a conflict
    * @details Two UcClasses have a conflict if any pair of slots of the two classes overlap\n
    * Time complexity: O(n * logn) it mainly depends on the sorting time of the merged vector
    * @return true if the classes have a conflict, false otherwise
    */
    bool classesOverlap(const Turma &t1, const Turma &t2) const;

    /**
    * @brief Function that verifies if a given request has a conflict with the schedule of a given student
    *
    * @details A request has a conflict with the schedule if the class that student wants to enroll in causes a conflict with any of the current classes
    * of the student\n
    * Time complexity: O(t*log n + n²logn) where:\n
    * - t is the number of classes the student is enrolled in\n
    * - n is the number of lines in classes_per_uc.csv\n
    * - l is the number of slots of the first class\n
    * - r is the number of slots of the second class\n
    * @param request
    *
    * @return true if the request has a conflict with the schedule of the student, false otherwise
    */
    bool requestHasCollision(const Request &request) const;

    /**
     * @brief Function that verifies if by changing to the new class, the student will exceed the max number of students allowed.
     *
     * @details The cap (maximum number of students in a class) is set to be the maximum number of students currently enrolled in q class.
     * If all classes have  the same number of students (and therefor the cap wouldn't  allow a new student to enroll).\n
     * The cap is set to the maximum number of students in a class + 1.\n
     *
     * Time complexity: O(nlog n) where:\n
     * - n is the number of schedules (lines in the classes_per_uc.csv file)
     */
    bool requestExceedsCap(const Request &request) const;

    /**
     * @brief Function that verifies if the change to the new class provokes disequilibrium.
     *
     * @details In our program we say disequilibrium occurs if by changing to the new class the
     * difference between the number of students of the classes he comes from and goes to is greater
     * than 4. \n
     * If he comes from a class with more students to a class with less students it doesn't provoke disequilibrium.\n
     * If he comes from a class with less students to a class with more students it does provoke disequilibrium if the difference of the number of students is 4 or greater.\n
     *
     * Time complexity: O(log n) where:\n
     * - n is the number of schedules (lines in the classes_per_uc.csv file)
     */
    bool requestProvokesDisequilibrium(const Request &request) const;

    /**
     * @brief Function that processes the changingRequests in the queue
     *
     * @details if the request has any problem (conflict, disequilibrium, cap exceeded) it is added to the queue of failedRequests, otherwise it is processed and the student is removed from the former class and added to the new class\n
     *
     * Time complexity: O(t*log n + n²log(n)) + O(nlog n) where:\n
     * - n is the number of schedules (lines in the classes_per_uc.csv file)\n
     * - t is the number of classes the student is enrolled in\n
     */
    void processChangingRequest(const Request &request);

    /**
     * @brief Function that processes the removalRequests in the queue
     * @details A Removal request is always accepted\n
     * Time complexity: O(h) + O(log n * log n) + O(log p) where:\n
     * - n is the number of schedules (lines in the classes_per_uc.csv file)\n
     * - p is the number of lines in the students.csv file\n
     * - h is the number of classes of the student submitting the request\n
     */
    void processRemovalRequest(const Request &request) const;

    /**
     * @brief Function that processes the enrollmentRequests in the queue
     * @details Time complexity: O(t*log n + n²log(n)) + O(nlog n) + O(log p) where:\n
     * - n is the number of schedules (lines in the classes_per_uc.csv file)\n
     * - p is the number of lines in the students.csv file\n
     * - t is the number of classes the student is enrolled in\n
     * - n is the number of lines in classes_per_uc.csv\n
     */
    void processEnrollmentRequest(const Request &request);

    /**
     * @brief Function that processes all changingRequests in the queue
     * @details Time complexity: O(n²log(n)) where:\n
     * - n is the number of schedules (lines in the classes_per_uc.csv file)\n
     */
    void processRequests();

    /**
     * @brief Function that writes all information to the files
     * @details Time complexity: O(st) where:
     * - s is the number of students in the set \n
     * - t is the number of classes of each student \n
     */
    void writeFiles();

    /**
    * @brief Function that prints all changingRequests in the queue
    * @details Time complexity: O(v)+O(w)+O(z) where:\n
     * - v is the number of removal request\n
     * - w is the number of changing requests \n
     * - z is the number of enrollment requests\n
    */
    void printPendingRequests() const;

    /**
     * @brief Function that prints all the rejected changingRequests
     * @details Time complexity: O(a) where a is the number of rejected requests
     */
    void printRejectedRequests() ;

private:
    /**
     * @brief A set to store student information.
     *
     * @see StudentClasses
     */
    set<StudentClasses> students;
    /** @brief Vector that stores all the schedules */
    vector<TurmaSchedule> schedules;
    queue<Request> changingRequests;
    /** @brief Queue that stores all the removal requests */
    queue<Request> removalRequests;
    /** @brief Queue that stores all the enrollment requests */
    queue<Request> enrollmentRequests;
    /** @brief Queue that stores all the rejected changingRequests */
    queue<pair<Request, string>> rejectedRequests;

    /**@brief stack that stores all types o successfully processedRequest*/
    stack<vector<Request>> ProcessedRequests;

    /**@brief set of all turmas*/
    set<Turma> turmas;
    /**@brief stack that stores all types o successfully processedRequest*/
    stack<Request> processedRequests;

    /**@brief Hash table to store all turmas, based on the TurmasHash function*/

    unordered_set<Turma, Turma::TurmaHash> turmasTable;

    /**
     * @brief Process a removal request
     * @param request
     * @note pushes the request into the respective queue
     * */
    void processRemovalRequest(const Request &request);
};
#endif //AED2324_PRJ1_G15_PARSE_H
