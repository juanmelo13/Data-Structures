#ifndef GRITVM_H
#define GRITVM_H

#include "GritVMBase.hpp"

#include <list>

class GritVM : public GritVMInterface {
public:
    GritVM();
    STATUS              load(const std::string filename, const std::vector<long> &initialMemory);
    STATUS              run();
    std::vector<long>   getDataMem();
    STATUS              reset();
protected:
    // Useful functions called by some public methods
    long evaluate(Instruction& instruct);
    void advance(long jumpDistance);
    void printVM(bool printData, bool printInstruction);
private:
    std::vector<long> dataMem;
    std::list<Instruction> instructMem; 
    std::list<Instruction>::iterator currentInstruct;
    STATUS machineStatus;
    long accumulator; // Stores the results of various operations as an intermediate
};

#endif //GRITVM_H