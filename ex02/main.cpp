#include "PmergeMe.hpp"
#include <iostream>

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
