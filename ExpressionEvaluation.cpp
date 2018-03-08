#include <iostream>
#include <stack>

int calcPrecedence (char op) {
    switch (op) {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    }
    return -1;
}

int checkType (char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        return 2;
    }
    return 1;
}

int performFunction (int a, int b, char c) {
    std::cout << a << " " << b << " " << c << std::endl;
    switch (c) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return 0;
}
int main () {
    std::string expression;
    int t;
    std::cin >> t;
    while (t--) {
        std::cin >> expression;
        std::stack<char> operands;
        std::stack<char> operators;
        for (auto i = 0; i < expression.length (); i++) {
            switch (checkType (expression[i])) {
            case 1:
                operands.push (expression[i]);
                break;

            case 2:
                while (!operators.empty () &&
                       calcPrecedence (operators.top ()) <= calcPrecedence (expression[i])) {
                    char c = operators.top ();
                    operators.pop ();
                    int operand1 = operands.top () - 48;
                    operands.pop ();
                    int operand2 = operands.top () - 48;
                    operands.pop ();
                    operands.push (performFunction (operand1, operand2, c) + 48);
                }
                operators.push (expression[i]);
                break;
            }
        }
        while (!operators.empty ()) {
            char c = operators.top ();
            operators.pop ();
            int operand1 = operands.top () - 48;
            operands.pop ();
            int operand2 = operands.top () - 48;
            operands.pop ();
            operands.push (performFunction (operand1, operand2, c) + 48);
        }

        std::cout << operands.top () << std::endl;
    }
    return 0;
}