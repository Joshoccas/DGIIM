/** 
 * @file Point2D.cpp
 * @author lcv
 * @date 16 de enero de 2020, 20:06
 */
#include<iostream>
#include "Point2D.h"

using namespace std;

Point2D::Point2D() {
    px = py = 0;
}

Point2D::Point2D(int x, int y) {
    px = x;
    py = y;
}

void Point2D::setX(int px) {
    this->px = px;
}

void Point2D::setY(int py) {
    this->py = py;
}

int Point2D::getX() const {
    return px;
}

int Point2D::getY() const {
    return py;
}

void Point2D::read() {
    cin >> px >> py;
}

void Point2D::print() const {
    cout << "("<<px << "," << py<<")";
}

