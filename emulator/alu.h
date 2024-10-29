#ifndef ALU_H
#define ALU_H

#include <bitset>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class ALU
{
private:
    int pc;

    std::vector<std::function<int(uint8_t, uint8_t, uint8_t)>> functions;
    std::vector<uint16_t> &memory;

    int am(uint8_t op1, uint8_t op2, uint8_t op3);
    int sm(uint8_t op1, uint8_t op2, uint8_t op3);
    int mm(uint8_t op1, uint8_t op2, uint8_t op3);
    int dm(uint8_t op1, uint8_t op2, uint8_t op3);
    int bnem(uint8_t op1, uint8_t op2, uint8_t op3);
    int sltm(uint8_t op1, uint8_t op2, uint8_t op3);
    int ai(uint8_t op1, uint8_t op2, uint8_t op3);
    int si(uint8_t op1, uint8_t op2, uint8_t op3);
    int mi(uint8_t op1, uint8_t op2, uint8_t op3);
    int di(uint8_t op1, uint8_t op2, uint8_t op3);
    int lci(uint8_t op1, uint8_t op2, uint8_t op3);
    int sci(uint8_t op1, uint8_t op2, uint8_t op3);
    int lo(uint8_t op1, uint8_t op2, uint8_t op3);
    int so(uint8_t op1, uint8_t op2, uint8_t op3);
    int jb(uint8_t op1, uint8_t op2, uint8_t op3);

public:
    ALU(std::vector<uint16_t> &mem, int pcInit);

    void printMemory();
    void printInColumnsBinary(const std::vector<uint16_t> &list, int columns);
    void printInColumnsDecimal(const std::vector<uint16_t> &list, int columns);
    void printPC();
    void printInstruction(uint16_t instruction);
    void printExecuting(uint16_t instruction);
    int execute(uint16_t instruction);

    void setPC(int newPC);
    int getPC();

    std::map<std::string, int> M;
    std::map<uint8_t, std::string> OPCODES;
    std::map<uint8_t, std::string> MEMORY_REGISTERS;
};

#endif // ALU_H