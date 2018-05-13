#include <iostream>
#include <fstream>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "tree.h"
#include "word.h"

int main(int argc, char **argv) {
    //TODO Have this work with command line arguments instead
    std::cout << "Enter a file name: ";
    std::string filename;
    std::cin >> filename;

    std::ifstream file;
    file.open(filename);

    if(!file.good()) {
        std::cerr << "ERROR: File does not exist or can not be accessed" << std::endl;
        return 1;
    }

    auto bst = new BinarySearchTree<Word>;

    std::string delimiters(" ,.?");
    std::vector<std::string> parts;
    for(std::string line; std::getline(file, line);) {
        boost::split(parts, line, boost::is_any_of(delimiters));

        for(std::string &word : parts) {
            std::transform(word.begin(), word.end(), word.begin(), tolower);

            if(!word.empty()) {
                if(!bst->exists(Word(word))) {
                    bst->insert(Word(word));

                } else {
                    bst->get(Word(word))->increaseCount();
                }
            }
        }
    }

    bst->print();

    delete bst;
    return 0;
}