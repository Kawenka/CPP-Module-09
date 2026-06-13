#include "RPN.hpp"
#include <climits>

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN &RPN::operator=(const RPN& other) {
    if (this != &other)
        this->_stack = other._stack;
    return *this;
}

RPN::~RPN() {}

void RPN::calculate(const std::string& expression) {
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (token.length() == 1 && std::string("+-*/").find(token) != std::string::npos) {
            if (this->_stack.size() < 2) {
                std::cout << "Error" << std::endl;
                return ;
            }

            long right = this->_stack.top();
            this->_stack.pop();
            long left = this->_stack.top();
            this->_stack.pop();

            if (token == "+") this->_stack.push(left + right);
            if (token == "-") this->_stack.push(left - right);
            if (token == "*") this->_stack.push(left * right);
            if (token == "/") {
                if (right == 0) {
                    std::cerr << "Error" << std::endl;
                    return;
                }
                this->_stack.push(left / right);
            }
            if (this->_stack.top() > INT_MAX || this->_stack.top() < INT_MIN) {
                std::cerr << "Error" << std::endl;
                return;
            }
        }
        else {
            if (token.length() > 1 || !std::isdigit(token[0])) {
                std::cerr << "Error" << std::endl;
                return;
            }
            int value = std::atoi(token.c_str());
            this->_stack.push(value);
        }
    }
    if (this->_stack.size() != 1) {
        std::cerr << "Error" << std::endl;
        return;
    }
    std::cout << this->_stack.top() << std::endl;
}
