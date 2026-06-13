/**
 * @file BitcoinExchange.hpp
 * @author Kawenka
 * @version 1.0
 * @date 2026-06-13
 * @brief Definition of the BitcoinExchange class for handling Bitcoin value conversions.
 */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <exception>
# include <sstream>
# include <iomanip>
# include <climits>

/**
 * @class BitcoinExchange
 * @brief Manages a database of Bitcoin prices and processes input files for conversions.
 */
class BitcoinExchange {
    private:
        std::map< std::string, double > _database;

        /**
         * @brief Validates if a date string is in the correct YYYY-MM-DD format and is logically valid.
         * * @param date The date string to validate.
         * @return true if valid, false otherwise.
         */
        bool isValidDate( const std::string& date );

        /**
         * @brief Validates if a value is positive and within the required range (0-1000).
         * * @param value The value to validate.
         * @return true if valid, false otherwise.
         */
        bool isValidValue( double value );

        /**
         * @brief Loads the internal database from a CSV file.
         * * @param filename The path to the CSV file.
         */
        void loadDatabase( const std::string& filename );

    public:
        /**
         * Canonical form
         */
        BitcoinExchange();
        BitcoinExchange( const std::string& filename );
        BitcoinExchange( const BitcoinExchange& other );
        BitcoinExchange &operator=( const BitcoinExchange& other );
        ~BitcoinExchange();

        /**
         * @brief Processes an input file and prints Bitcoin values based on historical data.
         * * @param inputFile The path to the input file.
         */
        void processInputFile( const std::string& inputFile );

        /**
         * @class CantOpenFileException
         * @brief Exception thrown when a file cannot be opened.
         */
        class CantOpenFileException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mCannot open file\033[0m";
                }
        };

        /**
         * @class InvalidDateException
         * @brief Exception thrown when a date is invalid.
         */
        class InvalidDateException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mInvalid date\033[0m";
                }
        };

        /**
         * @class InvalidValueException
         * @brief Exception thrown when a value is invalid.
         */
        class InvalidValueException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mInvalud value\033[0m";
                }
        };

        /**
         * @class InvalidFileException
         * @brief Exception thrown when a file format is invalid.
         */
        class InvalidFileException : public std::exception {
            public:
                virtual const char * what() const throw() {
                    return "\033[31mInvalid file\033[0m";
                }
        };
};

#endif
