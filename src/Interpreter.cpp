#include <iostream>
#include <stdexcept>

#include "Interpreter.h"

namespace bfi
{
Interpreter::Interpreter(std::string program_) : program(program_){};

void Interpreter::run()
{
    char c;
    for (int i = 0; i < program.size(); i++)
    {
        c = program[i];
        switch (c)
        {
            case '>':
                the_pointer++;
                break;
            case '<':
                the_pointer--;
                break;
            case '+':
                (*the_pointer)++;
                break;
            case '-':
                (*the_pointer)--;
                break;
            case '.':
                std::cout << *the_pointer;
                break;
            case ',':
                std::cin >> *the_pointer;
                break;
            case '[':
                if(!(*the_pointer)) {
                    while(*the_pointer != ']' && i < program.size())
                        i++;
                    if(i == program.size()) // TODO: Make proper exception classes and think about error messages
                        throw std::invalid_argument("No matching ] found for [");
                }
                else {

                }
                break;
        }
    }
};
}