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

#include "expressionNode.cpp"


class ExpressionTree {
public:
  ExpressionNode* root;

  ExpressionTree() : root(nullptr){}

  void setRoot(ExpressionNode* node){
    root = node;
  }

  ExpressionNode* getRoot() const{
    return root;
  }
};
