
#include "../syntax_analyzer/syntax_analyzer.h"
#include "../arithmetic_parser/arithmetic_parser.h"

class interpretator {
    private:
    std::vector<std::string> program;
    std::map<std::string, int> variables;

     std::vector<std::string> Preparation_program();

    public:
     void Run (std::string);
     void Run_program();
};