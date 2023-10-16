#include <iostream>
#include "trees/abb.hpp"
#include "calculator/calculator.hpp"
#include <map>

int main()
{
    std::map <std::string, int> map_variables;
    std::map <std::string, int>::iterator iterador_map = map_variables.begin();

    calc::Calculator calculadora(0);

    calculadora.menu(map_variables);

    std::cout << "me voy a matar:1!!\n";

    while (iterador_map != map_variables.end())
    {
        std::cout << "Llave: " << iterador_map->first << "\nValor: " << iterador_map->second << std::endl;
        iterador_map++;
    }

    
    /*
    std::string infix = "x+x*2+ans";
    std::vector <std::string> postfix_vector = calculadora.infixToPostfix(infix);

    std::cout << "infix: " << infix << std::endl;
    std::cout << "postfix: ";

    for (int i = 0; i < postfix_vector.size(); i++)
    {
        std::cout << postfix_vector[i];
    }
    std::cout << std::endl << std::endl;
    std::cout << "infix length: " << infix.length() << std::endl;
    std::cout << "postfix length: " << postfix_vector.size() << "\n";
    */

    return 0;
}