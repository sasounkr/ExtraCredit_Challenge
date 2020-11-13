
#include "expression.h"
#include <iostream>
using namespace std;

void print_inorder(shared_ptr<Node> root) {
    if (!root)
        return;
    print_inorder(root->left);
    cout << root->token;
    print_inorder(root->right);
}

int main() {
    string input;
    cin >> input;
    auto root = convert_to_tree(input);
    // this should print the expression in order
    print_inorder(root);
    cout << endl;
    // once you have completed part 1, uncomment the line below
    // cout << evaluate(input) << endl;
    // deallocate memory
    clear(root);
    return 0;
}