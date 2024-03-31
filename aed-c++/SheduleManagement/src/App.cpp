/**
 * @file App.cpp
 *
 * @brief Implementation of the App class
 *
 * @details This file contains the implementation of the App class
 *
 * @see App.h
 */
#include "../include/App.h"

App::App(const Parse &parser) {
    this->parser = parser;
    this->sleepTime = 350000;
}

void App::waitForInput() const{
    usleep(sleepTime);
    string enter;
    cout << "Press any key to continue: " << endl;
    cin.ignore();
    getline(cin, enter);
    cout << endl;
    system("clear");
}

int App::optionsMenu() const {

    int option;

    cout    << "+--------------------------------------------------+" << endl
            << "|             Schedule Management LEIC             |" << endl
            << "+---------------------- Menu ----------------------+" << endl <<"\n"
            << "[1] Consultas" << endl
            << "[2] Pedidos" << endl
            << "[3] Gestao de Pedidos"<< endl
            << "[0] Exit" << endl;
    cout    << endl << "----------------------------------------------------" << endl <<"\n"
            << "Select an option: " ;

    cin >> option;
    cout << endl;
    while(option < 0 || option > 3) {
        if (cin.fail()) {
            cin.clear();
        }
        cout << ">> Please choose a valid option: ";
        cin >> option;
        cout << endl;
    }
    return option;
}

int App::consultasMenu() const{
    int option;
    system("clear");
    cout << endl << "----------------------- CONSULTAS -----------------------" << endl << "\n"
         << "1 Students" << endl
         << "2 Schedule" << endl
         << "3 Classes" << endl
         << "4 UCs" << endl
         << "5 Years of L.EIC" << endl
         << "0 Back to Main Menu" << endl << "\n"
         << "Select an option: ";
    cin >> option;
    cout << endl;
    while(option < 0 || option > 5) {
        if (cin.fail()) {
            cin.clear();
        }
        cout << ">> Please choose a valid option: ";
        cin >> option;
        cout << endl;
    }
    return option;
}
int App::optionsMenuClasses() const{
    int option;
    system("clear");
    cout << endl << "=======================================================" << endl << "\n"
         << "1 Check all Classes " << endl
         << "2 Check Classes by year" << endl
         << "3 Check Classes UC" << endl
         << "0 Back to main menu" << endl << "\n"

         << "Select an option: ";
    cin >> option;
    cout << endl;
    while (option < 0 || option > 3) {
        if (cin.fail()) {
            cin.clear();
        }
        cout << ">> Please choose a valid option: ";
        cin >> option;
        cout << endl;
    }
    return option;
}
int App::optionsMenuShedule() const{
    int option;
    system("clear");
    cout << endl << "=======================================================" << endl << "\n"
         << "1 Check student schedule" << endl
         << "2 Check class schedule" << endl
         << "3 Check UC schedule" << endl
         << "0 Back to main menu" << endl << "\n"

         << "Select an option: ";
    cin >> option;
    cout << endl;
    while (option < 0 || option > 5) {
        if (cin.fail()) {
            cin.clear();
        }
        cout << ">> Please choose a valid option: ";
        cin >> option;
        cout << endl;
    }
    return option;
}

int App::optionsMenuUc() const {
    int option;
    system("clear");
    cout << endl << "=======================================================" << endl << "\n"
         << "1 List all UCs by Nº of students" << endl
         << "2 Check UCs by year" << endl
         << "0 Back to main menu" << endl << "\n"

         << "Select an option: ";
    cin >> option;
    cout << endl;
    while (option < 0 || option > 2) {
        if (cin.fail()) {
            cin.clear();
        }
        cout << ">> Please choose a valid option: ";
        cin >> option;
        cout << endl;
    }
    return option;
}

int App::optionsMenuAlunos() const{
    int option;
    system("clear");
    cout << endl << "=======================================================" << endl << "\n"
         << "1 List students by UC" << endl
         << "2 List students by Class" << endl
         << "3 List students by Year" << endl
         << "4 List students enrolled in more than n UCS" << endl
         << "5 List all students of LEIC" << endl
         << "0 Back to main menu" << endl << "\n"

         << "Select an option: ";
    cin >> option;
    cout << endl;
    while (option < 0 || option > 5) {
        if (cin.fail()) {
            cin.clear();
        }
        cout << ">> Please choose a valid option: ";
        cin >> option;
        cout << endl;
    }
    return option;
}

int App::gestaoPedidosMenu() const {
    int option;
    system("clear");
    cout << endl << "----------------------- GESTAO DE PEDIDOS -----------------------" << endl << "\n"
         << "1 Print pending requests" << endl
         << "2 Process requests" << endl
         << "3 Print rejected requests" << endl
         << "4 Undo the request" << endl
         << "0 Back to main menu" << endl << "\n"
         << "Select a gestao de pedidos option: ";
    cin >> option;
    cout << endl;
    while (option < 0 || option > 4) {
        if (cin.fail()) {
            cin.clear();
        }
        cout << ">> Please choose a valid option: ";
        cin >> option;
        cout << endl;
    }
    return option;
}

int App::run() {
    system("clear");
    parser.readFiles();

    while (true) {
        system("clear");
        int option = optionsMenu();
        switch (option) {
            case 1: {
                int consulta_option=-1;
                do{
                    consulta_option=consultasMenu();
                    switch(consulta_option){
                        case 1:{
                            int alunos_option = -1;
                            do{
                                alunos_option = optionsMenuAlunos();
                                switch (alunos_option){
                                    case 1:{
                                        checkUcStudents();
                                        waitForInput();
                                        break;
                                    }
                                    case 2:{
                                        checkClassStudents();
                                        waitForInput();
                                        break;
                                    }
                                    case 3:{
                                        checkStudentsByYear();
                                        waitForInput();
                                        break;
                                    }
                                    case 4:{
                                        checkBynUcs();
                                        waitForInput();
                                        break;
                                    }
                                    case 5:{
                                        checkCourseStudents();
                                        waitForInput();
                                        break;
                                    }
                                }
                            }while(alunos_option!=0);
                            break;
                        }
                        case 2:{
                            int schedule_option = -1;
                            do{
                                schedule_option = optionsMenuShedule();
                                switch (schedule_option){
                                    case 1:{
                                        checkStudentSchedule();
                                        waitForInput();
                                        break;
                                    }
                                    case 2:{
                                        checkClassSchedule();
                                        waitForInput();
                                        break;
                                    }
                                    case 3:{
                                        checkUcSchedule();
                                        waitForInput();
                                        break;
                                    }
                                }
                            }while(schedule_option != 0);
                            break;
                        }
                        case 3:{
                            int classes_options = optionsMenuClasses();
                            while(classes_options != 0){
                                checkClasses(classes_options);
                                waitForInput();
                                classes_options = optionsMenuClasses();
                            }
                            break;
                        }
                        case 4:{
                            int UCs_options = optionsMenuUc();
                            while(UCs_options != 0){
                                checkUcs(UCs_options);
                                waitForInput();
                                UCs_options = optionsMenuUc();
                            }
                            break;
                        }
                        case 5:{
                            int year_options = -1;
                            do{
                                year_options = optionsMenuYear();
                            }while(year_options!= 0);
                            system("clear");
                            break;
                        }
                    }
                }while(consulta_option!=0);
                break;
            }
            case 2: {
                int pedidos_option = requestsMenu();
                if(pedidos_option != 0) {
                    submitNewRequest(pedidos_option);
                }
                break;
            }
            case 3: {
                int gestao_pedidos_option=-1;
                do{
                    gestao_pedidos_option= gestaoPedidosMenu();
                    switch(gestao_pedidos_option){
                        case 1: {
                            printPendingRequests();
                            //waitForInput();
                            break;
                        }
                        case 2: {
                            processPendingRequests();
                            //waitForInput();
                            break;
                        }
                        case 3: {
                            parser.printRejectedRequests();
                            waitForInput();
                            break;
                        }
                        case 4: {
                            //processPendingRequests();
                            //waitForInput();
                            break;
                        }
                    }
                }while(gestao_pedidos_option!=0);
                break;
            }
            case 0: {
                saveInformation();
                return 0;
            }
            default:
                cout << ">> Invalid option." << endl;
        }
    }
}

void App::checkStudentSchedule() const {
    string upNumber;
    cout << "Please insert the student's UP number: ";
    cin >> upNumber;
    parser.printStudentSchedule(upNumber);
}

void App::checkClassSchedule() const{
    string classCode;
    cout << "Please insert the class code: "; cin >>classCode; cout<<endl;
    parser.printClassSchedule(classCode);
}

int App::sortingMenu() const {
    cout << "1 By name ascending" << endl;
    cout << "2 By name descending" << endl;
    cout << "3 By UPcode ascending" << endl;
    cout << "4 By UPcode descending" << endl;
    cout << "In which order do you want to display the students? ";
    int option; cin >> option; cout << endl;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(option < 1 || option > 4){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    return option;
}

void App::checkClassStudents() const {
    int option = sortingMenu();
    string ucCode, classCode;
    cout << "Please insert the uc code: " << endl;
    cin >> ucCode;
    cout << "Please insert the Class code: " << endl;
    cin >> classCode;
    cout << endl;
    Turma turma = Turma(classCode, ucCode);
    switch (option) {
        case 1:
            parser.printClassStudents(turma, "By name ascending");
            break;
        case 2:
            parser.printClassStudents(turma, "By name descending");
            break;
        case 3:
            parser.printClassStudents(turma, "By UPcode ascending");
            break;
        case 4:
            parser.printClassStudents(turma, "BY UPcode descending");
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}

void App::checkUcSchedule() const {
    string ucCode;
    cout << "Insert the uc code: "; cin >> ucCode; cout << endl;
    parser.printUcSchedule(ucCode);
}

void App::checkUcStudents() const{

    vector<Turma> byYear = filterTurmasByYear();

    cout << byYear[0].getUcCode() << endl;
    // Iterate through the vector, and print only unique values
    for (size_t i = 1; i < byYear.size(); ++i) {
        if (byYear[i].getUcCode() != byYear[i - 1].getUcCode()) {
            cout << byYear[i].getUcCode() << endl;
        }
    }

    cout << "Chose an Uc from above (code): " << endl;
    string UCcode; cin >> UCcode; cout << endl;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(find_if(byYear.begin(), byYear.end(), [&UCcode](Turma &t){return t.getUcCode() == UCcode;}) == byYear.end()){
        cout << ">> Please choose a valid UCcode: "; cin >> UCcode; cout << endl;
    }

    int option = sortingMenu();

    switch (option) {
        case 1:
            parser.printUcStudents(UCcode, "By name ascending");
            break;
        case 2:
            parser.printUcStudents(UCcode, "By name descending");
            break;
        case 3:
            parser.printUcStudents(UCcode, "By UPcode ascending");
            break;
        case 4:
            parser.printUcStudents(UCcode, "By UPcode descending");
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}

void App::checkStudentsByYear() const{
    int option = sortingMenu();

    switch (option) {
        case 1:
            parser.printStudentsByYear("By name ascending");
            break;
        case 2:
            parser.printStudentsByYear("By name descending");
            break;
        case 3:
            parser.printStudentsByYear("By UPcode ascending");
            break;
        case 4:
            parser.printStudentsByYear("BY UPcode descending");
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}

void App::checkBynUcs() {
    multiset<StudentClasses, studentByNUCS> studentsbyNUCS = parser.getStudentsByNUCS();
    int ucs_n;
    cout << "\nEstudantes com mais de quantas UCs? ";
    cin >> ucs_n;

    vector<StudentClasses> v;
    for (const auto& student : studentsbyNUCS) {
        if (student.getTurmas().size() > ucs_n)
            v.push_back(student);
    }
    system("clear");
    int option = sortingMenu();

    switch (option) {
        case 1:
            sort(v.begin(), v.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() < b.getStudentName();});
            for(auto & student : v)
                cout << student << "\n";
            break;
        case 2:
            sort(v.begin(), v.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() > b.getStudentName();});
            for(auto & student : v)
                cout << student << "\n";
            break;
        case 3:
            sort(v.begin(), v.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentCode() < b.getStudentCode();});
            for(auto & student : v)
                cout << student << "\n";
            break;
        case 4:
            sort(v.begin(), v.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentCode() > b.getStudentCode();});
            for(auto & student : v)
                cout << student << "\n";
            break;
        default:
            cout << ">> Invalid option." << endl;
    }



    cout << "\n\n\tExiste um total de " << v.size() << " estudantes com mais de " << ucs_n << " UCs." << endl;
}

int App::requestsMenu() const {
    system("clear");
    int option;
    cout << endl << "----------------------- PEDIDOS -----------------------" << endl << endl;
    cout << "There are 3 types of requests:" << endl;
    cout << "1 - Switch class (Switch)" << endl;
    cout << "2 - Enroll in a new uc (Add)" << endl;
    cout << "3 - Cancel a uc registration (Remove)" << endl;
    cout << "0 - Go back" << endl;
    cout << "What type of request do you want to submit? ";
    cin >> option;
    while(option < 0 || option > 3) {
        if (cin.fail()) {
            cin.clear();
        }
        cout << ">> Please choose a valid option: ";
        cin >> option;
        cout << endl;
    }
    return option;
}

void App::submitChangingRequest(StudentClasses* student) {
    string ucCode, classCode;
    vector<Turma> byStudent = filterByStudent(*student);
    system("clear");
    cout << "========================================" << endl << endl;

    cout << "The student is enrolled in the following UCs" << endl;

    cout << byStudent[0].getUcCode() << endl;
    // Iterate through the vector, and print only unique values
    for (size_t i = 1; i < byStudent.size(); ++i) {
        if (byStudent[i].getUcCode() != byStudent[i - 1].getUcCode()) {
            cout << byStudent[i].getUcCode() << endl;
        }
    }

    cout << endl << "Choose an UC from above" << endl;
    cin >> ucCode;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(find_if(byStudent.begin(), byStudent.end(), [&ucCode](Turma &t){return t.getUcCode() ==ucCode;}) == byStudent.end()){
        cout << ">> Please choose a valid UCcode: "; cin >> ucCode; cout << endl;
    }
    Turma t = student->findTurma(ucCode);
    if(t == Turma()){
        cout << ">> This student is not enrolled in this uc." << endl;
        waitForInput();
        return;
    }
    cout << "Please insert the class code: ";
    cin >> classCode;
    if(t.getClassCode() == classCode){
        cout << ">> This student is already in this class." << endl;
        waitForInput();
        return;
    }
    TurmaSchedule *ts = parser.findSchedule(Turma(classCode, ucCode));
    if (ts == nullptr) {
        cout << ">> Class not found." << endl;
        waitForInput();
        return;
    }
    parser.addChangingRequest(*student, Turma(classCode, ucCode));
    cout << ">> Request submitted successfully." << endl;
    waitForInput();
}

void App::submitEnrollmentRequest(StudentClasses *student) {
    string ucCode, classCode;
    system("clear");
    cout << "========================================" << endl << endl;

    vector<Turma> byStudent = filterByStudent(*student);
    unordered_set<Turma, Turma::TurmaHash> turmasTable = parser.getTurmasTable();
    vector<Turma> turmas(turmasTable.begin(), turmasTable.end());

    cout << "The student is enrolled in the following UCs" << endl;

    cout << byStudent[0].getUcCode() << endl;
    // Iterate through the vector, and print only unique values
    for (size_t i = 1; i < byStudent.size(); ++i) {
        if (byStudent[i].getUcCode() != byStudent[i - 1].getUcCode()) {
            cout << byStudent[i].getUcCode() << endl;
        }
    }
    cout << endl << "Enter an UC :" << endl;
    cin >> ucCode; cout << endl;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(find_if(turmas.begin(), turmas.end(), [&ucCode](Turma &t){return t.getUcCode() == ucCode;}) == turmas.end()){
        cout << ">> Please choose a valid UCcode: "; cin >> ucCode; cout << endl;
    }

    cout << "Please insert the class code: ";
    cin >> classCode;
    cout << "Finding class ..." << endl;
    TurmaSchedule *cs = parser.findSchedule(Turma(classCode, ucCode));
    if (cs == nullptr) {
        cout << ">> Class not found." << endl;
        waitForInput();
        return;
    }
    cout << "Submiting request" << endl;
    parser.addEnrollmentRequest(*student, Turma(classCode, ucCode));
    cout << parser.getNumberOfPendingRequests() << endl;
    cout << ">> Request submitted successfully." << endl;
    waitForInput();
}

void App::submitRemovalRequest(StudentClasses *student) {
    string ucCode;
    vector<Turma> byStudent = filterByStudent(*student);
    system("clear");
    cout << "========================================" << endl << endl;
    cout << "The student is enrolled in the following UCs" << endl;

    cout << byStudent[0].getUcCode() << endl;
    // Iterate through the vector, and print only unique values
    for (size_t i = 1; i < byStudent.size(); ++i) {
        if (byStudent[i].getUcCode() != byStudent[i - 1].getUcCode()) {
            cout << byStudent[i].getUcCode() << endl;
        }
    }


    cout << endl << "Choose an UC from above" << endl;
    cin >> ucCode; cout << endl;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(find_if(byStudent.begin(), byStudent.end(), [&ucCode](Turma &t){return t.getUcCode() == ucCode;}) == byStudent.end()){
        cout << ">> Please choose a valid UCcode: "; cin >> ucCode; cout << endl;
    }
    for(const Turma &i : student->getTurmas()){
        if(i.getUcCode() == ucCode){
            parser.addRemovalRequest(*student, i);
            cout << ">> Request submitted successfully." << endl;
            return;
        }
    }
    cout << ">> Request submitted successfully." << endl;
    waitForInput();
}

void App::submitNewRequest(int option) {
    string upNumber;
    cout << "Please insert the student's UP number: ";
    cin >> upNumber;
    cout << endl;
    StudentClasses *student = parser.findStudent(upNumber);
    if (student == nullptr) {
        cout << ">> Student not found." << endl;
        waitForInput();
        return;
    }
    switch (option) {
        case 1:
            submitChangingRequest(student);
            break;
        case 2:
            submitEnrollmentRequest(student);
            break;
        case 3:
            submitRemovalRequest(student);
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}

void App::processPendingRequests() {
    if(parser.getNumberOfPendingRequests() == 0){
        cout << ">> There are no pending requests." << endl;
        waitForInput();
        return;
    }
    string s;
    cout << "Do you want to see all pending changingRequests first? (y/n) "; cin >> s; cout << endl;
    if(s == "y" || s == "Y"){
        parser.printPendingRequests();
        //waitForInput();
    }
    parser.processRequests();
    saveInformation();
    waitForInput();
}

void App::saveInformation() {
    parser.writeFiles();
}

void App::printPendingRequests() const {
    system("clear");
    if(parser.getNumberOfPendingRequests() == 0){
        cout << "======================================" << endl;
        cout << ">> There are no pending requests." << endl;
        waitForInput();
        return;
    }
    parser.printPendingRequests();
    waitForInput();
}

void App::checkCourseStudents() const {
    int option = sortingMenu();

    switch (option) {
        case 1:
            parser.printCourseStudents("By name ascending");
            break;
        case 2:
            parser.printCourseStudents("By name descending");
            break;
        case 3:
            parser.printCourseStudents("By UPcode ascending");
            break;
        case 4:
            parser.printCourseStudents("BY UPcode descending");
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}

void App::checkClasses(int type) const {
    unordered_set<Turma, Turma::TurmaHash> turmasTable = parser.getTurmasTable();

    vector<Turma> filteredTurmas(turmasTable.begin(), turmasTable.end());
    vector<Turma> byYear;
    vector<Turma> byUc;

    //filtrar as turmas por uc
    if(type == 3){

        byYear = filterTurmasByYear();

        cout << byYear[0].getUcCode() << endl;
        // Iterate through the vector, and print only unique values
        for (size_t i = 1; i < byYear.size(); ++i) {
            if (byYear[i].getUcCode() != byYear[i - 1].getUcCode()) {
                cout << byYear[i].getUcCode() << endl;
            }
        }

        cout << "========================================" << endl;

        cout << "Chose an Uc from above (code): " << endl;
        string UCcode; cin >> UCcode; cout << endl;
        if(cin.fail())
            throw invalid_argument(">> Invalid number");
        while(find_if(byYear.begin(), byYear.end(), [&UCcode](Turma &t){return t.getUcCode() == UCcode;}) == byYear.end()){
            cout << ">> Please choose a valid UCcode: "; cin >> UCcode; cout << endl;
        }
        copy_if(byYear.begin(), byYear.end(), back_inserter(byUc), [&UCcode](Turma &t1){return t1.getUcCode() == UCcode;});
        filteredTurmas = byUc;
    }

    //filtrar as turmas por ano
    else if(type == 2){
        byYear = filterTurmasByYear();
        filteredTurmas = byYear;
    }

    int option = sortingClassesMenu();

    switch (option) {
        case 1:
            parser.sortTypeClasses(filteredTurmas, "By name ascending");
            break;
        case 2:
            parser.sortTypeClasses(filteredTurmas, "By name descending");
            break;
        case 3:
            parser.sortTypeClasses(filteredTurmas, "By UPcode ascending");
            break;
        case 4:
            parser.sortTypeClasses(filteredTurmas, "BY UPcode descending");
            break;
        case 5:
            parser.sortTypeClasses(filteredTurmas, "By number of students ascending");
            break;
        case 6:
            parser.sortTypeClasses(filteredTurmas, "");
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}

int App::optionsMenuYear() const {

    cout << "1 List ascending by number of students" << endl;
    cout << "2 List descending by number of students" << endl
    << endl << "0 Go Back" << endl;

    int option; cin >> option; cout << endl;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(option < 0 || option > 2){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }

    vector<pair<int, string>> v = parser.getOcupationYear();

    switch (option) {
        case 1:
            sort(v.begin(), v.end());
            for(const auto& p : v)
                cout << "(" << p.first << ")" << " " << p.second << endl;
            break;
        case 2:
            sort(v.rbegin(), v.rend());
            for(const auto& p : v)
                cout << "(" << p.first << ")" << " " << p.second << endl;
            break;
        case 0:
            return 0;
        default:
            cout << ">> Invalid option." << endl;
    }
    return option;
}

int App::sortingClassesMenu() const {

    cout << "1 By name ascending" << endl;
    cout << "2 By name descending" << endl;
    cout << "3 By UPcode ascending" << endl;
    cout << "4 By UPcode descending" << endl;
    cout << "5 By number of students ascending" << endl;
    cout << "6 By number of students descending" << endl;
    cout << "In which order do you want to display the classes? ";
    int option; cin >> option; cout << endl;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(option < 1 || option > 6){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    return option;

}

void App::checkUcs(int type) const {
    unordered_set<Turma, Turma::TurmaHash> turmasTable = parser.getTurmasTable();

    vector<Turma> filteredTurmas(turmasTable.begin(), turmasTable.end());
    vector<Turma> byYear;

    //filtrar por ano
    if(type == 2){
        byYear = filterTurmasByYear();
        filteredTurmas = byYear;
    }

    int option = sortingMenuUc();

    switch (option) {
        case 1:
            parser.sortTypeUCs(filteredTurmas, "By number of students ascending");
            break;
        case 2:
            parser.sortTypeUCs(filteredTurmas, "");
            break;
        default:
            cout << ">> Invalid option." << endl;
    }
}

int App::sortingMenuUc() const {
    cout << "1 List by Nº of students ascending" << endl;
    cout << "2 List by Nº of students descending" << endl;
    cout << "Choose:  ";
    int option; cin >> option; cout << endl;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(option < 1 || option > 6){
        cout << ">> Please choose a valid option: "; cin >> option; cout << endl;
    }
    return option;
}

vector<Turma> App::filterTurmasByYear() const {
    unordered_set<Turma, Turma::TurmaHash> turmasTable = parser.getTurmasTable();

    vector<Turma> filteredTurmas(turmasTable.begin(), turmasTable.end());
    vector<Turma> byYear;

    //filtrar as turmas por ano
    cout << "========================================" << endl;
    cout << "Choose a year 1º, 2º or 3º" << endl;
    unsigned int year; cin >> year; cout << endl;
    if(cin.fail())
        throw invalid_argument(">> Invalid number");
    while(year < 1 || year > 3){
        cout << ">> Please choose a valid year: "; cin >> year; cout << endl;
    }
    cout << "========================================" << endl;
    copy_if(filteredTurmas.begin(), filteredTurmas.end(), back_inserter(byYear), [&year](Turma &t1){return t1.getClassCode()[0] - '0' == year;});

    sort(byYear.begin(), byYear.end());

    return byYear;

}
vector<Turma> App::filterByStudent(const StudentClasses &student) const {
    unordered_set<Turma, Turma::TurmaHash> turmasTable = parser.getTurmasTable();
    vector<Turma> filteredTurmas(turmasTable.begin(), turmasTable.end());
    vector<Turma> byStudent;
    copy_if(filteredTurmas.begin(), filteredTurmas.end(), back_inserter(byStudent), [&student](Turma &t1){return student.isEnrolled(t1.getUcCode());});
    sort(byStudent.begin(), byStudent.end());
    return byStudent;
}

vector<Turma> App::filterBYUc(const string &UCcode) const {
    unordered_set<Turma, Turma::TurmaHash> turmasTable = parser.getTurmasTable();
    vector<Turma> filteredTurmas(turmasTable.begin(), turmasTable.end());
    vector<Turma> byStudent;
    copy_if(filteredTurmas.begin(), filteredTurmas.end(), back_inserter(byStudent), [&UCcode](const Turma &t1){return t1.getUcCode() == UCcode;});
    sort(byStudent.begin(), byStudent.end(), [](const Turma &t1, const Turma &t2){return t1.getClassCode() < t2.getClassCode();});
    return byStudent;

}


