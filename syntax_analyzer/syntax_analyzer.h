#include <vector>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <algorithm>
#include <cctype>
#include <regex>
#include <iostream>
#include "../lexical_analyzer/lexical_analyzer.h"

class syntax_analyzer {
private:
    int Find(std::vector<std::pair<std::string, std::vector<std::string>>> &, std::string);
    std::map<std::string , int> table_of_variables;
    std::vector<std::string> arithmetic_sign {"+" , "-" , "/", "*"};
    std::vector<std::string> states {"1" , "2" , "3", "4", "5","6","7","8","9","10","11", "12","13"};
    std::vector<std::string> constants;
    std::map<std::string, int> variables;
    std::set<std::pair<int,std::pair<std::string,std::string>>> errors;
    std::vector<std::string> program;
    bool Checking_brackets();
    int Go_next(int=1, int=0, int=0);
    std::map<int, std::vector<std::pair<std::string, std::vector<std::string>>>> rules {
        {1, {{"PROGRAM" , {"word"}},
            {"word" , {";"}},
            {";" , {"2"}}
        }},
        {2, {{"VAR" , {"word"}},
            {"word" , {"," , ":"}},
            {"," , {"word"}},
            {":" , {"INTEGER"}},
            {"INTEGER" , {";"}},
            {";" , {"3"}}
        }},
        {3, {{"BEGIN" , {"4" , "10" , "11", "12", "13"}}
        }},
        {4, {
            {"word" , {"5"}},
        }},
         {10, {
            {"CASE" , {"6"}},
        }},
        {5 , {{":=" , {"word" , "const", "("}},
            {"word" , {";" , "arithmetic sign" , ")"}},
            {"const" , {";" , "arithmetic sign", ")"}},
            {"arithmetic sign" , {"word" , "const", "("}},
            {"(" , {"word" , "const" , "("}},
            {")" , {"arithmetic sign" , ")" , ";"}},
            {";" , {"11", "4", "10" ,"12" , "13"}},
            {"CASE" , {"6"}},
        }},
        {6, {{"word" , {"OF"}},
            {"OF" , {"7"}}
        }},
        {7, {{"const", {":"}},
            {":", {"8"}}
        }},
        {8, {
            {"word" , {"9"}},
        }},
        {9 , {{":=" , {"word" , "const", "("}},
            {"word" , {";" , "arithmetic sign" , ")"}},
            {"const" , {";" , "arithmetic sign", ")"}},
            {"arithmetic sign" , {"word" , "const", "("}},
            {"(" , {"word" , "const" , "("}},
            {")" , {"arithmetic sign" , ")" , ";"}},
            {";" , {"END_CASE", "7","8"}},
            {"END_CASE" , {"11", "4", "10", "12", "13"}},
        }},
        {11 , {{"END" , {"@"}},
                {"@" , {"@"}}}},
        {12 , {{"READ" , {"("}},
                {"(" , {"word"}},
                {"word" , {",", ")"}},
                {")" , {";"}},
                {"," , {"word"}},
                {";", {"4" , "10" , "12", "11", "13"}}
        }},
        {13 , {{"WRITE" , {"("}},
                {"(" , {"word"}},
                {"word" , {",",")"}},
                {")" , {";"}},
                {"," , {"word"}},
                {";", {"4" , "10" , "12", "11", "13"}}
        }}
        };
public:
    int Do_syntax_analyzer (int=1, int=0, int=0);
    std::string Get_errors();
    std::map<std::string, int> Get_variables();
    std::vector<std::string> Get_constants();
    std::vector<std::string> Get_program();
    syntax_analyzer(std::string);
};


