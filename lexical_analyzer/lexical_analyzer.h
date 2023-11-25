
#include <boost/filesystem/operations.hpp>
#include <boost/program_options.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <string>
#include <vector>
#include <iostream>
class lexical_analyzer {
public:
    static std::string Get_program_from_file(std::string); 
    static std::vector<std::string> Get_vector_word(std::string);
    static void Preparing_line(std::string&);
public:
    static std::vector<std::string> Get_program (std::string);
};
