/*
 * utils.hpp 
 * 
 *  posee funciones de utilidad, destinadas para facilitar el calculo en solvePostfix() (calculator.cpp)
 *  y determinar si un string es un operador, numero o variable !
 * 
 */

#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <string>
#include <cmath>

namespace calc 
{
    // struct de posibles operaciones para ahorrarse
    // condiciones if/else en solvePostfix()
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

    int pemdas(std::string c);  // determina orden de operaciones (utilizado en infixToPostfix en calculator.cpp)

    double suma(double a, double b);
    double resta(double a, double b);
    double mult(double a, double b);
    double div(double a, double b);
    double potencia(double a, double b);
    
} /* namespace calc */

#endif // _UTILS_HPP