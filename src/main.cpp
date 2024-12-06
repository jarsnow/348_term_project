#include <iostream>
#include <string>
#include "evaluator.cpp"
#include "expressionTree.cpp"
#include "parser.cpp"
#include "tokenizer.cpp"

using namespace std;

int main() {
    string expression;
    
    // Startup Message
    cout << "Welcome to the expression parser!\n" << endl;
    cout << "Enter 'quit' to exit the program.\n" << endl;
    
    while (true){ // Loop until quit is entered

        // Step 1: Get input from the user
        cout << "Please enter a mathematical expression (e.g., 3 + 4 * (4 / 2)): ";
        getline(cin, expression);

        // Step 2: Check for quit condition
        if (expression == "quit" ||  expression == "Quit") {
            cout << "Goodbye!" << endl;
            break; //will end program
        }

        try { // to handle classes raising errors

            // Step 3: Tokenize the input expression
            Tokenizer tokenizer; // Create instance of Tokenizer class
            vector<string> tokens = tokenizer.tokenize(expression); // will return the result of tokenizing the input expression as a string vector named tokens

            // Step 4: Parse the tokens into an expression tree
            Parser parser; // Create instance of Parser class
            ExpressionNode* expressionTree = parser.parse(tokens); // 

            // Step 5: Evaluate the expression tree
            Evaluator evaluator; // Create instance of Evaluator class
            double result = evaluator.evaluate(expressionTree); // Stores result of evaluating expression in double named result

            // Step 6: Display the result
            cout << "The result of the expression is: " << result << endl;

            // Cleanup
            delete expressionTree; // Free the dynamically allocated tree (assuming the tree is dynamically allocated)

        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl; // Will provide discription of error
        }

    }

    return 0;
}
