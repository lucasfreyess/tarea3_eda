#include "calculator/calculator.hpp"

int main()
{
    trees::ABB abbtree;
    std::map <std::string, int> map_variables;
    
    calc::Calculator calculadora;

    calculadora.menu(abbtree, map_variables);

    //std::cout << "\nen main: \n";

    //std::cout << "valor asignado de x: " << map_variables["x"] << "\n\n";

    return 0;
}