#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    std::ifstream inputFile("text.txt"); // Replace "input.txt" with your file name
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    int charCount = 0;
    int wordCount = 0;
    int lineCount = 0;

    while (std::getline(inputFile, line)) {
        lineCount++;
        // Count words and characters in the line
        std::istringstream iss(line);
        std::string word;

        while (iss >> word) {
            if (!word.empty()) { // Exclude empty words (whitespace)
                wordCount++;
                cout << word << endl;
                charCount += word.size();
            }
        }
    }

    std::cout << "Character count: " << charCount << std::endl;
    std::cout << "Word count: " << wordCount << std::endl;
    std::cout << "Line count: " << lineCount << std::endl;

    inputFile.close();

    return 0;
}
