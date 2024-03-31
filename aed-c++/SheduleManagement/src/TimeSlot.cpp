/**
 * @file TimeSlot.cpp
 * @brief Implementation of the TimeSlot class
 * @see TimeSlot.h
 * */
#include "../include/TimeSlot.h"

TimeSlot::TimeSlot(const string &week_day, const float &start_hour, const float &duration, const string &type) :
week_day_(week_day), start_hour_(start_hour), duration_(duration), type_(type){};

const string &TimeSlot::getWeekDay() const {
    return week_day_;
}

const float TimeSlot::getStartHour() const {
    return start_hour_;
}

const float TimeSlot:: getEndHour() const{
    return start_hour_ + duration_;
}

const string &TimeSlot::getType() const {
    return type_;
}

//TODO verificar se overlaps esta bem implementada
bool TimeSlot::overlaps(const TimeSlot &rhs) const {
    if(this->getWeekDay() != rhs.getWeekDay())
        return false;
    if(this->getStartHour() >= rhs.getEndHour() || this->getEndHour() <= rhs.getStartHour())
        return false;
    if(this->type_ == "T" || rhs.getType() == "T")
        return false;
    return true;
}

bool TimeSlot::operator!=(const TimeSlot &rhs) const {
    return this->getStartHour() != rhs.getStartHour();
}

bool TimeSlot::operator==(const TimeSlot &rhs) const {
    return this->getStartHour() == rhs.getStartHour() && this->getEndHour() == rhs.getEndHour();
}

bool TimeSlot::operator<(const TimeSlot &rhs) const {
    if(this->getWeekDay() != rhs.getWeekDay()) {
        map <string, int> days = {{"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
                                  {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6},
                                  {"Sunday", 7}};
        return days[week_day_] < days[rhs.getWeekDay()];
    }

    if(this->getStartHour() == rhs.getStartHour()){
        if(this->getEndHour() == rhs.getEndHour()){
            return this->getType() < rhs.getType();
        }
        return this->getEndHour() < rhs.getEndHour();
    }
    return this->getStartHour() < rhs.getStartHour();
}

ostream &operator<<(ostream &os, const TimeSlot &Timeslot) {
    return os << Timeslot.getWeekDay() << ";" << std::endl
              << Timeslot.getStartHour() << ";" << std::endl
              << Timeslot.getEndHour() << ";" << std::endl
              << Timeslot.getType() << "." << std::endl;
}

