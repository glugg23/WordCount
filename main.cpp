#include <iostream>
#include <fstream>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "tree.h"
#include "word.h"

struct Sorter {
    bool operator()(const Word &a, const Word &b) const {
        return a.getCount() > b.getCount();
    }
};

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
    int totalCount = 0;

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

                ++totalCount;
            }
        }
    }

    std::vector<Word> words;
    bst->returnArray(words);

    std::sort(words.begin(), words.end(), Sorter());

    std::cout << "Total word count: " << totalCount << std::endl;
    std::cout << "Unique word count: "<< words.size() << std::endl;
    std::cout << '\n';

    for(const auto &word : words) {
        std::cout << word << std::endl;
    }

    delete bst;
    return 0;
}