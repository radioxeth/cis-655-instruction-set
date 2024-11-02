#include <algorithm>
#include <array>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "instr.hpp"
#include "parser.h"

/*
 * alias of std::vector<std::string>
 */
using lineOfTokens = std::vector<std::string>;

/*
 * @Brief- Check if any AlphaNumeric character is present
 *
 * @pram - str: being checked
 * @return - bool: true - no alphaNum character is present
 *                 false- alphaNum character is present
 */
bool isAnyAlphaNumeric(std::string &str) {
  return !std::none_of(str.begin(), str.end(), ::isalnum);
}

/*
 * @Brief - removes characters in a string based of the given predicate
 *
 * @param - line: string being edited
 * @param - pred: predicate used to remove if matching/true
 * @return - void
 */
template <typename T> void rm(std::string &line, T pred) {
  line.erase(std::remove_if(line.begin(), line.end(), pred), line.end());
}

/*
 * @Brief - decode takes lines of Tokens and outputs lines of instructions
 *
 * @param - loT: vector of Tokens
 * @return - std::vector<instruction>
 */
std::vector<Instruction::instruction>
decode(const std::vector<lineOfTokens> &loT) {
  std::vector<Instruction::instruction> machinecode;

  for (auto line : loT) {
    rm(line[1], [](auto t) { return (t == 'm') ? true : false; });
    rm(line[2], [](auto t) { return (t == 'm') ? true : false; });
    rm(line[3], [](auto t) { return (t == 'm') ? true : false; });

    machinecode.push_back(Instruction::instruction{
        .opcode = Instruction::strToOp[line[0]],
        .mem1 = static_cast<uint16_t>(std::stoul(line[1])),
        .mem2 = static_cast<uint16_t>(std::stoul(line[2])),
        .mem3 = static_cast<uint16_t>(std::stoul(line[3])),
    });
  }

  return machinecode;
}

/*
 * @Brief - parses a give line into a line of tokens
 *
 * @param - line: string representing a line of code
 * @return - returns optional:
 *          - lineOfTokens : 4 tokens [op, arg1, arg2, arg3]
 *          - nullopt : if no token
 */
std::optional<lineOfTokens> parseline(const std::string &line) {
  std::optional<lineOfTokens> linetokens = std::nullopt;

  std::istringstream in_ss(line);
  bool parserable = false;
  uint tokenCount = 0;
  std::vector<std::string> tokensParsed;
  for (std::string token; std::getline(in_ss, token, ' '); tokenCount++) {
    rm(token, ::isspace);
    rm(token, [](unsigned char x) { return x == ','; });
    if (token.size() > 0) {
      tokensParsed.push_back(token);
    } else {
      break;
    }
  }
  if (tokensParsed.size() == 4) {
    linetokens = std::make_optional(tokensParsed);
  }
  return linetokens;
}

/*
 * @Brief - parses a given file into a list of line tokens
 *
 * @param - in: input stream file of asm file
 * @return - list of linetokens
 */
std::vector<Instruction::instruction> Parser::parse(std::ifstream &in) {
  std::vector<std::vector<std::string>> outputs;
  for (std::string line; std::getline(in, line);) {
    auto commentIndex = line.find("//");
    if (commentIndex != std::string::npos) {
      auto lineNoComment = line.substr(0, commentIndex);

      if (isAnyAlphaNumeric(lineNoComment)) {
        auto lineTokens = parseline(line.substr(0, commentIndex));
        if (std::nullopt != lineTokens) {
          outputs.push_back(*lineTokens);
        }
      }
    }
  }

  return decode(outputs);
}
