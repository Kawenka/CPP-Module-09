#include "BitcoinExchange.hpp"

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << RED << "Usage : ./btc [FILENAME]" << RESET << std::endl;
        return 1;
    }

    try {
        BitcoinExchange btc;
        btc.processInputFile(argv[1]);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
