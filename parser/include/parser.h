#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <instr.hpp>
#include <string>
#include <vector>

namespace Parser {
std::vector<Instruction::instruction> parse(std::ifstream &in);
}

#endif // PARSER_H
