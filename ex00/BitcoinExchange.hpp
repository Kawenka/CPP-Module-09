#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <exception>
# include <sstream>
# include <iomanip>
# include <climits>


class BitcoinExchange {
    private:
        std::map< std::string, double > _database;

        bool isValidDate( const std::string& date );
        bool isValidValue( double value );
        void loadDatabase( const std::string& filename );

    public:
        BitcoinExchange();
        BitcoinExchange( const std::string& filename );
        BitcoinExchange( const BitcoinExchange& other );
        BitcoinExchange &operator=( const BitcoinExchange& other );
        ~BitcoinExchange();

        void processInputFile( const std::string& inputFile );

        class CantOpenFileException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mCannot open file\033[0m";
                }
        };

        class InvalidDateException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mInvalid date\033[0m";
                }
        };

        class InvalidValueException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mInvalud value\033[0m";
                }
        };

        class InvalidFileException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mInvalid file\033[0m";
                }
        };
};

#endif
