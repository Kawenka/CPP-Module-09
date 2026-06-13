/**
 * @file RPN.hpp
 * @author Kawenka
 * @version 1.0
 * @date 2026-06-13
 * @brief Definition of the RPN class for Reverse Polish Notation calculations.
 */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>
# include <cstdlib>

/**
 * @class RPN
 * @brief Handles Reverse Polish Notation (RPN) expression evaluation using a stack.
 */
class RPN {
    private:
        std::stack<long> _stack;
    public:
        /**
         * Canonical form
         */
        RPN();
        RPN( const RPN& other );
        RPN &operator=( const RPN& other );
        ~RPN();

        /**
         * @brief Evaluates an RPN expression and prints the result.
         * * @param expression The RPN string to evaluate.
         */
        void calculate( const std::string& expression );
};

#endif
