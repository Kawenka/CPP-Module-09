/**
 * @file PmergeMe.hpp
 * @author Kawenka
 * @version 1.0
 * @date 2026-06-13
 * @brief Definition of the PmergeMe class for sorting sequences using the Ford-Johnson algorithm.
 */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <sys/time.h>
# include <cstdlib>
# include <exception>
# include <iostream>

/**
 * @class PmergeMe
 * @brief Implements the Merge-Insertion sort (Ford-Johnson algorithm) using two different containers.
 */
class PmergeMe {
    private:
        std::vector<int> _vec;
        std::deque<int> _deque;

        /**
         * @brief Sorts a deque of integers using the Merge-Insertion sort algorithm.
         * * @param numbers The deque to sort.
         */
        void sortDeque( std::deque<int>& numbers );

        /**
         * @brief Sorts a vector of integers using the Merge-Insertion sort algorithm.
         * * @param numbers The vector to sort.
         */
        void sortVector( std::vector<int>& numbers );

        /**
         * @brief Retrieves the current time in microseconds.
         * @return The current time as a double.
         */
        double getTime();

        /**
         * @brief Calculates the n-th Jacobsthal number.
         * * @param n The index of the Jacobsthal number to calculate.
         * @return The n-th Jacobsthal number.
         */
        size_t jacobsthal(size_t n);

        /**
         * @brief Generic function to print the contents of a container.
         * * @param c The container to print.
         */
        template<typename container>
        void printContainer(container& c) {
        size_t i = 0;
        while (i < c.size()) {
            std::cout << c[i] << " ";
            i++;
        }
        std::cout << std::endl;
        }

        /**
         * @class InvalidArgumentException
         * @brief Exception thrown when an invalid argument is provided to the program.
         */
        class InvalidArgumentException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mInvalid argument\033[0m";
                }
        };

    public:
        /**
         * Canonical form
         */
        PmergeMe();
        PmergeMe( const PmergeMe& other );
        PmergeMe &operator=( const PmergeMe& other );
        ~PmergeMe();

        /**
         * @brief Starts the sorting process with the provided command line arguments.
         * * @param argc Number of command line arguments.
         * * @param argv Array of command line arguments.
         */
        void start(int argc, char **argv);
};

#endif
