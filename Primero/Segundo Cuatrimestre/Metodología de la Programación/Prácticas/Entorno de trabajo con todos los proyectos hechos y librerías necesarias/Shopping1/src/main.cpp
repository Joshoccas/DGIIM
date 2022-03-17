/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */


#include <string>
#include <cassert>
#include <iostream>
#include "Event.h"

#include "MPTests.h"

using namespace std;


/**
 * @brief displays the content of the array by using the method to_string that easy to transfer data to stream.  The content remains constant
 * @param array of the Events
 * @param nEvent number of events in the array
 */
void print(const Event array[], int &nEvent);

/**
 * @brief Update the counter per week day (value in 0..6) for every event found . 
 * It also shows the computed values on the screen in the following format
 * ~~~~
 *      SUNDAY(0) MONDAY(0) TUESDAY(0) WEDNESDAY(0) THURSDAY(0) FRIDAY(0) SATURDAY(0)
 *      +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 * 
 * @param arrayE an Event input array
 * @param nEvents number of events in arrayE
 * @param arrayA an int output array
 */
void computeActivity(const Event arrayE[], int  nEvents,  int arrayA[]);
/**
 * @brief Compute the  max number of activity events, and the day on which is produced
 * @param arrayA the counter of activities, an input array
 * @param ndays number of days
 * @param maxDay
 * @return maxActivity the counter of events of 
 */
int computeMaxActivityDay(const int arrayA[], int &maxDay, int ndays=7);

void lee_linea(string &line);



/**
 * @brief The main function of the program carries out the following procedure
 *   - It uses a static array of Events to store a sequence of events read from 
 * keyboard (likely to be redirected from a data file in the ./tests folder)
 *   - It reads the maximum number of valid records to be stored in the array.
 *   - If the event read is right (use the method isEmpty() to detect non-valid
 * records), it is stored in the array, otherwise, it is dismissed. Only valid records count.
 *   - Next, it computes the number of events found at each day of the week (complete the implementation
 * of the local function computeActivity() which also shows the result)
 *   - Next, it finds which is the day of highest activity recorded and show it on screen
 */
int main(int argc, char** argv){
    
    int ndays = 7;
    int arrayA[ndays] = {0}; // Vector de recuento de actividad de los días
    const int TAMANIO = 300;
    Event arrayE[TAMANIO]; // Vector de almacenamiento de eventos
    
    int eventos; // Número de eventos a leer
    int eventos_validos = 0; // Número de eventos válidos 
    string evento; // Cadena para ir leyendo cada evento representado por
                   // un string
    
    int maxDay; // Día de actividad máxima
    
    
    do{
        cin >> eventos;
    }while ((eventos < 0) || (eventos > TAMANIO));
    
    for(int i = 0; i < eventos; i++){
        
        lee_linea(evento);
        
        arrayE[i].setEvent(evento);
        
        if(!(arrayE[i].isEmpty()))
            eventos_validos++;
    }
    
    // Salida de resultados
    
    computeActivity(arrayE, eventos, arrayA);
    
    CVAL << "Records read: " << eventos << endl;
    CVAL << "Valid records: " << eventos_validos << endl;
    CVAL << "Max activity: " << computeMaxActivityDay(arrayA, maxDay, ndays)
            << endl;
    CVAL << "Day of Max activity: " << DAYNAME[maxDay] << endl;

}

void print(const Event array[], int &nEvent){
    
    for(int i = 0; i < nEvent; i++)
        cout << array[i].to_string() << "\n";
}

void computeActivity(const Event arrayE[], int  nEvents,  int arrayA[]){
        
    for(int i = 0; i < nEvents; i++)
        arrayA[arrayE[i].getDateTime().weekDay()]++;
    
    CVAL << "Activity found:";
    for (int day=0; day<7; day++) {
        CVAL << " " << DAYNAME[day]<<"("<<arrayA[day]<<")";
    }
    CVAL << endl;
}

int computeMaxActivityDay(const int arrayA[], int &maxDay, int ndays){
    
    maxDay = 0;
    
    for(int i = 1; i < ndays; i++){
        
        if(arrayA[maxDay] < arrayA[i])
            maxDay = i;
    }
    
    return(arrayA[maxDay]);
}

void lee_linea(string &line){
    
    do{
        getline(cin, line);
    } while (line.length() == 0);
}