
/*
 * Brief: emulator for CIS 655 instruction set HW2 project
 *        runs the binary program passed as argument
 */

#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include "instr.hpp"

instruction intr = {};
struct Mem {
  // Using vector because we will not know how much we will need
  std::vector<uint8_t> program;
  std::vector<uint8_t> data;

  // size_t is max size of system pointer
  // size_t will hold largest possible index
  std::size_t program_counter;

  // registers should be const size
  std::array<uint16_t, 16> registers;
};

// need to pass in argv & argc
int main() {
  // should read in the binary program
  // then CPU function should run on Mem
  // user should be given a menu of options like
  //
  // s: step
  // p: print: prints current instruction: current state of memory and registers
  // d: dump: continuously steps and dumps step register and instruction
  // mw: write value to memory args: address, value
  // mr: read value at address: args: addess
  return 0;
}
