#include "GritVM.hpp"

#include <iostream>
#include <fstream>

// GritVM Compiler class implementation. 
//          By: Juan Jose Melo

GritVM::GritVM() {      // Constructor
    machineStatus = WAITING;
    accumulator = 0;
    printVM(false, false);
}

// Public functions
STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory) {       // Load a GritVM instruction file into the compiler
    if (machineStatus != WAITING) return machineStatus;     // Check if machine is WAITING

    std::ifstream instructFile;
    std::string gvmLine;

    instructFile.open(filename);
    if (!instructFile.is_open()) {      // Check if file opened correctly
        throw ("Error: File could not be opened");
        return machineStatus = ERRORED;
    }
    while (getline(instructFile, gvmLine)) {        // Read the file line by line
        if (gvmLine == "" || gvmLine.at(0) == '#' || isspace(gvmLine.at(0))) continue;      // Check for empty lines, comments and whitespace and skip them

        if (GVMHelper::parseInstruction(gvmLine).operation == UNKNOWN_INSTRUCTION) {        // Check for any unknown operations (errors)
            throw ("Error: Unknown instruction detected");
            return machineStatus = ERRORED;
        }

        instructMem.push_back(GVMHelper::parseInstruction(gvmLine));
    }
    instructFile.close();

    dataMem = initialMemory;
    printVM(!dataMem.empty(), !instructMem.empty());

    if (instructMem.empty()) return machineStatus = WAITING;
    else return machineStatus = READY;
}

STATUS GritVM::run() {      // Run the machine
    if (machineStatus != READY) return machineStatus;       // Check if machine is READY, and if so, set it to RUNNING
    else machineStatus = RUNNING;

    currentInstruct = instructMem.begin();
    while (machineStatus == RUNNING) {
        long jumpDistance = evaluate(*currentInstruct);
        advance(jumpDistance);
    }

    return machineStatus;
}

std::vector<long> GritVM::getDataMem() {return dataMem;}    // Return a copy of the data memory

STATUS GritVM::reset() {        // Reset the machine
    accumulator = 0;
    dataMem.clear();
    instructMem.clear();
    return machineStatus = WAITING;
}

// Private functions
long GritVM::evaluate(Instruction& instruct) {       // Evaluate an instruction
    long jumpDistance = 1;
    INSTRUCTION_SET operation = instruct.operation;
    long arg = instruct.argument;
    
    switch (operation) {        // Execute the desired instruction
    // Accumulator functions
    case CLEAR:
        accumulator = 0;
        break;
    // DM Management functions
    case AT:
        accumulator = dataMem.at(arg);
        break;
    case SET:
        dataMem.at(arg) = accumulator;
        break;
    case INSERT:
        dataMem.insert(dataMem.begin() + arg, accumulator);
        break;
    case ERASE:
        dataMem.erase(dataMem.begin() + arg);
        break;
    // Accumulator maths with a constant
    case ADDCONST:
        accumulator += arg;
        break;
    case SUBCONST:
        accumulator -= arg;
        break;
    case MULCONST:
        accumulator *= arg;
        break;
    case DIVCONST:
        accumulator /= arg;
        break;
    // Accumulator maths with a memory location
    case ADDMEM:
        accumulator += dataMem.at(arg);
        break;
    case SUBMEM:
        accumulator -= dataMem.at(arg);
        break;
    case MULMEM:
        accumulator *= dataMem.at(arg);
        break;
    case DIVMEM:
        accumulator /= dataMem.at(arg);
        break;
    // Instruction jump function
    case JUMPREL:
        jumpDistance = arg;
        break;
    case JUMPZERO:
        if (accumulator == 0) jumpDistance = arg;
        break;
    case JUMPNZERO:
        if (accumulator != 0) jumpDistance = arg;
        break;
    // Misc functions
    case NOOP:      // Do nothing
        break;
    case HALT:      // Halt
        machineStatus = HALTED;
        break;
    case OUTPUT:    // Output the accumulator
        std::cout << accumulator << std::endl;
        break;
    case CHECKMEM:  // Check memory size
        if (!(dataMem.size() >= static_cast<unsigned long>(arg))) machineStatus = ERRORED;
        break;
    default:
        machineStatus = ERRORED;
        break;
  }

    return jumpDistance;
}

void GritVM::advance(long jumpDistance) {       // Advance the current instruction based on the last evaluation
    if (jumpDistance == 0) machineStatus = ERRORED;
    else if (jumpDistance > 0) {
        for(long i = 0; i < jumpDistance; i++) {
            currentInstruct++;
        }
    } 
    else if (jumpDistance < 0) {
        for(long i = jumpDistance; i < 0; i++) {
            currentInstruct--;
        }
    }
}

void GritVM::printVM(bool printData, bool printInstruction) {  // Method provided by the instructor to output the machine's status and private data containers
    std::cout << "****** Output Dump ******" << std::endl;
    std::cout << "Status: " << GVMHelper::statusToString(machineStatus) << std::endl;
    std::cout << "Accumulator: " << accumulator << std::endl;
    if (printData) {
        std::cout << "*** Data Memory ***" << std::endl;
        
        int index = 0;
        std::vector<long>::iterator it = dataMem.begin();

        while (it != dataMem.end()) {
            long item = (*it);
            std::cout << "Location " << index++ << ": " << item << std::endl;
            it++;
        }
    }
    if (printInstruction) {
        std::cout << "*** Instruction Memory ***" << std::endl;
        int index = 0;
        std::list<Instruction>::iterator it = instructMem.begin();
        while (it != instructMem.end()) {
            Instruction item = (*it);
            std::cout << "Instruction " << index++ << ": " << GVMHelper::instructionToString(item.operation) << " " << item.argument << std::endl;
            it++;
        }
    }
}