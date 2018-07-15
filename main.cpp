#include <iostream>
#include <fstream>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "tree.h"
#include "word.h"

void splitInput(std::unique_ptr<BinarySearchTree<Word>> &bst, std::istream &in, int &totalCount, bool capitalFlag) {
    std::string delimiters(" ,.?");
    std::vector<std::string> parts;

    std::string line;
    while(std::getline(in, line)) {
        boost::split(parts, line, boost::is_any_of(delimiters));

        for(auto &word : parts) {
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
}

void print(std::ostream &os, const int count, const std::vector<Word> &words) {
    os << "Total word count: " << count << '\n';
    os << "Unique word count: "<< words.size() << '\n';
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

    auto bst = std::make_unique<BinarySearchTree<Word>>();
    int totalCount = 0;

    if(inputFlag) {
        if(!inputFile.good()) {
            std::cerr << "ERROR: File does not exist or can not be accessed" << std::endl;
            return 1;
        }

        splitInput(bst, inputFile, totalCount, capitalFlag);

    } else {
        std::cout << "Enter string:\n"
                     "(Press Ctrl-D on a new line to end)\n" << std::endl;

        splitInput(bst, std::cin, totalCount, capitalFlag);
    }

    std::vector<Word> words;
    bst->returnArray(words);

    std::sort(words.begin(), words.end(),
        [](Word a, Word b) { return a.getCount() > b.getCount(); });

    if(outputFlag) {
        print(outputFile, totalCount, words);

    } else {
        print(std::cout, totalCount, words);
    }

    return 0;
}