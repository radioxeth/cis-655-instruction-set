
/*
 * Brief: bit field representation of an instructions
 * w/ opcode const, and utility functions for managing instruction
 *
 * instruction bit fields are a fundamental component of the CPU
 * emulator
 *
 */

#ifndef INSTR_HPP
#define INSTR_HPP

#include <cstdint>
#include <map>
#include <ostream>
#include <string>

namespace Instruction {

#pragma "packed"
struct instruction {
  uint16_t opcode : 4;
  uint16_t mem1 : 4;
  uint16_t mem2 : 4;
  uint16_t mem3 : 4;
};
union instOrUint16 {
  instruction inst;
  uint16_t uint16;
};

static_assert(sizeof(instruction) == sizeof(uint16_t),
              "add instruction must be 16bits");

static std::ostream &operator<<(std::ostream &stream, instruction inst) {
  return stream << "op: " << inst.opcode << " mem1: " << inst.mem1
                << " mem2: " << inst.mem2 << " mem3: " << inst.mem3;
}

enum opcode : uint8_t {
  /* Add mem-mem*/
  am = 0b0000,
  /* Subtract mem-mem*/
  sm = 0b0001,
  /* Multiply mem-mem*/
  mm = 0b0010,
  /* Integer Divide mem-mem*/
  dm = 0b0011,
  /* Branch not equal mem-mem*/
  bnem = 0b0100,
  /* Set less than mem-mem*/
  sltm = 0b0101,
  /* Add immediate*/
  ai = 0b0110,
  /* Subtract immediate*/
  si = 0b0111,
  /* Multiply immediate*/
  mi = 0b1000,
  /* Divide immediate*/
  di = 0b1001,
  /* Load constant immediate*/
  lci = 0b1010,
  /* Store constant immediate*/
  sci = 0b1011,
  /* Load using offset*/
  lo = 0b1100,
  /* Store using offset*/
  so = 0b1101,
  /* Jump*/
  jb = 0b1110,
  /* No Operation*/
  noop = 0b1111,
};

static std::map<std::string, int> M = {
    {"M0", 0},   {"M1", 1},   {"M2", 2},   {"M3", 3},  {"M4", 4},   {"M5", 5},
    {"M6", 6},   {"M7", 7},   {"M8", 8},   {"M9", 9},  {"M10", 10}, {"M11", 11},
    {"M12", 12}, {"M13", 13}, {"M14", 14}, {"M15", 15}};

static std::map<uint8_t, std::string> OPCODES = {
    {0b0000, "am"},   {0b0001, "sm"},   {0b0010, "mm"},  {0b0011, "dm"},
    {0b0100, "bnem"}, {0b0101, "sltm"}, {0b0110, "ai"},  {0b0111, "si"},
    {0b1000, "mi"},   {0b1001, "di"},   {0b1010, "lci"}, {0b1011, "sci"},
    {0b1100, "lo"},   {0b1101, "so"},   {0b1110, "jb"}};

static std::map<std::string, uint8_t> strToOp = {
    {"am", 0b0000},   {"sm", 0b0001},   {"mm", 0b0010},  {"dm", 0b0011},
    {"bnem", 0b0100}, {"sltm", 0b0101}, {"ai", 0b0110},  {"si", 0b0111},
    {"mi", 0b1000},   {"di", 0b1001},   {"lci", 0b1010}, {"sci", 0b1011},
    {"lo", 0b1100},   {"so", 0b1101},   {"jb", 0b1110},  {"noop", 0b1111}};

static std::map<uint8_t, std::string> MEMORY_REGISTERS = {
    {0b0000, "M0"},  {0b0001, "M1"},  {0b0010, "M2"},  {0b0011, "M3"},
    {0b0100, "M4"},  {0b0101, "M5"},  {0b0110, "M6"},  {0b0111, "M7"},
    {0b1000, "M8"},  {0b1001, "M9"},  {0b1010, "M10"}, {0b1011, "M11"},
    {0b1100, "M12"}, {0b1101, "M13"}, {0b1110, "M14"}, {0b1111, "M15"}};
} // namespace Instruction
#endif /* INSTR */
