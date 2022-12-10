#include <iostream>

#include "functions.cpp"


int main() {
    auto trees = read_trees("day8");
    
    std::cout << "Solution part 1: " << count_visible_trees(trees) << std::endl;   

    std::cout << "\nSolution part 2: " << determine_highest_viewing_score(trees) << std::endl;

    return 0;
}  
