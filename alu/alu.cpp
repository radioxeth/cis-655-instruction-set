#include "alu.h"

ALU::ALU(std::vector<uint16_t> &mem, int pcInit) : memory(mem), pc(pcInit)
{
    functions.resize(15);
    functions[0] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return am(op1, op2, op3); };
    functions[1] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return sm(op1, op2, op3); };
    functions[2] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return mm(op1, op2, op3); };
    functions[3] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return dm(op1, op2, op3); };
    functions[4] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return bnem(op1, op2, op3); };
    functions[5] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return sltm(op1, op2, op3); };
    functions[6] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return ai(op1, op2, op3); };
    functions[7] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return si(op1, op2, op3); };
    functions[8] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return mi(op1, op2, op3); };
    functions[9] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return di(op1, op2, op3); };
    functions[10] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return lci(op1, op2, op3); };
    functions[11] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return sci(op1, op2, op3); };
    functions[12] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return lo(op1, op2, op3); };
    functions[13] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return so(op1, op2, op3); };
    functions[14] = [this](uint8_t op1, uint8_t op2, uint8_t op3)
    { return jb(op1, op2, op3); };
}

// Add the function implementations for each ALU operation, printing, and executing here...
int ALU::am(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[op3] = memory[op1] + memory[op2];
    return 1;
}

// subtract memory-memory
// opcode 0001
int ALU::sm(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[op3] = memory[op1] - memory[op2];
    return 1;
}

// multiply memory-memory
// opcode 0010
int ALU::mm(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[op3] = memory[op1] * memory[op2];
    return 1;
}

// divide memory-memory
// opcode 0011
int ALU::dm(uint8_t op1, uint8_t op2, uint8_t op3)
{
    if (memory[op2] == 0)
    {
        std::string op = "dm " + std::to_string(op1) + " " + std::to_string(op2) + " " + std::to_string(op3);
        throw std::invalid_argument("Error: Division by zero.\nOPCODE: " + op);
    }
    memory[op3] = memory[op1] / memory[op2];
    return 1;
}

// branch if not equal memory-memory
// opcode 0100
int ALU::bnem(uint8_t op1, uint8_t op2, uint8_t op3)
{
    if (memory[op1] != memory[op2])
    {
        return int(op3); // Adjust program counter
    }
    else
    {
        return 1;
    }
}

// set less than memory-memory
// opcode 0101
int ALU::sltm(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[op3] = (memory[op1] < memory[op2]) ? 1 : 0;
    return 1;
}

// add immediate
// opcode 0110
int ALU::ai(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[op3] = memory[op1] + op2;
    return 1;
}

// subtract immediate
// opcode 0111
int ALU::si(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[op3] = memory[op1] - op2;
    return 1;
}

// multiply immediate
// opcode 1000
int ALU::mi(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[op3] = memory[op1] * op2;
    return 1;
}

// divide immediate
// opcode 1001
int ALU::di(uint8_t op1, uint8_t op2, uint8_t op3)
{
    if (op2 == 0)
    {
        std::string op = "di " + std::to_string(op1) + " " + std::to_string(op2) + " " + std::to_string(op3);
        throw std::invalid_argument("Error: Division by zero.\nOPCODE: " + op);
    }
    memory[op3] = memory[op1] / op2;
    return 1;
}

// load constant immediate
// opcode 1010
int ALU::lci(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[op3] = op1 + op2;
    return 1;
}

// subtract constant immediate
// opcode 1011
int ALU::sci(uint8_t op1, uint8_t op2, uint8_t op3)
{
    // is this right?
    memory[op3] = op1 - op2;
    return 1;
}

// load using offset
// opcode 1100
int ALU::lo(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[op3] = memory[memory[op1] + memory[op2]];
    return 1;
}

// store using offset
// opcode 1101
int ALU::so(uint8_t op1, uint8_t op2, uint8_t op3)
{
    memory[memory[op1] + memory[op2]] = memory[op3];
    return 1;
}

// jump back
// opcode 1110
int ALU::jb(uint8_t op1, uint8_t op2, uint8_t op3)
{
    return -(int(op1 + op2 + op3));
}

// Functions related to PC
void ALU::setPC(int newPC)
{
    pc = newPC;
}

int ALU::getPC()
{
    return pc;
}

void ALU::printPC()
{
    std::cout << "CURRENT PC: " << pc << std::endl;
}

void ALU::printInstruction(uint16_t instruction)
{
    uint8_t opcode = (instruction >> 12) & 0x0F; // Extract bits [15:12]
    uint8_t op1 = (instruction >> 8) & 0x0F;     // Extract bits [11:8]
    uint8_t op2 = (instruction >> 4) & 0x0F;     // Extract bits [7:4]
    uint8_t op3 = instruction & 0x0F;

    std::cout << "INSTRUCTION (BINARY): " << std::bitset<4>(opcode) << " " << std::bitset<4>(op1) << " " << std::bitset<4>(op2) << " " << std::bitset<4>(op3) << std::endl;
}

void ALU::printAligned(const std::string& label, const std::string& value) 
{
    const int regWidth = 20; 
    const int valWidth = 0;

    // Using fixed width for alignment
    std::cout << std::left << std::setw(regWidth) << label 
              << std::setw(valWidth) << "| " << value << std::endl;
}

void ALU::printInstructionList(uint16_t instruction)
{
    // Bounds check for previous and next instructions
    int prevIndex = (pc > 0) ? pc - 1 : -1;
    int nextIndex = (pc < memory.size() - 1) ? pc + 1 : -1;

    // Empty instructions
    const uint16_t EMPTY_INSTRUCTION = 0x0000;

    // Helper function to format 16-bit binary correctly
    auto formatBinary = [](uint16_t value) 
    {
        std::bitset<16> bits(value);
        std::string binaryStr = bits.to_string();
        return binaryStr.substr(0, 4) + " " + 
               binaryStr.substr(4, 4) + " " + 
               binaryStr.substr(8, 4) + " " + 
               binaryStr.substr(12, 4);
    };

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "PROGRAM COUNTER     | CONTENTS (BINARY)" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    // Print previous instruction
    if (prevIndex != -1 && memory[prevIndex] != EMPTY_INSTRUCTION) 
    {
        printAligned("PREV --> " + std::to_string(prevIndex), formatBinary(memory[prevIndex]));
    } else 
    {
        printAligned("PREV --> " + (prevIndex != -1 ? std::to_string(prevIndex) : "NONE"), "NO INSTRUCTION");
    }
    // Print current instruction
    if (memory[pc] != EMPTY_INSTRUCTION) 
    {
        printAligned("CURR --> " + std::to_string(pc), formatBinary(memory[pc]));
    } else 
    {
        printAligned("CURR --> " + std::to_string(pc), "NO INSTRUCTION");
    }

    // Print next instruction
    if (nextIndex != -1 && memory[nextIndex] != EMPTY_INSTRUCTION) 
    {
        printAligned("NEXT --> " + std::to_string(nextIndex), formatBinary(memory[nextIndex]));
    } else 
    {
        printAligned("NEXT --> " + (nextIndex != -1 ? std::to_string(nextIndex) : "NONE"), "NO INSTRUCTION");
    }
}

// execute(0000 0000 0000 0000)
int ALU::execute(uint16_t instruction)
{
    uint8_t opcode = (instruction >> 12) & 0x0F; // Extract bits [15:12]
    uint8_t op1 = (instruction >> 8) & 0x0F;     // Extract bits [11:8]
    uint8_t op2 = (instruction >> 4) & 0x0F;     // Extract bits [7:4]
    uint8_t op3 = instruction & 0x0F;

    if (opcode >= 0 && opcode < functions.size())
    {
        pc += functions[opcode](op1, op2, op3);
    }
    else
    {
        throw std::invalid_argument("Error: Invalid opcode." + std::to_string(opcode));
    }

    return pc;
}

void ALU::printExecuting(uint16_t instruction)
{
    uint8_t opcode = (instruction >> 12) & 0x0F; // Extract bits [15:12]
    uint8_t op1 = (instruction >> 8) & 0x0F;     // Extract bits [11:8]
    uint8_t op2 = (instruction >> 4) & 0x0F;     // Extract bits [7:4]
    uint8_t op3 = instruction & 0x0F;

    if (opcode == 0b1110)
    {
        std::cout << "CURRENT INSTRUCTION:  " << Instruction::OPCODES[opcode] << " " << std::to_string(op1) << " " << std::to_string(op2) << " " << std::to_string(op3) << std::endl;
        return;
    }
    else if (opcode == 0b1010 || opcode == 0b1011)
    {
        std::cout << "CURRENT INSTRUCTION:  " << Instruction::OPCODES[opcode] << " " << std::to_string(op1) << " " << std::to_string(op2) << " " << Instruction::MEMORY_REGISTERS[op3] << std::endl;
        return;
    }
    else if (opcode == 0b0110 || opcode == 0b0111 || opcode == 0b1000 || opcode == 0b1001)
    {
        std::cout << "CURRENT INSTRUCTION:  " << Instruction::OPCODES[opcode] << " " << Instruction::MEMORY_REGISTERS[op1] << " " << std::to_string(op2) << " " << Instruction::MEMORY_REGISTERS[op3] << std::endl;
        return;
    }
    else if (opcode == 0b0100)
    {
        std::cout << "CURRENT INSTRUCTION:  " << Instruction::OPCODES[opcode] << " " << Instruction::MEMORY_REGISTERS[op1] << " " << Instruction::MEMORY_REGISTERS[op2] << " " << std::to_string(op3) << std::endl;
        return;
    }

    std::cout << "CURRENT INSTRUCTION:  " << Instruction::OPCODES[opcode] << " " << Instruction::MEMORY_REGISTERS[op1] << " " << Instruction::MEMORY_REGISTERS[op2] << " " << Instruction::MEMORY_REGISTERS[op3] << std::endl;
}

// Functions to Print Memory and Contents (if needed)
void ALU::printMemory()
{
    int c = 0;
    for (auto const &x : memory)
    {
        std::cout << c << " : " << x << std::endl;
        c++;
    }
}

void ALU::printInColumnsBinary(const std::vector<uint16_t> &list, int columns)
{
    int rows = (list.size() + columns - 1) / columns; // Calculate number of rows needed

    // Print the elements in multiple columns
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            int index = i + j * rows;
            if (index < list.size())
            {

                // print the 16 bit number in binary
                std::cout << std::setw(3) << index << " : " << std::setw(6) << std::bitset<16>(list[index]) << " | ";
            }
        }
        std::cout << std::endl;
    }
}

void ALU::printInColumnsDecimal(const std::vector<uint16_t> &list, int columns)
{
    int rows = (list.size() + columns - 1) / columns; // Calculate number of rows needed

    // Print the elements in multiple columns
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            int index = i + j * rows;
            if (index < list.size())
            {
                std::cout << std::setw(3) << index << " : " << std::setw(6) << list[index] << " | ";
            }
        }
        std::cout << std::endl;
    }
}

void ALU::printFirstHalfInColumnsBinary(const std::vector<uint16_t> &list, int columns)
{
    int halfMem = list.size() / 2;
    int rows = (halfMem + columns - 1) / columns;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "               MEMORY TABLE                  " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            int index = i + j * rows;
            if (index < halfMem) 
            {
                std::cout << std::setw(2) << index << " : " << std::setw(4) << std::bitset<16>(list[index]);
                if (j < columns - 1) 
                {
                    std::cout << " | ";
                }
            }
        }
        std::cout << std::endl;
    }
}

void ALU::printFirstHalfInColumnsDecimal(const std::vector<uint16_t> &list, int columns)
{
    int halfMem = list.size() / 2;
    int rows = (halfMem + columns - 1) / columns;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "               MEMORY TABLE                  " << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < columns; ++j) 
        {
            int index = i + j * rows;
            if (index < halfMem) 
            {
                std::cout << std::setw(3) << index << " : " << std::setw(13) << list[index];
                if (j < columns - 1) 
                {
                    std::cout << " | ";
                }
            }
        }
        std::cout << std::endl;
    }
}
