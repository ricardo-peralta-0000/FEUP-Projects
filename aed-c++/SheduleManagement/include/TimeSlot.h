#ifndef AED2324_PRJ1_G15_TIMESLOT_H
#define AED2324_PRJ1_G15_TIMESLOT_H

/**
 * @file TimeSlot.h
 * @brief Header file for the TimeSlot class
 * @details This file contains the declaration of the TimeSlot class
 * */
#include <iostream>
#include <map>
#include "Turma.h"

/**
 * @class TimeSlot
 * @brief Represents a specific time slot for a class
 * */
class TimeSlot {
public:
    /**
     * @brief Constructor for the TimeSlot class
     * @param week_day Week day of the class
     * @param start_hour Start hour of the class
     * @param duration Duration of the class
     * @param type Type of the class
     * */
    TimeSlot(const std::string &week_day, const float &start_hour, const float &duration, const std::string &type);

    /**
     * @brief Getter for the week day
     * @return Week day of the class as a string
     * */
    const string &getWeekDay() const;

    /**
     * @brief Getter for the type of class
     * @return Type of the class as a string
     * */
    const string &getType() const;

    /**
     * @brief Getter for the start hour
     * @return Start hour of the class
     * */
    const float getStartHour() const;

    /**
     * @brief Getter for the ending hour of the timeslot
     * @return End hour of the class
     * */
    const float getEndHour() const;

    /**
     * @brief Checks if the timeslot overlaps with another timeslot
     * This method checks if this time slot overlaps with another time
     * slot based on their day of the week and time.
     * @param rhs Timeslot to compare with
     * @return True if the timeslots overleap, false otherwise
     * */
    bool overlaps(const TimeSlot &rhs) const;

    /**
     * @brief Overload of the inequality (!=) operator
     * @param rhs The right-hand side time slot to compare with
     * @return True if the timeslots are different, false otherwise
     * */
    bool operator!=(const TimeSlot &rhs) const;

    /**
     * @brief Overload of the equality (==) operator
     * @param rhs The right-hand side time slot to compare with
     * @return True if the timeslots are equal, false otherwise
     * */
    bool operator==(const TimeSlot &rhs) const;

    /**
     * @brief Overload of the less than (<) operator
     * This operator compares time slots first by
     * the day of the week, then by the starting hour,
     * and finally by the type.
     * @param rhs The right-hand side time slot to compare with
     * @return True if the left-hand side time slot is less than the right-hand side time slot, false otherwise
     * */
    bool operator<(const TimeSlot &rhs) const;

    /**
     * @brief Overload of the stream insertion (<<) operator to display a TimeSlot
     * @param os The output stream
     * @param Timeslot The TimeSlot object instantiation to display
     * @return The output stream
     * */
    friend ostream &operator<<(ostream &os, const TimeSlot &Timeslot);
private:
    string week_day_; /**< Represents the day of the week when the class takes place. */
    float start_hour_; /**< Represents the starting hour of the class. */
    float duration_; /**< Represents the duration of the class in hours. */
    string type_; /**< Represents the type of class. */
};

#endif //AED2324_PRJ1_G15_TIMESLOT_H