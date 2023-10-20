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
        int (*funcion) (int, int);
    } operacion;

    bool isOperator(char c);
    bool isOperator(std::string c);   // sobrecarga!

    bool isNumber(char c);
    bool isNumber(std::string c);

    bool isVariable(char c);
    bool isVariable(std::string c);

    int pemdas(std::string c);

    int suma(int a, int b);
    int resta(int a, int b);
    int mult(int a, int b);
    int div(int a, int b);
    int potencia(int a, int b);
    
} /* namespace calc */

#endif // _UTILS_HPP