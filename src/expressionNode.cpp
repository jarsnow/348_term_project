#pragma once

class ExpressionNode {
public:
  ExpressionNode* leftChild;
  ExpressionNode* rightChild;

  virtual ~ExpressionNode() {}
};

class OperatorNode : public ExpressionNode {
public:
  char operation;
};

class NumberNode : public ExpressionNode {
public:
  float number;
};
  
