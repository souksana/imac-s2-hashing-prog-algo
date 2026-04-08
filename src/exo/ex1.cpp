#include "ex1.hpp"

// hash simple
size_t folding_string_hash(std::string const& s, size_t max) {
    size_t hash { 0 };
    for (char c : s) {
        hash = (hash + static_cast<size_t>(c)) % max;
    }
    return hash;
}

// hash ordonné
size_t folding_string_ordered_hash(std::string const& s, size_t max) {
    size_t hash { 0 };
    for (size_t i { 0 }; i < s.size(); i++) {
        hash = (hash + static_cast<size_t>(s[i]) * (i + 1)) % max;
    }
    return hash;
}

// bonus :D
size_t polynomial_rolling_hash(std::string const& s, size_t p, size_t m) {
    size_t hash  { 0 };
    size_t power { 1 };
    for (char c : s) {
        hash  = (hash + static_cast<size_t>(c) * power) % m;
        power = (power * p) % m;
    }
    return hash;
}