#include <iostream>
#include <deque>
#include <vector>

#include "functions.cpp"


int main() {
    auto stacks_and_moves = read_stacks_and_moves("day5");
    
    std::cout << "Solution part 1: " << read_top_of_stacks_after_move(stacks_and_moves.stacks, stacks_and_moves.moves) << std::endl;   

    std::cout << "\nSolution part 2: " << read_top_of_stacks_after_whole_stack_move(stacks_and_moves.stacks, stacks_and_moves.moves) << std::endl;

    return 0;
}  
