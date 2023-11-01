#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>

std::set<char> valid_chars = {'>', '<', '+', '-', '.', ',', '[', ']'};

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
                    i++; // Proceed to next instruction
                    uint skip_counter = 0; // Number of ] that need to be skipped
                    while (i < program.size() && !(program[i] == ']' && !skip_counter))
                    {
                        if (program[i] == '[')
                            skip_counter++;
                        else if (program[i] == ']' && skip_counter)
                            skip_counter--;
                        i++;
                    }

                    if (i == program.size()) // TODO: Make proper exception classes and think about error messages
                        throw std::invalid_argument("No matching ] found for [");
                }
                else
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
            default:
                throw std::invalid_argument("Invalid command");
        }
        i++;
    }
}

std::string sanitize(const std::string & line)
{
    std::string sanitized;
    for (auto i = line.begin(); i != line.end(); i++)
        if (valid_chars.find(*i) != valid_chars.end())
            sanitized += *i;
    return sanitized;
}

int main(int argc, char * argv[])
{
    std::string program;
    if (argc == 1)
    { // No filename; Assume single line
        std::getline(std::cin, program);
        program = sanitize(program);
    }
    else if (argc == 2)
    { // Run file
        std::ifstream source{argv[1]};
        if (source.is_open())
        {
            std::string line;
            while (!source.eof())
            {
                std::getline(source, line);
                program += sanitize(line);
            }
        }
    }
    else
        throw std::invalid_argument("INVALID");

    run(program);
    return 0;
}
