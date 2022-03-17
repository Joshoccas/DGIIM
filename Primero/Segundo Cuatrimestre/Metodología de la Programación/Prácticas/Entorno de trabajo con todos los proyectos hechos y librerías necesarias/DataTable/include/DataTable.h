/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReportAnsi.h
 * Author: lcv
 *
 * Created on 18 de febrero de 2021, 13:06
 */
#include <string>

#ifndef REPORTANSI_H
#define REPORTANSI_H

#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define FIELD_WIDTH 10
#define ITEMS_PER_ROW 15

/*
 *  int n
 *  int value[]; o double value[];
 *  string label[];
 * 
 * value[0]     value[1] ...    value[n]
 * ----------------------------------------
 * label[0]     label[1] ...    label[n]
 * 
 * cout << myReport.setTitle("Title").defReport(n, labels, value).showReport() << endl;
 */

class DataTable {
private:
    std::string _title, _xlabels[MAX_WIDTH], _ylabels[MAX_HEIGHT];
    double _data[MAX_WIDTH][MAX_HEIGHT];
    int _width, _height, _decpos;
    double get(int row, int col) const;
    
public:

    DataTable();

    DataTable & clear();

    int getWidth() const;

    int getHeight() const;
    
    
    DataTable & setTitle(std::string title);
    
    DataTable & defXLabels(const std::string labels[], int nlabels);
    DataTable & defXLabels(const char * const labels[], int nlabels);

    DataTable & addValues(std::string ylabel, int values[]);
    DataTable & addValues(std::string ylabel, double values[]);
    
    std::string showPlainReportH(int decpos = 0) const;
    std::string showPlainReportV(int decpos = 0) const;
    std::string showFancyReport(int decpos = 0) const;
    

    /**
     * @brief Shows the number of events in the EventSet and a numeric 
     * value that encodes the whole set of events
     * @return A string made up of the size of the EventSet and the
     * numeric code of its content
     * @warning please do not modify its implementation
     */
    std::string reportData() const;
    
};



#endif /* REPORTANSI_H */

