#include <iostream>
#include "trees/abb.hpp"
#include "calculator/calculator.hpp"
#include <map>

int main()
{
    trees::ABB abbtree;
    std::map <std::string, int> map_variables;
    //std::map <std::string, int>::iterator iterador_map = map_variables.begin();

    calc::Calculator calculadora(0);

    calculadora.menu(abbtree, map_variables);

    //std::cout << "\nen main: \n";

    //std::cout << "valor asignado de x: " << map_variables["x"] << "\n\n";

    //abbtree.updateSize();
    //abbtree.traverse();

    //while (iterador_map != map_variables.end())
    //{
    //    std::cout << "Llave: " << iterador_map->first << "\nValor: " << iterador_map->second << std::endl;
    //   iterador_map++;
    //}

    return 0;
}