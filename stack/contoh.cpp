#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

// Fungsi untuk menentukan prioritas operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Fungsi untuk mengubah infix ke prefix
string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());
    stack<char> operators;
    string prefix = "";

    for (char ch : infix) {
        if (isalnum(ch)) {
            prefix += ch;
        } else if (ch == ')') {
            operators.push(ch);
        } else if (ch == '(') {
            while (!operators.empty() && operators.top() != ')') {
                prefix += operators.top();
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()) > precedence(ch)) {
                prefix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        prefix += operators.top();
        operators.pop();
    }

    reverse(prefix.begin(), prefix.end());
    return prefix;
}

// Fungsi untuk mengubah prefix ke postfix
string prefixToPostfix(string prefix) {
    stack<string> operands;
    reverse(prefix.begin(), prefix.end());

    for (char ch : prefix) {
        if (isalnum(ch)) {
            operands.push(string(1, ch));
        } else {
            string operand1 = operands.top();
            operands.pop();
            string operand2 = operands.top();
            operands.pop();
            string result = operand1 + operand2 + ch;
            operands.push(result);
        }
    }

    return operands.top();
}

// Fungsi untuk mengubah postfix ke infix
string postfixToInfix(string postfix) {
    stack<string> operands;

    for (char ch : postfix) {
        if (isalnum(ch)) {
            operands.push(string(1, ch));
        } else {
            string operand2 = operands.top();
            operands.pop();
            string operand1 = operands.top();
            operands.pop();
            string result = "(" + operand1 + ch + operand2 + ")";
            operands.push(result);
        }
    }

    return operands.top();
}

// Fungsi untuk mengubah infix ke postfix
string infixToPostfix(string infix) {
    stack<char> operators;
    string postfix = "";

    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

int main() {
    cout << "Program Konversi Notasi" << endl;
    cout << "=========================" << endl;

    string infix;
    cout << "Masukkan ekspresi infix: ";
    cin >> infix;

    string prefix = infixToPrefix(infix);
    cout << "Ekspresi prefix: " << prefix << endl;

    string postfix = prefixToPostfix(prefix);
    cout << "Ekspresi postfix: " << postfix << endl;

    string infixConverted = postfixToInfix(postfix);
    cout << "Ekspresi infix (dari postfix): " << infixConverted << endl;

    string postfixConverted = infixToPostfix(infix);
    cout << "Ekspresi postfix (dari infix): " << postfixConverted << endl;

    return 0;
}