
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>

#include "alu.h"
#include "instr.hpp"
#include "parser.h"

uint16_t byteSwap(uint16_t src)
{
  uint16_t q1 = src & 0xF000;
  uint16_t q2 = src & 0x0F00;
  uint16_t upper = (q1 >> 4) | (q2 << 4);
  uint16_t q3 = src & 0x00F0;
  uint16_t q4 = src & 0x000F;
  uint16_t lower = (q3 >> 4) | (q4 << 4);
  return (lower << 8) | (upper >> 8);
}
void runALU(std::vector<uint16_t> &mainMemory, int pcInit, int programSize);

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cout << "usage: parser <instruction_file>" << std::endl;
    std::exit(0);
  }

  std::string inputFileName = argv[1];
  std::ifstream inputStream(inputFileName);
  if (!inputStream.is_open())
  {
    std::cout << "Failed to open file." << std::endl;
    std::exit(1);
  }

  int pcInit = 32;
  const int memSize = 64;
  std::vector<uint16_t> mainMemory(memSize, 0);
  auto program = Parser::parse(inputStream);

  std::vector<uint16_t> instAsUint16;
  for (auto inst : program)
  {
    Instruction::instOrUint16 iou{inst};
    instAsUint16.push_back(byteSwap(iou.uint16));
  }

  mainMemory.insert(mainMemory.begin() + pcInit, instAsUint16.begin(),
                    instAsUint16.end());

  runALU(mainMemory, pcInit, program.size());
  inputStream.close();
  return 0;
}

void runALU(std::vector<uint16_t> &mainMemory, int pcInit, int programSize)
{

  ALU alu(mainMemory, pcInit);

  std::cout << "pc from " << pcInit << " to " << (pcInit + programSize - 1)
            << std::endl;

  alu.printInColumnsBinary(mainMemory, 4);
  alu.printPC();
  std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << "+            PRESS ENTER TO BEGIN           +" << std::endl;
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::string input;
  std::getline(std::cin, input);

  while (alu.getPC() < (pcInit + programSize))
  {
    // Information before execution
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "              BEFORE EXECUTION:              " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    // Print PC and current instruction (human readable)
    alu.printPC();
    alu.printExecuting(mainMemory[alu.getPC()]);

    // Print neighboring instructions
    alu.printInstructionList(mainMemory[alu.getPC()]);

    // Show current memory state
    alu.printFirstHalfInColumnsBinary(mainMemory, 2);
    // alu.printFirstHalfInColumnsDecimal(mainMemory, 2);
    std::cout << "---------------------------------------------" << std::endl;

    // Execute the instruction
    std::cout << "\n++++++++++++++++++++++++++++++++++++++++++++++"
              << std::endl;
    std::cout << "+   PRESS ENTER TO EXECUTE THE INSTRUCTION   +" << std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::getline(std::cin, input);

    alu.execute(mainMemory[alu.getPC()]);

    // Information after execution
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "              AFTER EXECUTION:               " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    alu.printPC();

    alu.printInstructionList(mainMemory[alu.getPC()]);

    alu.printFirstHalfInColumnsBinary(mainMemory, 2);
    // alu.printFirstHalfInColumnsDecimal(mainMemory, 2);
    std::cout << "---------------------------------------------" << std::endl;

    // Continue to next instruction
    std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "+           PRESS ENTER TO CONTINUE         +" << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::getline(std::cin, input);
  }
}
