#include "expression.h"

#include <cmath>

bool greater_precendence(char lhs, char rhs) { 
    return OP_PRECEDENCE.find(lhs)->second > OP_PRECEDENCE.find(rhs)->second; 
}

bool is_op(char t) { return OP_PRECEDENCE.find(t) != OP_PRECEDENCE.end(); }

shared_ptr<Node> insert_op(shared_ptr<Node> root, char op) {
    auto temp = root;
    // assuming the tree isn't empty
    while (is_op(temp->token) && greater_precendence(op, temp->token)) 
        temp = temp->right;
    auto new_node = make_shared<Node>(op, temp, nullptr, temp->parent);
    if (temp->parent) 
        temp->parent->right = new_node;
    else 
        root = new_node;
    temp->parent = new_node;
    return root;
}

shared_ptr<Node> insert_num(shared_ptr<Node> root, char num) {
    auto temp = root;
    if (temp) {
        while (temp->right)
            temp = temp->right;
        temp->right = make_shared<Node>(num, nullptr, nullptr, temp);
    }
    else 
        root = make_shared<Node>(num, nullptr, nullptr, nullptr);
    return root;
}

// assume the string has single digit numbers
// assume not an empty string
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
    if (!root) return;
    evaluate_helper(root->left, tokens);
    evaluate_helper(root->right, tokens);
    if (is_op(root->token)) {
        int lhs, rhs, result;
        rhs = tokens.top();
        tokens.pop();
        lhs = tokens.top();
        tokens.pop();
        switch (root->token) {
        case '+':
            result = lhs + rhs;
            break;
        case '-':
            result = lhs - rhs;
            break;
        case '*':
            result = lhs * rhs;
            break;
        case '/':
            result = lhs / rhs;
            break;
        default:
            result = (int) pow(lhs, rhs);
        }
        tokens.push(result);
    } else {
        tokens.push(root->token - '0');
    }
}

void clear(shared_ptr<Node> root) {
    clear_helper(root);
    root = nullptr;
}

void clear_helper(shared_ptr<Node> root) {
    if (root) {
        clear_helper(root->left);
        clear_helper(root->right);
        root->left = nullptr;
        root->right = nullptr;
    }
}