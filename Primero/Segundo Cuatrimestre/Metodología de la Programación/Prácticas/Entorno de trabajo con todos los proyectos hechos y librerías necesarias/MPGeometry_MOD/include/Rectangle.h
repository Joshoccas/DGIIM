/** 
 * @file Rectangle.h
 * @author lcv
 * @date 16 de enero de 2020, 20:04
 */
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point2D.h"
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
    Rectangle();
    /**
     * @brief Constructor with parameters
     * @param x XY Coordinates of top-left corner
     * @param y
     * @param w Width of the rectangle
     * @param h Height of the rectangle
     */
    Rectangle(int x, int y, int w, int h);
    /**
     * @brief Initializes the data of the rectangle
     * @param x XY Coordinates of top-left corner
     * @param y
     * @param w Width of the rectangle
     * @param h Height of the rectangle
     */
    void setGeometry(int x, int y, int w, int h);
    /**
     * @brief Initializes the data of the rectangle
     * @param tl Top-left point
     * @param br Bottom-right corner
     */
    void setGeometry(const Point2D &tl, const Point2D &br);
    /**
     * @brief Queries the top-left corner
     * @return The point
     */
    Point2D getTopLeft() const;
    /**
     * @brief Queries the bottom-right corner
     * @return The point
     */
    Point2D getBottomRight() const;
    /**
     * @brief For a rectangle to be valid this condition must hold
     * topleft.getX() \< = bottomright.getX() && topleft.getY() \> = bottomright.getY()
     * otherwise it is an empty (incorrect) rectangle
     * @return Whether the rectangle is empty or not
     */
    bool isEmpty() const;
    /**
     * @brief Reads the two points of the rectangle
     */
    void read();
    /**
     * @brief Prints the rectangle in the form [Point2D - Point2D]
     */
    void print() const;
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

/**
 * @brief Calculates whether a point is internal to a rectangle
 * @param p The point
 * @param r The rectangle
 * @return @retval true if @p p is inscribed within @p r, @retval false otherwise
 */
bool isInside(const Point2D &p, const Rectangle &r);



#endif /* RECTANGLE_H */

