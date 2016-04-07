//
//  main.cpp
//  Calculator
//
//  Created by Ian MacCallum on 2/18/16.
//  Copyright © 2016 Ian MacCallum. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_map> // unordered_map >> __hash_table >> cmath
#include <stack> // stack >> deque >> algorithm

// Exception type
enum Exception {
  DivideByZero,
  UndefinedVariable,
  SyntaxError,
  InvalidParenthesis,
  Unknown
};

// Operation type
enum Op {
  None,           // For Highest-Level
  Addition,       // +
  Subtraction,    // -
  Multiplication, // *
  Division,       // /
  Exponent,       // ^
};

struct Operator {
  Op op;
  int precedence;
  int associativity;
  
  Operator(Op opr, int prec, int assoc) : op(opr), precedence(prec), associativity(assoc) { }
};

struct OperatorValue {
  Operator op;
  double value;
  OperatorValue(const Operator& opr, double val) : op(opr), value(val) { }
  int getPrecedence() const {
    return op.precedence;
  }
  bool isNull() const {
    return op.op == None;
  }
};

class Calculator {
private:
  std::unordered_map<std::string, double> variables;
  std::string expression;
  std::size_t index;
  std::stack<OperatorValue> stack;
  
  
public:
  // Calculation Function Definitions
  double calculate(double v1, double v2, const Operator& op) throw(Exception);
  double eval(const std::string& expression) throw(Exception);
  double eval(char c);
  
  // Variable Function Definitions
  double getVariable(std::string key) throw(Exception);
  void setVariable(std::string key, double value);
  
  // Parsing Function Definitions
  Operator parseOp();
  double parseExpr();
  double parseDecimal();
  double parseVariable() throw(Exception);
  double parseValue();
  
  // Helper Function Definitions
  std::string errorMessage(Exception e);
  double checkZero(double value) throw(Exception);
  bool checkEnd() const;
  char getCharacter() const;
};

// MARK: - Calculation Functions
double Calculator::calculate(double v1, double v2, const Operator& op) throw(Exception) {
  switch (op.op) {
    case Addition:        return v1 + v2;
    case Subtraction:     return v1 - v2;
    case Multiplication:  return v1 * v2;
    case Division:        return v1 / checkZero(v2);
    case Exponent:        return pow(v1, v2);
    default:              return 0;
  }
}

double Calculator::eval(const std::string& expression) throw(Exception) {
  this->expression = expression;
  double result = 0;
  index = 0;
  
  try {
    result = parseExpr();
    if (!checkEnd()) throw SyntaxError;
  } catch (Exception e) {
    while(!stack.empty()) stack.pop();
    throw e;
  }
  return result;
}

double Calculator::eval(char c) {
  std::string expr(1, c);
  return eval(expr);
}

// MARK: - Variable Functions
double Calculator::getVariable(std::string key) throw(Exception) {
  std::unordered_map<std::string,double>::const_iterator value = variables.find(key);
  
  if (value == variables.end()) {
    throw UndefinedVariable;
  } else {
    return value->second;
  }
}

void Calculator::setVariable(std::string key, double value) {
  variables[key] = value;
}

// MARK: - Parsing Functions
Operator Calculator::parseOp() {
  switch (getCharacter()) {
    case '+': index++;    return Operator(Addition, 1, 'L');
    case '-': index++;    return Operator(Subtraction, 1, 'L');
    case '/': index++;    return Operator(Division, 2, 'L');
    case '*': index++;    return Operator(Multiplication, 2, 'L');
    case '^': index++;    return Operator(Exponent, 3, 'R');
    default:              return Operator(None, 0, 'L');
  }
}

double Calculator::parseExpr() {
  // Create highest-level operation
  stack.push(OperatorValue(Operator(None, 0, 'L'), 0));
  
  // Parse value on left
  double value = parseValue();
  
  while (!stack.empty()) {
    // Parse operator and associated value based on precedence and associativity
    Operator op(parseOp());
    while (op.precedence  < stack.top().getPrecedence() || (op.precedence == stack.top().getPrecedence() && op.associativity == 'L')) {
      
      // End reached
      if (stack.top().isNull()) {
        stack.pop();
        return value;
      }
      
      // Reduce expression
      value = calculate(stack.top().value, value, stack.top().op);
      stack.pop();
    }
    
    // Push new value and operation to stack
    stack.push(OperatorValue(op, value));
    
    // Parse value on right
    value = parseValue();
  }
  return 0;
}

double Calculator::parseDecimal() {
  std::string s = "";
  char c = getCharacter();
  
  do {
    s += c;
    index++;
    c = getCharacter();
    
  } while ((c >= '0' && c <= '9') || c == '.'); // Break if not number or decimal
  return std::stod(s);
}

double Calculator::parseVariable() throw(Exception) {
  std::string s = "";
  char c = getCharacter();
  
  do {
    s += c;
    index++;
    c = getCharacter();
    
  } while ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')); // Break if not alphabetical character
  
  try {
    return getVariable(s);
  } catch (Exception e) {
    throw UndefinedVariable;
  }
  
}

double Calculator::parseValue() {
  double val = 0;
  
  char c = getCharacter();
  
  if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
    // Parse variable
    try {
      val = parseVariable();
    } catch (Exception e) {
      throw UndefinedVariable;
    }
  } else if (c >= '0' && c <= '9') {
    // Parse decimal
    val = parseDecimal();
  } else if (c == '(') {
    // Parse expression within parenthesis
    index++;
    val = parseExpr();
    if (getCharacter() != ')') {
      throw InvalidParenthesis;
    }
    index++;
  } else if (c == '+') {
    // Parse unary +
    index++;
    val =  parseValue();
  } else if (c == '-') {
    // Parse unary -
    index++;
    val =  -1 * parseValue();
  } else {
    if (!checkEnd()) throw SyntaxError;
  }
  
  return val;
}


// MARK: - Helper Functions
double Calculator::checkZero(double value) throw(Exception) {
  if (value == 0) {
    throw DivideByZero;
  }
  return value;
}

bool Calculator::checkEnd() const {
  return index >= expression.size();
}

char Calculator::getCharacter() const {
  return checkEnd() ? 0 : expression[index];
}

std::string Calculator::errorMessage(Exception e) {
  switch (e) {
    case DivideByZero: return "Division by zero"; break;
    case UndefinedVariable: return "Undefined variable"; break;
    case SyntaxError: return "Invalid syntax"; break;
    case InvalidParenthesis: return "Invalid parenthesis"; break;
    default: return "Unknown exception"; break;
  }
}

// MARK: - Main
int main(int argc, const char * argv[]) {
  
  Calculator calc = Calculator();
  std::string line;
  
  while (std::getline(std::cin, line)) {
    
    // Remove white space
    std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
    line.erase(end_pos, line.end());
    
    // Determine input type
    if (line.substr(0,3) == "let") {
      
      // Parse expression
      size_t index = line.find('=');
      std::string name = line.substr(3, index - 3);
      std::string expression = line.substr(index + 1, line.length() - index);
      
      // Set variable
      try {
        double value = calc.eval(expression);
        calc.setVariable(name, value);
      } catch (Exception e) {
        std::cout << calc.errorMessage(e) << std::endl;
      }
      
    } else if (line == "quit") {
      // Exit while loop
      break;
    } else {
      // Evaluate expression
      try {
        double value = calc.eval(line);
        std::cout << value << std::endl;
      } catch (Exception e) {
        std::cout << calc.errorMessage(e) << std::endl;
      }
    }
  }
  
  return 0;
}
