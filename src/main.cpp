#include <iostream>
#include <fstream>
#include <sstream>
#include "exo/ex1.hpp"
#include "exo/ex2.hpp"

// int main() {
//     size_t max { 1024 };

//     std::string s1 { "abc" };
//     std::string s2 { "cba" };

//     std::cout << "folding_string_hash(\"abc\") = "         << folding_string_hash(s1, max)              << std::endl;
//     std::cout << "folding_string_hash(\"cba\") = "         << folding_string_hash(s2, max)              << std::endl;

//     std::cout << "folding_string_ordered_hash(\"abc\") = " << folding_string_ordered_hash(s1, max)      << std::endl;
//     std::cout << "folding_string_ordered_hash(\"cba\") = " << folding_string_ordered_hash(s2, max)      << std::endl;

//     std::cout << "polynomial_rolling_hash(\"abc\") = "     << polynomial_rolling_hash(s1, 31, 1000000009) << std::endl;
//     std::cout << "polynomial_rolling_hash(\"cba\") = "     << polynomial_rolling_hash(s2, 31, 1000000009) << std::endl;

//     return 0;
// }

void test_ex1() {
    size_t max { 1024 };
    std::string s1 { "abc" };
    std::string s2 { "cba" };
 
    std::cout << "=== ex1 ===" << std::endl;
    std::cout << "folding_string_hash(\"abc\") = "         << folding_string_hash(s1, max)               << std::endl;
    std::cout << "folding_string_hash(\"cba\") = "         << folding_string_hash(s2, max)               << std::endl;
    std::cout << "folding_string_ordered_hash(\"abc\") = " << folding_string_ordered_hash(s1, max)       << std::endl;
    std::cout << "folding_string_ordered_hash(\"cba\") = " << folding_string_ordered_hash(s2, max)       << std::endl;
    std::cout << "polynomial_rolling_hash(\"abc\") = "     << polynomial_rolling_hash(s1, 31, 1000000009) << std::endl;
    std::cout << "polynomial_rolling_hash(\"cba\") = "     << polynomial_rolling_hash(s2, 31, 1000000009) << std::endl;
}
 
void test_ex2_example() {
    std::string map {
        "....#.....\n"
        ".........#\n"
        "..........\n"
        "..#.......\n"
        ".......#..\n"
        "..........\n"
        ".#..^.....\n"
        "........#.\n"
        "#.........\n"
        "......#...\n"
    };
 
    std::istringstream stream { map };
    Input_Structure input  { read_input(stream) };
    WalkResult      result { simulate(input) };
 
    std::cout << "\n=== ex2 - carte exemple ===" << std::endl;
    std::cout << "position initiale  : " << input.guard_pos              << std::endl;
    std::cout << "position finale    : " << result.final_position        << std::endl;
    std::cout << "pas effectues      : " << result.steps_taken           << std::endl;
    std::cout << "positions visitees : " << result.visited_positions.size() << " (attendu: 41)" << std::endl;
    std::cout << "positions boucle   : " << count_loop_positions(input)  << " (attendu: 6)"    << std::endl;
}
 
void test_ex2_file(std::string const& filepath) {
    std::ifstream file { filepath };
    if (!file.is_open()) {
        std::cerr << "impossible d'ouvrir le fichier : " << filepath << std::endl;
        return;
    }
 
    Input_Structure input  { read_input(file) };
    WalkResult      result { simulate(input) };
 
    std::cout << "\n=== ex2 - fichier reel ===" << std::endl;
    std::cout << "position initiale  : " << input.guard_pos              << std::endl;
    std::cout << "position finale    : " << result.final_position        << std::endl;
    std::cout << "pas effectues      : " << result.steps_taken           << std::endl;
    std::cout << "positions visitees : " << result.visited_positions.size() << " (attendu: entre 5300 et 5500)" << std::endl;
    std::cout << "positions boucle   : " << count_loop_positions(input)  << std::endl;
}
 
int main() {
    test_ex1();
    test_ex2_example();
    test_ex2_file("input_guard_patrol.txt");
 
    return 0;
}