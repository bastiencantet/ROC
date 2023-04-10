/*
** BastosBob
** Bastien CANTET
** 2023
** 
** BB_ROC
** files
*/

#include <vector>
#include <fstream>

#ifndef BB_ROC_FILES_HPP
#define BB_ROC_FILES_HPP

static std::vector<char> readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}

#endif //BB_ROC_FILES_HPP
