/**
 * @file Event.h
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 * 
 */

#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "DateTime.h"

/// Value assigned to any field which is found empty in the data
const char EMPTY_FIELD[] = "00000000"; 
/// A constant that defines an EMPTY event
const std::string EVENT_DEFAULT = (((std::string)"1971-01-01 00:00:00 UTC,view,")+EMPTY_FIELD+",,,,-1.000000,"+ EMPTY_FIELD+ ","+ EMPTY_FIELD);
/// The set  of valid types. The default time is the first one
const std::string VALID_TYPES[] = {"view","cart","purchase","remove_from_cart"};

/**
 *  @class Event 
 * 
 * @brief It stores every logged event of a web marketplace as it appears in
 * https://www.kaggle.com/mkechinov/ecommerce-events-history-in-cosmetics-shop
 * It contains the following fields
 *   - datetime is the time stamp of the record
 *   - type: One f these operations view, cart, remove_from_cart, purchase
 *   - prod_id: Product code. It is an integer value represented as a string, that is,
 * like "0020". It cannot be null, so if its read is "", then it must be filled with the
 * EMTPY_FIELD constant
 *   - cat_cod: The code of the category of the product involved in the event
 *   - brand: The name of the brand
 *   - price: the price of the product expressed as a double value
 *   - user_id: A code of the user that performs the operation. I cannot be a null value
 *   - session: Id of the browser session in which the event took place
 * 
 * When these fields appear in a text row, it  must appear in this order, separated by charcter ','
 * and taking into account that some fields might be null, that is, an empty string ""
 * datetime , type , prod_id , cat-cod , brand , price, user_id, session
 */
class Event {
private:
    DateTime _dateTime;
    std::string _type;
    std::string _prod_id; // NOTNULL
    std::string _cat_id;
    std::string _cat_cod;
    std::string _brand;
    double _price;
    std::string _user_id; //NOTNULL
    std::string _session; //NOTNULL
    // void split( std::string  l, std::string  date, std::string  time);
    void initDefault(); 
public:
    /**
     * @brief Constructor without parameters, set to default values 
     */
    Event();
    /**
     * @brief Given the full text of a line, it initializes the object with
     * the data contained in that line. If the data is not valid in any sense,
     * then the event is declared empty. More details in the PDF of the practice
     * @param line, an event in CSV format (coma as separator)
     */
    Event(const std::string  &line);
    
    /**
     * @brief It gives the date of the event
     * @return The date as a valid object
     */
    DateTime getDateTime() const;
    /**
     * @brief It gives the type of the event
     * @return A string that contains the type
     */
    std::string getType() const;
    /**
     * @brief It gives the Product ID of the event
     * @return A string that contains the Product ID
     */
    std::string getProductID() const;
    /**
     * @brief It gives the Category ID of the event
     * @return A string that contains the Category ID
     */
    std::string getCategoryID() const;
    /**
     * @brief It gives the Category Code of the event
     * @return A string that contains the Category Code
     */    
    std::string getCategoryCode() const;
    /**
     * @brief It gives the Brand of the event
     * @return A string that contains the Brand
     */
    std::string getBrand() const;
    /**
     * @brief It gives the Price of the event
     * @return A double
     */
    double getPrice() const;
    /**
     * @brief It gives the User ID of the event
     * @return A string that contains the User ID
     */
    std::string getUserID() const;
    /**
     * @brief It gives the Session of the event
     * @return A string that contains the Session
     */    
    std::string getSession() const;

    /**
     * @brief Sets the date and time of the event
     * @param Datetime in the format specified in @ref DateTime
     */
    void setDateTime(const std::string  &Datetime);
    /**
     * @brief Sets the type of the event among the valid types in \ref VALID_TYPES if it is not,
     * then it assumes a default value of VALID_TYPES[0]
     * @param type
     */
    void setType(const std::string  &type);
    /**
     * @brief It sets the Product ID of the event. If the value provided is the 
     * empty string "", it is set to \ref  EMPTY_FIELD
     * @param prod_id
     */
    void setProductID(const std::string  &prod_id);
    /**
     * @brief It sets the Category ID of the event. Empty strings "" are allowed
     * @param cat_id
     */
    void setCategoryID(const std::string  &cat_id);
    /**
     * @brief It sets the Category Code of the event. Empty strings "" are allowed
     * @param cat_cod
     */
    void setCategoryCode(const std::string  &cat_cod);
    /**
     * @brief It sets the Brand of the event. Empty strings "" are allowed
     * @param brand
     */
    void setBrand(const std::string  &brand);
    /**
     * @brief It sets the price
     * @param price
     * @precond 0 <= price
     */
    void setPrice(double price);
    /**
     * @brief It sets the User ID of the event. If the value provided is the 
     * empty string "", it is set to \ref  EMPTY_FIELD

     * @param user_id
     */
    void setUserID(const std::string  &user_id);
    /**
     * @brief It sets the Session of the event. If the value provided is the 
     * empty string "", it is set to \ref  EMPTY_FIELD
     * @param session
     */
    void setSession(const std::string  &session);
    /**
     * @brief It sets all the data members from a line that describe the event
     * @param line
     */
    void setEvent(const std::string  &line);
    /**
     * @brief verifies if the object is considered empty, when some of the fields are set to the default values
     * @return bool true if the event is considered empty, false otherwise
     */
    bool isEmpty() const;
    /**
     * @brief transform an event to a string, using separator
     * @return string that contains the event in CSV format
     */
    std::string to_string() const ;

    std::string reportData()  const {
        return to_string();
    }
};


#endif /* EVENT_H */