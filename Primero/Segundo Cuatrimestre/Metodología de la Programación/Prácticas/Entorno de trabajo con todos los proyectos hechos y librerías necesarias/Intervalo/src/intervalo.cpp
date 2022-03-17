/** 
 * @file   intervalo.cpp
 * @author decsai.ugr.es
 *
 */


#include <iostream>
#include <assert.h>
#include "intervalo.h"
using namespace std;

bool Intervalo::validar(double cotaInferior, double cotaSuperior, 
        bool cerradoInferior, bool cerradoSuperior)
{
    bool valido = false;
        
    if(cotaInferior < cotaSuperior)
        valido = true;
    else{
            
        if((cotaInferior == cotaSuperior) && 
                (cerradoInferior == cerradoSuperior))
            valido = true;
    }
        
    return(valido);
}
    
Intervalo::Intervalo()
    :cotaInf(7), cotaSup(7), cerradoInf(false), cerradoSup(false)
{}
    
Intervalo::Intervalo(double cinf, double csup)
{
    assert (validar(cinf,csup, true, true));
	cotaInf = cinf;
	cotaSup = csup;
	cerradoInf = true;
	cerradoSup = true;
}


Intervalo::Intervalo(double cinf, double csup, 
        bool cerradoInferior, bool cerradoSuperior)
{
    assert (validar(cinf,csup, cerradoInferior, cerradoSuperior));
	cotaInf = cinf;
	cotaSup = csup;
	cerradoInf = cerradoInferior;
	cerradoSup = cerradoSuperior;
}

double Intervalo::getCotaInf() const
{
    return(cotaInf);
}

double Intervalo::getCotaSup()const
{
    return(cotaSup);
}

bool Intervalo::esCerradoInf()const
{
    return(cerradoInf);
}

bool Intervalo::esCerradoSup()const
{
    return(cerradoSup);
}

bool Intervalo::esVacio()const
{
    bool es_vacio = false;
    
    if ((cotaInf == cotaSup) && !cerradoInf && !cerradoSup)
        es_vacio = true;
    
    return(es_vacio);
}

bool Intervalo::estaDentro(double n)const 
{
    bool esta_dentro = false;
    
    if ((n == cotaInf) && cerradoInf)
        
        esta_dentro = true;
    
    else if ((cotaInf < n) && (n < cotaSup))
        
        esta_dentro = true;
    
    else if ((n == cotaSup) && cerradoSup)
        
        esta_dentro = true;
    
    return(esta_dentro);
};

void escribir(const Intervalo &i)
{
    if (i.esCerradoInf() && i.esCerradoSup())
        
        cout << "[" << i.getCotaInf() << "," << i.getCotaSup() << " ]";
    
    else if (i.esCerradoInf() && !i.esCerradoSup())
        
        cout << "[" << i.getCotaInf() << "," << i.getCotaSup() << " )";
    
    else if (!i.esCerradoInf() && i.esCerradoSup())
        
        cout << "(" << i.getCotaInf() << "," << i.getCotaSup() << " ]";
    
    else if (!i.esCerradoInf() && !i.esCerradoSup())
        
        cout << "(" << i.getCotaInf() << "," << i.getCotaSup() << " )";
}

void leer(Intervalo &i)
{
    char cerInf;
    double cinf;
    char coma;
    double csup;
    char cerSup;
        
    cin >> cerInf;
    cin >> cinf;
    cin >> coma;
    cin >> csup;
    cin >> cerSup;
        
    if ((cerInf == '[')&&(cerSup == ']')){
            
        Intervalo j(cinf,csup);
        i = j;
    }
        
    else if ((cerInf == '[')&&(cerSup == ')')){
            
        Intervalo j(cinf, csup, true, false);
        i = j;
    }
        
    else if ((cerInf == '(')&&(cerSup == ']')){
            
        Intervalo j(cinf, csup, false, true);
        i = j;
    }
        
    else if ((cerInf == '(')&&(cerSup == ')')){
            
        Intervalo j(cinf, csup, false, false);
        i = j;
    }
}
