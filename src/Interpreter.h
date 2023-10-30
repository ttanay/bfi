#include <string>
#include <stack>

namespace bfi
{
class Interpreter
{
    char data[30000] = {0}; // Initialized to zero
    char *the_pointer = data;
    std::string program;
    std::stack<int> conditional_idxs;
public:
    /**
   Sets up the ffvm
  */
    Interpreter(std::string program);
    /**
  Iterates over the program executing each command on the ffvm
  */
    void run();
};
} // namespace bfi