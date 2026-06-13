#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <sys/time.h>
# include <cstdlib>
# include <exception>
# include <iostream>

class PmergeMe {
    private:
        std::vector<int> _vec;
        std::deque<int> _deque;

        void sortDeque( std::deque<int>& numbers );
        void sortVector( std::vector<int>& numbers );

        double getTime();

        size_t jacobsthal(size_t n);

        template<typename container>
        void printContainer(container& c) {
        size_t i = 0;
        while (i < c.size()) {
            std::cout << c[i] << " ";
            i++;
        }
        std::cout << std::endl;
        // std::cout << "length : " << i << std::endl;
        }

        class InvalidArgumentException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mInvalid argument\033[0m";
                }
        };

    public:
        PmergeMe();
        PmergeMe( const PmergeMe& other );
        PmergeMe &operator=( const PmergeMe& other );
        ~PmergeMe();

        void start(int argc, char **argv);
};

#endif
