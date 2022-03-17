# TESTS DOCUMENTATION FOR PROJECT Shopping1














































1. ## Suite  _01_Basics
   A. ## Test  DateTime_Constructors

      1. A newly create instance of DateTime gives the default date
      1. A newly created instance of DateTime by using a string gives the same string
   A. ## Test  DateTime_getters

      1. The year of the default datetime must be 2021
      1. The month of the default datetime must be 1
      1. The day of the default datetime must be 1
      1. The hour of the default datetime must be 0
      1. The minutes of the default datetime must be 0
      1. The seconds of the default datetime must be 0
   A. ## Test  DateTime_set

      1. Setting an instance of DateTime with a valid string gives the same date" ;
   A. ## Test  Event_ConstructorBase

      1. A newly created instance of Event gives the default event
      1. A newly created instance of Event is consdered empty
      1. A newly create instance of Event, initializaed with a string. gives the same string
      1. Setting the productid of an event to a good value X gives X
   A. ## Test  Event_Setters_getters

      1. Setting the datetime of an event to TODAY gives TODAY
      1. Setting the type of an event to a good value X gives X
      1. Setting the productid of an event to a good value X gives X
      1. Setting the productid of an event to a good value X gives X
      1. Setting the productid of an event to a good value X gives X
      1. Setting the productid of an event to a good value X gives X
      1. Setting the productid of an event to a good value X gives X
   A. ## Test  Integration_ECommerce5

      1. Simple test with five (5) records only
   A. ## Test  Integration_EMPTY

      1. Simple tet with an empty set of records
   A. ## Test  Integration_ECommerce49

      1. Test with 49 records
   A. ## Test  Integration_ECommerce_2019_Q4_200

      1. Test with 200 records of 2019-Q4
   A. ## Test  Integration_ECommerce_all_all_200

      1. Test with 200 records amongst all available years
1. ## Suite  _02_Intermediate
   A. ## Test  DateTime_isBefore

      1. A DateTime cannot be before itself
      1. Default date is before today
      1. Today is not before the Default date
   A. ## Test  DateTime_weekDay

      1. Today must be Thursday
      1. Tomorrow is Friday
      1. Yesterday was Wednesday
1. ## Suite  _03_Advanced
   A. ## Test  DateTime_BadValues

      1. Setting a bad date or time gives the default datetime
      1. Setting a bad date or time gives the default datetime
      1. Setting a bad date or time gives the default datetime
      1. Setting a bad date or time gives the default datetime
      1. Setting a bad date or time gives the default datetime
      1. Setting a bad date or time gives the default datetime
      1. Setting a bad date or time gives the default datetime
      1. Setting a bad date or time gives the default datetime
      1. Setting a bad date or time gives the default datetime
      1. Setting a date with the incorrect format throws an exception
   A. ## Test  Event_setType_Bad_Values

      1. Setting the type of an event to a good value X gives X
      1. Setting the type of an event to a good value X gives X
   A. ## Test  Event_Others_Bad_Values

      1. Setting the productid of an event to a good value X gives X
      1. Setting the productid of an event to a good value X gives X
      1. Setting the productid of an event to a good value X gives X
