#include "expressionNode.cpp"
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

//data structure to represent expressions
//
//EXAMPLE 
//      
//    (3+5)*(2-4)
//
//         *
//       /   \
//      +     -
//     / \   / \
//    3   5 2   4
//
//
//Things to consider:
//-create an expressionNode class
//-create 2 subclasses of expressionNode: numberNode and operatorNode 
//-leaves should be numbers internal nodes and root should be operators

/*
useful definitions:

E (EXPRESSION):
An expression is any thing like 3 + 5
E -> T
E -> T{+/-T} <- T is followed by any number of +T or -T

T (TERM):
A value that is two values multiplied
T -> F
T -> F{* or / F} <- F is followed by any number of *F or /F

F (FACTOR):
A value that is used in multiplication / 
F -> INTEGER
F -> (E)
F -> -F

*/

#pragma once
#include <iostream>

class ExpressionTree {
    private:
        vector<string> tokens;
        string curr_token;
        int curr_token_index = 0;

        void update_next_token(){
            curr_token_index++;
            if (curr_token_index >= tokens.size()){
              curr_token = "";
            }else {
              curr_token = tokens[curr_token_index];
            }
            //cout << "new token: " << curr_token << endl;
        }

        bool is_string_number(string input){
            //  cool one liner
            //  if the function finds a value that isn't a digit, it returns string::npos
            //  so if it's anything other than those digits, it isn't string::npos
            return curr_token.find_first_not_of("0123456789") == string::npos;
        }
         
        ExpressionNode* parse_factor() {
            if (curr_token == "+") {
                update_next_token();
                return parse_factor();
            }
            // if the current token is an integer, return it
            if (is_string_number(curr_token)) {
                NumberNode* curr_token_number = new NumberNode();
                curr_token_number->number = stoi(curr_token);
                update_next_token();
                return curr_token_number;
            }
            
            // check for negative number
            if (curr_token == "-") {
                update_next_token();

                // check for parens
                if (is_string_number(curr_token)) {
                    NumberNode* curr_token_number = new NumberNode();
                    curr_token_number->number = -stoi(curr_token);
                    update_next_token(); 
                    return curr_token_number;
                } else if (curr_token == "(") {
                    // negate expression i nparens
                    update_next_token();
                    ExpressionNode* expression_in_parenthesis = parse_expression();
                    if (curr_token == ")") {
                        update_next_token();
                        return negation_node(expression_in_parenthesis);
                    } else {
                        throw runtime_error("bad ending parenthesis");
                    }
                }
            }
            
            // get the expression inside a parenthesis if there's a parenthesis coming up
            if (curr_token == "(") {
                update_next_token();
                ExpressionNode* expression_in_parenthesis = parse_expression();
                if (curr_token == ")") {
                    update_next_token();
                    return expression_in_parenthesis;
                } else {
                    throw runtime_error("bad ending parenthesis");
                }
            }

            throw runtime_error("bad issue in parse_factor");
        }

        ExpressionNode *parse_exponentiation() { // code to parse exponents first
            ExpressionNode *factor_a = parse_factor();

            // Check for exponentiation operator "**"
            while (curr_token == "**") {
                update_next_token();
                ExpressionNode *factor_b = parse_factor();
                factor_a = exponent_nodes(factor_a, factor_b);
            }

            return factor_a; // go to other stuff
        }
                
        // expression
        ExpressionNode *parse_expression(){
            ExpressionNode *term_a = parse_term();

            // since a term can be followed by any number of +T or -T
            // continue to combine them to term_a node
            while (true){
                if (curr_token == "+"){
                    // add the next expression to the current one
                    update_next_token();
                    ExpressionNode *term_b = parse_term();
                    term_a = add_nodes(term_a, term_b);
                }else if (curr_token == "-"){
                    // subtract the next expression from the current one
                    update_next_token();
                    ExpressionNode *term_b = parse_term();
                    term_a = subtract_nodes(term_a, term_b);
                }else{
                    // the T +T -T has stopped, return the expression
                    return term_a;
                }
            }
        }

        ExpressionNode *parse_term(){
            ExpressionNode *factor_a = parse_exponentiation();

            // since a term can be followed by any number of +T or -T
            // continue to combine them to term_a node
            while (true){
                
                if (curr_token == "*"){
                    // add the next expression to the current one
                    update_next_token();
                    ExpressionNode *factor_b = parse_exponentiation();
                    factor_a = multiply_nodes(factor_a, factor_b);
                }else if (curr_token == "/"){
                    // divide the next expression from the current one
                    update_next_token();
                    ExpressionNode *factor_b = parse_exponentiation();
                    factor_a = divide_nodes(factor_a, factor_b);
                }else if (curr_token =="**"){
                    //exponent
                    update_next_token();
                    ExpressionNode *factor_b = parse_exponentiation();
                    factor_a = exponent_nodes(factor_a, factor_b);

                }else if (curr_token == "%"){
                    // mod the next expression from the current one
                    update_next_token();
                    ExpressionNode *factor_b = parse_exponentiation();
                    factor_a = modulus_nodes(factor_a, factor_b);
                }else{
                    // the F *F /F has stopped, return the expression
                    return factor_a;
                }
            }
        }

        // returns the expression node of an add
        // returns the root node with it's left and right child as two expression nodes
        OperatorNode *add_nodes(ExpressionNode *term_a, ExpressionNode *term_b){
            OperatorNode *add_node = new OperatorNode();
            add_node->operation = '+';
            add_node->leftChild = term_a;
            add_node->rightChild = term_b;
            
            return add_node;
        }

        // returns the expression node of a subtract
        // returns the root node with it's left and right child as two expression nodes
        OperatorNode *subtract_nodes(ExpressionNode *term_a, ExpressionNode *term_b){
            OperatorNode *sub_node = new OperatorNode();
            sub_node->operation = '-';
            sub_node->leftChild = term_a;
            sub_node->rightChild = term_b;
            
            return sub_node;
        }

        // returns the expression node of a multiplication
        // returns the root node with it's left and right child as two expression nodes
        OperatorNode *multiply_nodes(ExpressionNode *factor_a, ExpressionNode *factor_b){
            OperatorNode *mult_node = new OperatorNode();
            mult_node->operation = '*';
            mult_node->leftChild = factor_a;
            mult_node->rightChild = factor_b;
            
            return mult_node;
        }

        // returns the expression node of a division
        // returns the root node with it's left and right child as two expression nodes
        OperatorNode *divide_nodes(ExpressionNode *factor_a, ExpressionNode *factor_b){
            OperatorNode *div_node = new OperatorNode();
            div_node->operation = '/';
            div_node->leftChild = factor_a;
            div_node->rightChild = factor_b;
            
            return div_node;
        }
        
        
        OperatorNode *exponent_nodes(ExpressionNode *factor_a, ExpressionNode *factor_b){
            OperatorNode *exp_node = new OperatorNode();
            exp_node->operation = 'E';
            exp_node->leftChild = factor_a;
            exp_node->rightChild = factor_b;
            
            return exp_node;
        }

        
        // returns the expression node of a negation
        // returns root node with its left child as an expression node
        OperatorNode *negation_node(ExpressionNode *factor_node){
            OperatorNode *neg_node = new OperatorNode();
            neg_node->operation = 'N'; // N for negate
            neg_node->leftChild = factor_node;
            return neg_node;
        }

        // returns the expression node of a modulus
        // returns the root node with it's left and right child as two expression nodes
        OperatorNode *modulus_nodes(ExpressionNode *factor_a, ExpressionNode *factor_b){
            OperatorNode *mod_node = new OperatorNode();
            mod_node->operation = '%';
            mod_node->leftChild = factor_a;
            mod_node->rightChild = factor_b;
            
            return mod_node;
        }

    public:
        ExpressionNode *root;

        ExpressionNode* parse(vector<string> p_tokens){
            // update the current token, then start
            tokens = p_tokens;
            curr_token = tokens[0];
            root = parse_expression();
            return root;
        }
};
