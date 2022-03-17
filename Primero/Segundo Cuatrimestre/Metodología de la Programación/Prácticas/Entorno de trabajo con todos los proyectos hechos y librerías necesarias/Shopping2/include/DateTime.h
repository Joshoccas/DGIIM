/**
 * @file DateTime.h
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 * 
 */

#ifndef DATETIME_H
#define DATETIME_H

#include <string>

/// Array of day names
const char * const DAYNAME [] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};

/// Default date
#define DATETIME_DEFAULT "1971-01-01 00:00:00 UTC"

/** 
 * @class DateTime 
 * @brief Used to represent dates and times in 
 * the format YYYY-MM-dd hh:mm::ss, where
 * 
 * ~~~~
 *      YYYY-MM-dd hh:mm:ss UTC 
 *      +----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 * 
 *    - YYYY Year    Any value allowed
 *    - MM Month    values in [1, 12]
 *    - dd day      values depending on the calendar
 *    - hh hour     values in [0,23]
 *    - mm minute   values in [0,59]
 *    - ss seconds  values in [0, 59]
 */
class DateTime {
    int _year;
    int _month;
    int _day;
    int _hour;
    int _min;
    int _sec;
    
    void initDefault();


public:
    /**
     * @brief Base constructor. It sets the default date
     */
    DateTime();
    /**
     * @brief Constructor with arguments. If the string is a valid date and time, 
     * it is set, otherwise it sets to the default DateTime
     * @param date The string containing the date and time
     */
    DateTime(const std::string  &date);
    /**
     * @brief It gives the year
     * @return The year of the date as an integer value
     */
    int year() const ;
    /**
     * @brief It gives the month
     * @return The month of the date within its valid bounds
     */
    int month() const ;
    /**
     * @brief It gives the day
     * @return The day of the date within its valid bounds
     */
    int day() const ;
    /**
     * @brief It gives the hour
     * @return  The hour of the date within its valid bounds
     */
    int hour() const ;
    /**
     * @brief It gives the minutes
     * @return The number of minutes of the date within its valid bounds
     */
    int min() const ;
    /**
     * @brief It gives the number of seconds
     * @return The seconds of the date within its valid bounds
     */
    int sec() const ;
    /**
     * @brief Sets the dataTime if the string is correct, otherwise sets to 
     * the default value
     * @param date String given from the CSV format: 2019-10-01 00:15:06 UTC
     * @warning The tail " UTC" must be ignored 
     */
    void set(const std::string  &line);
    /**
     * @author DECSAI
     * @brief transform a dataTime to a string in the following 
     * format: 2019-10-01 00:15:06 UTC
     * @return string that contains dataTime, including the tailing UTC
     */
    std::string to_string() const ;
    /**
     * @brief check if the referenced object is before in time than the 
     * dataTime @p one
     * @param one DataTime to compare with
     * @return true when the DateTime string of this object is lexicographically 
     * before that the one given as argument
     */
    bool isBefore(const DateTime &one) const ;
    /**
     * @brief Computes the week day, from date of the dataTime. According to the Zeller's 
     * congruence given in wikipedia https://en.wikipedia.org/wiki/Zeller%27s_congruence
     * @return values in the range 0..6, where 0 is Sunday
     */
    int weekDay() const ;
};


#endif /* DATETIME_H */
