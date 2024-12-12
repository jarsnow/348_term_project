#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>

// Define a structure to represent a token
struct Token {
    enum Type { Number, Operator, Parenthesis } type;
    std::string value;
};

// Tokenizer function
std::vector<Token> tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < expression.length()) {
        char c = expression[i];

        // Skip whitespace
        if (std::isspace(c)) {
            i++;
            continue;
        }

        // Check for numeric constants
        if (std::isdigit(c)) {
            std::string number;
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
                number += expression[i];
                i++;
            }
            tokens.push_back({Token::Number, number});
            continue;
        }

        // Check for operators
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')') {
            // Handle ** operator (exponentiation)
            if (c == '*' && i + 1 < expression.length() && expression[i + 1] == '*') {
                tokens.push_back({Token::Operator, "**"});
                i += 2;
                continue;
            }
            // Add single-character operators
            tokens.push_back({Token::Operator, std::string(1, c)});
            i++;
            continue;
        }

        // Check for parentheses
        if (c == '(' || c == ')') {
            tokens.push_back({Token::Parenthesis, std::string(1, c)});
            i++;
            continue;
        }

        // If we encounter an invalid character
        throw std::runtime_error(std::string("Invalid character in expression: ") + c);
    }

    return tokens;
}
/*
int main() {
    std::string expression;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, expression);

    try {
        std::vector<Token> tokens = tokenize(expression);

        std::cout << "Tokens:" << std::endl;
        for (const auto& token : tokens) {
            std::cout << "Type: " << (token.type == Token::Number ? "Number" : (token.type == Token::Operator ? "Operator" : "Parenthesis"))
                      << ", Value: " << token.value << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
*/



