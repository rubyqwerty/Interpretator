#include "arithmetic_parser.h"

std::vector<std::string> arithmetic_parser::Do_polish_notation(std::vector<std::string> expression)
{
    std::vector<std::string> result;
    std::stack<std::string> stack;
    for (auto i : expression) {
        if (priorities.find(i) != priorities.end()) {
            while (!stack.empty() && stack.top() != ")" && stack.top() != "(" && priorities[stack.top()] <= priorities[i]) {
                result.push_back(stack.top());
                stack.pop();
            }
            stack.push(i);
        }
        else if (i == "(")
            stack.push(i);
        else if (i == ")") {
            while (!stack.empty() && stack.top() != "(") {
                result.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        }
        else
            result.push_back(i);
    }
    while (!stack.empty()) {
        result.push_back(stack.top());
        stack.pop();
    }
    return result;
}

std::string arithmetic_parser::Calculate(std::string first, std::string second, std::string sign) {
    if (sign == "-")
        return std::to_string(atoi(second.c_str()) - atoi(first.c_str()));
    if (sign == "+")
        return std::to_string(atoi(second.c_str()) + atoi(first.c_str()));
    if (sign == "*")
        return std::to_string(atoi(second.c_str()) * atoi(first.c_str()));
    if (sign == "/")
        return std::to_string(atoi(second.c_str()) / atoi(first.c_str()));
    return "";
}

std::string arithmetic_parser::Do_calculations_by_polish_notation(std::vector<std::string> expression)
{
    std::stack<std::string> stack;
    for (auto i : expression) {
        if (std::regex_match(i,  std::regex("([0-9])+")))
            stack.push(i);
        else if (std::regex_match(i,  std::regex("([a-z])+"))) {
            stack.push(std::to_string((*variables)[i]));
        }
        else {
            std::string first_operand = stack.top();
            stack.pop();
            std::string second_operand = stack.top();
            stack.pop();
            stack.push(Calculate(first_operand, second_operand, i));
        }
    }
    return stack.top();

}

arithmetic_parser::arithmetic_parser(std::map<std::string, int>& _variables)
{
    variables = &_variables;
    
}
