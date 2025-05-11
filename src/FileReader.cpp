//
// Created by alexandre on 21-12-2023.
//

#include "FileReader.h"

FileReader::FileReader(const std::string &fName) {
    file_.open(fName);
}

std::vector<std::vector<std::string>> FileReader::getData() {
    std::string line;
    std::getline(file_, line);
    while (std::getline(file_, line)) {
        std::istringstream iss(line);
        std::string value;
        std::vector<std::string> v;
        while (std::getline(iss, value, ',')) {
            v.push_back(value);
        }
        data_.push_back(v);
    }
    return data_;
}
