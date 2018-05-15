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

void print(std::ostream &os, const int count, const std::vector<Word> &words) {
    os << "Total word count: " << count << std::endl;
    os << "Unique word count: "<< words.size() << std::endl;
    os << '\n';

    for(const auto &word : words) {
        os << word << std::endl;
    }
}

int main(int argc, char **argv) {
    std::ifstream inputFile;
    std::ofstream outputFile;
    bool inputFlag = false, outputFlag = false, capitalFlag = false;

    for(int i = 0; i < argc; ++i) {
        if(std::string(argv[i]) == "-i") {
            inputFile.open(argv[i + 1]);
            inputFlag = true;
        }

        if(std::string(argv[i]) == "-o") {
            outputFile.open(argv[i + 1]);
            outputFlag = true;
        }

        if(std::string(argv[i]) == "-c") {
            capitalFlag = true;
        }
    }

    //TODO Add section here to get input from cin when inputFlag is false

    if(!inputFile.good()) {
        std::cerr << "ERROR: File does not exist or can not be accessed" << std::endl;
        return 1;
    }

    auto bst = new BinarySearchTree<Word>;

    std::string delimiters(" ,.?");
    std::vector<std::string> parts;
    int totalCount = 0;

    for(std::string line; std::getline(inputFile, line);) {
        boost::split(parts, line, boost::is_any_of(delimiters));

        for(std::string &word : parts) {
            if(capitalFlag) {
                std::transform(word.begin(), word.end(), word.begin(), tolower);
            }

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

    if(outputFlag) {
        print(outputFile, totalCount, words);

    } else {
        print(std::cout, totalCount, words);
    }

    delete bst;
    return 0;
}