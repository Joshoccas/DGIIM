/**
 * @file EventSet.h
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 * 
 */

#ifndef EVENTSET_H
#define EVENTSET_H

#include "DateTime.h"
#include "Event.h"

#define MAXEVENT  500

class EventSet {
private:
    Event _events[MAXEVENT]; // Set of events load correcty
    int _nEvents; // Number of available event
public:
    /**
     * @brief Basic constructor. All the attributes are initialized to its default 
     * value
     */
    EventSet();
    /**
     * @brief Returns the number of events stored.
     * @return The number of events
     */
    int size() const;
    /**
     * @brief transform an eventSet to a string, 
     * @return string that contains the number of components and en eventSEt serialized
     * 
     * @todo in order to define this function we suggest the use of (+) for string and the function to_string(int d) 
     */
    std::string to_string() const;
    /**
     * @brief Resets the set of events to 0 components 
     */
    void clear();
    /**
     * @brief Adds a new event at the end of the eventSet whenever there is some room.
     * @param e an Event
     * @return 1 when the operation has been successful, 0 when it fails
     * 
     */
    int add(const Event & e);
    /**
     * @brief  Adds a new event at the end of the eventSet whenever there is some room.
     * @param line the input string from which to form the Event
     * @return 1 when the operation as been successful, 0 otherwise
     */
    int add(const std::string& line);

    /**
     * @brief get the event in a position selected, for consulting
     * @param pos, position in the EventSet
     * @return the selected event in the EventSet
     * @warning If pos is not a valid value, it returns an EMPTY Event, that is
     * ane event whose isEmpty() method returns true.
     * the program
     */
    const Event & at(int pos) const;

    /**
     * @brief Shows the number of events in the EventSet and a numeric 
     * value that encodes the whole set of events
     * @return A string made up of the size of the EventSet and the
     * numeric code of its content
     * @warning please do not modify its implementation
     */
    std::string reportData() const {
        std::string result = "";
        for (int i = 0; i < _nEvents; i++) {
            result += std::to_string(std::hash<std::string>{}(_events[i].to_string()));
        }
        result = std::to_string(std::hash<std::string>{}(result));
        result = std::to_string(_nEvents) + " " + result;
        return result;
    }

    /**
     * @brief Writes the EventSet in an output stream in CSV format.
     * @param os output file stream
     */
    void write(std::ofstream &os) const;

    /**
     * @brief Reads the EventSet from an input stream
     * @param is input file stream
     * @param nelements number of elements to be read
     * @return bool True if the reading operation has been successful, false 
     * otherwise
     */
    bool read(std::ifstream &is, int nelements);
    
};

/**
 * @brief It Computes the total sum for price, on the complete EventSet
 * @return the total computed
 */
float sumPrice(const EventSet & evSet);
/**
 * @brief It explores all the EventSet and builds a string[] composed of all different
 * values taken by the field @a field
 * @param field The field of the event
 * @param values Array of values (as string) which is made up of all different values of the
 * field @a field
 * @param n_values Number of different values found
 */
void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values);
/**
 * @brief Extract a subset of the EventSet composed only of those events in which
 * the given @a field matches the given @a value
 * @param field     The name of the field of the event. According to @see Event.h
 * @param value     The value of the field that will be used to partition the EventSet
 * @return An EventSet which is a subset of the current one in which all events
 * have @a field == @a value
 * @deprecated
 */
EventSet rawFilterEvents(const EventSet& es, const std::string &field, const std::string &value);

extern Event NULL_EVENT; /// It defines an EMPTY Event which can be used to identify error cases

#endif /* EVENTSET_H */

