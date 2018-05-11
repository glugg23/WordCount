#pragma once

#include <iostream>

class Word {
private:
    std::string word;
    int count = 1;

public:
    explicit Word(std::string word) : word(std::move(word)) {}

    const std::string &getWord() const {
        return word;
    }

    int getCount() const {
        return count;
    }

    /*
     * This looks like a post-increment but actually is a pre-increment.
     * This has been done for stylistic reasons as there should never be
     * a reason to care in which order count gets increased
     */

    Word& operator++(int) {
        ++count;
        return *this;
    }

    bool operator==(const Word &rhs) const {
        return word == rhs.word;
    }

    bool operator!=(const Word &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Word &rhs) const {
        return word < rhs.word;
    }

    bool operator>(const Word &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Word &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Word &rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream &operator<<(std::ostream &os, const Word &word) {
        os << "{ word: \"" << word.word << "\", count: " << word.count << " }";
        return os;
    }
};