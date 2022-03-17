/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   datatools.h
 * Author: lcv
 *
 * Created on 26 de febrero de 2021, 10:53
 */

#ifndef DATATOOLS_H
#define DATATOOLS_H


#define UTFLEN 3
#define UTF_AT(s,i) ((std::string) s).substr(i*UTFLEN,UTFLEN)
#define STR(x) std::to_string((x))
#define MIN(a, b) ((a) < (b)? (a): (b))
#define MAX(a, b) ((a) < (b)? (b): (a))

std::string trim(std::string s, int max);

std::string format(std::string f, int v);

std::string format(std::string f, double v);

std::string format(std::string f, std::string v);


#endif /* DATATOOLS_H */

