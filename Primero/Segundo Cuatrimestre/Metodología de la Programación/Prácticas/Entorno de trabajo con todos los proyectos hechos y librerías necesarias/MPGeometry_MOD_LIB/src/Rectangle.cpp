/** 
 * @file Rectangle.cpp
 * @author lcv
 * @date 16 de enero de 2020, 20:06
 */
#include<iostream>
#include<cmath>
#include "Point2D.h"
#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle() { }

Rectangle::Rectangle(int x, int y, int w, int h) {
    topleft.setX(x);
    topleft.setY(y);
    bottomright.setX(x+w-1);
    bottomright.setY(y+h-1);
    // setGeometry(x,y,w,h);
}

void Rectangle::setGeometry(int x, int y, int w, int h) {
    topleft.setX(x);
    topleft.setY(y);
    bottomright.setX(x+w);
    bottomright.setY(y-h);
}

void Rectangle::setGeometry(const Point2D &tl, const Point2D &br) {
    topleft = tl;
    bottomright = br;
}

Point2D Rectangle::getTopLeft() const {
    return topleft;
}

Point2D Rectangle::getBottomRight() const {
    return bottomright;
}

bool Rectangle::isEmpty() const {
    return topleft.getX()>bottomright.getX() || topleft.getY() < bottomright.getY();
}

void Rectangle::read() {
    topleft.read();
    bottomright.read();
}

void Rectangle::print() const {
    cout << "[";
    topleft.print();
    cout << " - ";
    bottomright.print();
    cout << "] ";
}

Rectangle doOverlap(const Rectangle & r1, const Rectangle &r2) {
    Rectangle result;
    Point2D rTL, rBR;
    /* NO FRIEND
        rTL.setX(max(r1.getTopLeft().getX(),r2.getTopLeft().getX()));
        rTL.setY(max(r1.getTopLeft().getY(),r2.getTopLeft().getY()));
        rBR.setX(min(r1.getBottomRight().getX(),r2.getBottomRight().getX()));
        rBR.setY(min(r1.getBottomRight().getY(),r2.getBottomRight().getY()));
     */
    rTL.setX(max(r1.topleft.getX(),r2.topleft.getX()));
    rTL.setY(min(r1.topleft.getY(),r2.topleft.getY()));
    rBR.setX(min(r1.bottomright.getX(),r2.bottomright.getX()));
    rBR.setY(max(r1.bottomright.getY(),r2.bottomright.getY()));
    result.setGeometry(rTL,rBR);
    return result; // Read more
}

bool isInside(const Point2D &p, const Rectangle &r) {
    return r.getTopLeft().getX() <= p.getX() && p.getX()<=r.getBottomRight().getX() &&
           r.getTopLeft().getY() >= p.getY() && p.getY()>=r.getBottomRight().getY(); 
}

