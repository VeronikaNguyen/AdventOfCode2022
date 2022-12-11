#include <iostream>

#include "functions.cpp"


int main() {
    auto monkeys = read_monkeys("day11");
    
    std::cout << "Solution part 1: " << compute_monkey_business(monkeys, 20, true) << std::endl;   

    monkeys = read_monkeys("day11");

    std::cout << "\nSolution part 2: " << compute_monkey_business(monkeys, 10000, false) << std::endl;

    return 0;
}  
