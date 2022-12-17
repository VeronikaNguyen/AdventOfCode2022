#include <iostream>

#include "functions.cpp"


int main() {
    auto valves_and_tunnels = read_valves_and_tunnels("day16");
    
    std::cout << "Solution part 1: " << compute_highest_pressure(valves_and_tunnels.valves, valves_and_tunnels.tunnels, 30) << std::endl;   
     
    std::cout << "\nSolution part 2: " << "" << std::endl;

    return 0;
}  
