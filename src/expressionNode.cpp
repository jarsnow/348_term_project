class ExpressionNode {
public:
  ExpressionNode* leftChild;
  ExpressionNode* rightChild;

  virtual ~ExpressionNode() = default; //made the class polymorphic, fixes evaluator error
};

class OperatorNode : public ExpressionNode {
public:
  char operation;
};

class NumberNode : public ExpressionNode {
public:
  float number;
};
  
