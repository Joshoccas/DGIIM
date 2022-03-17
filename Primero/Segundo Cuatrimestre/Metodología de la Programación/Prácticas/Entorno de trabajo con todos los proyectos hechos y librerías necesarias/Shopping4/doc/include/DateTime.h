/**
 * @file DateTime.h
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 * 
 */

#ifndef DATETIME_H
#define DATETIME_H


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
     * @brief Constructor with arguments. If the string is a valid date and time, it is sets, 
     * otherwise it sets to the default DateTime
     * @param date The striing containig the date and time
     */
    DateTime(const std::string & date);
    /**
     * @brief It gives the year
     * @return The year of the date as an integer value
     */
    int year() const;
    /**
     * @brief It gives the month
     * @return The month of the date within its valid bounds
     */
    int month() const;
    /**
     * @brief It gives the day
     * @return The day of the date within its valid bounds
     */
    int day() const;
    /**
     * @brief It gives the hour
     * @return  The hour of the date within its valid bounds
     */
    int hour() const;
    /**
     * @brief It gives the minutes
     * @return The number of minutes of the date within its valid bounds
     */
    int min() const;
    /**
     * @brief It gives the number of seconds
     * @return The seconds of the date within its valid bounds
     */
    int sec() const;
    /**
     * @brief set the dataTime if is correct, as well as in date, as in time
     * @param date is the string given from the csv format  2019-10-01 00:15:06 UTC
     * @warning The tail " UTC" must be ignored 
     */
    void set(const std::string & line);
    /**
     * @author DECSAI
     * @brief transform a dataTime to a string following the format: 2019-10-01 00:15:06 UTC
     * @return string that contains dataTime and including the tailing UTC
     */
    std::string to_string() const;
    /**
     * @brief check if the referenced object is before in time than the dataTime one
     * @param one a dataTime to compare with
     * @return true when the DateTime string of this object is lexycographically before 
     * that the one given as argument
     */
    bool isBefore(const DateTime &one) const;
    
    /**
     * @brief Check if the referenced object and the argument belong to the same day
     * @param other DateTime to compare with
     * @return true if both DateTimes are from the same day, false otherwise
     */
    bool sameDay(const DateTime &other) const;

    /**
     * @brief Computes the week day, from date of the dataTime. According to the Zeller's congruence
     * look at wikipedia https://en.wikipedia.org/wiki/Zeller%27s_congruence
     * @return values in the range 0..6, where 0 is sunday
     */
    int weekDay() const;
};


#endif /* DATETIME_H */
