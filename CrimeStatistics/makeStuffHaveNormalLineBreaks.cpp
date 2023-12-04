//
// Created by laure on 22.11.2023.
//
#include <iostream>
#include <fstream>
#include <sstream>

void replaceCarriageReturns(const std::string& inputFilePath, const std::string& outputFilePath) {
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    std::ofstream outputFile(outputFilePath, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    // Read file content into a string
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string fileContent = buffer.str();

    // Replace '\r' with '\n'
    size_t pos = fileContent.find('\r');
    while (pos != std::string::npos) {
        fileContent.replace(pos, 1, "\n");
        pos = fileContent.find('\r', pos + 1);
    }

    // Write the modified content back to the file
    outputFile << fileContent;

    // Close the files
    inputFile.close();
    outputFile.close();

    std::cout << "Carriage returns replaced successfully." << std::endl;
}

int main() {
    replaceCarriageReturns("C:\\Users\\laure\\Documents\\Dev\\LearningCpp\\CrimeStatistics\\DANGER-1500000SalesRecords.txt", "C:\\Users\\laure\\Documents\\Dev\\LearningCpp\\CrimeStatistics\\beeegRecords.txt");

    return 0;
}