/* 
 * File:   Pair.h
 * @author MP-Team DECSAI
 * @warning To be revised by the students. Do not change the number of parameters 
 * only the way they are passing (const & ...)
 */

#ifndef PAIR_H
#define PAIR_H

#include "Event.h"

class Pair {

private:
    std::string _key;  // key search
    int _pos;          // a position in an array

public:

    /**
     * @brief default constructor 
     */
    Pair();

    /**
     * @brief Constructor with parameters
     * @param key value to be set 
     * @param int, position is set whenever is known, otherwise set to -1
     */
    
    Pair(const std::string & key, int pos = -1);

    /**
     * @brief It detect invalid pairs
     * @return It returns true when the pair contains EMPTY_FIELD and -1, and returns false otherwise 
     */
    bool isEmpty() const;
    
    /**
     * @brief Get the key value from the Pair.
     * @return A reference to the string representing the key
     */
    const std::string & getKey() const;

    /**
     * @brief Get the position value from the Pair.
     * @return  int, a position in an array  
     */
    const int getPos() const;
 
    /**
     * @brief Set a key value for a Pair. Check the validity of the key
     * @param string to be assigned 
     */
    void setKey(const std::string & key);

    /**
     * @brief Set a value for entry in the Pair. Check the validity of the position
     * @param int, the position to be set
     */
    void setPos(int pos);

    /**
     * @brief Set the key and position values for a Pair. Check for the validity 
     * of the new values 
     * @param string to be assigned
     * @param int, the position to be set
     */
    void set(const std::string & key, int pos);

    /**
     * @brief Convert the content in a string
     * @return string in format key space position
     */
    std::string to_string() const; /** es util para la depuracion? PERO necessary ?*/

    /**
     * @brief Set a Pair to the default values, key to the default value given in an 
     * Event, and pos to a unknown position (-1) called by the default constructor 
     * and set when overruled integrity restriction.
     */
    void initDefault(); /// called by constructor && and set overruling restriction

    /**
     * @brief Sereializes the class and encodes it
     * @return 
     */
    std::string reportData() const {
        std::string result = "";
        result = std::to_string(std::hash<std::string>{}(to_string()));
        return result;
    }
    
};

extern Pair NULL_PAIR;
/**
 * @brief check if two pair objects have the same key
 * @param left Pair
 * @param right Pair 
 * @return true when they are equal, false otherwise
 */
bool equalKey(const Pair & left ,const Pair & right);

#endif /* PAIR_H */

