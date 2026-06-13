#include "RPN.hpp"

int main(int argc, char **argv) {
    if (argc != 2)
        return 1;
    RPN rpn;
    rpn.calculate(argv[1]);
}
