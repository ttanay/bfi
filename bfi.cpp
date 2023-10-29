#include <exception>
#include <iostream>
#include <string>

#include "src/Interpreter.h"

namespace bfi
{

#define PROGRAM_LENGTH 4 * 1024

int main()
{
    std::string program;
    std::getline(std::cin, program);
    try
    {
        auto interpreter = bfi::Interpreter(program);
        interpreter.run();
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

} // namespace bfi