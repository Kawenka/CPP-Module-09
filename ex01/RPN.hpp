#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>
# include <cstdlib>

class RPN {
    private:
        std::stack<long> _stack;
    public:
        RPN();
        RPN( const RPN& other );
        RPN &operator=( const RPN& other );
        ~RPN();

        void calculate( const std::string& expression );
};

#endif
