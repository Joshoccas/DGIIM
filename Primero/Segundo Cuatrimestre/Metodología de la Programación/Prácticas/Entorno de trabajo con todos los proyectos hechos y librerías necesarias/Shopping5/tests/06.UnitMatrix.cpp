/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <string>
#include "DateTime.h"
#include "Event.h"
#include "EventSet.h"
#include "Index.h"
#include "gtest/gtest.h"
#include "MPTests.h"
#include <cmath>
#include "datatools.h"
#define private public
#include "Matrix.h"

using namespace std;

// https://docs.google.com/document/d/1NvaD4JTlby1MA_pjVpXO7_dova0_-b6uVa55hAjzTSo/edit
#define NDEC 5 
double estoMeLoRedondeas(double d) {
    int base = (int) pow(10,NDEC);
    int aux  = (int)(round(d*base));
    
    return aux*1.0/base;
}
TEST_F(_01_Basics, Matrix_Base_Constructor) {
    Matrix m;

    SKIP_ASSERT_EQ_R(0, m._ncols) << "A newly created instance of Matrix must have 0 columns" << endl;
    SKIP_ASSERT_EQ_R(0, m._nrows) << "A newly created instance of Matrix must have 0 rows" << endl;
    bool ptrok = (m._data == nullptr);
    SKIP_ASSERT_TRUE_R(ptrok) << "A newly created instance must have the pointer safely initialized to nullptr" << endl;
}

TEST_F(_01_Basics, Matrix_Parameter_Constructor) {
    size_t nrows = 10;
    size_t ncols = 5;
    Matrix m1(nrows, ncols);
    SKIP_ASSERT_EQ_R(ncols, m1.columns()) << "A newly created instance of Matrix must have " << ncols << " columns" << endl;
    SKIP_ASSERT_EQ_R(nrows, m1.rows()) << "A newly created instance of Matrix must have " << nrows << " rows" << endl;

    bool ok = true;
    double defValue = 0;

    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if (m1._data[i][j] != defValue) {
                ok = false;
            }
        }
    }

    SKIP_ASSERT_TRUE_R(ok) << "A newly created instance of Matrix must have every value initialize to " << defValue << endl;

    defValue = -7;
    Matrix m3(nrows, ncols, defValue);
    SKIP_ASSERT_EQ_R(ncols, m3.columns()) << "A newly created instance of Matrix must have " << ncols << " columns" << endl;
    SKIP_ASSERT_EQ_R(nrows, m3.rows()) << "A newly created instance of Matrix must have " << nrows << " rows" << endl;

    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if (m3._data[i][j] != defValue) {
                ok = false;
            }
        }
    }

    SKIP_ASSERT_TRUE_R(ok) << "A newly created instance of Matrix must have every value initialize to " << defValue << endl;
}

//TEST_F(_01_Basics, Matrix_Deallocate){
//    Matrix m (10, 10, -7);
//    m.deallocate();
//    
//    SKIP_ASSERT_EQ_R(0, m._ncols) << "A deallocated instance of Matrix must have 0 columns" << endl;
//    SKIP_ASSERT_EQ_R(0, m._nrows) << "A deallocated instance of Matrix must have 0 rows" << endl;
//    bool ptrok = (m._data == nullptr);
//    SKIP_ASSERT_TRUE_R(ptrok) << "A deallocated instance must have the pointer safely initialized to nullptr" << endl;
//}

TEST_F(_01_Basics, Matrix_Copy_Constructor) {
    size_t nrows = 10;
    size_t ncols = 5;
    double defValue = 2;
    Matrix m1(nrows, ncols, defValue);

    Matrix m2(m1);
    SKIP_ASSERT_EQ_R(m1.columns(), m2.columns()) << "A newly created instance of Matrix as a copy of another instance must have " << m1.columns() << " columns" << endl;
    SKIP_ASSERT_EQ_R(m1.rows(), m2.rows()) << "A newly created instance of Matrix as a copy of another instance must have " << m1.rows() << " rows" << endl;

    bool ok = true;

    for (int i = 0; i < m2._nrows; i++) {
        for (int j = 0; j < m2._ncols; j++) {
            if (m1._data[i][j] != m2._data[i][j]) {
                ok = false;
            }
        }
    }

    SKIP_ASSERT_TRUE_R(ok) << "A newly created instance of Matrix must have the same values as the given Matrix" << endl;
}

////TEST_F(_01_Basics, Matrix_Destructor){
////    if(true){
////        Matrix m(10,0), m2(m);
////        
////        m.deallocate();
////        // Se ha quedado todo a 0
////        bool cambia = (m._data != m2._data);
////    }
////    // Aquí es cuándo se llama al destructor
////}
//

TEST_F(_01_Basics, Matrix_At) {
    int f = 10, c = 5;
    double init = -1;
    Matrix m(f, c), m2(f, c, init);
    double d = -100;

    SKIP_ASSERT_EQ_R(0, m.at(0, 0)) << "A newly created instance of Matrix must all its values to 0" << endl;
    SKIP_ASSERT_EQ_R(init, m2.at(0, 0)) << "A newly created instance of Matrix must all its values to defvalue" << endl;

    for (int row = 0; row < f; row++) {
        for (int col = 0; col < c; col++) {
            SKIP_ASSERT_EQ_R(init, m2.at(row, col)) << "A newly created instance of Matrix must all its values to defvalue" << endl;
        }
    }

    for (d = -100; d < 100; d += 10) {
        m.at(0, 0) = d;
        SKIP_ASSERT_EQ_R(d, m.at(0, 0)) << "Changing the value of a row and column must be correct" << endl;
    }

    Matrix toy(f, c);
    for (int row = 0; row < f; row++) {
        for (int col = 0; col < c; col++) {
            toy.at(row, col) = row + col;
        }
    }
    for (int row = 0; row < f; row++) {
        for (int col = 0; col < c; col++) {
            SKIP_ASSERT_EQ_R(row + col, toy.at(row, col)) << "A newly created instance of Matrix must all its values to defvalue" << endl;
        }
    }
}

//TEST_F(_03_Advanced, Matrix_At_Advanced){
//    int f = 5;
//    int c = 2;
//    double defValue = 2.1, real;
//    Matrix m (f, c, defValue);
//    
//    real = m.at(f+1, c);    
//    SKIP_ASSERT_EQ_R(v_npos, real) << "Accessing out of bounds returns a negative value" << endl;
//    
//    real = m.at(f, c+1);    
//    SKIP_ASSERT_EQ_R(v_npos, real) << "Accessing out of bounds returns a negative value" << endl;
//}

TEST_F(_01_Basics, Matrix_Resize) {

    size_t nrows = 10;
    size_t ncols = 5;
    double defValue = 1.2;

    Matrix m1;
    m1.resize(nrows, ncols, defValue);

    SKIP_ASSERT_EQ_R(ncols, m1.columns()) << "Resized instance of Matrix must have " << ncols << " columns" << endl;
    SKIP_ASSERT_EQ_R(nrows, m1.rows()) << "Resized instance of Matrix must have " << nrows << " rows" << endl;

    bool ok = true;

    for (int i = 0; i < m1.rows(); i++) {
        for (int j = 0; j < m1.columns(); j++) {
            if (m1._data[i][j] != defValue) {
                ok = false;
            }
        }
    }

    SKIP_ASSERT_TRUE_R(ok) << "Resized instance of Matrix must have every value to " << defValue << endl;
}

TEST_F(_01_Basics, Matrix_Clear) {
    Matrix m(5, 3, 5.4);
    m.clear();

    SKIP_ASSERT_EQ_R(0, m.columns()) << "Cleared Matrix must have 0 columns" << endl;
    SKIP_ASSERT_EQ_R(0, m.rows()) << "Cleared Matrix must have 0 rows" << endl;
    bool ptrok = m._data == nullptr;
    SKIP_ASSERT_TRUE_R(ptrok) << "Cleared Matrix must have the pointer safely initialized to nullptr" << endl;

    SKIP_ASSERT_EQ_R(0, m._rowLabels.size()) << "Size of a cleared Matrix's rowLabels must be 0" << endl;
    SKIP_ASSERT_EQ_R(0, m._rowLabels.getIOnWhich()) << "The cleared Matrix's rowLabels must be indexed by UserID" << endl;

    SKIP_ASSERT_EQ_R(0, m._colLabels.size()) << "Size of a cleared Matrix's colLabels must be 0" << endl;
    SKIP_ASSERT_EQ_R(0, m._colLabels.getIOnWhich()) << "The cleared Matrix's colLabels must be indexed by UserID" << endl;
}

TEST_F(_01_Basics, Matrix_Brakets_Operator) {
    int f = 10, c = 5;
    double init = -1;
    Matrix m(f, c);
    Matrix m2(f, c, init);
    double d = -100;

    SKIP_ASSERT_EQ_R(0, m(0, 0)) << "A newly created instance of Matrix must all its values to 0" << endl;
    SKIP_ASSERT_EQ_R(init, m2(0, 0)) << "A newly created instance of Matrix must all its values to defvalue" << endl;

    for (int row = 0; row < f; row++) {
        for (int col = 0; col < c; col++) {
            SKIP_ASSERT_EQ_R(init, m2(row, col)) << "A newly created instance of Matrix must all its values to defvalue" << endl;
        }
    }

    m(0, 0) = d;
    SKIP_ASSERT_EQ_R(d, m(0, 0)) << "Changing the value of a row and columns must be correct" << endl;

    Matrix toy(f, c);
    for (int row = 0; row < f; row++) {
        for (int col = 0; col < c; col++) {
            toy(row, col) = row + col;
        }
    }
    for (int row = 0; row < f; row++) {
        for (int col = 0; col < c; col++) {
            SKIP_ASSERT_EQ_R(row + col, toy(row, col)) << "A newly created instance of Matrix must all its values to defvalue" << endl;
        }
    }
}

TEST_F(_02_Intermediate, Matrix_at_intermediate) {
    const double NPOS = -1;
    const int DIM = 3;

    const string ROW_LABELS[DIM] = {"A", "B", "C"};
    const string COL_LABELS[DIM] = {"D", "E", "F"};

    Matrix matrix(ROW_LABELS, DIM, COL_LABELS, DIM);

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            matrix.at(i, j) = i + j;

    /*
     Matrix:
     *    D E F
     *    -----
     *  A|0 1 2
     *  B|1 2 3
     *  C|2 3 4
     */

    // TEST: Correct access to each matrix's element by its labels.

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++) {
            SKIP_ASSERT_EQ_R(i + j, matrix.at(ROW_LABELS[i], COL_LABELS[j]))
                    << "Accesing an element by its LABELS should give "
                    << "its value.";
        }


    // TEST: Correct modification of each matrix's element by its labels.

    /*
     Modified matrix:
     *    D E F
     *    -----
     *  A|0 0 0
     *  B|0 0 0 
     *  C|0 0 0
     */

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++) {
            matrix.at(ROW_LABELS[i], COL_LABELS[j]) = 0;
            SKIP_ASSERT_EQ_R(0, matrix.at(ROW_LABELS[i], COL_LABELS[j]))
                    << "Modifying an element by its LABELS should change "
                    << "its value.";
        }

    // TEST: Accessing a bad value throws npos.

    const Matrix matrix2(ROW_LABELS, DIM, COL_LABELS, DIM, 0);

    double bad_value = matrix2.at("AS", "FG"); // An invalid position.

    SKIP_ASSERT_EQ_R(NPOS, bad_value) << "Accesing "
            << "an invalid position should throw npos. ";


}

TEST_F(_02_Intermediate, Matrix_op_brackets_intermediate) {
    const double NPOS = -1;
    const int DIM = 3;

    const string ROW_LABELS[DIM] = {"A", "B", "C"};
    const string COL_LABELS[DIM] = {"D", "E", "F"};

    Matrix matrix(ROW_LABELS, DIM, COL_LABELS, DIM);

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            matrix.at(i, j) = i + j;

    /*
     Matrix:
     *    D E F
     *    -----
     *  A|0 1 2
     *  B|1 2 3
     *  C|2 3 4
     */

    // TEST: Correct access to each matrix's element by its labels.

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++) {
            SKIP_ASSERT_EQ_R(i + j, matrix(ROW_LABELS[i], COL_LABELS[j]))
                    << "Accesing an element by its LABELS should give "
                    << "its value.";
        }


    // TEST: Correct modification of each matrix's element by its labels.

    /*
     Modified matrix:
     *    D E F
     *    -----
     *  A|0 0 0
     *  B|0 0 0 
     *  C|0 0 0
     */

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++) {
            matrix.at(ROW_LABELS[i], COL_LABELS[j]) = 0;
            SKIP_ASSERT_EQ_R(0, matrix(ROW_LABELS[i], COL_LABELS[j]))
                    << "Modifying an element by its LABELS should change "
                    << "its value.";
        }

    // TEST: Accessing a bad value throws npos.

    const Matrix matrix2(ROW_LABELS, DIM, COL_LABELS, DIM, 0);

    double bad_value = matrix2("AS", "FG"); // An invalid position.

    SKIP_ASSERT_EQ_R(NPOS, bad_value) << "Accesing "
            << "an invalid position should throw npos. ";


}

TEST_F(_02_Intermediate, Operator_assign) {

    int f = 10, c = f;

    double d1 = 352, d2 = 12.56;

    Matrix m1(f, c, d2), m2, m3(1, c, d2);
    Matrix m(f, c, d1);

    m = m2;

    SKIP_ASSERT_EQ_R(0, m.rows()) << " Assigning a null matrix to a matrix matches the number of rows" << endl;
    SKIP_ASSERT_EQ_R(0, m.columns()) << " Assigning a null matrix to a matrix matches the number of cols" << endl;

    /* No encuentro la version SKIP_ASSERT_NE_R */
    ASSERT_NE_R(nullptr, m._data) " Assigning a null matrix to a matrix point nullptr" << endl;

    m = m1;

    SKIP_ASSERT_EQ_R(f, m.rows()) << " Assigning one matrix to a null matrix match its number or rows" << endl;
    SKIP_ASSERT_EQ_R(c, m.columns()) << " Assigning one matrix to a null matrix match its number or cols" << endl;

    for (int i = 0; i < f; i++)
        for (int j = 0; i < c; i++) {
            SKIP_ASSERT_EQ_R(d2, m(i, j)) << " Assigning one matrix to another match all its values" << endl;
        }

    ASSERT_NE_R(m1._data, m._data) " Assigning one matrix to another don't point the same memory directory" << endl;

    double ** dat = m._data;

    m = m;

    SKIP_ASSERT_EQ_R(dat, m._data) " Assigning one matrix to the itself doesn't change the pointer memory directory" << endl;
}

TEST_F(_02_Intermediate, Operator_add_assign) {

    int f = 10, c = f;

    double d1 = 352, d2 = 12.56;

    Matrix m(f, c, d1);

    double ** dat = m._data;

    m += d2;

    SKIP_ASSERT_EQ_R(f, m.rows()) << " Adding a number to a matrix doesn't modify the number of rows" << endl;
    SKIP_ASSERT_EQ_R(c, m.columns()) << " Adding a number to a matrix doesn't modify the number of cols" << endl;

    for (int i = 0; i < f; i++)
        for (int j = 0; i < c; i++) {
            SKIP_ASSERT_EQ_R(d1 + d2, m(i, j)) << " Adding a number to a matrix change all its elements" << endl;
        }

    SKIP_ASSERT_EQ_R(dat, m._data) " Adding a number to a matrix doesn't change the pointer memory directory" << endl;
}

TEST_F(_02_Intermediate, Matrix_operator_product_assign) {

    int f = 3, c = 3;

    Matrix m(f, c), m2(f, c);

    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            m.at(i, j) = i * 2 - j;
            m2.at(i, j) = i * 2 - j;
        }
    }
    int val = 5;

    m2 *= val;


    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            SKIP_ASSERT_TRUE_R(m2.at(i, j) == m.at(i, j) * val) << "Using *= operator must multiply each element by val" << endl;
        }
    }
}

TEST_F(_02_Intermediate, Matrix_operator_ProductMatrix) {
    Matrix m1(3, 4, 1);
    Matrix m2(4, 2, 5);
    Matrix m3(1, 1, 1);


    //La matriz resultante debe tener fil de la matriz m1 y cols de m2
    Matrix m4(m1 * m2);
    SKIP_ASSERT_EQ_R(m1.rows(), m4.rows())
            << "The first matrix and the product do not have the same number"
            << " of rows." << endl;
    SKIP_ASSERT_EQ_R(m2.columns(), m4.columns())
            << "The second matrix and the product do not have the same number"
            << " of colums." << endl;

    // No multiplica matrices con dimensiones incorrectas. Todos elem a npos (3x3)
    Matrix m5(m1 * m3);
//    for (int r = 0; r < m5.rows(); r++)
//        for (int c = 0; c < m5.columns(); c++) {
//            SKIP_ASSERT_EQ_R(v_npos, m5.at(r, c)) << "The product of incorrect"
//                    << " dimensions does not have npos" << endl;
//        }

    // Cada posiciÃ³n (i,j) debe ser producto escalar de la fila i de la matriz
    // this y la columna j de la matriz m.
//    for (int r = 0; r < m4.rows(); r++)
//        for (int c = 0; c < m4.columns(); c++) {
//            int product = 0;
//
//            for (int i = 0; i < m1.columns(); i++)
//                product += m1.at(r, i) * m2.at(i, c);
//
//
//            SKIP_ASSERT_EQ_R(product, m4.at(r, c))
//                    << "The product of matrix is incorrect" << endl;
//        }
}

TEST_F(_02_Intermediate, Matrix_operator_ProductNumber) {
    int rows = 3;
    int cols = 4;
    int val = 7;
    Matrix m1(rows, cols, 2.5);
    Matrix m2(m1 * val);

    // La matriz resultante debe tener el mismo tamaÃ±o.
    SKIP_ASSERT_EQ_R(m1.rows(), m2.rows())
            << "The original matrix and the multiplied do not have the "
            << "same number of rows" << endl;
    SKIP_ASSERT_EQ_R(m1.columns(), m2.columns())
            << "The original matrix and the multiplied do not have the "
            << "same number of rows" << endl;

    // Cada elemento debe ser igual al original * val
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            SKIP_ASSERT_EQ_R(m1.at(r, c) * val, m2.at(r, c));
        }

}

TEST_F(_02_Intermediate, Matrix_operator_SumNumber) {
    int rows = 3;
    int cols = 4;
    int val = 7;
    Matrix m1(rows, cols, 2.5);
    Matrix m2(m1 + val);

    // La matriz resultante debe tener el mismo tamaÃ±o.
    SKIP_ASSERT_EQ_R(m1.rows(), m2.rows())
            << "The original matrix and the multiplied do not have the "
            << "same number of rows" << endl;
    SKIP_ASSERT_EQ_R(m1.columns(), m2.columns())
            << "The original matrix and the multiplied do not have the "
            << "same number of rows" << endl;

    // Cada elemento de la matriz nueva debe incrementar su valor en val
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            SKIP_ASSERT_EQ_R(m1.at(r, c) + val, m2.at(r, c));
        }

}


TEST_F(_03_Advanced, Matrix_Brakets_Operator){
    int f = 5;
    int c = 2;
    double defValue = 2.1;
    double real;
    Matrix m(f, c, defValue);
    
    real = m(f+1, c);    
    SKIP_ASSERT_EQ_R(v_npos, real) << "Accessing out of bounds returns a negative value" << endl;
    
    real = m(f, c+1);    
    SKIP_ASSERT_EQ_R(v_npos, real) << "Accessing out of bounds returns a negative value" << endl;
}

TEST_F(_03_Advanced, Matrix_constructor) {
    
    int f = 5, c = 5, init = -1;

    string rowLabels [] = {"pato", "perro", "pantera", "gato", "delfin"};
    string colLabels [] = {"jirafa", "leon", "tigre", "ballena", "loro"};
    string modificable[10];
    
    Matrix m1(rowLabels, f, colLabels, c);
    Matrix m2(rowLabels, f, colLabels, c, init);

    SKIP_ASSERT_EQ_R(f, m1.rows()) << " The number of rows in the matrix must be the one introduced in the constructor" << endl;
    SKIP_ASSERT_EQ_R(c, m1.columns()) << " The number of columns in the matrix must be the one introduced in the constructor" << endl;
    
    SKIP_ASSERT_EQ_R(f, m1.getRowLabels(modificable)) << " The number of entries in the row index must be the number of rows introduced in the constructor" << endl;
    SKIP_ASSERT_EQ_R(c, m1.getColLabels(modificable)) << " The number of entries in the col index must be the number of columns introduced in the constructor" << endl;
    
    for (int i = 0; i < c; i++) {
        SKIP_ASSERT_EQ_R(rowLabels[i], m1.labelAtRow(i)) << " Labels at rows must be the same that the labels introduced" << endl;
    }
    
    for (int i = 0; i < f; i++) {
        SKIP_ASSERT_EQ_R(colLabels[i], m1.labelAtCol(i)) << " Labels at columns must be the same that the labels introduced" << endl;
    }
    
    for (int i = 0; i < f; i++)
        
        for (int j = 0; j < c; j++) {
            
            SKIP_ASSERT_EQ_R(m1.at(i,j), 0) << " The value set by default should be 0" << endl;
            SKIP_ASSERT_EQ_R(m2.at(i,j), init) << " Value introduced in the constructor must be set in the matrix " << endl;
            
        }
}

TEST_F(_03_Advanced, Matrix_labelAtCol) {

    int f = 5, c = 5;

    string colLabels [] = {"salado", "dulce", "agrio", "amargo", "umami"};

    Matrix m(colLabels, f, colLabels, c);

    for (int col = 0; col < c; col++) {
        SKIP_ASSERT_EQ_R(colLabels[col], m.labelAtCol(col)) << " Label at column col must be equal to labelAtCol(col)" << endl;
    }
}



TEST_F(_03_Advanced, Matrix_labelAtRow) {

    int f = 5, c = 5;

    string rowLabels [] = {"F", "I", "Br", "Hg", "N"};
    string colLabels [] = {"Si", "Mn", "Be", "Ca", "Pb"};

    Matrix m(rowLabels, f, colLabels, c);

    for (int row = 0; row < f; row++) {
        SKIP_ASSERT_EQ_R(rowLabels[row], m.labelAtRow(row)) << " Label at row must be equal to labelAtRow(row)" << endl;
    }

}

TEST_F(_03_Advanced, rowIndexOf) {
   
    string rowLabels[] = {"B", "C", "A"};
    string colsLabels[] = {"Y", "Z", "X"};

    Matrix m (rowLabels, 3, colsLabels, 3);
    
    string label = "B";
//    SKIP_ASSERT_EQ_R(1, m.rowIndexOf(label)) << "Given a label, it must return the associated row" << endl;
   
    label = "T";
    static const int npos = -1;
//    SKIP_ASSERT_EQ_R(npos, m.rowIndexOf(label)) << "It must returns Matrix::npos if the label is not in the Matrix" << endl;
}

TEST_F(_03_Advanced, Matrix_ColIndexOf) {
    int r=11, c=7;
    string rowlabels [] = {"tesla", "audi", "mercedes", "bmw", "ferrari", "porsche", "bugatti", "lamborghini", "rolls royce", "mustang", "jaguar"};
    string collabels [] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
    
    Matrix m (rowlabels, r, collabels, c);
    
//    SKIP_ASSERT_EQ_R(m.colIndexOf(collabels[4]), 0) << "Given a label of a column, it must return the associated column" << endl;
    
//    SKIP_ASSERT_EQ_R(m.colIndexOf("tesla"), -1) << "Consulting for the column of which the label does not exist must return -1" << endl;
}

TEST_F(_03_Advanced, Matrix_getRowLabels){
    
    int f = 5, c = 5;
    
    string rowLabels [] = {"platano","manzana","fresa","pera","uva","sandia","melocoton","melon","cereza","kiwi"};
    string modificable[10];
    
    Matrix m(rowLabels, f, rowLabels, c);
    
    SKIP_ASSERT_EQ_R(f, m.getRowLabels(modificable)) << "n must be equal to getRowLabels" << endl;
}



TEST_F(_03_Advanced, Matrix_getColLabels) {


    //Para una matriz vacía el labels sale con su nullptr y el metodo nos da 0
    Matrix m;
    string labels[10];
    SKIP_ASSERT_TRUE_R(m.getColLabels(labels) ==  0 ) << "Getting the labels from an empty matrix should return 0" ;

    //Montamos una matriz 1xn, con labels en las columnas de la forma L-i
    //Y una sola label en la fila
    int n=3;

    string Clabels[3];
    for(int j=0; j<n; j++)
    {
        Clabels[j]= "L-"+to_string(j);
    }

    string Rlabels[1];
    Rlabels[0]= "LabelRow";

    Matrix m2(Rlabels, 1, Clabels, n, 1);
    SKIP_ASSERT_TRUE_R(m2.getColLabels(labels) ==  n ) << "Getting the labels from a 1x3 matrix should return 3" ;
    for(int j=0; j<3; j++)
    {
        SKIP_ASSERT_TRUE_R(labels[j]== "L-"+to_string(j)) << "The element " << j << "in labels is incorrect" ;
    }

}

TEST_F(_03_Advanced, Matrix_Operator) {
    int r=10, c=5;
    
    string rowLabels [] = {"calculus", "homomorphism", "set", "polynomial", "symmetrical", "spline", "eigenvalue", "kernel", "summation", "angle"};
    string colLabels [] = {"hyperplane", "tensor", "variance", "intersection", "factorial"};
    
    Matrix m(rowLabels, r, colLabels, c);
    
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            SKIP_ASSERT_EQ_R(m.at(i,j), m(i,j)) << "Value at column col and row r must be equal to m(i,j)" << endl;
        }
    }
    
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            SKIP_ASSERT_EQ_R(m.at(i,j), m(rowLabels[i],colLabels[j])) << "Value at column colIndexOf[colLabels[i]] and row rowIndexOf[rowLabels[i]] must be equal to m(rowLabels[i],colLabels[j])" << endl;
        }
    }
}

TEST_F(_03_Advanced, Matrix_Normalize) {
    int r=7, c=9;
    
    Matrix m(r, c);
    
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            double d = i/(j+1);
            m(i,j)=d;
        }
    }
    
    m.normalize();
    
    for (int i=0; i<r; i++) {
        long double sum_row=0;
        for (int j=0; j<c; j++) {
            sum_row+=m(i,j);
        }
        
        if (sum_row < 1)
            sum_row += 0.000000001;
        
        if (!(sum_row >= 1.000000001))
                sum_row = 1;
                    
        SKIP_ASSERT_EQ_R(sum_row, 1) << "The sum of all the values in a single row must be 1" << endl;
    }
}