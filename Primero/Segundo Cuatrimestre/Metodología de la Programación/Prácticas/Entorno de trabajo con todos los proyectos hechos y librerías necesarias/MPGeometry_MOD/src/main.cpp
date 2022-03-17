/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented (partially) by students
 * 
 */
/**
 * @mainpage MP1920Geometry
 * 
 * Given two rectangles and a sequence of points
 * this program calculates which points are inscribed within the intersection of the two
 * rectangles
 * - programmatically sets the data of the first rectangle
 * - reads the second rectangle  from keyboard
 * - calculates the intersection
 *    - if the intersection is empty, it ends
 *    - otherwise it reads the points and for each point
 *       - Check if the point belongs the intersection
 *       - Counts the number of points inscribed in the intersection
 *       - The sequence ends when a point with any negative coordinate is read
   * ~~~~
 *        B{(1,6) (6,1)}
 *  6+     +-----------------------------o
 *   |     |                             |
 *   |     |    A{(2,5) (5,2)}           |
 *  5+     |    +------------------o     |
 *   |     |    |                  |     |
 *   |     |    |                  |     |
 *  4+     |    |           o      |     |
 *   |     |    |                  |     |
 *   |     |    |                  |     |
 *  3+     |    |     o            |     |
 *   |     |    |                  |     |
 *   |     |    |                  |     |
 *  2+     |    o------------------+     |
 *   |     |                             |
 *   |     |                             |
 *  1+     o-----------------------------+
 *   |
 *   |
 *   o-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 *   0     1     2     3     4     5     6     7     8     9     10
 *
 *   A={(2,5) (5,2)}     B={(1,6) (6,1)}
 *   I={(2,5) (5,2)}
 *   P={(0,0), (1,1), (2,2), (3,3), (4,4), (5,5), (6,6)}
 *   P(I)={(2,2), (3,3), (4,4), (5,5)}
 * 
 *~~~~~
 *
 */
#include <iostream>
#include <cmath>
#include "Point2D.h"
#include "Rectangle.h"

using namespace std;


/**
 * @brief Main function
 * @return Always 0
 */
int main() {
    Rectangle A, B, Intersection;
    Point2D p; 
    int count;
    
    A.setGeometry(2,5,3,3);
    cout << "First rectangle is "; 
    A.print();
    cout << endl << "Type second rectangle: ";
    B.read();
    cout << endl << "Calculating intersection of: ";
    A.print();
    cout << " and ";
    B.print();
    cout << endl;
    Intersection = doOverlap(A,B);
    if (Intersection.isEmpty()) {
        cerr << "Empty intersection"<<endl;
    } else {
        cout << "The intersection is: ";
        Intersection.print();
        count = 0;
        cout << endl << "Reading points...";
        p.read();
        while (p.getX()>=0 && p.getY()>=0) {
            if (isInside(p,Intersection)) {
                p.print();
                count ++;
            } 
            p.read();
        }
        if (count > 0)
            cout << " fall within the intersection ("<< count<<" total)" << endl;
        else
            cout << " None of them falls within the intersection "<<endl;
    }

    return 0;
}

