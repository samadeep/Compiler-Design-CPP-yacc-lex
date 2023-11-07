#include <iostream>
#include <string>

bool isExpression(const std::string& input, int& index);

bool isTerm(const std::string& input, int& index);

bool isFactor(const std::string& input, int& index);

bool isNumber(const std::string& input, int& index);

int main() {
    std::string input;
    std::cout << "Enter a string to check if it belongs to the grammar: ";
    
    std::cin >> input;

    int index = 0;
    bool valid = isExpression(input, index) && index == input.length();

    if (valid) {
        std::cout << "The input string belongs to the grammar." << std::endl;
    } else {
        std::cout << "The input string does not belong to the grammar." << std::endl;
    }

    return 0;
}


// Function to check if a string is an Expression
bool isExpression(const std::string& input, int& index) {
    if (isTerm(input, index)) {
        while (index < input.length() && (input[index] == '+' || input[index] == '-')) {
            index++;
            if (!isTerm(input, index)) {
                return false;
            }
        }
        return true;
    }
    return false;
}


// Function to check if a string is a Term
bool isTerm(const std::string& input, int& index) {
    if (isFactor(input, index)) {
        while (index < input.length() && (input[index] == '*' || input[index] == '/')) {
            index++;
            if (!isFactor(input, index)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// Function to check if a string is a Factor
bool isFactor(const std::string& input, int& index) {
    if (isNumber(input, index)) {
        if (index < input.length() && (input[index] == '+' || input[index] == '-' || input[index] == '*' || input[index] == '/')) {
            return false;  // An operator should not follow a number
        }
        return true;
    } else if (index < input.length() && input[index] == '(') {
        index++;
        if (isExpression(input, index)) {
            if (index < input.length() && input[index] == ')') {
                index++;
                return true;
            }
        }
    }
    return false;
}

// Function to check if a string is a Number
bool isNumber(const std::string& input, int& index) {
    if (index < input.length() && isdigit(input[index])) {
        while (index < input.length() && isdigit(input[index])) {
            index++;
        }
        return true;
    }
    return false;
}
