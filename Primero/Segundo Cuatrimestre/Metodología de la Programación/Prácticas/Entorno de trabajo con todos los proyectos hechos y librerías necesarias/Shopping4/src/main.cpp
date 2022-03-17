/*
 * File:   main.cpp
 * Author: MP-team 
 * @warning To be implemented by students. Follow the instructions given in the headers
 */

/**
 * @brief This program must load a sample dataset given as parameters to the program.
 * 
 * The main() function has three mandatory parameters:  
 * "-input <input_file>"  "-events <number_events>"  "-index-by Brand|UserID"
 *    - input_file is the path to the file used as input
 *    - number_events is the number of events to be read from the input_file
 *    - Brand and UserID with the parameter index-by marks the field used to build
 *      the index
 *  there are also three optional parameters:
 * "-report-by Brand|UserID|Type|Datetime"  "-output <output_file>"  "-display Framed|Fancy"
 *    - report-by marks the column used for grouping the event when creating the reports
 *    - output_file is the file to store the output
 *    - display is used to choose the format of the DataTable output:
 *  *  * - If the parameter is absent, the report is shown in plain text, using DataTable::showPlainReportH(0)
 *  *  * - If the parameter is set to Framed, the report is shown using a table format, with DataTable::showFramedReportH(0)
 *  *  * - If the parameter is set to Fancy, the report is shown as histograms using an external library, with DataTable::showFancyReportH(0)
 * 
 * ALL THE PARAMETERS CAN BE GIVEN IN ANY ORDER
 * 
 * The following calls are correct and equivalent
 * shopping3 -input_file data/ECommerce41.dataset -events 30 -index-by Brand -report-by Brand -display Framed
 * shopping3 -events 30 -display Framed -report-by Brand -input_file data/ECommerce41.dataset -index-by Brand 
 *
 */

/**
 * NOTE: NO PARAMETERS EXECUTION
 * In order to modularize the development of this assignment, a simplified execution
 * mode is proposed, where only one parameter is employed. The execution of the
 * program using:
 * 
 * shopping3 -noargs
 * 
 * is intended to be used with input redirection. 
 * To this end, several input files have been prepared. They are placed in folder
 * tests/validation, with name <dataset.keyboard>. This files always contain the
 * same structure:
 * - Path to the input file
 * - Number of events to read from input
 * - Field used to build the index (Brand or UserID)
 * - Field used to group the reports (Brand, UserID, Type or DateTime)
 * 
 * The proper way to call the program using this structure is the following (using
 * ECommerce30.keyboard as input, for example)
 * dist/Debug/GNU-Linux/shopping3 -noargs < tests/validation/ECommerce30.keyboard
 */

#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include "Event.h"
#include "EventSet.h"
#include "Index.h"
#include "DataVector.h"
#include "MPTests.h"

#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3

using namespace std;


/**
 * @brief Update the counter per week day (value in 0..6) for every event found.
 * It also shows the computed values on the screen
 * @param evSet an input EventSet  
 * @param arrayA an int output array
 */
void computeActivity(EventSet evSet, int arrayA[]);

/**
 * @brief Breaks the program execution if an error is encountered during execution
 * @param errorcode Integer marking the type of error encountered (1 for arguments
 * error, 2 for open file error and 3 for data reading error, see ERROR_ARGUMENTS,
 * ERROR_OPEN and ERROR_DATA definitions above)
 * @param errordata String representing where the error has been produced (mainly
 * used to indicate the file that produced the error)
 */
void errorBreak(int errorcode, string errordata);

/**
 * @brief Given anEventSet and a filtered Index over that dataset, build the
 * Event set with only the indexed events
 * @param es The original EventSet
 * @param indx The reduced Index
 * @return The subset of the EventSet referenced by the Index
 */
EventSet extractEventSet(EventSet es, Index indx);

/**
 * @brief Helper function that prints information about main parameters when the
 * program is not called properly. Should be called from @see errorBreak when the
 * errorcode is equal to 1
 */
void showHelp();

/**
 * Main block of the program. The full explanation of the behavior is given in
 * the comment above
 * @param argc Number of arguments passed to main
 * @param argv Strings representing those arguments
 * @return 
 */
int main(int argc, char** argv) {

    string ifilename = "error", ofilename = "", indexby = "error", reportby = "";
    int n2Read = -1;
    string curr_arg;
    ifstream ifile;
    ofstream ofile;

    bool noargs = false;

    // 1.- Read the input arguments from argv
    
    curr_arg = argv[1];
    if (curr_arg == "-noargs") {

        noargs = true;
    } 
    
    else if((argc >= 7)&&(argc <= 11)){
        
        for(int i=1; i < argc; i++){
            
            curr_arg = argv[i];
            
            if(curr_arg == "-report-by")
                reportby = argv[i+1];
            else if(curr_arg == "-index-by")
                indexby = argv[i+1];
            else if(curr_arg == "-input")
                ifilename = argv[i+1];
            else if(curr_arg == "-events")
                n2Read = stoi(argv[i+1]);
            else if(curr_arg == "-output")
                ofilename = argv[i+1];
        }
    }
    else{
        errorBreak(ERROR_ARGUMENTS, "");
    }
    // end check syntax

    // 2.- If the execution is a non-argument execution, read information from
    // cin, else check that the arguments provided are correct
    if (noargs) {
        cout << endl << "Please type the input file name: ";
        cin >> ifilename;
        cout << endl << "Please type the number of records to read: ";
        cin >> n2Read;
        cout << "Please select the field to index for (UserID, Brand): ";
        cin >> indexby;
        cout << endl << "Please select the field to filter with (DateTime, UserID, Brand, Type): ";
        cin >> reportby;
        cout << endl << "Please indicate the output file (empty for no output file): ";
        cin >> ofilename;
    } else {
        
        if((n2Read == -1)||(ifilename == "error")||(indexby == "error"))
                errorBreak(ERROR_ARGUMENTS,"");
    }
    
    // 3.- Try to open the proposed input file
    
    ifile.open(ifilename);
    
    if(!ifile){
        errorBreak(ERROR_OPEN, ifilename);
    }
        

    // 4.- Read the events from the input file and load them in a EventSet.
    //     Only the correct ones will be charged on the EventSet
    
    EventSet originalES;
    bool no_error = originalES.read(ifile,n2Read);
    
    if(!no_error){
        errorBreak(ERROR_DATA, ifilename);
    }
    
    ifile.close();

    // 5.- Build the main index, depending on the input argument

    Index index;
    int OnBrand;
    
    if(indexby == "Brand")
        OnBrand = 1;
    else
        OnBrand = 0;
    
    index.build(originalES,OnBrand);
    
    
    // 6.- Print the amount of events read and events indexed. Keep in mind that
    // the size of the index can be lesser than the size of the EventSet, since
    // the Events with empty Brand cannot be indexed
    
    cout << originalES.size();
    cout << index.size();

    // 7.- Filter the original EventSet using the main Index. The filtered EventSet
    // will contain only the indexed Events (if the Index is built by user, the
    // original and the filtered EventSets will be identical, since every event
    // must have an associated UserID. If the index is built by brand, the filtered
    // EventSet can be smaller than the original dataset, since there are Events
    // without Brand, which cannot be indexed

    EventSet filteredES(extractEventSet(originalES,index));
    
    // 8.- Compute activity by weekday

    int arrayA[7];
    
    computeActivity(filteredES,arrayA);
    
    // 9.- Generate reports (traffic and money amount) grouped by the corresponding
    // field (indicated by parameter -report-by, Brand by default). Also, save
    // the value, the amount of traffic and the index of the element that generated
    // most traffic

    
    int field_size = 0;
    string fields[MAXEVENT];
    int fields_traffic[MAXEVENT] = {0};
    
    if(reportby == "")
        reportby = "Brand";

    findUnique(filteredES, reportby, fields, field_size);
    
    cout << filteredES.to_string() << endl;
    
    for(int i=0; i < field_size; i++)
        cout << fields[i];
    
    double moneyByField[MAXEVENT];
    
    for(int i = 0; i < field_size; i++){
        
        moneyByField[i] = 
                sumPrice(rawFilterEvents(filteredES, reportby, fields[i]));
        
        fields_traffic[i] = 
                rawFilterEvents(filteredES, reportby, fields[i]).size();
    }

    DataVector amountData;
    amountData.alloc(field_size);
    amountData.setTitle("Money/" + reportby);
    amountData.loadLabels(fields);
    amountData.loadValues(moneyByField);
    
    
    DataVector hitsData;
    hitsData.alloc(field_size);
    hitsData.setTitle("Traffic/" + reportby);
    hitsData.loadLabels(fields);
    hitsData.loadValues(fields_traffic);
    
    int max_traffic = fields_traffic[0];
    int max_value = 0;
    
    for(int i = 1; i < field_size; i++){
        if(fields_traffic[i]>max_traffic){
            max_value = i;
            max_traffic = fields_traffic[i];
        }
    }
    
    EventSet to_be_indexed(rawFilterEvents(filteredES, reportby, 
            fields[max_value]));
    
    Index traffic_index;
    traffic_index.build(to_be_indexed, OnBrand);
    
    // 10.- Display information, depending on the display mode specified by
    // -display (Plain mode by default). Also, print the information about the
    // element with highest traffic (its value and the number of events generated)

    cout << amountData.showPlainReportH(2);
    cout << hitsData.showPlainReportH(0);
    cout << "Highest traffic choice (" << fields[max_value] << ") with " << 
            max_traffic << " hits.";
    
    // 11. Save the EventSet corresponding to the element with highest traffic in
    // the output file, if specified

    
    if(ofilename != ""){
        
        ofile.open(ofilename);

        if(ofile)
            to_be_indexed.write(ofile);
        else
            errorBreak(ERROR_OPEN,ofilename);
    }
    
    ofile.close();
    
    // 12.- Report everything to the tests suite using REPORT_DATA2
    REPORT_DATA2(originalES, "Original read from dataset");
    REPORT_DATA2(filteredES, "Events indexed");
    REPORT_DATA2(hitsData, "Report traffic");
    REPORT_DATA2(amountData, "Report amount");

    return 0;
}

void errorBreak(int errorcode, string errordata) {
    
    if (errorcode == ERROR_ARGUMENTS){
        CVAL << "Error in call ";
        std::exit(-1);
    }
    
    else if (errorcode == ERROR_DATA){
        CVAL << "Data error in file " << errordata;
        std::exit(-1);
    }
    
    else if (errorcode == ERROR_OPEN){
        CVAL << "Error opening file " << errordata;
        std::exit(-1);
    }
}

void computeActivity(EventSet evSet, int arrayA[]) {
    
    for(int i=0; i<7; i++)
        arrayA[i]=0;
    
    for(int i = 0; i < evSet.size(); i++)
        if(!evSet.at(i).isEmpty())
            arrayA[evSet.at(i).getDateTime().weekDay()]++;
}

EventSet extractEventSet(EventSet es, Index indx) {
    
    EventSet subset;
    
    for(int i=0; i < indx.size(); i++)
        subset.add(es.at(indx.at(i).getPos()));
    
    return(subset);
}

void showHelp() {
    cout << "Please use: -input <filename> -events <number> -index-by UserID|Brand [-report-by UserID|Brand|Type|DateTime -output <filename>]" << endl;
    cout << "\n-input <filename>\n\tRead events from dataset in <filename>";
    cout << "\n-events <number>\n\tNumber of events to read";
    cout << "\n-index-by <field>\n\tField to index by. It can only be UserID or Brand";
    cout << "\n\nOptional arguments";
    cout << "\n-report-by <field>\n\tField to report by. It can only be UserID, Brand, Type or DateTime. The default value is Brand";
    cout << "\n-output <filename>\n\tFile to save the dataset of the field selected with -index-by with maximum traffic. If not specified, it does not save anything" << endl << endl;
}