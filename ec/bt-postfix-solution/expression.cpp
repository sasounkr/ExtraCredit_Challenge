#include "expression.h"

#include <cmath>

bool greater_precendence(char lhs, char rhs) { 
    return OP_PRECEDENCE.find(lhs)->second > OP_PRECEDENCE.find(rhs)->second; 
}

bool is_op(char t) { return OP_PRECEDENCE.find(t) != OP_PRECEDENCE.end(); }

shared_ptr<Node> insert_op(shared_ptr<Node> root, char op) {
    auto temp = root;
    // assuming the tree isn't empty
    // go as right as possible until we hit a number or a token with higher precedence
    while (is_op(temp->token) && greater_precendence(op, temp->token)) 
        temp = temp->right;
    auto new_node = make_shared<Node>(op, temp, nullptr, temp->parent);
    // if temp has a parent, then we have temp's parent adopt our new_node
    if (temp->parent) 
        temp->parent->right = new_node;
    // else, temp must have been root node, make new_node the root
    else 
        root = new_node;
    temp->parent = new_node;
    return root;
}

shared_ptr<Node> insert_num(shared_ptr<Node> root, char num) {
    auto temp = root;
    // if not empty tree
    if (temp) {
        // go to rightmost node
        while (temp->right)
            temp = temp->right;
        temp->right = make_shared<Node>(num, nullptr, nullptr, temp);
    }
    // else, allocate memeory for empty tree
    else 
        root = make_shared<Node>(num, nullptr, nullptr, nullptr);
    return root;
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

// postfix traversal so we can do the postfix evaluation algorithms
void evaluate_helper(shared_ptr<Node> root, stack<int>& tokens) {
    if (!root) return;
    evaluate_helper(root->left, tokens);
    evaluate_helper(root->right, tokens);
    // if operator, pop top 2 elements in stack, calc result, push result back in stack
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
    // else, it's a number. push number to stack
    } else {
        tokens.push(root->token - '0');
    }
}

void clear(shared_ptr<Node>& root) {
    if (root) {
        clear(root->left);
        clear(root->right);
        root = nullptr;
    }
}
