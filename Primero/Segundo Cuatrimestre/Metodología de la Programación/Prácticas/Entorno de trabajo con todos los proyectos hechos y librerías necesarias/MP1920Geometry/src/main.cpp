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
 */
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @class Point2D
 * @brief To represent a point in a two-dimensional space
 */
class Point2D {
private:
    double px, py; ///< Coordinates of the point
public:
    /**
     * @brief Basic constructor
     */
    Point2D() {
        px = py = 0;
    }
    /**
     * @brief Constructor with initialization parameters
     * @param x Coordinate
     * @param y Coordinate
     */
    Point2D(int x, int y) {
        px = x;
        py = y;
    }
    /**
     * @brief Initializes the X coordinate
     * @param px New value for X
     */
    void setX(int px) {
        this->px = px;
    }
    /**
     * @brief Initializes the Y coordinate
     * @param py New value for Y
     */
    void setY(int py) {
        this->py = py;
    }
    /**
     * @brief Queries the X coordinate
     * @return Value of X
     */
    int getX() const {
        return px;
    }
    /**
     * @brief Queries the Y coordinate
     * @return Value of Y
     */
    int getY() const {
        return py;
    }
    /**
     * @brief Reads the XY value from keyboard
     */
    void read() {
        cin >> px >> py;
    }
    /**
     * @brief Prints the XY values in the screen  in the form (X,Y)
     */
    void print() const {
        cout << "("<<px << "," << py<<")";
    }
};

/**
 * @class Rectangle
 * @brief To represent a rectangle  in a two-dimensional space as a pair 
 * or points, the top-left corner and the bottom-right one 
 */
class Rectangle {
private:
    Point2D topleft, bottomright; ///< Points that define the rectangle
public:
    /**
     * @brief Basic constructor
     */
    Rectangle() { }
    
    /**
     * @brief Constructor with parameters
     * @param x XY Coordinates of top-left corner
     * @param y
     * @param w Width of the rectangle
     * @param h Height of the rectangle
     */
    Rectangle(int x, int y, int w, int h) {
        topleft.setX(x);
        topleft.setY(y);
        bottomright.setX(x+w-1);
        bottomright.setY(y+h-1);
        // setGeometry(x,y,w,h);
    }
    
    /**
     * @brief Initializes the data of the rectangle
     * @param x XY Coordinates of top-left corner
     * @param y
     * @param w Width of the rectangle
     * @param h Height of the rectangle
     */
    void setGeometry(int x, int y, int w, int h) {
        topleft.setX(x);
        topleft.setY(y);
        bottomright.setX(x+w);
        bottomright.setY(y-h);
    }
    /**
     * @brief Initializes the data of the rectangle
     * @param tl Top-left point
     * @param br Bottom-right corner
     */
    void setGeometry(const Point2D &tl, const Point2D &br) {
        topleft = tl;
        bottomright = br;
    }
    /**
     * @brief Queries the top-left corner
     * @return The point
     */
    Point2D getTopLeft() const {
        return topleft;
    }
    /**
     * @brief Queries the bottom-right corner
     * @return The point
     */
    Point2D getBottomRight() const {
        return bottomright;
    }
    /**
     * @brief For a rectangle to be valid this condition must hold
     * topleft.getX() \< = bottomright.getX() && topleft.getY() \> = bottomright.getY()
     * otherwise it is an empty (incorrect) rectangle
     * @return Whether the rectangle is empty or not
     */
    bool isEmpty() const {
        return topleft.getX()>bottomright.getX() || topleft.getY() < bottomright.getY();
    }
    /**
     * @brief Reads the two points of the rectangle
     */
    void read() {
        topleft.read();
        bottomright.read();
    }
    /**
     * @brief Prints the rectangle in the form [Point2D - Point2D]
     */
    
    void print() const{
        cout << "[";
        topleft.print();
        cout << " - ";
        bottomright.print();
        cout << "] ";
    }
/**
 * @brief Calculates the rectangle intersection of the two given rectangles.
 * If there is no intersection, an empty rectangle is returned instead
 * @param r1 One rectangle
 * @param r2 Other rectangle
 * @return The rectangle given by the intersection of @p r1 and @p r2
 * @note This is an external function to the class Rectangle but since it
 * is also friend, this function is allowed access to private data/methods
 */    
    friend Rectangle doOverlap(const Rectangle & r1, const Rectangle &r2);

};


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

/**
 * @brief Calculates whether a point is internal to a rectangle
 * @param p The point
 * @param r The rectangle
 * @return @retval true if @p p is inscribed within @p r, @retval false otherwise
 */
bool isInside(const Point2D &p, const Rectangle &r) {
    return r.getTopLeft().getX() <= p.getX() && p.getX()<=r.getBottomRight().getX() &&
           r.getTopLeft().getY() >= p.getY() && p.getY()>=r.getBottomRight().getY(); 
}

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

