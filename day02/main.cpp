#include <iostream>
#include <vector>

#include "functions.cpp"


int main() {
    std::vector<std::pair<int, int>>  round_actions = read_file("day2");
    
    std::cout << "Solution part 1: " << compute_score_X_is_stone_Y_is_paper_Z_is_scissor(round_actions) << std::endl;   

    std::cout << "\nSolution part 2: " << compute_score_X_is_loss_Y_is_tie_Z_is_win(round_actions) << std::endl;

    return 0;
}  
