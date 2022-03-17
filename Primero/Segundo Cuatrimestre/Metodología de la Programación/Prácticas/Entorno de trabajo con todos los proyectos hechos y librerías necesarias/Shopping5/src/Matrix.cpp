/**
 * @file Matrix.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 * 
 */

#include "Matrix.h"
#include <fstream>
#include <assert.h>

double v_npos = Matrix::npos;
const double c_npos = Matrix::npos;

using namespace std;

/**
 * @brief Copies the values in a 2D matrix org with nrows and ncols to an also 2D matrix dest.
 * It is assumed that org and dest have the memory properly allocated 
 * @param dest destination matrix
 * @param org  source matrix
 * @param nrows number of rows
 * @param ncols number of cols
 */
void copy(double **dest, double **org, size_t nrows, size_t ncols) {
    
    for(int i = 0; i < nrows; i++){
        
        for(int j = 0; j < ncols; j++){
            
            dest[i][j] = org[i][j];
        }
    }
}

/** 
 * @brief this method reserve memory to allocate a 2D matrix of size r x c.
 * @param r number of rows
 * @param c number of cols
 * @return the pointer to the memory block containing the data
 */
double ** allocate(size_t r, size_t c) {
    double ** block;
    
    block = new double*[r];
    
    for(int i = 0; i < r; i++)
        block[i] = new double[c];
    
    return block;
}

/**
 * @brief In this method, given an index idx it returns the key in the position i, 
 * such that i is the first position in the index such that idx.at(i).getPos()==p
 * @param idx the input index
 * @param p number of 
 * @return the key for first position i in the index such that idx.at(i).getPos()==p
 */
string labelWithValuePosInIndex(const Index & idx, size_t p) {
    string salida;

    bool enc = false;
    for (int i = 0; i < idx.size(); i++) {
        if(idx.at(i).getPos() == p) {
            salida = idx.at(i).getKey();
            enc = true;
        }
    }
    return salida;
}

void Matrix::deallocate(){
    
    if(_data != nullptr){
        for(int i = 0; i < _nrows; i++)
            delete[] _data[i];

        delete[] _data;
        _data = nullptr;
    }
    
    _nrows = 0;
    _ncols = 0;
    _rowLabels.clear();
    _colLabels.clear();
}


Matrix::Matrix(){
    
    _nrows = 0;
    _ncols = 0;
    _data = nullptr;
    _rowLabels.clear();
    _colLabels.clear();
}

void Matrix::setValues(double valor){
     
    for(int i = 0; i < _nrows; i++){
        
        for(int j = 0; j < _ncols; j++){
            _data[i][j] = valor;
        }
    }
}



Matrix::Matrix(size_t f, size_t c, double vdef){
    
    _nrows = f;
    _ncols = c;
    _data = allocate(f,c);
    _rowLabels.clear();
    _colLabels.clear();
        
    setValues(vdef);
}

Matrix::Matrix(const Matrix& orig){
    
    _data = allocate(orig.rows(),orig.columns());
    _nrows = orig.rows();
    _ncols = orig.columns();
    
    for(int i = 0; i < _nrows; i++){
        
        for(int j = 0; j < _ncols; j++){
            _data[i][j] = orig.at(i,j);
        }
    }
    
    _rowLabels = orig._rowLabels;
    _colLabels = orig._colLabels;
}

Matrix::Matrix(const std::string *rowLabels, size_t nrows, const std::string * colsLabels, size_t ncols, double value){
    
    if((nrows >= 1)&&(ncols >= 1)){
        _nrows = nrows;
        _ncols = ncols;
        _rowLabels.clear();
        _colLabels.clear();
        _data = allocate(nrows,ncols);
        setLabels(_rowLabels, rowLabels, nrows);
        setLabels(_colLabels, colsLabels, ncols);
        setValues(value);
    }
    else
        Matrix();
}



std::string Matrix::labelAtRow(size_t row) const{
    return labelWithValuePosInIndex(_rowLabels, row);
}

std::string Matrix::labelAtCol(size_t col) const{
    return labelWithValuePosInIndex(_colLabels, col);
}

void Matrix::resize(size_t nrows, size_t ncols, double value){
   
    deallocate();
    _data = allocate(nrows,ncols);
    _nrows = nrows;
    _ncols = ncols;
    
    setValues(value);
}

void Matrix::resize(const std::string * rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double value){
    
    if((nrows >= 1)&&(ncols >= 1)){
        
        deallocate();
        _data = allocate(nrows,ncols);
        _nrows = nrows;
        _ncols = ncols;
        
        
        setLabels(_rowLabels, rowLabels, nrows);
        setLabels(_colLabels, colLabels, ncols);

        setValues(value);
    }
}

void Matrix::clear(){
    
    deallocate();
    _nrows = 0;
    _ncols = 0;
   
}

Matrix::~Matrix(){
    
    clear();
}

double & Matrix::at(size_t f, size_t c){
    
    if (((f >= 0)&&(f < _nrows))&&((c >= 0)&&(c < _ncols)))
        return _data[f][c];
    else
        return v_npos;
}

const double & Matrix::at(size_t f, size_t c) const{
    
    if (((f >= 0)&&(f < _nrows))&&((c >= 0)&&(c < _ncols)))
        return _data[f][c];
    else
        return v_npos;
}

double & Matrix::operator()(size_t f, size_t c){

    return (at(f,c));
}

const double & Matrix::operator()(size_t f, size_t c) const{

    return (at(f,c));
}

int Matrix::rowIndexOf(const std::string & label) const{
    
    bool encontrado = false;
    int resultado;
    
    for(int i = 0; (i < _nrows)&&!encontrado; i++){
        
        if(_rowLabels.at(i).getKey() == label){
            encontrado = true;
            resultado = i;
        }
    }
    
    if(encontrado)
        return resultado;
    else
        return npos;
}

int Matrix::colIndexOf(const std::string & label) const{
    
    bool encontrado = false;
    int resultado;
    
    for(int i = 0; (i < _ncols)&&!encontrado; i++){
        
        if(_colLabels.at(i).getKey() == label){
            encontrado = true;
            resultado = i;
        }
    }
    
    if(encontrado)
        return resultado;
    else
        return npos;
}

double & Matrix::at(const std::string & rowLabel, const std::string & colLabel){
  
    int f = rowIndexOf(rowLabel);
    int c = colIndexOf(colLabel);
    
    if((f == -1)||(c == -1))
        return v_npos;
    else
        return _data[f][c];
}

double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel){
   
    return(at(rowLabel, colLabel));
}

const double & Matrix::at(const std::string & rowLabel, const std::string & colLabel)const{
    
   int f = rowIndexOf(rowLabel);
   int c = colIndexOf(colLabel);
    
   if((f == -1)||(c == -1))
       return v_npos;
   else
       return _data[f][c];
}

const double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel)const{
  
    return (at(rowLabel, colLabel));
}

ostream & operator<<(ostream & flujo, const Matrix& m){
   
    flujo << m.rows() << " " << m.columns() << "\n";
    
    for(int i = 0; i < m.rows(); i++)
        flujo << m._rowLabels.at(i).getKey() << " ";
    
    flujo << "\n";
    
    for(int j = 0; j < m.columns(); j++)
        flujo << m._colLabels.at(j).getKey() << " ";
    
    flujo << "\n";
    
    for(int i = 0; i < m.rows(); i++){
        
        for(int j = 0; j < m.columns(); j++)
            flujo << m.at(i,j) << " ";
        
        flujo << "\n";
    }
    
    return flujo;
}

Matrix & Matrix::operator=(const Matrix& m){
    
    if(&m != this){
        
        this->deallocate();
        this->_nrows = m.rows();
        this->_ncols = m.columns();
        this->_data = allocate(m.rows(),m.columns());
        
        for(int i = 0; i < m.rows(); i++){
            
            for(int j = 0; j < m.columns(); j++)
                this->at(i,j) = m.at(i,j);
        }
        
        this->_rowLabels = m._rowLabels;
        this->_colLabels = m._colLabels;
    }
    
    return *this;
}

bool Matrix::setLabels(Index & idx, const string * labels, int nlabels){
     idx.clear();
    int lb,ub;
    bool correct = true;
    for (int i=0; i< nlabels && correct; i++){
        lb = idx.lower_bound(labels[i]);
        ub = idx.upper_bound(labels[i]);
        if (lb==ub) { // it is NOT in the set
            idx.add(Pair(labels[i],i));
        } else {
            correct = false;
         }
    }
    if (!correct) idx.clear();
    return correct;
 }

int Matrix::getLabels(const Index & idx, string * labels) const{
    if (idx.size() > 0) {
        for (int i = 0; i < idx.size(); i++) {
            labels[i] = idx.at(i).getKey();
        }
    }
    return idx.size();
}

int Matrix::getRowLabels(string * labels) const{
    return getLabels(_rowLabels,labels);
}

int Matrix::getColLabels(string *labels) const{
    return getLabels(_colLabels,labels);
}

size_t Matrix::columns() const{
    return _ncols;
}

size_t Matrix::rows() const{
    return _nrows;
}

//uncomment
void Matrix::save(const string & nf) const{
    ofstream fsal(nf);
    if (fsal.is_open()) {
        fsal << "#matrix "; 
        if (_rowLabels.size()==0)
            fsal << "unlabeled"<< endl;
        else fsal << "labeled" << endl;
        fsal << *this;
        fsal.close();
    } else cerr << "Fail creating " << nf << " file" <<endl;
}

void Matrix::load(const string & nf) {
    ifstream fent(nf);
    string labeled, cad;
    clear();
    if (fent.is_open()) {
         fent >> cad >> labeled;
         fent >> _nrows >> _ncols;
         if (labeled == "labeled"){
            for (int i=0;i<_nrows;i++){
                fent >> cad;
                _rowLabels.add(Pair(cad,i));
            }
             for (int i=0;i<_ncols;i++){
                fent >> cad;
                _colLabels.add(Pair(cad,i));
            }
        }
        _data = allocate(_nrows,_ncols); 
        for (int i = 0; i < _nrows; i++) {
            for (int j = 0; j < _ncols; j++) {
                fent >> _data[i][j];
            }
        }
        fent.close();
    } else cerr << "Fail reading " << nf << " file" <<endl;
}

Matrix & Matrix::operator*=(double val){
   
    for(int i = 0; i < this->rows(); i++){
        
        for(int j = 0; j < this->columns(); j++)
            this->at(i,j) *= val;
    }
    
    return *this;
}

Matrix & Matrix::operator+=(double val){
    
    for(int i = 0; i < this->rows(); i++){
        
        for(int j = 0; j < this->columns(); j++)
            this->at(i,j) += val;
    }
    
    return *this;
}

Matrix Matrix::operator*(const Matrix & m) const{
   
    if(_ncols == m.rows()){
        Matrix resultado(_nrows,m.columns());

        resultado._rowLabels = _rowLabels;
        resultado._colLabels = m._colLabels;

        double suma = 0;

        for(int i = 0; i < _nrows; i++){

            for(int j = 0; j < m.columns(); j++){

                for(int k = 0; k < _ncols ; k++)
                    suma+= at(i,k)*m.at(k,j);

                resultado.at(i,j) = suma;
                suma = 0;
            }
        }
        
        return resultado;
    }
    else{
        Matrix resultado(_nrows,_ncols,v_npos);
        return resultado;
    }
        
}

Matrix Matrix::operator+(double val) const{
    
    Matrix resultado(*this);
    
    for(int i = 0; i < resultado.rows(); i++){
        
        for(int j = 0; j < resultado.columns(); j++)
            resultado.at(i,j) += val;
    }
    
    return resultado;
}

Matrix Matrix::operator*(double val) const{
    
    Matrix resultado(*this);
    
    for(int i = 0; i < resultado.rows(); i++){
        
        for(int j = 0; j < resultado.columns(); j++)
            resultado.at(i,j) *= val;
    }
    
    return resultado;
}

Matrix operator+(double ival, const Matrix & dch){
  
    Matrix resultado(dch);
    
    for(int i = 0; i < resultado.rows(); i++){
        
        for(int j = 0; j < resultado.columns(); j++)
            resultado.at(i,j) += ival;
    }
    
    return resultado;
}

Matrix operator*(double ival, const Matrix & dch){
   
    Matrix resultado(dch);
    
    for(int i = 0; i < resultado.rows(); i++){
        
        for(int j = 0; j < resultado.columns(); j++)
            resultado.at(i,j) *= ival;
    }
    
    return resultado;
}

Matrix & Matrix::normalize(){

    double suma_fila = 0;
    
    for(int i = 0; i < _nrows; i++){
        
        for(int j = 0; j < _ncols; j++)
            suma_fila += at(i,j);
        
        if(suma_fila == 0){
            for(int j = 0; j < _ncols; j++)
                at(i,j) = 1.0/_ncols;
        }
        else{
            for(int j = 0; j < _ncols; j++)
                at(i,j) = at(i,j)/suma_fila;
        }
        
        
        suma_fila = 0;
    }
    
    return *this;
}