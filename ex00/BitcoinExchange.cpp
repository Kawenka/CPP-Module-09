/**
 * @file BitcoinExchange.cpp
 * @author Kawenka
 * @version 1.0
 * @date 2026-06-13
 * @brief Implementation of the BitcoinExchange class methods for database management and value calculation.
 */

#include "BitcoinExchange.hpp"

/**
 * Canonical form
 */
BitcoinExchange::BitcoinExchange() {
    this->loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const std::string& filename) {
    this->loadDatabase(filename);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    this->_database = other._database;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other)
        this->_database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

/**
 * @brief Loads historical Bitcoin data from a CSV file.
 * Reads the file line by line, validates date and value formats, 
 * and stores valid data in the internal structure.
 * * @param filename The path to the data file.
 * @throw BitcoinExchange::CantOpenFileException If the file cannot be opened.
 * @throw BitcoinExchange::InvalidFileException If the file is empty or invalid from the first line.
 */
void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream dataFile(filename.c_str());
    if (!dataFile)
        throw BitcoinExchange::CantOpenFileException();

    std::string line;
    if (!std::getline(dataFile, line))
        throw BitcoinExchange::InvalidFileException();

    while (std::getline(dataFile, line)) {
        if (line.empty())
            continue;
        
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            continue;
        std::string date = line.substr(0, pos);
        if (!BitcoinExchange::isValidDate(date))
            continue;
        
        std::string stringValue = line.substr(pos + 1);
        double value = 0;
        std::stringstream ss(stringValue);
        if (!(ss >> value))
            continue;

        char leftover;
        if (ss >> leftover)
            continue;
        if (value < 0)
            continue;
        
        this->_database[date] = value;
    }
}

/**
 * @brief Processes a user input file to evaluate Bitcoin amounts at specific dates.
 * Outputs the calculation result or an error message for each read line.
 * * @param inputFile The path to the input file containing the requests.
 * @throw BitcoinExchange::CantOpenFileException If the file cannot be opened.
 * @throw BitcoinExchange::InvalidFileException If the file is empty or unreadable.
 */
void BitcoinExchange::processInputFile(const std::string& inputFile) {
    std::ifstream inputfile(inputFile.c_str());
    if (!inputfile)
        throw BitcoinExchange::CantOpenFileException();

    std::string line;
    if (!std::getline(inputfile, line))
        throw BitcoinExchange::InvalidFileException();

    while (std::getline(inputfile, line)) {
        if (line.empty())
            continue;

        if (line.length() < 14 || line.substr(10, 3) != " | ") {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr(0, 10);
        std::string stringValue = line.substr(13);

        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << date << std::endl;   
            continue;
        }

        double value = 0;
        std::stringstream ss(stringValue);
        if (!(ss >> value)) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        char leftover;
        if (ss >> leftover) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        if (!isValidValue(value))
            continue;

        std::map<std::string, double>::iterator it = this->_database.lower_bound(date);

        if (it == this->_database.begin() && it->first != date) {
            std::cout << "Error: date too old, no data available." << std::endl;
            continue;
        }

        if (it == this->_database.end() || it->first != date)
            it--;
            
        std::cout << date << " => " << value << " = " << value * it->second << std::endl;
    }
}

/**
 * @brief Checks the format compliance and temporal validity of a date.
 * Ensures the string respects the YYYY-MM-DD format and accounts for leap years.
 * * @param date The string representing the date to validate.
 * @return true if the date is syntactically and logically correct, false otherwise.
 */
bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.length() != 10)
        return false;

    int year, month, day;
    char sep1, sep2, leftover;
    std::stringstream ss(date);

    if (!(ss >> year >> sep1 >> month >> sep2 >> day))
        return false;
    if (sep1 != '-' || sep2 != '-')
        return false;
    if (ss >> leftover)
        return false;

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    if (month == 2) {
        bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > (is_leap ? 29 : 28))
            return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    }

    return true;
}

/**
 * @brief Verifies that the provided numerical value is within allowed limits.
 * The value must be strictly positive and not exceed 1000.
 * * @param value The floating-point number to evaluate.
 * @return true if the value is between 0 (exclusive) and 1000 (inclusive), false otherwise.
 */
bool BitcoinExchange::isValidValue(double value) {
    if (value < 0) {
        std::cout << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000) {
        std::cout << "Error: too large number." << std::endl;
        return false;
    }
    return true;
}
