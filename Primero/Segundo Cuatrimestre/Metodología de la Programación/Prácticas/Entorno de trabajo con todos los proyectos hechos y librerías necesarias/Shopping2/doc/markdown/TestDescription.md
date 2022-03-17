# TESTS REPORT OF PROJECT shopping2

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
| 6::1 | _01_Basics.EventSet_Constructor |  A newly created instance of EventSet must have size = 0
| 6::2 | _01_Basics.EventSet_Constructor |  A newly created instance of EventSet must ha a to_string empty '0'
| 7::1 | _01_Basics.EventSet_add_event |  Adding an event to a newly created instance of EventSet must have size = 1
| 7::2 | _01_Basics.EventSet_add_event | Adding the default event to an empty event set must have a to_string equal to the default event
| 7::3 | _01_Basics.EventSet_add_event |  Adding 1 event to a filled EventSet increases its size in 1
| 8::1 | _01_Basics.EventSet_add_line |  Adding a line to a newly created instance of EventSet must have size = 1
| 8::2 | _01_Basics.EventSet_add_line | Adding the default event, as a line, to an empty event set must have a to_string equal to the default event
| 8::3 | _01_Basics.EventSet_add_line |  Adding 1 event, as a line, to a filled EventSet increases its size in 1
| 9::1 | _01_Basics.EventSet_at_basic | Querying the event at the 0 position should match with the first event added to the EventSet
| 9::2 | _01_Basics.EventSet_at_basic | Querying the event at the middle position should match with the event added which was added at that point
| 10::1 | _01_Basics.Integrated_5_records | Simple test with five records only and no purchase
| 11::1 | _01_Basics.Integrated_49_records | Simple test with 49 records only with 6 purchases
| 12::1 | _01_Basics.Integrated_200_records | Simple test with 200 records and 10 purchases
| 13::1 | _01_Basics.Integrated_500_records | Simple test with 500 records and 30 purchases
| 14::1 | _01_Basics.Integrated_300_records | Simple test with 300 records and 300 purchases
| 15::1 | _02_Intermediate.DateTime_isBefore | A DateTime cannot be before itself
| 15::2 | _02_Intermediate.DateTime_isBefore | Default date is before  today
| 15::3 | _02_Intermediate.DateTime_isBefore | Today is not before the  Default date
| 16::1 | _02_Intermediate.DateTime_weekDay | Today must be Thursday
| 16::2 | _02_Intermediate.DateTime_weekDay | Tomorrow is Friday
| 16::3 | _02_Intermediate.DateTime_weekDay | Yesterday was Wednesday
| 17::1 | _02_Intermediate.Event_getField | getField("DateTime") on any Event, must be equal to getDateTime()
| 17::2 | _02_Intermediate.Event_getField | In any row, querying the Event for field "Price" will produce the same string than getDateTime
| 17::3 | _02_Intermediate.Event_getField | In any case, querying the Event for field "UserID" will produce the same string than the former getUserID()
| 17::4 | _02_Intermediate.Event_getField | In any row, querying the EventS a mandatory field cannot give an empty string
| 17::5 | _02_Intermediate.Event_getField | In any row, querying  an optional field will produce the same string than the former event added to the EvenSet
| 18::1 | _02_Intermediate.EventSet_add_event_partial |  Adding MAXEVENT events to a newly created EventSet increases its size in MAXEVENT
| 19::1 | _02_Intermediate.EventSet_at_intermediate | Querying the event at the last position should match with the last event added to the EventSet
| 19::2 | _02_Intermediate.EventSet_at_intermediate | Accessing EventSet at() a certain position and changing the user ID of the event, this change will remain in the EventSet itself
| 19::3 | _02_Intermediate.EventSet_at_intermediate | Accessing EventSet at() a certain position and changing the brand of the event, this change will remain in the EventSet itself
| 20::1 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 20::2 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 20::3 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 20::4 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 20::5 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 20::6 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 20::7 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 20::8 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 20::9 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 20::10 | _03_Advanced.DateTime_BadValues | Setting a date with the incorrect format throws an exception
| 21::1 | _03_Advanced.Event_setType_Bad_Values | Setting the type of an event to a good value X gives X
| 21::2 | _03_Advanced.Event_setType_Bad_Values | Setting the type of an event to a good value X gives X
| 22::1 | _03_Advanced.Event_Others_Bad_Values | Setting the productid of an event to a good value X gives X
| 22::2 | _03_Advanced.Event_Others_Bad_Values | Setting the productid of an event to a good value X gives X
| 22::3 | _03_Advanced.Event_Others_Bad_Values | Setting the productid of an event to a good value X gives X
| 23::1 | _03_Advanced.EventSet_add_event_full |  Adding one single Event events to a partly filled EventSet must return 1
| 23::2 | _03_Advanced.EventSet_add_event_full |  Adding one single Event events to a completely filled EventSet does not produce any change in the EventSet
| 23::3 | _03_Advanced.EventSet_add_event_full |  Adding one single Event events to a completely filled EventSet must return 0
| 24::1 | _03_Advanced.EventSet_at_advanced | Querying an EventSet beyond its legal limits gives an EMPTY event
| 24::2 | _03_Advanced.EventSet_at_advanced | Querying an EventSet beyond its legal limits gives an EMPTY event
| 24::3 | _03_Advanced.EventSet_at_advanced | Querying an EventSet within its legal limits always gives a NON-EMPTY event
| 25::1 | _03_Advanced.EventSet_externalfunctions | sumPrice must give the sum of all prices of a given EventSet, and it doesnt 
| 25::2 | _03_Advanced.EventSet_externalfunctions | UniqueBrands() must give the number of different brands, but it doesnt 
| 25::3 | _03_Advanced.EventSet_externalfunctions | UniqueUsers() must give the number of different users, but it doesnt 
