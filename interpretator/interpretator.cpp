#include "interpretator.h"

std::vector<std::string> interpretator::Preparation_program()  {
        std::vector<std::string> program_for_execution;
        auto begin = std::find(program.begin(), program.end(), "BEGIN");
        begin++;
        while (*begin != "END") {
            program_for_execution.push_back(*begin);
            begin++;
        }
        return program_for_execution;
}

void interpretator::Run (std::string load_to_file) {
        syntax_analyzer analyzer(load_to_file);

        if (analyzer.Do_syntax_analyzer()) {
            program = analyzer.Get_program();
            program = Preparation_program();
            variables = analyzer.Get_variables();
            Run_program();
        }
	    else {
		    std::cout << "\nProgram not correct\nError in:\n" << analyzer.Get_errors();
		    return;
	    }
}

void interpretator::Run_program() {
        arithmetic_parser parser (variables);
        for (auto word = program.begin(); word!=program.end();word++) {
            if (*word == "CASE") {
                std::string case_params;
                word++;
                case_params = *word;
                word = std::find(word, std::find(word, program.end(), "END_CASE"), std::to_string(variables[case_params]));
                if (word == std::find(word, program.end(), "END_CASE")) {
                   continue;
                }
                word+=2;
                while (*word != "END_CASE" && !(std::regex_match(*word,  std::regex("[-]{0,1}([0-9])+")) && *(word+1) == ":")) {
                    if (*(word+1) == ":=") {
                        std::vector<std::string> arithmetic_expression (word + 2, std::find(word, program.end(), ";"));
                        arithmetic_expression = parser.Do_polish_notation(arithmetic_expression);
                        std::string value = parser.Do_calculations_by_polish_notation(arithmetic_expression);
                        variables[*(word)] = atoi(value.c_str());
                    }
                    
                    word++;
                }
                word = std::find(word, program.end(), "END_CASE");
            }
            else if (*word == "READ") {
                std::vector<std::string> params;
                while (*word!=";") {
                    if (std::regex_match(*word,  std::regex("([a-z])+"))) {
                        std::string value;
                        std::cin >> value;
                        if (!std::regex_match(value,  std::regex("([-]{0,1})([0-9])+"))) {
                            std::cout << "Error input!\n";
                            return;
                        }
                        variables[*word] = atoi(value.c_str());
                    }
                    word++;
                }
            }
            else if (*word == "WRITE") {
                while (*word!=";") {
                    if (std::regex_match(*word,  std::regex("([a-z])+"))) {
                       std::cout << variables[*word] << " ";
                    }
                    word++;
                }
                std::cout << "\n";
            }
            else if (*(word+1) == ":=") {
                std::vector<std::string> arithmetic_expression (word + 2, std::find(word, program.end(), ";"));
                arithmetic_expression = parser.Do_polish_notation(arithmetic_expression);
                std::string value = parser.Do_calculations_by_polish_notation(arithmetic_expression);
                variables[*(word)] = atoi(value.c_str());
            }
            
        }
    }