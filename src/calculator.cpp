#include "calculator/calculator.hpp"
#include "calculator/utils.hpp"
#include "lLists/stack.hpp"
#include <iostream>

namespace calc
{
    void Calculator::menu(trees::ABB &abbtree, std::map <std::string, int> &map_variables)
    {
        std::cout << "=======================\n";
        std::cout << "CALCULADORA INTERACTIVA\n";
        std::cout << "=======================\n";

        while(1)
        {
            std::string input;
            std::getline(std::cin, input);

            if (input == "FIN" || input == "fin" || input == "Fin")
            {
                break;
            }

            else if (input == "tree")
            {
                abbtree.updateSize();
                abbtree.traverse();
            }

            else if (input.find("=") != std::string::npos)  // entonces probablemente se le esta asignando un valor a una variable (e.g., x = 6). 
            {
                assign_value(input, map_variables);
            }
            else  // entonces probablemente se ingreso una expresion, por lo que hay que hacer un arbol de esta, y calcular el resultado
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

                abbtree.clearAll();

                trees::ABBNode* new_root = abbtree.insert_postfix(vector_postfix);
                abbtree.insertNode(new_root);

                map_variables["ans"] = stoi(solvePostfix(vector_postfix, map_variables));
                std::cout << "ans = " << map_variables["ans"] << "\n\n";
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
        std::cout << "valor asignado: " << map_variables[aux_s] << "\n\n";
    }

    std::vector<std::string> Calculator::infixToPostfix(std::string s)
    {
        lLists::Stack stack;
        
        std::vector <std::string> vector_input;
        std::vector <std::string> vector_resultado;

        std::string big_number;

        for (int i = 0; i < s.length(); i++)
        {
            // si es que hay un 'ans' en el string, entonces se agrupa y se inserta en vector_input
            if (s[i] == 'a' && s[i + 1] == 'n')
            {
                std::string aux_s;
                aux_s += s[i];
                aux_s += s[i + 1];
                aux_s += s[i + 2];

                vector_input.push_back(aux_s);
                continue;
            }
            else if ( (s[i - 1] == 'a' && s[i] == 'n') || (s[i - 1] == 'n' && s[i] == 's') )
            {
                continue;
            }

            if (isNumber(s[i]))   
            {
                if (isNumber(s[i + 1]))   // es suficiente para poder distinguir un numero que posee mas de un digito
                {
                    // ademas, esto ocurre para todos los digitos, menos el ultimo
                    big_number += s[i];
                }

                if (s[i + 1] == ' ' || (i == s.length() - 1))
                {
                    // esto ocurre para el ultimo digito de un numero con mas de un digito
                    big_number += s[i];
                    vector_input.push_back(big_number);

                    big_number = "";
                }
            }
            else {
                std::string aux_s;
                aux_s = s[i];
                vector_input.push_back(aux_s);
            }
        }

        /*
        std::cout << "\nvector_input: ";
        for (int i = 0; i < vector_input.size(); i++)
        {
            std::cout << vector_input[i];

            if (i != vector_input.size() - 1)
            {
                std::cout << ",";
            }
        }
        std::cout << "\n";
        */

        for (int i = 0; i < vector_input.size(); i++)
        {
            std::string c = vector_input[i];

            if ( (c >= "a" && c <= "z") || (c >= "A" && c <= "Z") || (c >= "0" && c <= "9") )
            {
                vector_resultado.push_back(c);
            }
            else if (c == "(")
            {
                stack.push(c);
            }
            else if (c == ")")
            {
                while (stack.top()->getData() != "(")
                {
                    vector_resultado.push_back(stack.top()->getData());
                    stack.pop();
                }

                stack.pop();
            }
            else if (c == " ")  // ocurre cuando c es un espacio
            {
                continue;
            }
            else   // ocurre cuando c es un operador
            {    
                //char aux_top = (stack.top()->getData())[0];
                //std::cout << "aux_top: " << aux_top << std::endl;
                //std::string aux_s(1, c);    // constructor de string que permite especificar el tamano de c, y luego c, para convertirlo a string
                
                while (!stack.isEmpty() && pemdas(c) <= pemdas(stack.top()->getData()) )
                {
                    vector_resultado.push_back(stack.top()->getData());
                    stack.pop();
                }

                stack.push(c);
            }
        }

        while (!stack.isEmpty())
        {
            vector_resultado.push_back(stack.top()->getData());
            stack.pop();
        }

        return vector_resultado;
    }

    std::string Calculator::solvePostfix(std::vector <std::string> vector_postfix, std::map<std::string, int> map_variables)
    {
        lLists::Stack stack;

        operacion ff[] = {{"+", suma},
                          {"-", resta},
                          {"*", mult},
                          {"/", div},
                          {"^", potencia}};

        for (int i = 0; i < vector_postfix.size(); i++)
        {
            if (isOperator(vector_postfix[i]))
            {
                int valor_derecho;
                int valor_izquierdo;

                bool derecho_es_variable = false;
                bool izquierdo_es_variable = false;

                std::string operando_derecho = stack.top()->getData();
                stack.pop();

                std::cout << "operando derecho: " << operando_derecho << "\n";

                std::string operando_izquierdo = stack.top()->getData(); 
                stack.pop();

                std::cout << "operando izquierdo: " << operando_izquierdo << "\n";

                if (isVariable(operando_derecho))
                {
                    int valor_derecho = map_variables[operando_derecho];
                    derecho_es_variable = true;
                }
                if (isVariable(operando_izquierdo))
                {
                    int valor_izquierdo = map_variables[operando_izquierdo];
                    izquierdo_es_variable = true;
                }

                std::cout << "valor_izquierdo: " << valor_izquierdo << std::endl;

                for (int j = 0; j < 4; j++)
                {
                    if (vector_postfix[i] == ff[j].operador)
                    {

                        if (izquierdo_es_variable && derecho_es_variable)
                        {
                            int resultado = ff[j].funcion(valor_izquierdo, valor_derecho);
                            stack.push(std::to_string(resultado));
                        }
                        else if (!izquierdo_es_variable && derecho_es_variable)
                        {
                            int resultado = ff[j].funcion(stoi(operando_izquierdo), valor_derecho);
                            stack.push(std::to_string(resultado));
                        }
                        else if (izquierdo_es_variable && !derecho_es_variable)
                        {
                            std::cout << "q wea !!!\n"; 

                            int resultado = ff[j].funcion(valor_izquierdo, stoi(operando_derecho));
                            std::cout << "resultado: " << resultado << "\n";
                            stack.push(std::to_string(resultado));
                        }
                        else if (!izquierdo_es_variable && !derecho_es_variable)
                        {
                            int resultado = ff[j].funcion(stoi(operando_izquierdo), stoi(operando_derecho));
                            stack.push(std::to_string(resultado));
                        }

                        break;
                    }
                }
            }

            else {
                stack.push(vector_postfix[i]);
            }
        }

        return stack.top()->getData(); // solo queda un item en el stack: la respuesta de la expresion postfija !!
    }

    Calculator::Calculator(int ans)
    {
        this->ans = ans;
        //this->test = test;
    }

    Calculator::~Calculator() 
    {}

}