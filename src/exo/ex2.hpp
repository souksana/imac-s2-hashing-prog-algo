#pragma once

#include <iostream>
#include <unordered_set>
#include <string>

// ============================================================
// Direction & Position
// ============================================================

enum class Direction {
    Haut,
    Droite,
    Bas,
    Gauche
};

struct Position {
    int x {};
    int y {};

    bool operator==(Position const& other) const {
        return x == other.x && y == other.y;
    }

    Position& operator+=(Position const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Position& operator+=(Direction const& dir) {
        switch (dir) {
            case Direction::Haut:   y -= 1; break;
            case Direction::Droite: x += 1; break;
            case Direction::Bas:    y += 1; break;
            case Direction::Gauche: x -= 1; break;
        }
        return *this;
    }
};

std::ostream& operator<<(std::ostream& os, Position const& pos);
Position operator+(Position lhs, Position const& rhs);
Position operator+(Position lhs, Direction const& dir);
Direction turn_right(Direction dir);

// ============================================================
// Hash de Position dans le namespace std
// ============================================================

namespace std {
    template <>
    struct hash<Position> {
        size_t operator()(Position const& pos) const {
            return hash<int>{}(pos.x) ^ (hash<int>{}(pos.y) << 16);
        }
    };
}

// ============================================================
// Structure d'entree
// ============================================================

struct Input_Structure {
    Position                     guard_pos {};
    Direction                    guard_dir { Direction::Haut };
    std::unordered_set<Position> obstacles {};
    int width  {};
    int height {};
};

Input_Structure read_input(std::istream& input_stream);

// ============================================================
// Simulation
// ============================================================

struct WalkResult {
    Position                     final_position {};
    size_t                       steps_taken    {};
    std::unordered_set<Position> visited_positions {};
};

WalkResult simulate(Input_Structure const& input);

// ============================================================
// Detection de boucle
// ============================================================

// etat du garde : position + direction
struct GuardState {
    Position  pos {};
    Direction dir {};

    bool operator==(GuardState const& other) const {
        return pos == other.pos && dir == other.dir;
    }
};

namespace std {
    template <>
    struct hash<GuardState> {
        size_t operator()(GuardState const& state) const {
            // combine le hash de la position et de la direction
            return hash<Position>{}(state.pos) ^ (hash<int>{}(static_cast<int>(state.dir)) << 1);
        }
    };
}

bool creates_loop(Input_Structure const& input, Position const& extra_obstacle);
int  count_loop_positions(Input_Structure const& input);