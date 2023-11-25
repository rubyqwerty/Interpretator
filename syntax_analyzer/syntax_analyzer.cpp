#include "syntax_analyzer.h"

int syntax_analyzer::Find(std::vector<std::pair<std::string, std::vector<std::string>>>& rule, std::string line) {
    int index = 0;
    for (auto& i : rule) {
        if (i.first == line) return index;
        index++;
    }
    return -1;
}

int syntax_analyzer::Do_syntax_analyzer(int state, int cur_word_graph, int cur_word_program)
{
    if (!cur_word_program)
        if (!Checking_brackets()) {
            errors.insert({0, {"()","Error in backets"}});
            return false;
        }
    if (cur_word_program >= program.size()) return false;
    if (cur_word_graph >= rules[state].size()) return false;
   // std::cout << state << " " << rules[state][cur_word_graph].first << " " << program[cur_word_program] <<  " " << cur_word_program << std::endl;
    if (rules[state][cur_word_graph].first == "@") return true;
   
    if (rules[state][cur_word_graph].first == program[cur_word_program]) {
        return Go_next(state, cur_word_graph, cur_word_program);
    }
    else if (rules[state][cur_word_graph].first == "word"){
        if (state <= 2) {
            if (std::regex_match(program[cur_word_program],  std::regex("([a-z]){1,9}"))){
                variables.insert({program[cur_word_program] , 0});
                return Go_next(state, cur_word_graph, cur_word_program);
            } 
            errors.insert({cur_word_program, {"<" + program[cur_word_program] + ">", "Error in variable (length must < 9)"}});
            return false;
        }
        else {
            if (std::regex_match(program[cur_word_program],  std::regex("([a-z]){1,9}")) && variables.count(program[cur_word_program]) > 0){
                return Go_next(state, cur_word_graph, cur_word_program);
            }
            errors.insert({cur_word_program, {"<" + program[cur_word_program] + ">", "Error in variable (unknow variable)"}});
            return false;

        }
    }
    else if (rules[state][cur_word_graph].first == "const") {
        if (std::regex_match(program[cur_word_program],  std::regex("([-]{0,1}[0-9]+)"))){
            constants.push_back(program[cur_word_program]);
            return Go_next(state, cur_word_graph, cur_word_program);
        }
        return false;
    }
    else if (rules[state][cur_word_graph].first == "arithmetic sign") {
        if (std::find(arithmetic_sign.begin(), arithmetic_sign.end(), program[cur_word_program]) != arithmetic_sign.end()) {
            return Go_next(state, cur_word_graph, cur_word_program);
        }
        errors.insert({cur_word_program, {"<" + program[cur_word_program] + ">", "Error in arithmetic sign or unexpected operator"}});
        return false;
    }
    errors.insert({cur_word_program, {"<" + program[cur_word_program] + ">", "Unexpected operator"}});
    return false;
}

int syntax_analyzer::Go_next(int state, int cur_word_graph, int cur_word_program)
{
     for (auto& i : rules[state][cur_word_graph].second) {
        if (std::find(states.begin(), states.end(), i) != states.end()){
            if(Do_syntax_analyzer(atoi(i.c_str()), 0, cur_word_program+1)) return true;
            continue;
        }
        if(Do_syntax_analyzer(state, Find(rules[state], i), cur_word_program+1)) return true;

     }
     return false;
}

bool syntax_analyzer::Checking_brackets()
{
    std::stack<std::string> brackets;
    int state = 0;
    for (auto i : program) {
        if (i == ":=") state = 1;
        if (state) {
            if (i == "(")
                brackets.push("(");
            else if (!brackets.empty() && i == ")")
                brackets.pop();
            else if (i == ")")
                return false;

            if (i == ";") {
            if (!brackets.empty()) return false; 
            state = 0;
            }
        }
        
    }
    return true;
}

std::string syntax_analyzer::Get_errors()
{
    auto error_token = *std::max_element(errors.begin(), errors.end());
    std::string Res_error = "";
    for (auto it = errors.begin(); it!=errors.end(); ++it ) 
        if ((*it).first == error_token.first) Res_error += (*it).second.first + " " + (*it).second.second + "\n";
    return Res_error;
}

std::map<std::string, int> syntax_analyzer::Get_variables()
{
    return this->variables;
}

std::vector<std::string> syntax_analyzer::Get_constants()
{
    return this->constants;
}

std::vector<std::string> syntax_analyzer::Get_program()
{
    return this->program;
}

syntax_analyzer::syntax_analyzer(std::string load_to_file)
{
    program = lexical_analyzer::Get_program(load_to_file);
    program.push_back("@");
}
