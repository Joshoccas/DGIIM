# TESTS REPORT OF PROJECT shopping1

This is the list of tests of the project
 
| ID | NAME | DESCRIPTION |
| :----- |:------ | :---- |
| 1::1 | _01_Basics.DateTime_Constructors | A newly create instance of DateTime gives the default date
| 1::2 | _01_Basics.DateTime_Constructors | A newly created instance of DateTime by using a string gives the same string
| 2::1 | _01_Basics.DateTime_getters | The year of the default datetime must be 1971
| 2::2 | _01_Basics.DateTime_getters | The month of the default datetime must be 1
| 2::3 | _01_Basics.DateTime_getters | The day of the default datetime must be 1
| 2::4 | _01_Basics.DateTime_getters | The hour of the default datetime must be 0
| 2::5 | _01_Basics.DateTime_getters | The minutes of the default datetime must be 0
| 2::6 | _01_Basics.DateTime_getters | The seconds of the default datetime must be 0
| 3::1 | _01_Basics.DateTime_set | Setting an instance of DateTime with a valid string gives the same date
| 4::1 | _01_Basics.Event_ConstructorBase | A newly created instance of Event gives the default event
| 4::2 | _01_Basics.Event_ConstructorBase | A newly create instance of Event, initializaed with a string. gives the same string
| 5::1 | _01_Basics.Event_Setters_getters | Setting the datetime of an event to TODAY gives TODAY
| 5::2 | _01_Basics.Event_Setters_getters | Setting the type of an event to a good value X gives X
| 5::3 | _01_Basics.Event_Setters_getters | Setting the productid of an event to a good value X gives X
| 5::4 | _01_Basics.Event_Setters_getters | Setting the categoryID of an event to a good value X gives X
| 5::5 | _01_Basics.Event_Setters_getters | Setting the category code of an event to a good value X gives X
| 5::6 | _01_Basics.Event_Setters_getters | Setting the brand of an event to a good value X gives X
| 5::7 | _01_Basics.Event_Setters_getters | Setting the price of an event to a good value X gives X
| 6::1 | _01_Basics.Integration_ECommerce5 | Simple test with five (5) records only
| 7::1 | _01_Basics.Integration_EMPTY | Simple tet with an empty set of records
| 8::1 | _01_Basics.Integration_ECommerce49 | Test with 49 records
| 9::1 | _01_Basics.Integration_ECommerce_2019_Q4_200 | Test with 200 records of 2019-Q4
| 10::1 | _01_Basics.Integration_ECommerce_all_all_200 | Test with 200 records amongst all available years
| 11::1 | _02_Intermediate.DateTime_isBefore | A DateTime cannot be before itself
| 11::2 | _02_Intermediate.DateTime_isBefore | Default date is before  today
| 11::3 | _02_Intermediate.DateTime_isBefore | Today is not before the  Default date
| 12::1 | _02_Intermediate.DateTime_weekDay | Today must be Thursday
| 12::2 | _02_Intermediate.DateTime_weekDay | Tomorrow is Friday
| 12::3 | _02_Intermediate.DateTime_weekDay | Yesterday was Wednesday
| 13::1 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 13::2 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 13::3 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 13::4 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 13::5 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 13::6 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 13::7 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 13::8 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 13::9 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 13::10 | _03_Advanced.DateTime_BadValues | Setting a date with the incorrect format throws an exception
| 14::1 | _03_Advanced.Event_setType_Bad_Values | Setting the type of an event to a good value X gives X
| 14::2 | _03_Advanced.Event_setType_Bad_Values | Setting the type of an event to a good value X gives X
| 15::1 | _03_Advanced.Event_Others_Bad_Values | Setting the productid of an event to a good value X gives X
| 15::2 | _03_Advanced.Event_Others_Bad_Values | Setting the productid of an event to a good value X gives X
| 15::3 | _03_Advanced.Event_Others_Bad_Values | Setting the productid of an event to a good value X gives X
