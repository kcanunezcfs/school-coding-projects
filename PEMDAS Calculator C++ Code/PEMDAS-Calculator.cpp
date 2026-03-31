#include <iostream> 
#include <cctype>   // check if character is a digit
#include <cmath>    // math functions
#include <string>   // string manipulation
#include <sstream>  // string stream classes for breaking into tokens / extracting data
#include <iomanip>  // formatting for floating-point results

using namespace std;

// Node of the Linked list
struct Node {
  string data;  /*operand*/
  Node* next;
};

// Linked list-based stack
class Stack {
  private:
    Node* top;
  
  public:
    Stack() : top(nullptr) {}

    void push(string value) {       // allocate new node, set 'data' to passed 'value', update to top
      Node* newNode = new Node();
      newNode->data = value;
      newNode->next = top;
      top = newNode;
    }

    string pop() {                  // remove-return top element / if empty, throws an error
      if (isEmpty()) {
        throw runtime_error("Stack is empty.");
      }
      Node* temp = top;
      string value = top->data;
      top = top->next;
      delete temp;
      return value;
    }

    string peek() const {           // return top element (non-removal) / check current top element
      if (isEmpty()) {
        throw runtime_error("Stack is empty.");
      }
      return top->data;
      }

    bool isEmpty() const {         // check if stack is empty
      return top == nullptr;
    }

    ~Stack() {                     // destructor
      while (!isEmpty()) {
        pop();
      }
    }
};

// Operator precedence function
int precedence(char op) {
  if (op == '+' || op == '-') return 1;   // lowest
  if (op == '*' || op == '/') return 2;   // higher
  if (op == '^') return 3;                // highest
  return 0;
}

// Operator checker function
bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Conversion INFIX -> POSTFIX function
string infixToPostfix(const string& expression) {
  Stack operators;
  string postfix;

  for (size_t i = 0; i < expression.length(); i++) {
    char ch = expression[i];

    // if-statement for multidigit numbers
    if (isdigit(ch)) {
      // Handle multi-digit numbers
      while (isdigit(expression[i]) || expression[i] == '.') {
          postfix += expression[i++];
      }
      postfix += ' ';
      --i;
    }
    
    else if (ch == '(') {
      operators.push(string(1, ch));
    }

    else if (ch == ')') {
      while (!operators.isEmpty() && operators.peek() != "(") {
        postfix += operators.pop() + ' ';
      }
      operators.pop(); // remove '('
    }

    else if (isOperator(ch)) {
      while (!operators.isEmpty() && precedence(operators.peek()[0]) >= precedence(ch)) {
        postfix += operators.pop() + ' ';
      }
      operators.push(string(1, ch));
    }
  }
    
  while (!operators.isEmpty()) {
     postfix += operators.pop() + ' ';
  }
    
  return postfix;
}

double evaluatePosfix(const string& postfix) {
  Stack stack;
  istringstream tokens(postfix);
  string token;

  while (tokens >> token) {
    if (isdigit(token[0]) || (token[0] == '.' && token.length() > 1)) {
      stack.push(token);
    }
    else {
      double val2 = stod(stack.pop());
      double val1 = stod(stack.pop());
      double result;

      switch (token[0]) {
        case '+': result = val1 + val2; break;
        case '-': result = val1 - val2; break;
        case '*': result = val1 * val2; break;
        case '/': result = val1 / val2; break;
        case '^': result = pow(val1, val2); break;
        default: throw runtime_error("Invalid operator!");
      }

      stack.push(to_string(result));
    }
  }

  return stod(stack.pop());
}

// Check for balanced parentheses and valid characters function
bool isValidExpression(const string& expression) {
  int parenthesesBalance = 0;
  bool lastWasOperator = false;   // to check consecutive operators
  bool lastWasDigit = false;      // to ensure proper operand/operator flow

  for (size_t i = 0; i < expression.length(); i++) {
    char ch = expression[i];

    if (isdigit(ch)) {
      lastWasDigit = true;
      lastWasOperator = false;    // continue reading the number (multi-digit numbers and decimals)
      while (i + 1 < expression.length() && (isdigit(expression[i + 1]) || expression[i + 1] == '.')) {
        i++;
      }
    } 
    else if (ch == '(') {
      parenthesesBalance++;
      lastWasOperator = true;  // opening parenthesis acts like an operator
      lastWasDigit = false;
    } 
    else if (ch == ')') {
      parenthesesBalance--;
      if (parenthesesBalance < 0) {
        return false;  // closing parentheses > opening parentheses
      }
      lastWasOperator = false;
    } 
    else if (isOperator(ch)) {     // check if two operators are next to each other or operator is at invalid position
      if (lastWasOperator || (!lastWasDigit && ch != '-')) {
        return false;  // invalid placement of operators
      }
      lastWasOperator = true;
      lastWasDigit = false;
    } 
    else if (!isspace(ch)) { 
      // invalid character (not a digit, operator, or parentheses)
      return false;
    }
  }

  // ensure expression is not ending with an operator and parentheses are balanced
  if (parenthesesBalance != 0 || lastWasOperator) {
    return false;
  }
  return true;
}


int main() {
    while (true) {
        string expression;
        cout << "Enter a mathematical expression (or type exit): ";
        getline(cin, expression);

        if (expression == "exit") {
            break;
        }

        if (!isValidExpression(expression)) {
            cerr << "Error: Invalid mathematical expression." << endl;
            continue;
        }

        try {
            string postfix = infixToPostfix(expression);
            double result = evaluatePosfix(postfix);

            cout << fixed << setprecision(2);
            cout << "Result: " << result << endl;
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }

        cout << endl;
    }

    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}