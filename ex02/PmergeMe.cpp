#include "PmergeMe.hpp"
#include <cerrno>
#include <iostream>
#include <climits>
#include <algorithm>

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deque(other._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe& other) {
    if (this != &other) {
        this->_vec = other._vec;
        this->_deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

double PmergeMe::getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void PmergeMe::start(int argc, char **argv) {
    (void)argc;
    for (size_t i = 1; argv[i]; i++) {
        
        errno = 0;
        char *endPtr;
        long check = std::strtol(argv[i], &endPtr, 10);
        
        if (errno == ERANGE)
            throw PmergeMe::InvalidArgumentException();

        if (argv[i][0] == '\0' || *endPtr != '\0')
            throw PmergeMe::InvalidArgumentException();

        if (check < 0 || check > INT_MAX)
            throw PmergeMe::InvalidArgumentException();

        this->_vec.push_back(static_cast<int>(check));
        this->_deque.push_back(static_cast<int>(check));
    }

    std::cout << "Before: ";
    PmergeMe::printContainer(this->_vec);

    double startVector = getTime();
    this->sortVector(this->_vec);
    double timeVector = getTime() - startVector;

    double startDeque = getTime();
    this->sortDeque(this->_deque);
    double timeDeque = getTime() - startDeque;

    std::cout<< "After:  ";
    PmergeMe::printContainer(this->_deque);

    std::cout << "Time to process a range of " << this->_vec.size()
            << " elements with std::vector : " << timeVector << " us" << std::endl;
    std::cout << "Time to process a range of " << this->_deque.size()
            << " elements with std::deque : " << timeDeque << " us" << std::endl;
}

void PmergeMe::sortDeque(std::deque<int>& numbers) {
    int straggler = -1;
    bool odd = false;

    if (numbers.size() <= 1)
        return;

    if (numbers.size() % 2 == 1) {
        straggler = numbers[numbers.size() - 1];
        numbers.pop_back();
        odd = true;
    }

    std::deque<std::pair<int, int> > pairs;
    std::deque<int> winners;
    for (size_t i = 0; i < numbers.size(); i += 2) {
        int num1 = numbers[i];
        int num2 = numbers[i + 1];

        if (num1 > num2)
            pairs.push_back(std::make_pair(num2, num1)); 
        else
            pairs.push_back(std::make_pair(num1, num2));

        winners.push_back(pairs.back().second);
    }

    sortDeque(winners);

    std::deque<int> main;
    std::deque<int> waiting;

    // pushing the lowest number in the main deque
    for(std::deque<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        if (it->second == winners[0]) {
            main.push_back(it->first);
            main.push_back(it->second);
            pairs.erase(it);
            break;
        }
    }

    // pushing the rest
    for (size_t i = 1; i < winners.size(); i++) {
        for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
            if (it->second == winners[i]) {
                main.push_back(it->second);
                waiting.push_back(it->first);
                pairs.erase(it);
                break;
            }
        }
    }

    if (odd)
        waiting.push_back(straggler);

    if (waiting.empty()) {
        numbers = main;
        return ;
    }

    std::deque<int> n_jacob;
    size_t index_jacob = 2;

    while (jacobsthal(index_jacob) < waiting.size()) {
        n_jacob.push_back(jacobsthal(index_jacob));
        index_jacob++;
    }

    if (n_jacob.empty() || static_cast<size_t>(n_jacob.back()) < waiting.size() - 1)
        n_jacob.push_back(waiting.size() - 1);

    size_t last_index = 0;
    for (size_t i = 0; i < n_jacob.size(); i++) {
        size_t limit = n_jacob[i];
        size_t index = limit;
        while (1) {
            if (index < waiting.size()) {
                int insert = waiting[index];
                std::deque<int>::iterator it = std::lower_bound(main.begin(), main.end(), insert);
                main.insert(it, insert);
            }
            if (index == last_index)
                break;
            index--;
        }
        last_index = limit + 1;
    }

    numbers = main;
}

void PmergeMe::sortVector(std::vector<int>& numbers) {
    int straggler = -1;
    bool odd = false;

    if (numbers.size() <= 1)
        return;

    if (numbers.size() % 2 == 1) {
        straggler = numbers[numbers.size() - 1];
        numbers.pop_back();
        odd = true;
    }

    std::vector<std::pair<int, int> > pairs;
    std::vector<int> winners;
    for (size_t i = 0; i < numbers.size(); i += 2) {
        int num1 = numbers[i];
        int num2 = numbers[i + 1];

        if (num1 > num2)
            pairs.push_back(std::make_pair(num2, num1)); 
        else
            pairs.push_back(std::make_pair(num1, num2));

        winners.push_back(pairs.back().second);
    }

    sortVector(winners);

    std::vector<int> main;
    std::vector<int> waiting;

    // pushing the lowest number in the main vector
    for(std::vector<std::pair<int,int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        if (it->second == winners[0]) {
            main.push_back(it->first);
            main.push_back(it->second);
            pairs.erase(it);
            break;
        }
    }

    // pushing the rest
    for (size_t i = 1; i < winners.size(); i++) {
        for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
            if (it->second == winners[i]) {
                main.push_back(it->second);
                waiting.push_back(it->first);
                pairs.erase(it);
                break;
            }
        }
    }

    if (odd)
        waiting.push_back(straggler);

    if (waiting.empty()) {
        numbers = main;
        return ;
    }

    std::vector<int> n_jacob;
    size_t index_jacob = 2;

    while (jacobsthal(index_jacob) < waiting.size()) {
        n_jacob.push_back(jacobsthal(index_jacob));
        index_jacob++;
    }

    if (n_jacob.empty() || static_cast<size_t>(n_jacob.back()) < waiting.size() - 1)
        n_jacob.push_back(waiting.size() - 1);

    size_t last_index = 0;
    for (size_t i = 0; i < n_jacob.size(); i++) {
        size_t limit = n_jacob[i];
        size_t index = limit;
        while (1) {
            if (index < waiting.size()) {
                int insert = waiting[index];
                std::vector<int>::iterator it = std::lower_bound(main.begin(), main.end(), insert);
                main.insert(it, insert);
            }
            if (index == last_index)
                break;
            index--;
        }
        last_index = limit + 1;
    }

    numbers = main;
}

size_t PmergeMe::jacobsthal(size_t n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}
