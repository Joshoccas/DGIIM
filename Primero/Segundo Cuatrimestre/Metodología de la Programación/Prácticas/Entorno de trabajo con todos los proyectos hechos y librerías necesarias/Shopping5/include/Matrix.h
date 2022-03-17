/**
 * @file Matrix.h
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 * 
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>

#include "Index.h"

class Matrix {
public:

    static const int npos = -1;
    /**
     * Default constructor 
     * Creates a matrix with 0 rows and 0 columns
     */
    Matrix();

    /**
     * Copy constructor, makes this matrix a copy of org
     * @param orig
     */
    Matrix(const Matrix& orig);

    /**
     * Creates a 2D   unlabeled matrix with size r x c, being all its setted to the defValue
     * @param r number of rows
     * @param c number of cols
     * @param defValue value used to initialize all the elements in the matrix
     */
    Matrix(size_t r, size_t c, double defValue = 0.0);

    /** Creates a 2D labeled matrix with size nrows x ncols, being all its setted to the defValue.
     * The rows/columns are labeles using the values in rowLabels/colsLabels in such a way that
     * the  row 0 is labeled with rowLabels[0], the row 1 is labeled with rowLabel[1] and so on.
     * Similarly criteria is used in columns.
     * In case of error we get the default matrix
     * 
     * @param rowLabels 
     * @param nrows
     * @param colsLabels
     * @param ncols
     * @param defValue
     * @pre It is assumed that rowLabels/colsLabels have enough memory to store at least nrows/ncols labels.
     */
    Matrix(const std::string *rowLabels, size_t nrows, const std::string * colsLabels, size_t ncols, double defValue = 0.0);

    /**
     * Destructor
     */
    virtual ~Matrix();

    /************************************************/
    /****** Consultors ******************************/
    /************************************************/

    /**
     * Number of columns
     * @return number of columnos
     */
    size_t columns()const;
    /**
     * Number of rows
     * @return number of rows
     */

    size_t rows() const;
    /**
     *  Element at M[row][col]. Also check that row and col are valid positions in M
     * @param row
     * @param col
     * @return reference to the element at M[row][col]
     */
    const double & at(size_t row, size_t col) const;
    /**
     * Element at M[row][col].  
     * @param row
     * @param col
     * @return reference to the element at M[row][col]
     */
    const double & operator()(size_t row, size_t col) const;
    /**
     * Element at M[rowLabel][colLabel]. Also check that row and col are valid positions in M
     * @param row
     * @param col
     * @return reference to the element at M[rowLabel][colLabel]
     */
    const double & at(const std::string & rowLabel, const std::string & colLabel) const;
    /**
     * Element at M[rowLabel][colLabel].  
     * @param row
     * @param col
     * @return reference element at M[rowLabel][colLabel]
     */
    const double & operator()(const std::string & rowLabel, const std::string & colLabel) const;
    /**
     * Gives the label associated to the row in the matrix
     * @param row number of the row
     * @return the associated label
     */
    std::string labelAtRow(size_t row) const;

    /**
     * Gives the label associated to the column col in the matrix
     * @param col number of the column
     * @return the associated label
     */
    std::string labelAtCol(size_t col) const;
    /**
     * Given a label, return its associated row
     * @param the label
     * @return the number of the row
     */
    int getRowLabels(std::string *) const;
    /**
     * Given a label, return its associated column
     * @param the label
     * @return the number of the column
     */
    int getColLabels(std::string *) const;
    /**
     * Return the row number
     * @param label
     * @return     row associated to the label. It return Matrix::npos if the label is not in the Matrix
     */
    int rowIndexOf(const std::string & label) const;

    /**
     * Return the col number
     * @param label
     * @return     col associated to the label. It return Matrix::npos if the label is not in the Matrix
     */
    int colIndexOf(const std::string & label) const;
    /**
     *  Element at M[row][col]. No check is done
     * @param row
     * @param col
     * @return reference to the element at M[row][col]
     */
    double & at(size_t row, size_t col);
    /**
     *  Element at M[row][col]. No check is done
     * @param row
     * @param col
     * @return reference to the element at M[row][col]
     */
    double & operator()(size_t row, size_t col);
    /**
     * Element at M[rowLabel][colLabel]. No check is done
     * @param row
     * @param col
     * @return reference to the element at M[rowLabel][colLabel]
     */
    double & at(const std::string & rowLabel, const std::string & colLabel);

    /**
     * Element at M[rowLabel][colLabel]. No check is done
     * @param row
     * @param col
     * @return reference to the element at M[rowLabel][colLabel]
     */
    double & operator()(const std::string & rowLabel, const std::string & colLabel);
    /**
     * Change the size of the matrix to nrows x ncols initializing all its value to defValue
     * @param nrows
     * @param ncols
     * @param defValue by default it is used the value 0.0
     */
    void resize(size_t nrows, size_t ncols, double defValue = 0.0);
    /**
     * Change the size of the matrix to nrows x ncols initializing all its value to vdef. The rows/columns are labeled with rowLabels/colLabels. 
     * In case of error set the default matrix
     * @param nrows
     * @param ncols
     * @param vdef vauled used  by default it is used the value 0.0
     * 
     * @param rowLabels string array containing the label of the rows (this string is assumed to have length nrows)
     * @param colLabels string array containing the label of the columns (this string is assumed to have length ncols)
     * 
     */
    void resize(const std::string * rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double vdef = 0);
    /**
     * Set the matrix to the defaul values
     */
    void clear();
    /**
     * Modify the values in the matrix in such a way that for each row, the sum of all its elements is 1.0
     * @return 
     */
    Matrix & normalize();
    /**
     * Assign  new contents to the matrix, replacing its current contents, and modifying its size accordingly.
     * @param m the source matrix
     * @return reference to the matrix
     */
    Matrix & operator=(const Matrix & m);
    /**
     * Multiply each element in the matrix by val
     * @param val
     * @return reference to the matrix
     */
    Matrix & operator*=(double val);
    /**
     * Add a constan value to each element in the matrix
     * @param val
     * @return reference to the matrix
     */
    Matrix & operator+=(double val);
    /**
     * Matrix multiplication.                                               It check that *this and m have the proper dimensions 
     * @param m a matrix object  
     * @return a new matrix containing  (*this) x M
     * @precond The dimensions must be correct BEFORE calling this method
     */
    Matrix operator*(const Matrix & m) const;
    /**
     * Multiply   the matrix by a constant val
     * @param val
     * @return a new matrix with the values M x val
     */
    Matrix operator*(double val) const;
    /**
     * Add val to each element
     * @param val
     * @return a new matrix with values M+val
     */
    Matrix operator+(double val) const;
    
   
    
    // INPUT / OUTPUT 
    /**
     * Save the matrix in a file in the following format
     *
#matrix labeled|unlabeled
number_of_rows number_of_columns
[labelr1 labelr2 label_nrows]
[labelc1 labelc2 label_ncols]
[0][0]....m[0][ncols]
m[1][0]....m[1][ncols]
...
m[nrows][0] ...m[nrows][ncols]

     *      * 
     * where the first line use the magic word "#matrix" and indicates whether the matrix is labeled or unlabeled
     * in the case the matrix has no labels at rows and columns the third and four lines are empty
     * 
     * For example
     * 
#matrix labeled
2 2
A B
X Y
1 2
3 4
 
#matrix unlabeled
2 2
1.2 2.2
3.2 4.2

 *      
 * @param filename name of the file
 */
    void save(const std::string & filename) const;
    /**
     * Load a matrix from the file filename
     * It is assumed  that the file has the format above, otherwise the performace is undefined
     * @param filename
     */
    void load(const std::string & filename);

    friend std::ostream & operator<<(std::ostream & os, const Matrix & m);
  
    friend Matrix operator+(double ival, const Matrix & dch);
    friend Matrix operator*(double ival, const Matrix & dch);


private:


    int getLabels(const Index & idx, std::string *labels)const;
    bool setLabels(Index & idx, const std::string *labels, int nlabels);
    /**
     * Free the memory allocated for the matrix, i.e., pointed by _data.
     * @post _data is set to nullptr 
     */
    void deallocate();
    /**
     * Set all the values in the matrix to the value (by default 0.0)
     * @param value
     */
    void setValues(double value = 0.0);

    double ** _data;
    Index _rowLabels;
    Index _colLabels;

    size_t _nrows;
    size_t _ncols;

};
/**
 * Return a new matrix obtained by computing: val + M
 * 
 * @param ival
 * @param dch
 * @return resulting matrix
 */
Matrix operator+(double ival, const Matrix & M);
/**
 *  Return a new matrix obtained by computing: val * M
 * @param ival
 * @param M
 * @return resulting matrix
 */
Matrix operator*(double ival, const Matrix & M);

/** Insert the data representing the matrix into the ostream os with the following format
 * 
number_of_rows number_of_columns
[labelr1 labelr2 label_nrows]
[labelc1 labelc2 label_ncols]
m[0][0]....m[0][ncols]
m[1][0]....m[1][ncols]
...
m[nrows][0] ...m[nrows][ncols]
 
 * @param os output stream
 * @param m the matrix object
 * @return 
 */
 std::ostream & operator<<(std::ostream & os, const Matrix & m);
 
 extern double v_npos;
 extern const double c_npos;
#endif /* MATRIX_H */

