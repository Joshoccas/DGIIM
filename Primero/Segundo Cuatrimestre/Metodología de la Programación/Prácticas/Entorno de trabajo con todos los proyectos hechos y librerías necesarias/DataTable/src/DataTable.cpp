/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//#include <iostream>
//#include "DataTable.h"
//using namespace std;
//
//DataTable::DataTable() {
//    clear();
//}
//
//DataTable & DataTable::clear() {
//    _title = "";
//    _width = _height = 0;
//    return *this;
//}
//
//DataTable & DataTable::setTitle(string title) {
//    _title = title;
//    return *this;
//}
//
//int DataTable::getWidth() const {
//    return _width;
//}
//
//int DataTable::getHeight() const {
//    return _height;
//}
//
//double DataTable::get(int row, int col) const {
//    return _data[row][col];
//}
//
//DataTable & DataTable::defXLabels(const std::string labels[], int nlabels) {
//    clear();
//    _width = std::min(nlabels, MAX_WIDTH);
//    for (int i = 0; i < getWidth(); i++) {
//        _xlabels[i] = labels[i];
//    }
//    return *this;
//}
//
//DataTable & DataTable::defXLabels(const char* const labels[], int nlabels) {
//    clear();
//    _width = std::min(nlabels, MAX_WIDTH);
//    for (int i = 0; i < getWidth(); i++) {
//        _xlabels[i] = labels[i];
//    }
//    return *this;
//}
//
//DataTable & DataTable::addValues(std::string ylabel, int values[]) {
//    _ylabels[_height] = ylabel;
//    for (int i = 0; i < getWidth(); i++) {
//        _data[_height][i] = values[i];
//    }
//    _height++;
//    return *this;
//}
//
//DataTable & DataTable::addValues(std::string ylabel, double values[]) {
//    _ylabels[_height] = ylabel;
//    for (int i = 0; i < getWidth(); i++) {
//        _data[_height][i] = values[i];
//    }
//    _height++;
//    return *this;
//}
//
//DataTable & DataTable::addValues(std::string ylabel, int values[]) {
//    _ylabels[_height] = ylabel;
//    for (int i = 0; i < getWidth(); i++) {
//        _data[_height][i] = values[i];
//    }
//    _height++;
//    return *this;
//}
//
//
//string DataTable::showPlainReportH(int decpos) const {
//    string res = _title + "\n",
//            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
//            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s",
//            axis("-", FIELD_WIDTH);
//    double byrow;
//    char aux [MAX_WIDTH];
//    int i;
//    for (int j = getHeight() - 1; j >= 0; j--) {
//        byrow = 0;
//        i = 0;
//        while (i < getWidth()) {
//            sprintf(aux, flabel.c_str(), _ylabels[j].c_str());
//            res = res + aux;
//            for (int ii = 0; ii < ITEMS_PER_ROW && i + ii < getWidth(); ii++) {
//                sprintf(aux, fdata.c_str(), get(j, i + ii));
//                res += aux;
//                byrow += get(j, i + ii);
//            }
//            res += "\n";
//            sprintf(aux, flabel.c_str(), "");
//            res = res + aux;
//            for (int ii = 0; ii < ITEMS_PER_ROW && i + ii < getWidth(); ii++) {
//                sprintf(aux, flabel.c_str(), _xlabels[i + ii].c_str());
//                res += aux;
//            }
//            res += "\n";
//            i += ITEMS_PER_ROW;
//        }
//        sprintf(aux, fdata.c_str(), byrow);
//        res = res + aux + "\n";
//    }
//    return res;
//}
//
//string DataTable::showPlainReportV(int decpos) const {
//    string res = _title + "\n",
//            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
//            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s",
//            axis("-", FIELD_WIDTH);
//    double byrow;
//    char aux [MAX_WIDTH];
//    int i;
//
//    byrow = 0;
//    sprintf(aux, flabel.c_str(), _ylabels[0].c_str());
//    res = res + aux+"\n";
//    for (int i = 0; i < getWidth(); i++) {
//        sprintf(aux, flabel.c_str(), _xlabels[i].c_str());
//        res = res+aux;
//        for (int j = 0; j < getHeight(); j++) {
//            sprintf(aux, fdata.c_str(), get(j, i));
//            res += aux;
//            byrow += get(j, i);
//        }
//        res += "\n";
//    }
//    sprintf(aux, fdata.c_str(), byrow);
//    res = res + aux + "\n";
//    return res;
//}
////public static final String windowFrames[] = {"┌┐└┘─│┬┴┼┤├▄", "++++-|", "▁▂▃▄▅▆▇█", "▏▎▍▌▋▊▉█"};
//
//string DataTable::showFancyReport(int decpos) const {
//    string res = _title + "\n",
//            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
//            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s",
//            axis(FIELD_WIDTH, '-');
//    double byrow;
//    char aux [MAX_WIDTH];
//    res += "┌";
//    for (int i = 0; i < getWidth(); i++) {
//        res = res + axis;
//        if (i < getWidth() - 1)
//            res += "┬";
//    }
//    res += "┐\n";
//
//    for (int j = getHeight() - 1; j >= 0; j--) {
//        res += "│";
//        byrow = 0;
//        for (int i = 0; i < getWidth(); i++) {
//            sprintf(aux, fdata.c_str(), get(j, i));
//            res = res + aux + "│";
//            byrow += get(j, i);
//        }
//        sprintf(aux, fdata.c_str(), byrow);
//        res = res + aux + "\n";
//    }
//    res += "├";
//    for (int i = 0; i < getWidth(); i++) {
//        res = res + axis;
//        if (i < getWidth() - 1)
//            res += "┼";
//    }
//    res += "┤\n│";
//    for (int i = 0; i < getWidth(); i++) {
//        sprintf(aux, flabel.c_str(), _xlabels[i].c_str());
//        res = res + aux + "│";
//    }
//    res += "\n└";
//    for (int i = 0; i < getWidth(); i++) {
//        res = res + axis + "┘";
//    }
//    res += "\n";
//    return res;
//}
//
//string DataTable::reportData() const {
//    string result = showPlainReportH(2);
//    result = std::to_string(std::hash<std::string>{}
//    (result));
//    result = std::to_string(getWidth()) + " " + std::to_string(getHeight()) + " " + result;
//    return result;
//}
//
