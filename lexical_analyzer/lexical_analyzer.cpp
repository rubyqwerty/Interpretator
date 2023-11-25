#include "lexical_analyzer.h"
#include <regex>

std::string lexical_analyzer::Get_program_from_file(std::string load_to_file) {
	const boost::interprocess::mode_t mode = boost::interprocess::read_only;
	boost::interprocess::file_mapping fm(load_to_file.c_str(), mode);
	boost::interprocess::mapped_region region(fm, mode, 0, 0);
	const char* begin = static_cast<const char*>(
			region.get_address()
			);
	std::string text_program = begin;
    return text_program;
}

std::vector<std::string> lexical_analyzer::Get_vector_word(std::string program)
{
    std::vector<std::string> vector_word;
    boost::split( vector_word, program, boost::is_any_of(" "), boost::token_compress_on);
    return vector_word;
}

void lexical_analyzer::Preparing_line(std::string& program)
{
    program = std::regex_replace(program, std::regex("(\\s)+"), " ");
    program = std::regex_replace(program, std::regex(";"), " ; ");
    program = std::regex_replace(program, std::regex("[+]"), " + ");
    program = std::regex_replace(program, std::regex("-"), " - ");
    program = std::regex_replace(program, std::regex("/"), " / ");
    program = std::regex_replace(program, std::regex(","), " , ");
    program = std::regex_replace(program, std::regex(":"), " : ");
    program = std::regex_replace(program, std::regex("[*]"), " * ");
    program = std::regex_replace(program, std::regex("(\\s)+:(\\s)+="), " := ");
    program = std::regex_replace(program, std::regex("[(]"), " ( ");
    program = std::regex_replace(program, std::regex("[)]"), " ) ");
    program = std::regex_replace(program, std::regex("[(](\\s)+-"), "( 0 -");
    program = std::regex_replace(program, std::regex(":=(\\s)+-"), ":= 0 -");
    program = std::regex_replace(program, std::regex("[(](\\s)+-"), "( 0 -");
    program = std::regex_replace(program, std::regex("([*|+|/|-]+)(\\s)+-(\\s)+([a-z|0-9]+)"), "$1 ( 0 - $4 )");
    program = std::regex_replace(program, std::regex("([-])(\\s)+([0-9]+)(\\s)+([:])"), "$1$3 $5");
}

std::vector<std::string> lexical_analyzer::Get_program(std::string load_to_file)
{
    std::string program = Get_program_from_file(load_to_file);
    Preparing_line(program);
    return Get_vector_word(program);
}
