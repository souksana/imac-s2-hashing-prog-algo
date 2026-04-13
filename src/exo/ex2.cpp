#include "ex2.hpp"

// ============================================================
// POS DIR
// ============================================================

std::ostream& operator<<(std::ostream& os, Position const& pos) {
    os << "(" << pos.x << ", " << pos.y << ")";
    return os;
}

Position operator+(Position lhs, Position const& rhs) {
    lhs += rhs;
    return lhs;
}

Position operator+(Position lhs, Direction const& dir) {
    lhs += dir;
    return lhs;
}

Direction turn_right(Direction dir) {
    switch (dir) {
        case Direction::Haut:   return Direction::Droite;
        case Direction::Droite: return Direction::Bas;
        case Direction::Bas:    return Direction::Gauche;
        case Direction::Gauche: return Direction::Haut;
        default:                return dir;
    }
}

// ============================================================
// LECTURE CARTE
// ============================================================

Input_Structure read_input(std::istream& input_stream) {
    Input_Structure input {};
    int y { 0 };

    for (std::string line {}; std::getline(input_stream, line, '\n') and line != "";) {
        input.width = static_cast<int>(line.size());
        for (int x { 0 }; x < static_cast<int>(line.size()); x++) {
            char c { line[x] };
            if (c == '#') {
                input.obstacles.insert({ x, y });
            } else if (c == '^' || c == '>' || c == 'v' || c == '<') {
                input.guard_pos = { x, y };
                switch (c) {
                    case '^': input.guard_dir = Direction::Haut;   break;
                    case '>': input.guard_dir = Direction::Droite; break;
                    case 'v': input.guard_dir = Direction::Bas;    break;
                    case '<': input.guard_dir = Direction::Gauche; break;
                }
            }
        }
        y++;
    }

    input.height = y;
    return input;
}

// ============================================================
// SIMULATION
// ============================================================

static bool is_in_bounds(Position const& pos, int width, int height) {
    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
}

WalkResult simulate(Input_Structure const& input) {
    WalkResult result {};

    Position  pos { input.guard_pos };
    Direction dir { input.guard_dir };

    result.visited_positions.insert(pos);

    while (true) {
        Position next { pos + dir };

        if (!is_in_bounds(next, input.width, input.height)) {
            result.final_position = pos;
            break;
        }

        if (input.obstacles.count(next)) {
            dir = turn_right(dir);
        } else {
            pos = next;
            result.visited_positions.insert(pos);
            result.steps_taken++;
        }
    }

    return result;
}

// ============================================================
// DETECTION BOUCLE
// ============================================================

// simule avec un obstacle supplementaire, retourne true si boucle
bool creates_loop(Input_Structure const& input, Position const& extra_obstacle) {
    std::unordered_set<GuardState> visited_states {};

    Position  pos { input.guard_pos };
    Direction dir { input.guard_dir };

    while (true) {
        GuardState state { pos, dir };

        // etat deja vu : boucle detectee
        if (visited_states.count(state)) {
            return true;
        }
        visited_states.insert(state);

        Position next { pos + dir };

        // garde sort de la carte : pas de boucle
        if (!is_in_bounds(next, input.width, input.height)) {
            return false;
        }

        // obstacle reel ou obstacle supplementaire : on tourne
        if (input.obstacles.count(next) || next == extra_obstacle) {
            dir = turn_right(dir);
        } else {
            pos = next;
        }
    }
}

// compte pos ou ajouter un obstacle cree une boucle
int count_loop_positions(Input_Structure const& input) {
    // on recupere les positions visitees par le garde sans obstacle supplementaire
    WalkResult base { simulate(input) };

    int count { 0 };

    for (Position const& candidate : base.visited_positions) {
        // on ne peut pas placer un obstacle sur la position initiale du garde
        if (candidate == input.guard_pos) {
            continue;
        }
        if (creates_loop(input, candidate)) {
            count++;
        }
    }

    return count;
}