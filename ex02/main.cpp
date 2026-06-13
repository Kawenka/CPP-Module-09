/**
 * @file main.cpp
 * @author Kawenka
 * @version 1.0
 * @date 2026-06-13
 * @brief Entry point for the PmergeMe sorting program.
 */

#include "PmergeMe.hpp"
#include <iostream>

/**
 * @brief Main function.
 * Initializes the PmergeMe instance and starts the sorting process with command-line arguments.
 * * @param argc Number of command line arguments.
 * * @param argv Array of command line arguments.
 * @return 0 on success.
 */
int main(int argc, char **argv) {
    PmergeMe pmergeme;
    if (argc <= 2)
        return 0;

    try {
        pmergeme.start(argc, argv);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    return (0);
}
