//logic for evaluating the expression tree
//
//Things to consider:
//-tree traversal
//-compute expressions
//for evaluation use recursion to solve for leftNode [OPERATOR] rightNode
//note that leaves (nodes with no children) will be numbers and internal nodes will be operators

#include <iostream>
#include <string>
#include "expressionTree.cpp"

class Evaluator {
public:
    double evaluate(ExpressionNode* node) {
        if (!node) {
            throw "Null node encountered in expression tree.";
        }

        NumberNode* numberNode = dynamic_cast<NumberNode*>(node);
        if (numberNode) {
            return numberNode->number;
        }

        OperatorNode* operatorNode = dynamic_cast<OperatorNode*>(node);
        if (operatorNode) {
            double leftValue = evaluate(operatorNode->leftChild);
            double rightValue = evaluate(operatorNode->rightChild);

            switch (operatorNode->operation) {
                case '+': return leftValue + rightValue;
                case '-': return leftValue - rightValue;
                case '*': return leftValue * rightValue;
                case '/':
                    if (rightValue == 0) {
                        throw "Division by zero.";
                    }
                    return leftValue / rightValue;
                default:
                    throw "Invalid operator encountered.";
            }
        }

        throw "Unknown node type encountered.";
    }
};

