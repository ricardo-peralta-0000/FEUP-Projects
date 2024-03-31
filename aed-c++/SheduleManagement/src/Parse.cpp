/**
 * @file Parse.cpp
 *
 * @brief Handles parsing and processing of class schedules and student information.
 *
 * @details This file contains the implementation of the Parse class.
 *
 * @see Parse.h
 *
 */
#include "../include/Parse.h"
#include <chrono>

Parse::Parse() = default;

void Parse::readFiles() {
    auto start = std::chrono::high_resolution_clock::now();

    createSchedules();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
    setSchedules();
    createStudents();

}

void Parse::createSchedules(){
    fstream file("../docs/input/classes_per_uc.csv");
    file.ignore(1000, '\n');
    vector<string> row;
    string line, word;
    while (getline(file, line)) {
        if(line[line.size()-1] == '\r')
            line.resize(line.size()-1);
        row.clear();
        stringstream str(line);
        while(getline(str, word, ',')) //Number of words per line is constant(O(1))
            row.push_back(word);
        Turma turma(row[1], row[0], 0);
        TurmaSchedule cs(turma);
        turmasTable.insert(turma);
        //cout << cs.getUcTurmas() << endl;
        schedules.push_back(cs);
    }
}

void Parse::setSchedules() {
    fstream file("../docs/input/classes.csv");
    file.ignore(1000, '\n');
    vector<string> row;
    string line, word;
    while (getline(file, line)) {
        row.clear();
        if (line[line.size() - 1] == '\r')
            line.resize(line.size() - 1);
        stringstream str(line);
        while (getline(str, word, ',')) //Number of words per line is constant(O(1)
            row.push_back(word);
        string classCode = row[0], ucCode = row[1], weekDay = row[2], startTime = row[3], duration = row[4], type = row[5];
        Turma turma(classCode, ucCode);
        TimeSlot timeSlot(weekDay, stof(startTime), stof(duration), type);
        //cout << turma << endl;
        //cout << timeSlot;
        unsigned long scheduleIndex = binarySearchSchedules(turma);  //O(log n)
        if (scheduleIndex != -1) {
            schedules[scheduleIndex].addSlot(timeSlot);
        }
    }
}

void Parse::createStudents() {
    fstream file("../docs/input/students_classes.csv");
    file.ignore(1000, '\n');
    vector<string> row;
    string line, word;
    while (getline(file, line)) { //O(p), being p the number of lines in the file students_classes.csv
        row.clear();
        word.clear();
        if (line[line.size() - 1] == '\r')
            line.resize(line.size() - 1);
        stringstream str(line);
        while (getline(str, word, ',')) //Number of words per line is constant(O(1)
            row.push_back(word);
        string id = row[0], name = row[1];

        Turma newTurma = Turma(row[3], row[2], 1);

        auto it1 = turmasTable.find(newTurma);
        if(it1 != turmasTable.end()){
            turmasTable.erase(it1);
            newTurma.setSize(it1->getSize() + 1);
            turmasTable.insert(newTurma);
        }

        unsigned long i = binarySearchSchedules(newTurma); //O(log n) where n is the number of schedules(lines in the classes_per_uc.csv file)
        StudentClasses student(id, name);
        //cout << student << newTurma << endl;
        if (students.find(student) == students.end()) {
            student.addTurma(this->schedules[i].getUcTurmas());
            students.insert(student); //O(log n)
        } else {
            auto it = students.find(student);
            StudentClasses modStudent = *it;
            students.erase(it);
            modStudent.addTurma(this->schedules[i].getUcTurmas());
            students.insert(modStudent);
        }
        this->schedules[i].addStudent(student);
    }
}

unsigned long int Parse::binarySearchSchedules(const Turma &desiredTurma) const{
    unsigned long left = 0, right = schedules.size() - 1, middle = 0;

    while(left <= right){

        middle = (left + right)/2;
        if(schedules[middle].getUcTurmas() == desiredTurma)
            return middle;
        else if(schedules[middle].getUcTurmas() < desiredTurma)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return -1;
}

StudentClasses* Parse::findStudent(const string &studentId) const{
    auto student = students.find(StudentClasses(studentId, "")); //O(log p)
    return const_cast<StudentClasses *>(student == students.end() ? nullptr : &(*student));
}

TurmaSchedule* Parse::findSchedule(const Turma &turma) const {
    unsigned long index = binarySearchSchedules(turma); //O(log n)
    if(index == -1) return nullptr;
    return const_cast<TurmaSchedule*>(&schedules[index]);
}

vector<TurmaSchedule> Parse::classesOfUc(const string &ucId) const {
    vector<TurmaSchedule> classes;
    for(const TurmaSchedule &cs : schedules){
        if(cs.getUcTurmas().getUcCode() == ucId){
            classes.push_back(cs);
        }
    }
    return classes;
}

vector<StudentClasses> Parse::studentsOfUc(const string &ucId) const {
    vector<StudentClasses> ucStudents;
    vector<TurmaSchedule> ucClasses = classesOfUc(ucId); //O(n)
    for(const TurmaSchedule &ts : ucClasses){ //O(jq)
        for(const StudentClasses &student : ts.getStudents()){
            ucStudents.push_back(student);
        }
    }
    return ucStudents;
}


string ucIdToString(const string &ucId) {
    /** Maps ucId to uc abbreviation */
    map<string, string> name = {{"L.EIC001", "ALGA"}, {"L.EIC002", "AM I"}, {"L.EIC003", "FP"},
                                {"L.EIC004", "FSC"}, {"L.EIC005", "MD"}, {"L.EIC011", "AED"},
                                {"L.EIC012", "BD"}, {"L.EIC013", "F II"}, {"L.EIC014", "LDTS"},
                                {"L.EIC015", "SO"}, {"L.EIC021", "FSI"}, {"L.EIC022", "IPC"},
                                {"L.EIC023", "LBAW"}, {"L.EIC024", "PFL"}, {"L.EIC025", "RC"}};
    return name[ucId];
}

/**
 * @struct compareDayWeek
 * @brief Compares weekdays
 * @details Compares weekdays by their order in the week
 * @see Parse::printStudentSchedule()
 * */
struct compareDayWeek
{
    bool operator()(const string &d1, const string &d2) const
    {
        map <string, int> days = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}, {"Sunday", 7}};
        return days[d1] < days[d2];
    }
};

string toHours(float t){
    // Calculate the integer part as hours and the fractional part as minutes
    int hours = static_cast<int>(t);
    int minutes = static_cast<int>((t - hours) * 60);

    // manip the result in HH::MM format
    stringstream format;
    format << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes;

    return format.str();
}

void Parse::printStudentSchedule(const std::string &studentId) const {
    system("clear");
    StudentClasses* student = findStudent(studentId); //O(log p)
    if(student == nullptr) {
        cout << "Student not found!" << endl;
        return;
    }

    //Maps a weekday to a pair of slot/ucId (weekdays and slots are ordered because of map)
    map<string, map<TimeSlot, vector<string>>, compareDayWeek> weekdaySlot;
    list<Turma> studentClasses = student->getTurmas();

    for (const Turma &turma: studentClasses) { //O(hlog n) + O(hl*log(r*log(c))
        TurmaSchedule *cs = findSchedule(turma);
        for(const TimeSlot &slot: cs->getSlots()){//O(hl*log(r*log(c))
            weekdaySlot[slot.getWeekDay()][slot].push_back(turma.getUcCode()); //number of weekdays is constant
        }
    }

    cout << endl <<  ">> The student " << student->getSID().StudentName << " with UP number " << student->getSID().StudentCode
         << " is enrolled in the following classes:" << endl << "   ";
    student; //O(h)

    cout << endl << ">> The student's schedule is:" << endl;

    for(const auto &weekday: weekdaySlot) { //number of weekdays is constant
        cout << "   >> " << weekday.first << ": " << endl;
        for (const auto &slot: weekday.second) {//O(c) where c is the number of slots in a weekday
            cout << "      " << toHours(slot.first.getStartHour()) << " to "
                 << toHours(slot.first.getEndHour()) << "\t" << slot.first.getType() << "\t";
            for (const string &classId: slot.second) {//O(d) where d is the number of classes in a slot
                cout << ucIdToString(classId) << " - "<< classId << " ";
            }
            cout << endl;
        }
    }
}

void Parse::printClassSchedule(const std::string &classCode) const {
    system("clear");

    //maps a weekday to a pair Slot/ucId. Because we use a map it automatically sorts the weekdays and slots

    map<string, map<TimeSlot, vector<string>>, compareDayWeek> weekdaySlot;

    for(const TurmaSchedule &cs: schedules){ //O(n*l*log(r*log(c)) where n is the number of schedules, l is the number of slots in a schedule, c is the number of slots in a weekday and r is the number of weekdays
        if(cs.getUcTurmas().getClassCode() == classCode){
            for(const TimeSlot &slot: cs.getSlots()){
                weekdaySlot[slot.getWeekDay()][slot].push_back(cs.getUcTurmas().getClassCode());
            }
        }
    }

    if(weekdaySlot.empty()) {cout<<">> Class not found"<<endl; return;}

    cout << ">> The schedule for the class " << classCode << " is:" << endl;
    for(const auto &weekday: weekdaySlot) { //number of weekdays is constant
        cout << "   >> " << weekday.first << ": " << endl;
        for (const auto &slot: weekday.second) { //O(cd) where c is the number of slots in a given weekday and d is the number of classes in a slot
            cout << "      " << toHours(slot.first.getStartHour()) << " to "
                 << toHours(slot.first.getEndHour()) << "\t" << slot.first.getType() << "\t";
            for (const string &classId: slot.second) {
                cout << ucIdToString(classId) << " - "<< classId << " ";
            }
            cout << endl;
        }
    }

}

void Parse::printUcSchedule(const string &ucCode) const{
    system("clear");

    //maps a weekday to a pair Slot/ucId. Because we use a map it automatically sorts the weekdays and slots
    map<string, map<TimeSlot, vector<string>>, compareDayWeek> weekdaySlot;

    for(const TurmaSchedule &cs : schedules){ //O(n*l*log(r*log(c)) where n is the number of schedules, l is the number of slots in a schedule, c is the number of slots in a weekday and r is the number of weekdays
        if(cs.getUcTurmas().getUcCode() == ucCode){
            for(const TimeSlot &slot : cs.getSlots()){
                weekdaySlot[slot.getWeekDay()][slot].push_back(cs.getUcTurmas().getClassCode());
            }
        }
    }

    if(weekdaySlot.empty()){
        cout << ">> Uc not found" << endl;
        return;
    }
    cout << ">> The schedule for the Uc " << ucCode << " is:" << endl;
    for(const auto &weekday: weekdaySlot) { //number of weekdays is constant
        cout << "   >> " << weekday.first << ": " << endl;
        for (const auto &slot: weekday.second) { //O(cd) where c is the number of slots in a given weekday and d is the number of classes in a slot
            cout << "      " << toHours(slot.first.getStartHour()) << " to "
                 << toHours(slot.first.getEndHour()) << "\t" << slot.first.getType() << "\t";
            for (const string &classCode: slot.second) {
                cout << classCode << " ";
            }
            cout << endl;
        }
    }
}

void Parse::printClassStudents(const Turma &turma, const string &orderType) const{
    TurmaSchedule* cs = findSchedule(turma); //O(log n)
    if(cs == nullptr){
        cout << ">> Class not found" << endl;
        return;
    }
    system("clear");
    cout<<">> The students of the class "<<turma.getClassCode()<<" in the uc " << turma.getUcCode() <<" are:"<<endl;
    cs->printStudents(orderType); //O(q log q), where q is the number of students in the ClassSchedule
}

void Parse::printUcStudents(const string &ucId, const string &sortType) const {
    system("clear");
    vector<StudentClasses> studentsVector = studentsOfUc(ucId); //O(n) + O(jq) where n is the number of schedules(lines in classes_per_uc.csv file), j the number of ClassSchedules with a given ucId and q the number of students in a given ClassSchedule cs
    if(studentsVector.empty()){
        cout << ">> Uc not found" << endl;
        return;
    }
    if (sortType == "By name ascending") {
        sort(studentsVector.begin(), studentsVector.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() < b.getStudentName(); });   //O(d log d) where d is the number of students in a given uc
    } else if (sortType == "By name descending") {
        sort(studentsVector.rbegin(), studentsVector.rend(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() < b.getStudentName(); }); //O(d log d)
    } else if (sortType == "By UPcode ascending") {
        sort(studentsVector.begin(), studentsVector.end()); //O(d log d)
    } else if (sortType == "By UPcode descending") {
        sort(studentsVector.rbegin(), studentsVector.rend()); //O(d log d)
    } else {
        cout << "Invalid sortType" << endl;
        return;
    }

    cout << endl << ">> Number of students: " << studentsVector.size() << endl;
    cout << ">> Students:" << endl;
    for (const StudentClasses &student: studentsVector) { //O(d)
        cout << student.getStudentName() << " - " << student.getStudentCode() << endl;
    }
}

set<StudentClasses> Parse::getStudentsByYear(unsigned int year) const{
    set<StudentClasses> studentsByYear;
    for(const StudentClasses& student : students){
        if(student.getYear() == year)
            studentsByYear.insert(student);
    }
    return studentsByYear;
}

int Parse::getNumberOfStudentsUc(const std::string &ucId) const {
    return studentsOfUc(ucId).size();
}

int Parse::getNumberOfStudentsUcClass(const Turma &t) const{
    return findSchedule(t)->getStudents().size();
}

int Parse::getNumberOfPendingRequests() const {
    return changingRequests.size() + enrollmentRequests.size() + removalRequests.size();
}

Turma Parse::getFormerClass(const Request &request) const {
    return request.getStudent().findTurma(request.getDesiredUcClass().getUcCode());
}

void Parse::addChangingRequest(const StudentClasses &student, const Turma &t) {
    changingRequests.emplace(student, t, "Changing");
}

void Parse::addEnrollmentRequest(const StudentClasses &student, const Turma &t) {
    enrollmentRequests.emplace(student, t, "Enrollment");
}

void Parse::addRemovalRequest(const StudentClasses &student, const Turma &t) {
    removalRequests.emplace(student, t, "Removal");
}

bool Parse::classesOverlap(const Turma &t1, const Turma &t2) const{
    if(t1.getUcCode() == t2.getUcCode()) return false; //O(1)
    TurmaSchedule* cs1 = findSchedule(t1); //O(log n) being n the number of schedules
    TurmaSchedule* cs2 = findSchedule(t2); //O(log n)

    vector<TimeSlot> merged = cs1->getSlots();
    merged.insert(merged.end(), cs2->getSlots().begin(), cs2->getSlots().end());

    sort(merged.begin(), merged.end());

    for(size_t i = 1; i < merged.size(); i++){
        if(merged[i].overlaps(merged[i - 1]))
            return true;
    }
    return false;
}

bool Parse::requestHasCollision(const Request &request) const{
    StudentClasses student = request.getStudent(); //O(1)
    Turma desiredClass = request.getDesiredUcClass(); //O(1)
    list<Turma> studentClasses = student.getTurmas(); //O(1)
    for (const Turma &t : studentClasses){
        if(classesOverlap(t, desiredClass)) return true; //(n²logn)
    }
    return false;
}

bool Parse::requestExceedsCap(const Request &request) const{
    vector < TurmaSchedule> classesUc = classesOfUc(request.getDesiredUcClass().getUcCode());  //O(n) where n is the number of schedules
    sort(classesUc.begin(), classesUc.end(), [](const TurmaSchedule &c1, const TurmaSchedule &c2){  //O(nlog n)
        return c1.getStudents().size() < c2.getStudents().size();
    });

    int cap = classesUc.back().getNumStudents();
    if(classesUc[0].getNumStudents() == cap) cap++;
    return cap < getNumberOfStudentsUcClass(request.getDesiredUcClass()) + 1;
}

bool Parse::requestProvokesDisequilibrium(const Request &request) const {
    int numFormerClass = getNumberOfStudentsUcClass((getFormerClass(request))) -1; //O(log n)
    int numNewClass = getNumberOfStudentsUcClass(request.getDesiredUcClass()) + 1;

    return (numNewClass) - (numFormerClass) >= 4;
}

void Parse::processChangingRequest(const Request &request) {
    if(requestHasCollision(request)){ //O(n²*log n)
        rejectedRequests.emplace(request, "Collision in the students' schedule");
    }
    else if(requestExceedsCap(request)){ //O(nlog n) where n is the number of schedules (lines in the classes_per_uc.csv file)
        rejectedRequests.emplace(request, "Exceeds maximum number of students allowed in the class");
    }
    else if(requestProvokesDisequilibrium(request)){ //O(log n)
        rejectedRequests.emplace(request, "Change provokes disequilibrium between classes");
    }
    else{
        processedRequests.push(request);
        StudentClasses* student = findStudent(request.getStudent().getStudentCode()); //O(log n)
        Turma t = findSchedule(request.getDesiredUcClass())->getUcTurmas(); //O(log n)
        Turma t_prev = student->changeTurma(t);
        findSchedule(request.getDesiredUcClass())->addStudent(*student);
        findSchedule(t_prev)->removeStudent(*student);
        cout << "   "; request.printHeader();
    }
}

void Parse::processRemovalRequest(const Request &request){
    StudentClasses* student = findStudent(request.getStudent().getStudentCode()); // O(log p)
    Turma t = findSchedule(request.getDesiredUcClass())->getUcTurmas(); //O(log n)
    student->removeTurma(t);
    findSchedule(t)->removeStudent(*student); //O(log n + log n)
    cout << "   "; request.printHeader(); cout << endl;
    processedRequests.push(request);

}

void Parse::processEnrollmentRequest(const Request &request) {

    cout << "Processing" << endl;
    cout << request.getStudent().getTurmas().size() << endl;

    if(requestHasCollision(request)){ //O(n²logn)
        rejectedRequests.emplace(request, "Collision in the students' schedule");
    }
    else if(requestExceedsCap(request)){ //O(nlog n)
        rejectedRequests.emplace(request, "Exceeds maximum number of students allowed in the class. Choose another class");
    }
    else if(request.getStudent().getTurmas().size() >= 6){
        rejectedRequests.emplace(request, "Exceeds maximum number of enrolled UCs");
    }
    else{
        processedRequests.push(request);

        StudentClasses* student = findStudent(request.getStudent().getStudentCode()); //O(log p)
        Turma t = findSchedule(request.getDesiredUcClass())->getUcTurmas(); //O(log n)
        student->addTurma(t);
        findSchedule(t)->addStudent(*student); //O(log n + log q)
        cout << "   "; request.printHeader();
    }

    cout << " Done Processing" << endl;

    cout << endl;
}

void Parse::processRequests() {
    cout << ">> Accepted removal requests:" << endl;
    while(!removalRequests.empty()){
        Request request = removalRequests.front();
        removalRequests.pop();
        processRemovalRequest(request); // O(h) + O(log n + log n) + O(log p)
    }
    cout <<endl<< ">> Accepted changing requests:" << endl;
    while(!changingRequests.empty()){
        Request request = changingRequests.front();
        changingRequests.pop();
        processChangingRequest(request); //O(n²logn) + O(nlog n)
    }
    cout <<endl<< ">> Accepted enrollment requests:" << endl;
    while(!enrollmentRequests.empty()){
        Request request = enrollmentRequests.front();
        enrollmentRequests.pop();
        processEnrollmentRequest(request); //O(n²logn) + O(nlog n) + O(log p)
    }

    if(!rejectedRequests.empty()){
        cout << ">> Some Requests were rejected" << endl;
        writeRejectedRequest();
        printRejectedRequests();
        return;
    }else{
        cout <<endl<< ">> All Requests were accepted!" << endl;
    }
}

void Parse::writeFiles(){
    ofstream file;
    file.open("../docs/requests/accepted_requests.csv", ios::app);

    if (!file.is_open()) {
        cout << "Error opening file! Unable to save." << endl;
        return;
    }
    //cout << processedRequests.size() << endl;
    while(!processedRequests.empty()){
        auto request = processedRequests.top();

        auto student = request.getStudent();
        auto desiredUcClass = request.getDesiredUcClass();

        processedRequests.pop();

        // Write data in CSV format
        file << student.getStudentName() << "," << student.getStudentCode() << "," << request.getType() << ",";

        if (request.getType() == "Removal") {
            file << "," << desiredUcClass.getUcCode();
        } else {
            file << "," << desiredUcClass.getUcCode() << "," << desiredUcClass.getClassCode();
        }
        file << endl;
    }

    file.close();
}
void Parse::writeRejectedRequest(){
    ofstream file;
    file.open("../docs/requests/rejected_requests.csv", ios::app);

    while (!rejectedRequests.empty()) {
        auto p = rejectedRequests.front();
        auto student = p.first.getStudent();
        auto desiredUcClass = p.first.getDesiredUcClass();
        rejectedRequests.pop();

        // Write data in CSV format
        file << student.getStudentName() << ","
             << student.getStudentCode() << ","
             << p.first.getType() << ",";

        if (p.first.getType() == "Removal") {
            file << "Requested Uc: " << desiredUcClass.getUcCode();
        } else {
            file << "Requested class: " << desiredUcClass.getUcCode() << " - " << desiredUcClass.getClassCode();
        }

        file << "," << p.second << endl;
    }

    file.close();
}

void Parse::printPendingRequests() const {
    queue<Request> pendingRemovalRequests = removalRequests;
    cout << endl << ">> Removal requests (" << pendingRemovalRequests.size() << "):" << endl;
    while (!pendingRemovalRequests.empty()) { //O(v)
        cout << "   "; pendingRemovalRequests.front().printHeader();
        pendingRemovalRequests.pop();
    }
    queue<Request> pendingChangingRequests = changingRequests;
    cout << endl << ">> Changing requests (" << pendingChangingRequests.size() << "):" << endl;
    while (!pendingChangingRequests.empty()) { //O(w)
        cout << "   "; pendingChangingRequests.front().printHeader();
        pendingChangingRequests.pop();
    }
    queue<Request> pendingEnrollmentRequests = enrollmentRequests;
    cout << endl << ">> Enrollment requests (" << pendingEnrollmentRequests.size() << "):" << endl;
    while (!pendingEnrollmentRequests.empty()) { //O(z)
        cout << "   "; pendingEnrollmentRequests.front().printHeader();
        pendingEnrollmentRequests.pop();
    }
    cout << endl;
}

void Parse::printRejectedRequests() {

    ifstream file;
    file.open("../docs/requests/rejected_requests.csv");

    string line;
    getline(file, line); // Read and discard the header row
    while (getline(file, line)) {
        istringstream ss(line);
        string studentName, studentCode, type, requestedInfo, reason;

        // Parse the CSV line into individual fields
        getline(ss, studentName, ',');
        getline(ss, studentCode, ',');
        getline(ss, type, ',');
        getline(ss, requestedInfo, ',');
        getline(ss, reason);

        cout << studentName << " (" << studentCode << " ) [" << type << " ] " << requestedInfo << " Reason: "<< reason << endl;
    }
    cout << endl;
    file.close();
}

void Parse::printCourseStudents(const string& sortingType) const {
    system("clear");

    vector<StudentClasses> s(students.begin(), students.end());

    if(sortingType == "By name ascending")
        sort(s.begin(), s.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() < b.getStudentName();});

    else if(sortingType == "By name descending")
        sort(s.begin(), s.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() > b.getStudentName();});

    else if(sortingType == "By UPcode ascending")
        sort(s.begin(), s.end());
    else
        sort(s.rbegin(),s.rend());

    for(const auto& student : s){
        cout << student;
    }
}

void Parse::printStudentsByYear(const string& sortingType) const {
    system("clear");
    unsigned int year;
    cout << "Please insert the desired year: ";
    cin >> year;
    cout << endl;

    set<StudentClasses> st = Parse::getStudentsByYear(year);

    vector<StudentClasses> s(st.begin(), st.end());

    if(sortingType == "By name ascending")
        sort(s.begin(), s.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() < b.getStudentName();});

    else if(sortingType == "By name descending")
        sort(s.begin(), s.end(), [](const StudentClasses &a, const StudentClasses &b) { return a.getStudentName() > b.getStudentName();});

    else if(sortingType == "By UPcode ascending")
        sort(s.begin(), s.end());
    else
        sort(s.rbegin(),s.rend());

    for(const auto& student : s){
        cout << student;
    }

    cout << year << " year has " << "(" << s.size() << ")" << " students" << endl;
}

multiset<StudentClasses, studentByNUCS> Parse::getStudentsByNUCS() {
    multiset<StudentClasses, studentByNUCS> sortedByNUCS;
    for (const auto& student: students) {
        sortedByNUCS.insert(student);
    }
    return sortedByNUCS;
}

void Parse::sortTypeClasses(vector<Turma> &s, const string& sortingType) {

    if(sortingType == "By class name ascending")
        sort(s.begin(), s.end(), [](const Turma &a, const Turma &b) { return a.getClassCode() < b.getClassCode();});

    else if(sortingType == "By class name descending")
        sort(s.begin(), s.end(), [](const Turma &a, const Turma &b) { return a.getClassCode() > b.getClassCode();});

    else if(sortingType == "By UCcode ascending")
        sort(s.begin(), s.end(), [](const Turma &a, const Turma &b) { return a.getUcCode() < b.getUcCode();});
    else if(sortingType == "By UCcode descending")
        sort(s.begin(),s.end(), [](const Turma &a, const Turma &b) { return a.getUcCode() > b.getUcCode();});
    else if(sortingType == "By number of students ascending")
        sort(s.begin(),s.end(), [](const Turma &a, const Turma &b) { return a.getSize() > b.getSize();});
    else
        sort(s.begin(),s.end(), [](const Turma &a, const Turma &b) { return a.getSize() < b.getSize();});


    for(const auto& t : s){
        cout << "(" << t.getSize() << ") "<< t.getClassCode() << " | " << t.getUcCode() << endl;
    }
}

vector<pair<int, string>> Parse::getOcupationYear() const {
    vector<pair<int, string>> numberOFStudentByYear;

    int count1 = 0, count2 = 0, count3 = 0;

    for(const auto& student : students){
        if(student.getYear() == 1)
            count1++;
        else if(student.getYear() == 2)
            count2++;
        else
            count3++;
    }

    numberOFStudentByYear.emplace_back(count1, "1º Ano");
    numberOFStudentByYear.emplace_back(count2, "2º Ano");
    numberOFStudentByYear.emplace_back(count3, "3º Ano");

    return numberOFStudentByYear;
}


unordered_set<Turma, Turma::TurmaHash> Parse::getTurmasTable() const {
    return turmasTable;
}

void Parse::sortTypeUCs(vector<Turma> &s, const string& sortingType) {

    //accumulate each UCcode size into uniques, this way we have the number of students in each UC
    map<string, unsigned int> numberOfStudentsByUc;

    for(const Turma& t : s)
        numberOfStudentsByUc[t.getUcCode()] += t.getSize();

    vector<pair<string, unsigned int>> accumulated(numberOfStudentsByUc.begin(), numberOfStudentsByUc.end());

    if(sortingType == "By number of students ascending")
        sort(accumulated.begin(),accumulated.end(),
             [](const pair<string, unsigned int> &a, const pair<string, unsigned int> &b) { return a.second > b.second;});
    else
        sort(accumulated.begin(),accumulated.end(),
             [](const pair<string, unsigned int> &a, const pair<string, unsigned int> &b) { return a.second < b.second;});


    for(const auto &item : accumulated){
        string UC = item.first;
        unsigned int numberOfStudents = item.second;
        cout << "("<< numberOfStudents << ") " << UC << endl;
    }

    cout << "The UC with the most number of students is  " << accumulated[0].first << " with " << accumulated[0].second << " students" << endl << endl;
}


