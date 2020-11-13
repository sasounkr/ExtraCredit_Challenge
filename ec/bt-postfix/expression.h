#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <map>
#include <memory>
#include <string>
#include <stack>
using namespace std;

struct Node 
{
	char token;
    shared_ptr<Node> parent;
	shared_ptr<Node> left;
	shared_ptr<Node> right;
	Node(char x, shared_ptr<Node> left, shared_ptr<Node> right, shared_ptr<Node> parent) : 
        token(x), left(left), right(right), parent(parent) {}
};

// assume all operands are left associative 
const map<char, int> OP_PRECEDENCE {
    { '+', 0 },
    { '-', 0 },
    { '*', 1 },
    { '/', 1 },
    { '^', 2 }
};
bool greater_precendence(char lhs, char rhs);
bool is_op(char t);

// assuming 'op' is an operator
shared_ptr<Node> insert_op(shared_ptr<Node> root, char op);
// assuming 'num' is a single digit num
shared_ptr<Node> insert_num(shared_ptr<Node> root, char num);
// assuming 'expression' has no spaces at all
shared_ptr<Node> convert_to_tree(string expression);
int evaluate(string expression);
void evaluate_helper(shared_ptr<Node> root, stack<int>& tokens);
void clear(shared_ptr<Node> root);
void clear_helper(shared_ptr<Node> root);

#endif