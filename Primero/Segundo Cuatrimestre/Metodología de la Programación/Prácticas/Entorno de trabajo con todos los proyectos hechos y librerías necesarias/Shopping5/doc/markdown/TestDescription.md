# TESTS REPORT OF PROJECT shopping3

This is the list of tests of the project
 
| ID | NAME | DESCRIPTION |
| :----- |:------ | :---- |
| 1::1 | _01_Basics.DateTime_Constructors | A newly create instance of DateTime gives the default date
| 1::2 | _01_Basics.DateTime_Constructors | A newly created instance of DateTime by using a string gives the same string
| 2::1 | _01_Basics.DateTime_getters | The year of the default datetime must be 2021
| 2::2 | _01_Basics.DateTime_getters | The month of the default datetime must be 1
| 2::3 | _01_Basics.DateTime_getters | The day of the default datetime must be 1
| 2::4 | _01_Basics.DateTime_getters | The hour of the default datetime must be 0
| 2::5 | _01_Basics.DateTime_getters | The minutes of the default datetime must be 0
| 2::6 | _01_Basics.DateTime_getters | The seconds of the default datetime must be 0
| 3::1 | _01_Basics.DateTime_set | Setting an instance of DateTime with a valid string gives the same date
| 4::1 | _01_Basics.DateTime_sameDay | Two DateTimes with different initializations give different sameDay
| 4::2 | _01_Basics.DateTime_sameDay | When a DateTime is used to initialized a seecond DateTime, both must be sameDay
| 5::1 | _01_Basics.Event_ConstructorBase | A newly created instance of Event gives the default event
| 5::2 | _01_Basics.Event_ConstructorBase | A newly create instance of Event, initializaed with a string. gives the same string
| 6::1 | _01_Basics.Event_Setters_getters | Setting the datetime of an event to TODAY gives TODAY
| 6::2 | _01_Basics.Event_Setters_getters | Setting the type of an event to a good value X gives X
| 6::3 | _01_Basics.Event_Setters_getters | Setting the productid of an event to a good value X gives X
| 6::4 | _01_Basics.Event_Setters_getters | Setting the categoryID of an event to a good value X gives X
| 6::5 | _01_Basics.Event_Setters_getters | Setting the category code of an event to a good value X gives X
| 6::6 | _01_Basics.Event_Setters_getters | Setting the brand of an event to a good value X gives X
| 6::7 | _01_Basics.Event_Setters_getters | Setting the price of an event to a good value X gives X
| 7::1 | _01_Basics.EventSet_Constructor |  A newly created instance of EventSet must have size = 0
| 7::2 | _01_Basics.EventSet_Constructor |  A newly created instance of EventSet must ha a to_string empty '0'
| 8::1 | _01_Basics.EventSet_add_event |  Adding an event to a newly created instance of EventSet must have size = 1
| 8::2 | _01_Basics.EventSet_add_event | Adding the default event to an empty event set must have a to_string equal to the default event
| 8::3 | _01_Basics.EventSet_add_event |  Adding 1 event to a filled EventSet increases its size in 1
| 9::1 | _01_Basics.EventSet_add_line |  Adding a line to a newly created instance of EventSet must have size = 1
| 9::2 | _01_Basics.EventSet_add_line | Adding the default event, as a line, to an empty event set must have a to_string equal to the default event
| 9::3 | _01_Basics.EventSet_add_line |  Adding 1 event, as a line, to a filled EventSet increases its size in 1
| 10::1 | _01_Basics.EventSet_at_basic | Querying the event at the 0 position should match with the first event added to the EventSet
| 10::2 | _01_Basics.EventSet_at_basic | Querying the event at the middle position should match with the event added which was added at that point
| 11::1 | _01_Basics.Pair_Constructors | After the creation of a new instance of Pair, it shows its default value
| 11::2 | _01_Basics.Pair_Constructors | After the creation of a new instance of Pair by using a string and an int, it shows these two same values
| 11::3 | _01_Basics.Pair_Constructors | After the creation of a new instance of Pair by using a string and NO int, it shows the string and -1 default value
| 12::1 | _01_Basics.Pair_isEmpty | Any newly created instance of Pair, without specifying any arguments, is considered to be emtpy
| 12::2 | _01_Basics.Pair_isEmpty | Any instance of Pair with valid key and pos, could not be considered emtpy
| 13::1 | _01_Basics.Pair_setters | After the creation of a new instance of Pair and setting it by using a string and an int, it shows these two same values
| 13::2 | _01_Basics.Pair_setters | After the creation of a new instance of Pair and setting the key to a given string, it shows this same string
| 13::3 | _01_Basics.Pair_setters | After the creation of a new instance of Pair and setting the value to a given number, it shows this same number
| 14::1 | _01_Basics.Pair_getters | After the creation of a new instance of Pair and setting it by using a string and an int, getKey() returns the same string
| 14::2 | _01_Basics.Pair_getters | After the creation of a new instance of Pair and setting it by using a string and an int, getPost() resturns the same integer
| 14::3 | _01_Basics.Pair_getters | After the creation of a new instance of Pair and setting the key to a given string, getKey() returns this same string
| 14::4 | _01_Basics.Pair_getters | After the creation of a new instance of Pair and setting the value to a given number, getPos() returns the same number
| 15::1 | _01_Basics.Index_Constructors |  A newly created instance of Index must have size = 0
| 15::2 | _01_Basics.Index_Constructors |  A newly created instance of Index must write as ": On brand? 0"
| 16::1 | _01_Basics.Index_getIOnWhich | Building an index by Users reports 0
| 16::2 | _01_Basics.Index_getIOnWhich | Building an index by brand reports 1
| 17::1 | _01_Basics.Index_clear | Clearing a brand new instance of Index leaves it empty
| 17::2 | _01_Basics.Index_clear | Clearing an instance of Index with existing records leaves it empty
| 18::1 | _01_Basics.Integrated_5_records | Execution of a simple test with five records only
| 18::2 | _01_Basics.Integrated_5_records | The output file of this test with five records only is not as expected, please have a look at ./tests/validation/ECommerce5-hit.dataset
| 19::1 | _01_Basics.Integrated_30_records | Execution of a test with 30 records only
| 20::1 | _01_Basics.Integrated_41_records | Execution of a simple test with 41 records
| 20::2 | _01_Basics.Integrated_41_records | The output file of this test with 41 records is not as expected, please have a look at ./tests/validation/ECommerce41-hit.dataset
| 21::1 | _01_Basics.Integrated_162_records | Execution of a simple test with 162 records
| 21::2 | _01_Basics.Integrated_162_records | The output file of this test with 162 records is not as expected, please have a look at ./tests/validation/ECommerce162-hit.dataset
| 22::1 | _01_Basics.Integrated_926_records | Execution of a simple test with 926 records
| 22::2 | _01_Basics.Integrated_926_records | The output file of this test with 926 records is not as expected, please have a look at ./tests/validation/ECommerce926-hit.dataset
| 23::1 | _01_Basics.Integrated_Args_5_records | Execution of a simple test with five records only + mainargs
| 23::2 | _01_Basics.Integrated_Args_5_records | The output file of this test with five records only is not as expected, please have a look at ./tests/validation/ECommerce5-hit.dataset
| 24::1 | _01_Basics.Integrated_Args_30_records | Execution of a test with 30 records only + mainargs
| 25::1 | _01_Basics.Integrated_Args_41_records | Execution of a simple test with 41 records only + mainargs
| 25::2 | _01_Basics.Integrated_Args_41_records | The output file of this test with 41 records only is not as expected, please have a look at ./tests/validation/ECommerce41-hit.dataset
| 26::1 | _01_Basics.Integrated_Args_162_records | Execution of a simple test with 162 records only + mainargs
| 26::2 | _01_Basics.Integrated_Args_162_records | The output file of this test with 162 records only is not as expected, please have a look at ./tests/validation/ECommerce162-hit.dataset
| 27::1 | _01_Basics.Integrated_Args_926_records | Execution of a simple test with 500 records only + mainargs
| 27::2 | _01_Basics.Integrated_Args_926_records | The output file of this test with 500 records only is not as expected, please have a look at ./tests/validation/ECommerce926-hit.dataset
| 28::1 | _02_Intermediate.DateTime_isBefore | A DateTime cannot be before itself
| 28::2 | _02_Intermediate.DateTime_isBefore | Default date is before  today
| 28::3 | _02_Intermediate.DateTime_isBefore | Today is not before the  Default date
| 29::1 | _02_Intermediate.DateTime_weekDay | Today must be Thursday
| 29::2 | _02_Intermediate.DateTime_weekDay | Tomorrow is Friday
| 29::3 | _02_Intermediate.DateTime_weekDay | Yesterday was Wednesday
| 30::1 | _02_Intermediate.Event_getField | getField("DateTime") on any Event, must be equal to getDateTime()
| 30::2 | _02_Intermediate.Event_getField | In any row, querying the Event for field "Price" will produce the same string than getDateTime
| 30::3 | _02_Intermediate.Event_getField | In any case, querying the Event for field "UserID" will produce the same string than the former getUserID()
| 30::4 | _02_Intermediate.Event_getField | In any row, querying the EventS a mandatory field cannot give an empty string
| 30::5 | _02_Intermediate.Event_getField | In any row, querying  an optional field will produce the same string than the former event added to the EvenSet
| 31::1 | _02_Intermediate.EventSet_add_event_partial |  Adding MAXEVENT events to a newly created EventSet increases its size in MAXEVENT
| 32::1 | _02_Intermediate.EventSet_at_intermediate | Querying the event at the last position should match with the last event added to the EventSet
| 32::2 | _02_Intermediate.EventSet_at_intermediate | Accessing EventSet at() a certain position and changing the user ID of the event, this change will remain in the EventSet itself
| 32::3 | _02_Intermediate.EventSet_at_intermediate | Accessing EventSet at() a certain position and changing the brand of the event, this change will remain in the EventSet itself
| 33::1 | _02_Intermediate.Index_3x3_just_build | In any case, building the same index twice gives the same result
| 33::2 | _02_Intermediate.Index_3x3_just_build | The index by user built within experiment 3x3 differs from the expected one
| 33::3 | _02_Intermediate.Index_3x3_just_build | The index by brand built within experiment 3x3 differs from the expected one
| 34::1 | _02_Intermediate.Index_B_BxU_build_at | 0 The index by brand built within experiment BxU is the same key during U consecutive positions
| 34::2 | _02_Intermediate.Index_B_BxU_build_at | 0 The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
| 34::3 | _02_Intermediate.Index_B_BxU_build_at | 1 The index by brand built within experiment BxU is the same key during U consecutive positions
| 34::4 | _02_Intermediate.Index_B_BxU_build_at | 1 The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
| 34::5 | _02_Intermediate.Index_B_BxU_build_at | 2 The index by brand built within experiment BxU is the same key during U consecutive positions
| 34::6 | _02_Intermediate.Index_B_BxU_build_at | 2 The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
| 34::7 | _02_Intermediate.Index_B_BxU_build_at | 3 The index by user built within experiment BxU changes the key at point U
| 34::8 | _02_Intermediate.Index_B_BxU_build_at | 4 The index by brand built within experiment BxU is the same key during U consecutive positions
| 34::9 | _02_Intermediate.Index_B_BxU_build_at | 4 The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
| 34::10 | _02_Intermediate.Index_B_BxU_build_at | 5 The index by brand built within experiment BxU is the same key during U consecutive positions
| 34::11 | _02_Intermediate.Index_B_BxU_build_at | 5 The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
| 34::12 | _02_Intermediate.Index_B_BxU_build_at | 6 The index by brand built within experiment BxU is the same key during U consecutive positions
| 34::13 | _02_Intermediate.Index_B_BxU_build_at | 6 The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
| 34::14 | _02_Intermediate.Index_B_BxU_build_at | 7 The index by user built within experiment BxU changes the key at point U
| 34::15 | _02_Intermediate.Index_B_BxU_build_at | 8 The index by brand built within experiment BxU is the same key during U consecutive positions
| 34::16 | _02_Intermediate.Index_B_BxU_build_at | 8 The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
| 34::17 | _02_Intermediate.Index_B_BxU_build_at | 9 The index by brand built within experiment BxU is the same key during U consecutive positions
| 34::18 | _02_Intermediate.Index_B_BxU_build_at | 9 The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
| 34::19 | _02_Intermediate.Index_B_BxU_build_at | 10 The index by brand built within experiment BxU is the same key during U consecutive positions
| 34::20 | _02_Intermediate.Index_B_BxU_build_at | 10 The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units
| 34::21 | _02_Intermediate.Index_B_BxU_build_at | 11 The index by user built within experiment BxU changes the key at point U
| 35::1 | _02_Intermediate.Index_U_BxU_build_at | 0 The index by user built within experiment BxU is the same key during B consecutive positions
| 35::2 | _02_Intermediate.Index_U_BxU_build_at | 0 The index by user built within experiment BxU indexes B consecutive positions for the same key
| 35::3 | _02_Intermediate.Index_U_BxU_build_at | 1 The index by user built within experiment BxU is the same key during B consecutive positions
| 35::4 | _02_Intermediate.Index_U_BxU_build_at | 1 The index by user built within experiment BxU indexes B consecutive positions for the same key
| 35::5 | _02_Intermediate.Index_U_BxU_build_at | 2 The index by user built within experiment BxU is the same key during B consecutive positions
| 35::6 | _02_Intermediate.Index_U_BxU_build_at | 2 The index by user built within experiment BxU indexes B consecutive positions for the same key
| 35::7 | _02_Intermediate.Index_U_BxU_build_at | 3 The index by user built within experiment BxU changes the key at point B
| 35::8 | _02_Intermediate.Index_U_BxU_build_at | 4 The index by user built within experiment BxU is the same key during B consecutive positions
| 35::9 | _02_Intermediate.Index_U_BxU_build_at | 4 The index by user built within experiment BxU indexes B consecutive positions for the same key
| 35::10 | _02_Intermediate.Index_U_BxU_build_at | 5 The index by user built within experiment BxU is the same key during B consecutive positions
| 35::11 | _02_Intermediate.Index_U_BxU_build_at | 5 The index by user built within experiment BxU indexes B consecutive positions for the same key
| 35::12 | _02_Intermediate.Index_U_BxU_build_at | 6 The index by user built within experiment BxU is the same key during B consecutive positions
| 35::13 | _02_Intermediate.Index_U_BxU_build_at | 6 The index by user built within experiment BxU indexes B consecutive positions for the same key
| 35::14 | _02_Intermediate.Index_U_BxU_build_at | 7 The index by user built within experiment BxU changes the key at point B
| 35::15 | _02_Intermediate.Index_U_BxU_build_at | 8 The index by user built within experiment BxU is the same key during B consecutive positions
| 35::16 | _02_Intermediate.Index_U_BxU_build_at | 8 The index by user built within experiment BxU indexes B consecutive positions for the same key
| 35::17 | _02_Intermediate.Index_U_BxU_build_at | 9 The index by user built within experiment BxU is the same key during B consecutive positions
| 35::18 | _02_Intermediate.Index_U_BxU_build_at | 9 The index by user built within experiment BxU indexes B consecutive positions for the same key
| 35::19 | _02_Intermediate.Index_U_BxU_build_at | 10 The index by user built within experiment BxU is the same key during B consecutive positions
| 35::20 | _02_Intermediate.Index_U_BxU_build_at | 10 The index by user built within experiment BxU indexes B consecutive positions for the same key
| 35::21 | _02_Intermediate.Index_U_BxU_build_at | 11 The index by user built within experiment BxU changes the key at point B
| 36::1 | _02_Intermediate.Integrated_EMPTY | Execution of a simple test with an empty set of records
| 37::1 | _02_Intermediate.Integrated_ErrorLoading | Execution of a simple test with an error when opening the data file
| 38::1 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 38::2 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 38::3 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 38::4 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 38::5 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 38::6 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 38::7 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 38::8 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 38::9 | _03_Advanced.DateTime_BadValues | Setting a bad date or time gives the default datetime
| 38::10 | _03_Advanced.DateTime_BadValues | Setting a date with the incorrect format throws an exception
| 39::1 | _03_Advanced.Event_setType_Bad_Values | Setting the type of an event to a good value X gives X
| 39::2 | _03_Advanced.Event_setType_Bad_Values | Setting the type of an event to a good value X gives X
| 40::1 | _03_Advanced.Event_Others_Bad_Values | Setting the productid of an event to a good value X gives X
| 40::2 | _03_Advanced.Event_Others_Bad_Values | Setting the productid of an event to a good value X gives X
| 40::3 | _03_Advanced.Event_Others_Bad_Values | Setting the productid of an event to a good value X gives X
| 41::1 | _03_Advanced.EventSet_add_event_full |  Adding one single Event events to a partly filled EventSet must return 1
| 41::2 | _03_Advanced.EventSet_add_event_full |  Adding one single Event events to a completely filled EventSet does not produce any change in the EventSet
| 41::3 | _03_Advanced.EventSet_add_event_full |  Adding one single Event events to a completely filled EventSet must return 0
| 42::1 | _03_Advanced.EventSet_at_advanced | Querying an EventSet beyond its legal limits gives an EMPTY event
| 42::2 | _03_Advanced.EventSet_at_advanced | Querying an EventSet beyond its legal limits gives an EMPTY event
| 42::3 | _03_Advanced.EventSet_at_advanced | Querying an EventSet within its legal limits always gives a NON-EMPTY event
| 43::1 | _03_Advanced.EventSet_externalfunctions | sumPrice must give the sum of all prices of a given EventSet, and it doesnt 
| 43::2 | _03_Advanced.EventSet_externalfunctions | UniqueBrands() must give the number of different brands, but it doesnt 
| 43::3 | _03_Advanced.EventSet_externalfunctions | UniqueUsers() must give the number of different users, but it doesnt 
| 44::1 | _03_Advanced.EventSet_write | Any EventSet writes into a disk file exactly its to_string() without the number of events
| 45::1 | _03_Advanced.EventSet_read | Any EventSet read from a disk file must have a to_string(), without the number of events, comparable to the content of the file
| 46::1 | _03_Advanced.Index_U_BxU_bounds | 0 The index by user built within experiment BxU lower bounds User u with u*B
| 46::2 | _03_Advanced.Index_U_BxU_bounds | 0 The index by user built within experiment BxU upper bounds User u with (u+1)*B
| 47::1 | _03_Advanced.Index_B_BxU_bounds | 0 The index by brand built within experiment BxU lower bounds Brand b with b*U
| 47::2 | _03_Advanced.Index_B_BxU_bounds | 0 The index by brand built within experiment BxU upper bounds Brand b with (b+1)*U
| 48::1 | _03_Advanced.Index_add | Inserting any pair in any index increases its size in one
| 48::2 | _03_Advanced.Index_add | Adding a  key at the end of the index places the new key in its previous upperbound
| 48::3 | _03_Advanced.Index_add | Adding a  key at the beginning of the index gives a lower bound equals to 0 after the insertion
| 49::1 | _03_Advanced.Index_B_BxU_rawFilterIndex | In an Index BxU , filtering the index by brand-i produces an index with exactly size U
| 50::1 | _03_Advanced.Index_U_BxU_rawFilterIndex | In an Index BxU , filtering the index by user-i produces an index with exactly size B
| 51::1 | _03_Advanced.Index_Type_BxU_rawFilterIndex | In an Index BxU , filtering the index by Type=cart produces an index with exactly size B
| 52::1 | _03_Advanced.Index_DateTime_BxU_rawFilterIndex | In an Index BxU , filtering the index by DateTime equals to the first available date produces an index with exactly size B
| 53::1 | _03_Advanced.Index_BxU_sumPrice | Given a BxU Index, a filter by user 0 the sum of prices amounts to (U*B)/4*(1+B)/2
| 53::2 | _03_Advanced.Index_BxU_sumPrice | Given a BxU Index, a filter by brand 0 the sum of prices amounts to U*(b+1)
| 53::3 | _03_Advanced.Index_BxU_sumPrice | Given a BxU Index, a filter by Type=view the sum of prices amounts to (B*U)/4*(1+B)/2
| 53::4 | _03_Advanced.Index_BxU_sumPrice | Given a BxU Index, a filter by date=2021-03-1  10:32:00 UTC the sum of prices amounts to U*day
| 54::1 | _03_Advanced.Integrated_ErrorData | Execution of a simple test with an error when reading the data file
| 55::1 | _03_Advanced.Integrated_ErrorSaving | Execution of a simple test with an error when saving the data file
| 56::1 | _03_Advanced.Integrated_Args_no_open | Execution of a simple test with 500 records only + mainargs
| 57::1 | _03_Advanced.Integrated_Args_error_data | Execution of a simple test with 500 records only + mainargs
| 58::1 | _03_Advanced.Integrated_Args_error_missing_arg | Execution of a simple test with 500 records only + mainargs
| 58::2 | _03_Advanced.Integrated_Args_error_missing_arg | Execution of a simple test with 500 records only + mainargs
| 59::1 | _03_Advanced.Integrated_Args_error_bad_arg | Execution of a simple test with 500 records only + mainargs
