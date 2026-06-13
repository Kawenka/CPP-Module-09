/**
 * @file main.cpp
 * @author Kawenka
 * @version 1.0
 * @date 2026-06-13
 * @brief Entry point for the RPN calculation program.
 */

#include "RPN.hpp"

/**
 * @brief Main function.
 * Parses the command line argument as an RPN expression and evaluates it.
 * * @param argc Number of command line arguments.
 * * @param argv Array of command line arguments.
 * @return 0 on success, 1 on failure.
 */
int main(int argc, char **argv) {
    if (argc != 2)
        return 1;
    RPN rpn;
    rpn.calculate(argv[1]);
}
