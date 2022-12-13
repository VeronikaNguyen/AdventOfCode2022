#include <iostream>
#include <utility>

#include "functions.cpp"


int main() {
    auto lists = read_lists("day13");

    std::cout << "Solution part 1: " << determine_sum_of_correct_pairs(lists) << std::endl;   

    std::cout << "\nSolution part 2: " << determine_decoder_key(lists) << std::endl;

    return 0;
}  
