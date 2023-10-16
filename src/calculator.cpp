#include "calculator/calculator.hpp"
#include "lLists/stack.hpp"
#include <iostream>


namespace calc
{
    int pemdas(std::string c)      
    {
        if (c == "^")
            return 3;

        else if (c == "/" || c == "*")
            return 2;

        else if (c == "+" || c == "-")
            return 1;

        else   
            return -1;
    }

    void Calculator::menu(std::map <std::string, int> &map_variables)
    {
        std::cout << "=======================\n";
        std::cout << "CALCULADORA INTERACTIVA\n";
        std::cout << "=======================\n";

        while(1)
        {
            std::string input;
            std::getline(std::cin, input);

            if (input == "adios")
            {
                break;
            }

            //std::cout << "input: " << input << "\n";
            std::cout << "input: " << std::endl;
            for (int i = 0; i < input.length(); i++)
            {
                std::cout << "[" << i << "]: " << input[i] << std::endl;  
            }
            std::cout << std::endl;

            if (input.find("="))  // entonces probablemente se le esta asignando un valor a una variable (e.g., x = 6)
            {
                std::cout << "alo sans\n";
                std::string aux_s(1, input[0]);
                map_variables[aux_s] = input[input.length()];  // asumiendo que el ultimo caracter de input es un numero
            }
            else  // entonces probablemente se ingreso una expresion, por lo que hay que calcular el resultado
            {     
                std::vector <std::string> vector_postfix = infixToPostfix(input);
            }
            //std::cout << "output: " << std::endl;
            //for (int i = 0; i < vector_postfix.size(); i++)
            //{
            //    std::cout << "[" << i << "]: " << vector_postfix[i] << std::endl;
            //}

        }
    }

    std::vector<std::string> Calculator::infixToPostfix(std::string s)
    {
        lLists::Stack stack;
        std::string resultado;
        
        for (int i = 0; i < s.length(); i++)
        {
            char c = s[i];

            //std::cout << "c: " << c << std::endl;

            if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') )
            {
                resultado += c;
            }
            else if (c == '(')
            {
                std::string aux_s = "(";
                stack.push(aux_s);
            }
            else if (c == ')')
            {
                while (stack.top()->getData() != "(")
                {
                    resultado += stack.top()->getData();
                    stack.pop();
                }

                stack.pop();
            }
            else if (c == ' ')  // ocurre cuando c es un espacio
            {
                continue;
            }
            else   // ocurre cuando c es un operador
            {    
                //char aux_top = (stack.top()->getData())[0];
                //std::cout << "aux_top: " << aux_top << std::endl;
                std::string aux_s(1, c);    // constructor de string que permite especificar el tamano de c, y luego c, para convertirlo a string
                
                while (!stack.isEmpty() && pemdas(aux_s) <= pemdas( (stack.top()->getData()) ))
                {
                    resultado += stack.top()->getData();
                    stack.pop();
                }

                stack.push(aux_s);
            }
        }

        while (!stack.isEmpty())
        {
            resultado += stack.top()->getData();
            //std::cout << "stack: " << stack.top()->getData() << ", ";
            stack.pop();
        }
        //std::cout << std::endl;

        std::vector <std::string> vector_resultado;

        //std::cout << "resultado length: " << resultado.length() << std::endl;

        for (int i = 0; i < resultado.length(); i++)
        {   
            char char_final = resultado[resultado.length()];

            //std::cout << "[" << i << "]: " << resultado[i] << std::endl;

            if (resultado[i] == 'a' && resultado[i + 1] == 'n')
            {
                std::string aux_s;
                aux_s += resultado[i];
                aux_s += resultado[i + 1];
                aux_s += resultado[i + 2];

                vector_resultado.push_back(aux_s);
                continue;
            }
            else if ( (resultado[i - 1] == 'a' && resultado[i] == 'n') || (resultado[i - 1] == 'n' && resultado[i] == 's') )
            {

                continue;
            }

            std::string aux_s(1, resultado[i]);

            //std::cout << "AAAAAAAAA [" << i << "]: " << aux_s << std::endl;

            vector_resultado.push_back(aux_s);
        }

        return vector_resultado;
    }

    Calculator::Calculator(int ans)
    {
        this->ans = ans;
        //this->test = test;
    }

    Calculator::~Calculator() 
    {}

}