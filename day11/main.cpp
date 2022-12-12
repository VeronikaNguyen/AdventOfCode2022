#include <iostream>
#include <vector>

#include "functions.cpp"


int main() {
    std::vector<Monkey> monkeys = read_monkeys("day11");
    std::vector<Monkey> monkeys_copy = monkeys;

    std::cout << "Solution part 1: " << compute_monkey_business(monkeys, 20, true) << std::endl;   

    std::cout << "\nSolution part 2: " << compute_monkey_business(monkeys_copy, 10000, false) << std::endl;

    return 0;
}  
