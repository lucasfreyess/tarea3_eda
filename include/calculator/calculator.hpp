/*
 * calculator.hpp
 *
 *  creado para manejar las funciones relacionadas al calculo de expresiones postfijas!
 * 
 */

#ifndef _CALCULATOR_HPP
#define _CALCULATOR_HPP

#include "trees/abb.hpp"
#include <map>

namespace calc
{
    class Calculator
    { 
        private:
            void assignValue(std::string input, std::map <std::string, double> &map_variables);
            std::vector<std::string> infixToPostfix(std::string); // devuelve un vector compuesto de la expresion posfija.
            std::string solvePostfix(std::vector <std::string> vector_postfix, std::map<std::string, double> &map_variables);

        public:
            void menu(trees::ABB &abbtree, std::map <std::string, double> &map_variables);
            
            Calculator();
            ~Calculator();  
    };
} /* namespace calc */

#endif // _CALCULATOR_HPP