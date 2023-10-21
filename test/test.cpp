#include "calculator/calculator.hpp"

int main()
{
    trees::ABB abbtree;
    std::map <std::string, double> map_variables;
    calc::Calculator calculadora;

    calculadora.menu(abbtree, map_variables);

    return 0;
}