/* 
 * File:   main.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students 
 */

#include <string>
#include <cassert>
#include <iostream>
#include <cstring>
#include "MPTests.h"
#include "Event.h"
#include "EventSet.h"
#include "DataVector.h"


using namespace std;

void lee_linea(string &line);

/**
 * @brief Update the counter per week day (value in 0..6) for every event found . 
 * It also shows the computed values on the screen
 * @param evSet an input EventSet  
 * @param arrayA an int output array
 */

void computeActivity(const EventSet & evSet, int arrayA[]);
/**
 * @brief This program must load a sample dataset given by keyboard, but really
 * redirected from a disk data file. Introduce in an EventSet only those records non
 * empty, and then produce the following reports
 *   - Inform about the total number of records read
 *   - Filter this EvenSet and extract only those of type "purchase". Le us call it
 *     "purchaseSet". Inform of its size.
 *   - Take purchaseSet and produce the following reports
 *       - How many sales have been detected each day of the week. Something like
 *~~~~ 
 *    Sales/Weekday 3 records
 *         0         1        2  
 *    SUNDAY    MONDAY  TUESDAY
 *~~~~
 *       - Extract the unique set of brands in purchaseSet and find the amount of money
 * sold by every brand. Please take into account that this field might be empty, that is
 * "", therefore, it will appear as an "unknown" brand marked with the empty string "". 
 * Something like
 * ~~~~
 *      $$/Brand    103.25 US$
 *      brand1     100.10
 *      brand2       3.15
 *      ...
 * ~~~~
 *       - Extract the unique set of Users in purchaseSet and find how how many products
 * have bought every User. Something like.
 * ~~~~
 *      QTY/User    3 records
 *      user1       1
 *      user2       1
 *      user3       1
 * ~~~~
 *   - At every report you are suggested to use the class DataVector. Let say we have the following data
 * ~~~~
 *      string brands [2]={"brand1", "brand2"}
 *      int nbrands = 2;
 *      double salesByBrand [2]={100.10,3.15}
 *      int nsales = nbrands;
 * ~~~~
 *   - The report might be made by hand or making use of the class DataVector and its methods
 * boths showReport() which shows a report on the screen, and reportData() which encodes its content as
 * an encrypted long number which may be easily transferred or compared. In order to do that,
 * the following steps could be carried out
 * 
 * ~~~
 *    DataVector brandData;
 * 
 *    brandData.alloc(nbrands);
 *    brandData.setTitle(""$$/Brand");
 *    brandData.loadLabels(brands);
 *    brandData.loadValues(salesByBrand);
 *    cout << brandData.showPlainReport(2); // Number od decimal digits
 *    REPORT_DATA(brandData);
 * ~~~
 * 
 *   
 * @return 
 */
int main() {

    string event;
    Event one;
    EventSet eventS, aux;
    int n2Read = 0, nEvents = 0;

    // 1. Read the events from the dataset and load them in a EventSet 
    //    only the correct ones will be charged on the EventSet
    
    do{
        cin >> n2Read;
    }while (n2Read < 0);
    
    for(int i = 0; i < n2Read; i++){
        
        lee_linea(event);
        
        one.setEvent(event);
        
        if(!one.isEmpty()){
            
            eventS.add(one);
            nEvents++;
        }
    }

    // 2. Prepare a new eventSet by selecting the purchase Events
    
    EventSet purchaseSet = rawFilterEvents(eventS, "Type", "purchase");

    // 3. show the size of the new purchaseSet
    
    int sales = purchaseSet.size();
    cout << "Sales found: " << sales << endl;
    
    // 4. show the distribution for purchase in week days 
    
    int countWeekDay[7];
    computeActivity(purchaseSet, countWeekDay);
    
    DataVector weeklyData;
    
    weeklyData.alloc(0);
    
    weeklyData.alloc(7);
    weeklyData.setTitle("Sales/day");
    weeklyData.loadLabels(DAYNAME);
    weeklyData.loadValues(countWeekDay);
    cout << weeklyData.showPlainReportH(2);

    // 5. Find the money spent on every brand which is present in purchaseSet
    
    int brands_size = 0;
    string brands[sales];
    
    findUnique(purchaseSet, "Brand", brands, brands_size);
    
    double salesByBrand[brands_size];
    
    for(int i = 0; i < brands_size; i++){
        
        salesByBrand[i] = 
                sumPrice(rawFilterEvents(purchaseSet, "Brand", brands[i]));
    }
    
    DataVector brandData;
    brandData.alloc(0);
    
    brandData.alloc(brands_size);
    brandData.setTitle("Sales/Brand");
    brandData.loadLabels(brands);
    brandData.loadValues(salesByBrand);
    cout << brandData.showPlainReportH(2);

    // 6. Find the number of sales for every user present in purchaseSet
    
    int nUsers = 0;
    string users[sales];
    
    findUnique(purchaseSet, "UserID", users, nUsers);
    
    int nsalesByUser[nUsers];
    
    for(int i = 0; i < nUsers; i++){
        
        nsalesByUser[i] = 
                rawFilterEvents(purchaseSet, "UserID", users[i]).size();
    }
    
    DataVector usersData;
    
    usersData.alloc(0);

    usersData.alloc(nUsers);
    usersData.setTitle("QTY/User");
    usersData.loadLabels(users);
    usersData.loadValues(nsalesByUser);
    cout << usersData.showPlainReportH(2);

    // Report everything to the integration tests
    
    REPORT_DATA(eventS);
    REPORT_DATA(purchaseSet);
    REPORT_DATA(weeklyData);
    REPORT_DATA(brandData);
    REPORT_DATA(usersData);
    return 0;
}

void computeActivity(const EventSet & evSet, int arrayA[]) {
    
    for(int i=0; i<7; i++)
        arrayA[i]=0;
    
    for(int i = 0; i < evSet.size(); i++)
        if(!evSet.at(i).isEmpty())
            arrayA[evSet.at(i).getDateTime().weekDay()]++;
}

void lee_linea(string &line){
    
    do{
        getline(cin, line);
    } while (line.length() == 0);
}
