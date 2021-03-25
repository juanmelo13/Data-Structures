#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"

#include <map>
#include <sstream>

// Huffman Tree class implementation. The class has the abilityt to compress, serialize and decompress a message using Huffman Static Code.
//                      Writen by: Juan Melo

class HuffmanTree : public HuffmanTreeBase {
public: 
    std::string compress(const std::string inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string inputCode, const std::string serializedTree);
protected:
    std::map<char, size_t> countFrequencies(std::string str);
    HuffmanNode* createTree(std::map<char, size_t> freq);
    void destroyTree(HuffmanNode* root);
    void encodePrefixes(HuffmanNode* root, std::string pref, std::map<char, std::string> &prefixes);
    void postOrderSerial(const HuffmanNode* root, std::stringstream &serial) const;
private:
    HuffmanNode* T;     // Huffman Tree
};

#endif // HUFFMAN_TREE_H