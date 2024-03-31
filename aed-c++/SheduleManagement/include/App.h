#ifndef AED2324_PRJ1_G15_APP_H
#define AED2324_PRJ1_G15_APP_H

/**
 * @file App.h
 * @brief Header file for the App class
 * @details This file contains the declaration of the App class
 * */
#include "Parse.h"
#include <unistd.h>

/**
 * @brief Class that represents the application
 * @details This class provides a menu-based user interface for interacting with the program.
 * */
class App {
public:

    /**
    * @brief Constructor, sleepTime is set to 350000 ms
    * @details Time complexity: O(1)
    * @param ScheduleManager manager
    */
    explicit App(const Parse &parser);

    /**
     * @brief Function that prints the menu to consult the current information
     * @return the option chosen by the user
     * */
    int consultasMenu() const;

    /**
     * @brief Function that prints the menu to choose the request management option
     * @return the option chosen by the user
     * */
    int gestaoPedidosMenu() const;

    /**
    * @brief Function that runs the application, it calls the menu and the functions to read the files
    * @return 0 if the application was closed successfully
    */
    int run();

    /**
     * @brief Waits for user input before continuing.
     * This function adds a delay and prompts the user to press Enter to continue.
     * */
    void waitForInput() const;

    /**
    * @brief Function that prints the alunos menu
    * @return the option chosen by the user
    */
    int optionsMenuAlunos() const;

    /**
    * @brief Function that prints the schedule menu
    * @return the option chosen by the user
    */
    int optionsMenuShedule() const;

    /**
    * @brief Function that prints the classes menu
    * @return the option chosen by the user
    */
    int optionsMenuClasses() const;

    /**
    * @brief Function that prints the Year menu
    * @return the option chosen by the user
    */
    int optionsMenuYear() const;

    /**
    * @brief Function that prints the Uc menu
    * @return the option chosen by the user
    */
    int optionsMenuUc() const;
    /**
    * @brief Function that prints the main menu
    * @return the option chosen by the user
    */
    int optionsMenu() const;
    /**
     * @brief Ask the user to insert the sorting option
     * @return sorting option
     */
    int sortingMenu() const;
    int sortingClassesMenu() const;
    int sortingMenuUc() const;

    /**
     * @brief Asks the user to insert the type of request
     * @details Time complexity: O(1)
     */
    int requestsMenu() const;

    /**
    * @brief Asks the user to input the students's UP number and prints the schedule of that student
     * @details Time complexity: O(log p) + O(hlog n) + O(hl*log(r*log(c)) + O(cd)
     * where: \n
     * - p is the number of lines in students_classes.csv \n
     * - h is the number of classes of the student \n
     * - n is the number of students \n
     * - l is the number of slots in a given ClassSchedule \n
     * - r is the number of slots in a weekday \n
     * - c is the number of slots in a weekday \n
     * - d is the number of classes in a slot\n
    */
    void checkStudentSchedule() const;

    /**
     * @brief Ask the user to insert the class code and prints the schedule of that class
     * @details Time complexity: O(n*l*log(r*log(c)) + O(cd) where: \n
     * - n is the number of schedules \n
     * - l is the number of slots in a schedule \n
     * - c is the number of slots in a weekday \n
     * - r is the number of weekdays \n
     * - d is the number of classes in a slot\n
     */
    void checkClassSchedule() const;
    /**
     * @brief Asks the user to insert the ucCode and classCode and prints the students enrolled
     * @details Time complexity: O(log n) + O(q log q) where: \n
     * - n is the number of schedules(lines classes_per_uc.csv) \n
     * - q is the number of students in the ClassSchedule
    */
    void checkClassStudents() const;
    /**
     * @brief Asks the user to insert the ucId and prints the schedule of that uc
     * @details Time complexity: O(n*l*log(r*log(c)) + O(cd) where: \n
     * - n is the number of schedules\n
     * - l is the number of slots in a schedule \n
     * - c is the number of slots in a weekday\n
     * - r is the number of weekdays \n
     * - d is the number of classes in a slot \n
    */
    void checkUcSchedule() const;

    /**
     * @brief Checks and prints the students in a specific UC.
     * @details Asks the user to insert the ucCode and prints the students enrolled
     */
    void checkUcStudents() const;

    /**
    * @brief Checks and prints the list of students sorted by year.
    * We can choose the sorting order, including by name or UP code in ascending or descending order.
    */
    void checkStudentsByYear() const;

    /**
     * @brief Checks and prints the list of students in a course.
     * This function checks and prints the list of students in a specific course.
     * We can choose the sorting order, including by name or UP code in ascending or descending order.
     * */
    void checkCourseStudents() const;

    /**
     * @brief Checks and prints the list of classes filter byYear
     *
     * */
    void checkClasses(int type) const;

    /**
     * @brief Checks and prints the list of classes filter byYear, and byUC
     * */
    void checkUcs(int type) const;


    /**
     * @brief Filters the turmasTable into a vector containing all the Turmas of a year
     * @note asks the user the year to filter
     * @details Time complexity O(nlog(n)) because we sort the vector at the end
     */
    vector<Turma> filterTurmasByYear() const;



    /**
     * @brief Checks and prints the list of students in multiple courses.
     * */
    void checkBynUcs();
    /**
    * @brief Function that allows the student to submit a request to change a class
    */
    void submitNewRequest(int option);

    /**
     * @brief Asks the user to insert the class code he wants to change into
     * @details Time complexity: O(log n) where:
     * - n is the number of schedules(lines file classes_per_uc.csv)
     */
    void submitChangingRequest(StudentClasses* student);

    /**
     * @brief Asks the user to insert the uc code he wants to cancel
     * @details Time complexity: O(t) where t is the number of UcClasses of the student
     */
    void submitRemovalRequest(StudentClasses* student);

    /**
     * @brief Asks the user to insert the uc code he wants to enroll into
     * @details Time complexity: O(log n) where n is the number of schedules(lines file classes_per_uc.csv)
     */
    void submitEnrollmentRequest(StudentClasses* student);

    /**
     * @brief Function that processes all pending changingRequests
     * @details Time complexity: Time complexity: O(h) + O(log n * log n) + O(log p) + O(t*log n + t*lr) + O(nlog n) where: \n
     * - n is the number of schedules (lines in the classes_per_uc.csv file)\n
     * - p is the number of lines in the students.csv file \n
     * - h is the number of classes of the student submitting the request \n
     * - t is the number of classes the student is enrolled in \n
     * - n is the number of lines in classes_per_uc.csv \n
     * - l is the number of slots of the first class    \n
     */
    void processPendingRequests();

    /**
     * @brief Prints the list of pending requests.
     * */
    void printPendingRequests() const;

    /**
     * @brief Function that writes the information to the files before closing the program
     * @details Time complexity: O(O(st) where s is the number of students in the set and t is the number of classes of each student)
     */
    void saveInformation();


private:

    /**
     * @brief An instance of the Parse class for handling file parsing and data processing.
     * */
    Parse parser;

    /**
     * @brief The sleep time value used for waiting for user input (in microseconds).
     * */
    int sleepTime;

    /**
     * @brief Filters the turmasTable into a vector containing all the Turmas of a specific student
     * @param student
     * @details Time complexity O(nlog(n)) because we sort the vector at the end
     */
    vector<Turma> filterByStudent(const StudentClasses &student) const;

    vector<Turma> filterBYUc(const string &UCcode) const;
};

#endif //AED2324_PRJ1_G15_APP_H
