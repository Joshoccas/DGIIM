/* 
 * File:   Index.h
 * @author MP-Team DECSAI
 * @warning To be revised by the students. Do not change the number of parameters 
 * only the way they are passing (const & ...)
 */

#ifndef INDEX_H
#define INDEX_H

#include "Pair.h"
#include "Event.h"
#include "EventSet.h"

class Index {
private:
    Pair *_entries; // array of Pair
    int _nEntries; // Number of active entries
    int _onBrand; //  1 on Brand 0 on UserID (bool for 2 indexes o int for more indexes)
    int _capacity;

    /**
     * @brief Set on which field is mounted the index( 1 Brand, 0 userID). Set at the build moment
     */
    void setIOnWhich(int val);
    
    void allocate(unsigned size); 
    void reallocate(unsigned size);  
    void deallocate();
    void copy(const Index &orig);
    
public:

    /**
     * @brief Default constructor. Initializes parameters to default values
     */
    Index();

    /**
     * @brief Constructor defining the type of index to be created. Depending on
     * the type, the values of the pairs will be set using users or brands
     * @param type Type of the index
     *  - Value 0 indicates an index over the users
     *  - Value 1 indicates an index over the brands
     */
    Index(int onBrand); // UsersIndex onBrand=0  o BrandType onBrand=1, defaults to 0

    /**
     * @brief Gets the size of the index
     * @return int representing the size of the index
     */
    int size() const;
    
    /**
     * @brief Detects whether an index is empty or not
     * @return true if the index has no elements, false otherwise
     */
    inline bool isEmpty() {  return size()==0; }

    /**
     * @brief Build the index using the Brand o the userID as searching key according to the onBrand value.
     * @param evSet origin
     * @param onBrand if 1 then build an index by brand, otherwise by User
     */
    void build(const EventSet & evSet, int onBrand);

    /**
     * @brief Informs on which field is mounted the index, 1 Brand 0 userID
     * @return the number 0,1
     */
    int getIOnWhich() const;

    /**
     * @brief get the Pair in a position selected, for consulting
     * @param pos, position in the Index
     * @return the selected Pair in the Index
     */
    const Pair & at(int pos) const;

    /**
     * @brief Clears the index, setting the number of entries to 0
     */
    void clear();

    /**
     * @brief get the Pair in a position selected, for modification
     * @param pos, position in the Index
     * @return the selected Pair in the Index
     */
    Pair & at(int pos);



    /**
     * @brief Returns the position to the first element in the Index
     * which is not considered to go before key (i.e., either it is the first 
     * element equal to the key or it is strictly bigger), look at the example.
     * @param key the searching key a string
     * example: // 10 20 30 30 40 50 60 70
     * low_bound(30) ....^
     * low_bound(35) ..........^
     * @return a position in the Index
     */
    int lower_bound(const std::string & key) const;

    /**
     * @brief Returns the position to the first element in the Index which is 
     * considered to go after the key
     * look at the example.
     * example: // 10 20 30 30 40 50 60 70
     * upper_bound(30) ........^
     * upper_bound(35) ........^
     * @param key String representing the searching key
     * @return a position in the Index
     */
    int upper_bound(const std::string & key) const;

    /**
     * @brief Inserts a new entry in the index, in a way that the index remains in ascending 
     * order of searching key. 
     * procedure: use the method upper_bound (see  description) that provides 
     * the exact position where to insert. Once the position is found, the 
     * method has to make room by moving all the posterior records one position 
     * in the index
     * @param an entry in the index. The name has to be correct
     * @return 1 when insertion is successful, 0 if it fails
     * 
     */
    int add(const Pair & pair);

    /**
     * @brief Displays the information about the Index on screen
     */
    void print()const;

    std::string to_string() const {
        std::string res = "";
        Pair local;
        res += ": On brand? " + std::to_string(_onBrand);
        for (int i = 0; i < _nEntries; i++) {
            local = at(i);
            res += "\n: " + local.to_string();
        }
        return res;
    }

    std::string reportData() const {
        std::string result = "";
        for (int i = 0; i < _nEntries; i++) {
            result += _entries[i].to_string();
        }
        result = std::to_string(std::hash<std::string>{}
        (result));
        result = std::to_string(_nEntries) + " " + result;
        return result;
    }

    Index(const Index &orig);
    ~Index();
    Index & operator=(const Index & one);

};
#endif /* INDEX_H */

// external functions

/**
 * @brief Extracts a subset of the introduced Index, those composed only of the events in which
 * the given @a field matches the given @a value
 * @param evSet EventSet where to recover the events in order to check the field values.
 * @param indx  Index through which the events are covered efficiently, the search is reduced. 
 * @param field     The name of the field of the event. According to @see Event.h
 * @param value     The value of the field that will be used to partition the EventSet
 * @return An EventSet which is a subset of the current one in which all events
 * have @a field == @a value
 */

Index rawFilterIndex(const EventSet & evSet, const Index & indx, const std::string &field, const std::string &value);

/**
 * @brief Retrieve an event pointed by the pos position in the index
 * @param evSet EventSet from which to recover it
 * 
 * @param pos int, entry number in the index
 * @return 
 */
/**
 * 
 * @param evSet
 * @param pos
 * @return 
 */
Event getEvent(const EventSet & evSet, const Index & indx, int pos);

/**
 * @brief Writes the events pointed by the pos position in the index into the stream 
 * in CSV format.
 * @param os output file stream
 * @param evSet EventSet from which to recover them
 * @param indx, the index to go through
 */

void write(std::ofstream &os, const EventSet & evSet, const Index & indx);

/**
 * @brief It Computes the total sum for price, on the events selected by the complete index 
 * @param evSet EventSet from which to recover them
 * @param indx, the index to go through
 * @return the total computed
 */
float sumPrice(const EventSet & evSet, const Index & indx);