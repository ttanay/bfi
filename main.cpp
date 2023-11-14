#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <stdexcept>
#include <vector>
#include <string>

#define SIZE 30000

std::set<char> valid_chars = {'>', '<', '+', '-', '.', ',', '[', ']'};

void run(const std::string & program)
{
    char data[SIZE] = {0};
    int the_pointer = 0;
    std::vector<int> conditional_idxs;

    char c;
    int i = 0;
    while (i < program.size())
    {
        c = program[i];
        switch (c)
        {
            case '>':
                if(the_pointer == SIZE - 1)
                    throw std::out_of_range("overflow");
                the_pointer++;
                break;
            case '<':
                the_pointer--;
                break;
            case '+':
                data[the_pointer]++;
                break;
            case '-':
                data[the_pointer]--;
                break;
            case '.':
                std::cout << data[the_pointer];
                break;
            case ',':
                std::cin >> data[the_pointer];
                break;
            case '[':
                if (!(data[the_pointer]))
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

                    if (i == program.size())
                        throw std::invalid_argument("No matching ] found for [");
                }
                else {
                    conditional_idxs.push_back(i);
                }
                break;
            case ']':
                if ((data[the_pointer]))
                {
                    // Jump back
                    i = conditional_idxs.back() + 1;
                    continue;
                }
                else
                {
                    conditional_idxs.pop_back();
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
