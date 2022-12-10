#include <iostream>

#include "functions.cpp"


int main() {
    auto instructions = read_instructions("day9");
    
    std::cout << "Solution part 1: " << determine_visited_positions(instructions, 2) << std::endl;   

    std::cout << "\nSolution part 2: " << determine_visited_positions(instructions, 10)  << std::endl;

    return 0;
}  
