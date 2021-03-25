#include "HuffmanTree.hpp"
#include <stack>

//////////////////////////////////////        Protected Functions          //////////////////////////////////////
// Make a map with frequency per character
std::map<char, size_t> HuffmanTree::countFrequencies(std::string str) { 
    std::map<char, size_t> freq;
    for (unsigned int i = 0; i < str.length(); i++) {
        freq[str.at(i)]++;
    }
    return freq;
}

// Construct a Huffman Tree
HuffmanNode* HuffmanTree::createTree(std::map<char, size_t> freq) {
    // Build a HeapQueue of HuffmanNode elements.
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> H;

    for (std::map<char, size_t>::iterator p = freq.begin(); p != freq.end(); p++) {
        HuffmanNode* n = new HuffmanNode(p->first, p->second);
        H.insert(n);
    }

    HuffmanNode *left, *right, *parent;
    // Construct the HuffmanTree
    while (H.size() != 1) {
        left = H.min();
        H.removeMin();
        right = H.min();
        H.removeMin();

        parent = new HuffmanNode('\0', left->getFrequency() + right->getFrequency());
        parent->left = left;
        parent->right = right;

        H.insert(parent);
    }
    return H.min();   
}

// Destruct a Huffman Tree
void HuffmanTree::destroyTree(HuffmanNode* root) {
    if (root != nullptr && root->isBranch()) {
        destroyTree(root->left);
        destroyTree(root->right);
    }
    if(root != nullptr) delete root;
}

// Construct a map with the prefixes per character
void HuffmanTree::encodePrefixes(HuffmanNode* root, std::string pref, std::map<char, std::string> &prefixes) {
    if (root->isLeaf()) {
        prefixes[root->getCharacter()] = pref;
    }
    if (root->left != nullptr) {
        encodePrefixes(root->left, pref + "0", prefixes);
    }
    if (root->right != nullptr) {
        encodePrefixes(root->right, pref + "1", prefixes);
    }
}

// Traverse a tree to create the serialized version
void HuffmanTree::postOrderSerial(const HuffmanNode* root, std::stringstream &serial) const {
    if (root->isBranch()) {
        postOrderSerial(root->left, serial);
        postOrderSerial(root->right, serial);
    }
    
    if (root->isLeaf()) serial << "L" << root->getCharacter();
    else serial << "B";
}

//////////////////////////////////////        Public Functions          //////////////////////////////////////
std::string HuffmanTree::compress(const std::string inputStr) {
    // Destroy any previous trees
    // if (T != nullptr) destroyTree(T);    // CAUSING SEGMENTATION ERROR!

    // Maps that contain frequency and prefix per character
    std::map<char, size_t> frequencies = countFrequencies(inputStr);
    std::map<char, std::string> prefixes;

    // Huffman Tree
    T = createTree(frequencies);
    encodePrefixes(T, "", prefixes);

    std::string encoded;
    for (unsigned int i = 0; i < inputStr.length(); i++) {  // string encoding...
        encoded.append(prefixes[inputStr.at(i)]);
    }
    
    return encoded;
}

std::string HuffmanTree::serializeTree() const {
    // String Stream with the serialized tree
    std::stringstream serial;
    postOrderSerial(T, serial);

    return serial.str();
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    // Temporary stack and node pointers
    std::stack<HuffmanNode*> tempStack;
    HuffmanNode *left, *right, *curr;

    // Create a Huffman tree from the serialized version
    for (std::string::const_iterator i = serializedTree.begin(); i != serializedTree.end(); i++) {
        if (*i == 'L') {
            tempStack.push(new HuffmanNode(*(++i), 0));
        }
        else if (*i == 'B') {
            right = tempStack.top();
            tempStack.pop();
            left = tempStack.top();
            tempStack.pop();

            T = new HuffmanNode('\0', 0);
            T->left = left;
            T->right = right;
            tempStack.push(T);
        }
    }

    T = tempStack.top();
    
    std::stringstream decoded;

    
    // Decode using the tree
    curr = T;
    for (std::string::const_iterator i = inputCode.begin(); i != inputCode.end(); i++) {
        curr = *i == '0' ? curr->left : curr->right;
        if (curr->isLeaf()) { 
            decoded << curr->getCharacter();
            curr = T;
        }
        
    }

    return decoded.str();
}