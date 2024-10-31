#include "alu.h"

int main() {
    std::vector<uint16_t> instructions = {
        0b1010000010000000, // lci 0, 8, M0         // m0 max store first element to start
        0b1010000010000001, // lci 0, 8, M1         // m1 min store first element to start
        0b1010000001110010, // lci 0, 7, M2         // second element
        0b1010000010110011, // lci 0, 11, M3        // third element
        0b1010000010100100, // lci 0, 10, M4        // fourth element
        0b1010000001000101, // lci 0, 4, M5         // array size
        0b1010000000010110, // lci 0, 1, M6         // index to loop with start at 1 for this problem
        0b1010000000000111, // lci 0, 0, M7         // 0 for logic comparisons
        0b1010000000011000, // lci 0, 1, M8         // 1 for logic comparisons
        0b1010000000011001, // lci 0, 1, M9         // base address of array start at 1 because first element stored twice

        0b0000100101101111, // am M9, M6, M15       // calculate address of element going to compare to min and max
        0b1100111101111010, // lo M15, M7, M10      // load element going to compare to min and max in m10

        0b0101101000001011, // sltm M10, M0, M11    // compare current element examining to min
        0b0100101110000010, // bnem M11, M8, 2      // branch to next comparison if not a new min
        0b1100100101100000, // lo M9, M6, M0        // update min if a new min

        0b0101000110101011, // sltm M1, M10, M11    // compare current element examining to max
        0b0100101110000010, // bnem M11, M8, 2      // branch to next iteration if not a new max
        0b1100100101100001, // lo M9, M6, M1        // update max if a new max

        0b0110011000010110, // ai M6, 1, M6         // increment index
        0b0101011001011011, // sltm M6, M5, M11     // compare index to size
        0b0100101110000010, // bnem M11, M8, 2      // branch out of loop if index not < size
        0b1110000000001011, // jb 0, 0, 11          // jump to beginning of loop 11 instructions above this one (am)

        0b1010000111111100, // lci 1, 15, M12       // calculate address 16
        0b1010001011111101, // lci 2, 15, M13       // calculate address 17
        0b1101110001110000, // so M12, M7, M0       // store min in address 16
        0b1101110101110001, // so M13, M7, M1       // store max in address 17
        // 0b1001000000000111  // di M0, 0, M11     // to check if the program halts
    };

    int pcInit = 32;
    const int memSize = 64;
    std::vector<uint16_t> mainMemory(memSize, 0);

    ALU alu(mainMemory, pcInit);

    // set the memory at the PC with the opcodes
    for (int i = 0; i < instructions.size(); i++)
    {
        mainMemory[alu.getPC() + i] = instructions[i];
    }

    // std::cout << "pc from " << pcInit << " to " << (pcInit + instructions.size() - 1) << std::endl;
    // alu.printInColumnsBinary(mainMemory, 4);
    // alu.printPC();

    std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::cout << "+            PRESS ENTER TO BEGIN           +" << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    while (alu.getPC() < (pcInit + instructions.size())) {
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
        std::cout << "\n++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
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
    return 0;
}
