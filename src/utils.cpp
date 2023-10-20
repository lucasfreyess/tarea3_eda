#include "calculator/utils.hpp"

namespace calc
{
    bool isOperator(char c)
    {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    bool isOperator(std::string c)
    {
        return (c == "+" || c == "-" || c == "*" || c == "/" || c == "^");
    }

    bool isNumber(char c)
    {
        return (c >= '0' && c <= '9');
    }

    bool isNumber(std::string c)
    {
        return (c >= "0" && c <= "9");
    }

    bool isVariable(char c)
    {
        return ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') );
    }

    bool isVariable(std::string c)
    {
        return ( (c >= "a" && c <= "z") || (c >= "A" && c <= "Z") );
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

    double suma(double a, double b)
    {
        return a + b;
    }
    
    double resta(double a, double b)
    {
        return a - b;
    }

    double mult(double a, double b)
    {
        return a * b;
    }

    double div(double a, double b)     // hay q ver division de float !!
    {
        return a / b;
    }

    double potencia(double a, double b)
    {
        return pow(a, b);
    }
}