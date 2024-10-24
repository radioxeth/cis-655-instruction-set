
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

// example of possible instruction layout
#include <cstdint>

#pragma "packed"
struct instruction {
  uint16_t opcode : 4;
  uint16_t reg1 : 4;
  uint16_t reg2 : 4;
  uint16_t reg3 : 4;
};

static_assert(sizeof(instruction) == sizeof(uint16_t),
              "add instruction must be 16bits");

enum opcode : uint8_t {
  /* Add reg-mem*/
  am = 0b0000,
  /* Subtract reg-mem*/
  sm = 0b0001,
  /* Multiply reg-mem*/
  mm = 0b0010,
  /* Integer Divide reg-mem*/
  dm = 0b0011,
  /* Branch not equal reg-mem*/
  bnem = 0b0100,
  /* Set less than reg-mem*/
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
  ju = 0b1110,
  /* No Operation*/
  noop = 0b1111,
};

#endif /* INSTR */
