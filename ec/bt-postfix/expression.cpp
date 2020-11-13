#include "expression.h"

#include <cmath>

bool greater_precendence(char lhs, char rhs) {
    return OP_PRECEDENCE.find(lhs)->second > OP_PRECEDENCE.find(rhs)->second;
}

bool is_op(char t) { return OP_PRECEDENCE.find(t) != OP_PRECEDENCE.end(); }

shared_ptr<Node> insert_op(shared_ptr<Node> root, char op) {
    // TODO
}

shared_ptr<Node> insert_num(shared_ptr<Node> root, char num) {
    // TODO
}

// assume string is a valid expression... so nothing like 1+2*
// assume the string has single digit numbers
// assume not an empty string
// assume string has no spaces
shared_ptr<Node> convert_to_tree(string expression) {
    shared_ptr<Node> root = nullptr;
    for (char t : expression)
        root = is_op(t) ? insert_op(root, t) : insert_num(root, t);
    return root;
}

int evaluate(string expression) {
    auto root = convert_to_tree(expression);
    stack<int> tokens;
    evaluate_helper(root, tokens);
    clear(root);
    return tokens.top();
}

void evaluate_helper(shared_ptr<Node> root, stack<int>& tokens) {
    // TODO
}

void clear(shared_ptr<Node>& root) {
    if (root) {
        clear(root->left);
        clear(root->right);
        root = nullptr;
    }
}
