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
                    uint skip_counter = 0; // Number of ] that need to be skipped
                    while (program[i] == ']' && !skip_counter && i < program.size()) {
                        if(program[i] == '[')
                            skip_counter++;
                        else if(program[i] == ']' && skip_counter)
                            skip_counter--;
                        i++;
                    }

                    if (i == program.size()) // TODO: Make proper exception classes and think about error messages
                        throw std::invalid_argument("No matching ] found for [");
                    continue;
                }
                conditional_idxs.push(i);
                break;
            case ']':
                if ((*the_pointer))
                {
                    // Jump back
                    i = conditional_idxs.top() + 1;
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
