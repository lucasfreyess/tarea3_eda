#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <string>
#include <cmath>

namespace calc 
{
    //struct de posibles operaciones para ahorrarse
    //condiciones if en solvePostfix() de la clase calculator!!
    typedef struct operacion  
    {
        std::string operador;
        double (*funcion) (double, double);
    } operacion;

    bool isOperator(char c);
    bool isOperator(std::string c);   // sobrecarga!

    bool isNumber(char c);
    bool isNumber(std::string c);

    bool isVariable(char c);
    bool isVariable(std::string c);

    int pemdas(std::string c);

    double suma(double a, double b);
    double resta(double a, double b);
    double mult(double a, double b);
    double div(double a, double b);
    double potencia(double a, double b);
    
} /* namespace calc */

#endif // _UTILS_HPP