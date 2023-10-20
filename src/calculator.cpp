#include "calculator/calculator.hpp"
#include "calculator/utils.hpp"
#include "lLists/stack.hpp"
#include <iostream>

namespace calc
{
    void Calculator::menu(trees::ABB &abbtree, std::map <std::string, double> &map_variables)
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

            else if (input == "tree" || input == "Tree")
            {
                abbtree.updateSize();
                abbtree.traverse();
            }

            else if (input.find("=") != std::string::npos)  // entonces se le esta asignando un valor a una variable (e.g., x = 6). 
            {
                assignValue(input, map_variables);
            }
            else  // entonces probablemente se ingreso una expresion, por lo que hay que hacer un arbol de esta, y calcular el resultado
            {     
                std::vector <std::string> vector_postfix = infixToPostfix(input);
                
                abbtree.clearAll();

                trees::ABBNode* new_root = abbtree.insertPostfix(vector_postfix);
                abbtree.insertNode(new_root);

                map_variables["ans"] = stod(solvePostfix(vector_postfix, map_variables));  // stod: string to double
                std::cout << "ans = " << map_variables["ans"] << "\n";
            }
        }
    }

    void Calculator::assignValue(std::string input, std::map <std::string, double> &map_variables)
    {
        std::string aux_s(1, input[0]);
        std::string valor;

        // asumiendo que existe un espacio entre '=' y el primer caracter
        // del valor, input.find("=") + 2 es el primer caracter.
        for (int j = input.find("=") + 2; j < input.length(); j++)    
        {
            valor += input[j];
        }

        map_variables[aux_s] = stod(valor);   // stod: string-to-double
    }

    std::vector<std::string> Calculator::infixToPostfix(std::string s)
    {
        lLists::Stack stack;
        
        std::vector <std::string> vector_input;
        std::vector <std::string> vector_resultado;

        std::string big_number;

        // se convierte el string "s" en un vector (vector_input)
        for (int i = 0; i < s.length(); i++)
        {
            // si es que hay un 'ans' en el string, entonces se agrupa y se inserta en vector_input como un solo item
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

                if (s[i + 1] == ' ' || (i == s.length() - 1))  // esto ocurre para el ultimo digito de un numero con mas de un digito
                {
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

        // lo siguiente es el proceso de infijo a postfijo
        for (int i = 0; i < vector_input.size(); i++)
        {
            std::string c = vector_input[i];

            if ( isVariable(c) || isNumber(c) )
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
            else                // ocurre cuando c es un operador
            {    
                while ( !stack.isEmpty() && pemdas(c) <= pemdas(stack.top()->getData()) )
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

    std::string Calculator::solvePostfix(std::vector <std::string> vector_postfix, std::map <std::string, double> &map_variables)
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
                double valor_derecho = 0;
                double valor_izquierdo = 0;

                bool derecho_es_variable = false;
                bool izquierdo_es_variable = false;

                std::string operando_derecho = stack.top()->getData();
                stack.pop();

                std::string operando_izquierdo = stack.top()->getData(); 
                stack.pop();

                if (isVariable(operando_derecho))
                {
                    valor_derecho = map_variables[operando_derecho];
                    derecho_es_variable = true;
                }
                if (isVariable(operando_izquierdo))
                {
                    valor_izquierdo = map_variables[operando_izquierdo];
                    izquierdo_es_variable = true;
                }

                for (int j = 0; j < 5; j++)
                {
                    if (vector_postfix[i] == ff[j].operador)
                    {

                        if (izquierdo_es_variable && derecho_es_variable)
                        {
                            double resultado = ff[j].funcion(valor_izquierdo, valor_derecho);
                            stack.push(std::to_string(resultado));
                        }
                        else if (!izquierdo_es_variable && derecho_es_variable)
                        {
                            double resultado = ff[j].funcion(stod(operando_izquierdo), valor_derecho);
                            stack.push(std::to_string(resultado));
                        }
                        else if (izquierdo_es_variable && !derecho_es_variable)
                        {
                            //std::cout << "\nvalor_operando_izquierdo: " << valor_izquierdo << "\n"; 
                            //std::cout << "\nvalor_numero_derecho: " << stoi(operando_derecho) << "\n";

                            double resultado = ff[j].funcion(valor_izquierdo, stod(operando_derecho));
                            stack.push(std::to_string(resultado));
                        }
                        else if (!izquierdo_es_variable && !derecho_es_variable)
                        {
                            double resultado = ff[j].funcion(stod(operando_izquierdo), stod(operando_derecho));
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

    Calculator::Calculator()
    {}

    Calculator::~Calculator() 
    {}

}