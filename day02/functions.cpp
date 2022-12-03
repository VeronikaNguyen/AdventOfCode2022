#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <vector>


std::vector<std::pair<int, int>> read_file(std::string file_name) {
    std::ifstream infile(file_name);
    char action_char = '\0', reaction_char = '\0';
    std::string line = "";
    std::vector<std::pair<int,int>> round_actions;
    std::map<char, int> action = {{'A', 0}, {'B', 1}, {'C', 2}};        // 0: rock, 1: paper, 2: scissor
    std::map<char, int> reaction = {{'X', 0}, {'Y', 1}, {'Z', 2}};

    while (infile >> action_char >> reaction_char) {
        round_actions.push_back(std::make_pair(action[action_char], reaction[reaction_char]));
    }
    return round_actions;
}


int compute_score_X_is_stone_Y_is_paper_Z_is_scissor(std::vector<std::pair<int, int>> round_actions) {
    int score = 0;
    for (auto action_and_reaction: round_actions) {
        score += action_and_reaction.second + 1;
        if (action_and_reaction.first == action_and_reaction.second) {
            score += 3;
        } else if ((action_and_reaction.first + 1) % 3 == action_and_reaction.second % 3) {
            score += 6;
        }
    }
    return score;
}


int compute_score_X_is_loss_Y_is_tie_Z_is_win(std::vector<std::pair<int, int>> round_actions)  {
    int score = 0;
    for (auto action_and_reaction: round_actions) {
        if (action_and_reaction.second == 1) {
            score += 3;
            score += action_and_reaction.first + 1;
        } else if (action_and_reaction.second == 2) {
            score += 6;
            score += (action_and_reaction.first + 1) % 3 + 1; 
        }
        else {
            score += (action_and_reaction.first - 1 + 3) % 3 + 1;
        }
    }
    return score;
}
