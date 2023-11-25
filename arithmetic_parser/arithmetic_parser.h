#include <string>
#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <regex>

class arithmetic_parser {
    public:
    std::map<std::string, int>* variables;
    std::map<std::string, int> priorities {
        {"+", 2},
        {"-", 2},
        {"/", 1},
        {"*", 1}
    };
    std::vector<std::string> Do_polish_notation(std::vector<std::string>);
    std::string Calculate(std::string first, std::string second, std::string sign);
    public:
    std::string Do_calculations_by_polish_notation(std::vector<std::string>);
    arithmetic_parser(std::map<std::string, int>&);
};


