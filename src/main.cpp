#include <iostream>
#include "exo/ex1.hpp"

int main() {
    size_t max { 1024 };

    std::string s1 { "abc" };
    std::string s2 { "cba" };

    std::cout << "folding_string_hash(\"abc\") = "         << folding_string_hash(s1, max)              << std::endl;
    std::cout << "folding_string_hash(\"cba\") = "         << folding_string_hash(s2, max)              << std::endl;

    std::cout << "folding_string_ordered_hash(\"abc\") = " << folding_string_ordered_hash(s1, max)      << std::endl;
    std::cout << "folding_string_ordered_hash(\"cba\") = " << folding_string_ordered_hash(s2, max)      << std::endl;

    std::cout << "polynomial_rolling_hash(\"abc\") = "     << polynomial_rolling_hash(s1, 31, 1000000009) << std::endl;
    std::cout << "polynomial_rolling_hash(\"cba\") = "     << polynomial_rolling_hash(s2, 31, 1000000009) << std::endl;

    return 0;
}