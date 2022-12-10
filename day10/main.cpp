#include <iostream>

#include "functions.cpp"


int main() {
    auto instructions = read_instructions("day10");
    auto register_values = compute_register_values(instructions);
    
    std::cout << "Solution part 1: " << compute_signal_strengths_sum_at_rounds(register_values, std::vector<int>{20, 60, 100, 140, 180, 220}) << std::endl;   

    std::cout << "\nSolution part 2: " << std::endl;
    print_sprite(register_values, std::vector<int>{40, 80, 120, 160, 200, 240}, 40);

    return 0;
}  
