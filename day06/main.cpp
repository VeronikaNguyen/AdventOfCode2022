#include <iostream>
#include <vector>

#include "functions.cpp"


int main() {
    auto buffer = read_buffer("day6");
    
    std::cout << "Solution part 1: " << determine_start_of_package(buffer, 4) << std::endl;   

    std::cout << "\nSolution part 2: " << determine_start_of_package(buffer, 14) << std::endl;

    return 0;
}  
