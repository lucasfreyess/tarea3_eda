#ifndef _CALCULATOR_HPP
#define _CALCULATOR_HPP

#include "trees/abb.hpp"
#include <string>
#include <vector>
#include <map>

namespace calc
{
    class Calculator
    {
        private:
            int ans;
            //std::string test;

        public:
            //int pemdas(std::string); // jerarquia de operaciones
            void menu(trees::ABB &abbtree, std::map <std::string, int> &map_variables);
            void assign_value(std::string input, std::map <std::string, int> &map_variables);
            std::vector<std::string> infixToPostfix(std::string); // devuelve un vector compuesto de la expresion posfija. Es capaz de distinguir "ans"

            //Calculator(int ans, std::string test);
            Calculator(int ans);
            ~Calculator();
            
    };
}
#endif