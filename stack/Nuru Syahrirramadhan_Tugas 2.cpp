#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int peringkat(char operat) {
    if (operat == '+' || operat == '-') return 1;
    if (operat == '*' || operat == '/') return 2;
    if (operat == '^') return 3;
    return 0;
}

string infixToPrefix(string infix) {
    cout << "\nNotasi Infix:\t\t\t " << infix <<endl;
    
    reverse(infix.begin(), infix.end());

    stack<char> operators;
    string prefix = "";

    for (char karakter : infix) {
        if (isalnum(karakter)) {
            prefix += karakter;
        } else if (karakter == ')') {
            operators.push(karakter);
        } else if (karakter == '(') {
            while (!operators.empty() && operators.top() != ')') {
                prefix += operators.top();
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && peringkat(operators.top()) > peringkat(karakter)) {
                prefix +=operators.top();
                operators.pop();
            }
            operators.push(karakter);
        }
    }
    while (!operators.empty()) {
        prefix += operators.top();
        operators.pop();
    }
    reverse(prefix.begin(), prefix.end());
    
    return prefix;
}
string prefixToPostfix(string prefix) {
    stack<string> operand;
    reverse(prefix.begin(), prefix.end());

    for (char karakter : prefix) {
        if (isalnum(karakter)) {
            operand.push(string(1, karakter));
        } else {
            string operand1 = operand.top();
            operand.pop();
            string operand2 = operand.top();
            operand.pop();
            string result = operand1 + operand2 + karakter;
            operand.push(result);
        }
    }
    return operand.top();
}
string postfixToInfix(string postfix) {
    stack<string> operand;

    for (char karakter : postfix) {
        if (isalnum(karakter)) {
            operand.push(string(1, karakter));
        } else {
            string operand2 = operand.top();
            operand.pop();
            string operand1 = operand.top();
            operand.pop();
            string result = '(' + operand1 + karakter + operand2 + ')';
            operand.push(result);
        }
    }
    return operand.top();
}

int main() {
    cout << "Program Konversi Notasi Aritmatik" << endl;
    string infix;

    cout << "Masukkan Aritmatik Infix: ";
    cin >> infix;

    string prefix = infixToPrefix(infix);
    cout << "Hasil dari Infix ke Prefix:\t " << prefix << endl;
    
    string postfix = prefixToPostfix(prefix);
    cout << "Hasil Prefix ke Postfix:\t " << postfix << endl;
    
    string infixConv = postfixToInfix(postfix);
    cout << "Hasil Postfix ke Infix:\t\t " << infixConv << endl << endl;
}