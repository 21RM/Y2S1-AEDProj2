//
// Created by alexandre on 21-12-2023.
//

#ifndef AED_PROJ_2_FILEREADER_H
#define AED_PROJ_2_FILEREADER_H

#include <fstream>
#include <vector>
#include <sstream>
#include <string>


/**
 * @brief A class for reading data from a file and storing it in a vector of vectors of strings.
 */
class FileReader {
    std::ifstream file_; ///< Input file stream for reading data.
    std::vector<std::vector<std::string>> data_; ///< Vector of vectors to store the read data.

public:
    /**
     * @brief Constructor for the FileReader class.
     * @param fName The name of the file to be opened for reading.
     */
    FileReader(const std::string &fName);

    /**
     * @brief Get the data read from the file.
     * @return Vector of vectors containing the read data, where each inner vector represents a row of strings.
     */
    std::vector<std::vector<std::string>> getData();
};



#endif //AED_PROJ_2_FILEREADER_H
