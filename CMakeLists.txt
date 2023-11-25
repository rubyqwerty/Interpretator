cmake_minimum_required(VERSION 3.0)
project(Translator)
set(SOURCE main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})
find_package (Boost REQUIRED COMPONENTS system filesystem program_options regex)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries (Translator ${Boost_LIBRARIES}) 
add_subdirectory(lexical_analyzer)
add_subdirectory(arithmetic_parser)
add_subdirectory( syntax_analyzer)
add_subdirectory(interpretator)
include_directories(interpretator)
include_directories(syntax_analyzer)
target_link_libraries(Translator interpretator)
target_link_libraries(Translator arithmetic_parser)
target_link_libraries(Translator syntax_analyzer)
target_link_libraries(Translator lexical_analyzer)









