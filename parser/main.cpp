#include "parser.h"
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

int main(int argc, char *argv[]) {

  std::cout << std::endl;
  if (argc != 2) {
    std::cout << "usage: parser <instruction_file>" << std::endl;
    std::exit(0);
  }

  std::string inputFileName = argv[1];
  std::ifstream inputStream(inputFileName);
  if (!inputStream.is_open()) {
    std::cout << "Failed to open file." << std::endl;
    std::exit(1);
  }

  auto mechineCode = Parser::parse(inputStream);
  for (auto code : mechineCode) {
    Instruction::instOrUint16 iou{code};
    std::cout << std::hex << iou.inst << " " << iou.uint16 << std::endl;
  }
  std::cout << std::endl;

  inputStream.close();

  std::cout << std::endl << "Commands passed successfully." << std::endl;

  return 0;
}
