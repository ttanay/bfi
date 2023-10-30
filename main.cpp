#include <exception>
#include <iostream>
#include <stack>
#include <string>

void run(const std::string & program)
{
    char data[30000] = {0};
    char * the_pointer = data;
    std::stack<int> conditional_idxs;

    char c;
    int i = 0;
    while (i < program.size())
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
                if (!(*the_pointer))
                {
                    while (program[i] != ']' && i < program.size())
                        i++;
                    if (i == program.size()) // TODO: Make proper exception classes and think about error messages
                        throw std::invalid_argument("No matching ] found for [");
                }
                else
                {
                    conditional_idxs.push(i);
                }
                break;
            case ']':
                if (!(*the_pointer))
                {
                    // Jump back
                    i = conditional_idxs.top();
                    continue;
                }
                else
                {
                    conditional_idxs.pop();
                }
                break;
            case ' ':
            case '\t':
            case '\n':
                break;
            default:
                throw std::invalid_argument("Invalid command");
        }
        i++;
    }
}


int main()
{
    std::string program;
    std::getline(std::cin, program);
    // std::cout << "Your program: " << program;
    run(program);
    return 0;
}
