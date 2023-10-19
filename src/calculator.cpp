#include "calculator/calculator.hpp"
#include "lLists/stack.hpp"
#include <iostream>

namespace calc
{
    //x + x * 2 + ans

    void postorder(trees::ABBNode* root)
    {
        postorder(root->getLeft());
        postorder(root->getRight());

        std::cout << root->getData();
    }

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

    void Calculator::menu(trees::ABB &abbtree, std::map <std::string, int> &map_variables)
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
            //std::cout << "input: " << std::endl;
            //for (int i = 0; i < input.length(); i++)
            //{
            //    std::cout << "[" << i << "]: " << input[i] << std::endl;  
            //}
            //std::cout << std::endl;

            if (input.find("=") != std::string::npos)  // entonces probablemente se le esta asignando un valor a una variable (e.g., x = 6). 
            {
                assign_value(input, map_variables);
            }
            else  // entonces probablemente se ingreso una expresion, por lo que hay que calcular el resultado
            {     
                std::vector <std::string> vector_postfix = infixToPostfix(input);
                
                
                std::cout << "\npostfix: ";
                for (int i = 0; i < vector_postfix.size(); i++)
                {
                    if (i == vector_postfix.size() - 1)
                    {
                        std::cout << vector_postfix[i];
                    }
                    else {
                        std::cout << vector_postfix[i] << ",";
                    }
                }
                std::cout << "\n\n";

                /*    
                //for (int i = vector_postfix.size() - 1; i >= 0; i--)  // empieza desde el valor final de vector_postfix
		        //{
                //    std::string val = vector_postfix[i];
                //    abbtree.insert(val);
                //}
                */

                abbtree.clearAll();

                trees::ABBNode* new_root = abbtree.insert_postfix(vector_postfix);
                abbtree.insertNode(new_root);
            }
        }
    }

    void Calculator::assign_value(std::string input, std::map <std::string, int> &map_variables)
    {
        std::string aux_s(1, input[0]);
        std::string valor;

        for (int j = input.find("=") + 2; j < input.length(); j++)    // asumiendo q existe un espacio entre '=' y el primer caracter del valor, input.find("=") + 2 es el primer caracter.
        {
            valor += input[j];
        }

        //if (valor > std::to_string(INT32_MAX))
        //{
        //    std::cout << "El valor ingresado es muy grande !! Intentalo de nuevo.\n\n";
        //    return;
        //}

        std::cout << "variable: " << aux_s << std::endl;
        std::cout << "valor: " << stoi(valor) << "\n";

        map_variables[aux_s] = stoi(valor);
        std::cout << "valor asignado: " << map_variables["x"] << "\n\n";
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
                
                while (!stack.isEmpty() && pemdas(aux_s) <= pemdas(stack.top()->getData()) )
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
            stack.pop();
        }

        std::vector <std::string> vector_resultado;

        for (int i = 0; i < resultado.length(); i++)
        {   
            char char_final = resultado[resultado.length()];

            //std::cout << "[" << i << "]: " << resultado[i] << std::endl;

            // NECESARIO: agregar condicion sobre: 
            // para la siguiente expresion postfija: x,1,0,+,x,5,*,+
            // es necesario agrupar el "x,1,0,+..." en "x,10,+...", ya que sino no hace sentido

            // para ello, existen dos casos:  (el operador da lo mismo)
            //  1.- el orden es "x,1,0,+...". 
            //  2.- el orden es "1,0,x,+...". En este, es importante que se diga que i > 0

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