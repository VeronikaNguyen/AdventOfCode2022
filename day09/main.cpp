#include <iostream>

#include "functions.cpp"


int main() {
    auto positions = read_positions("day9");
    
    std::cout << "Solution part 1: " << determine_visited_positions(positions, 2) << std::endl;   

    std::cout << "\nSolution part 2: " << determine_visited_positions(positions, 10)  << std::endl;

    return 0;
}  
