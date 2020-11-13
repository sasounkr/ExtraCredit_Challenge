# READ THIS

- The challenge problem files are located at `ec/bt-postfix` directory
- The solution files are located at `ec/bt-postfix-solution` directory.

# The Challenge Problem
**Context**:
  In HW2, we were asked to implement a program that evaluates an expression. However, for the sake of simplification, the implementation did not account for operator precedence. What I mean by this is that our program doesn't understand how to evaluate something like "1+2x3". A human would easily know to evaluate 2x3 to 6, then add 1+6, with a final result of 7. 
  The type of expression we see in our daily lives is called an "infix expression". Unfortunately, computers can't really make sense of infix expressions, but, they can easily evaluate what's called a postfix expression. In a postfix expression, most of the operators go to the right of the operands. For example, "1+2x3" would become "123x+", and "1x2+3" would be "12x3+".
  
 **Actual Problem**:
  In your impelementation, given a valid expression, you will convert the expression into a binary tree, and then once you do that, you will use the postfix evaluation algorithm(a very simple algorithm) to evaluate an expression. The operators we will consider are `+`, `-`, `x`, `/`, and `^`. Assume all the operators are left associative. 

# Given Code
- struct `Node` that has members `parent`, `left`, and `right`. The struct also has a char `token` member(the struct is a modified version of the Moses Lee's struct in lab13)
- A constant map `OP_PRECEDENCE` is provided. Given an operator character, `OP_PRECEDENCE` will give you the precedence value of that operator. For example precedence('x') > precedence('+'). 
- `bool greater_precedence(char lhs, char rhs)`, assuming lhs and rhs are operators, `greater_precedence()` will return true if and only if precedence(lhs) > precedence(rhs). So greater_precedence('x', '+') evaluate to true.
- `bool is_op(char t)`, returns true if and only if `t` is an operator. This function is very useful for your impelemenetation!!!
- `shared_ptr<Node> convert_to_tree(string expression)`, assuming a legal expression and assuming your impelementation is correct, this function will turn an expression into a tree
- `int evaluate(string expression)`, assuming a legal expression, this function relies on the helper function `evaluate_helper()` that you will implement
- `void clear(shared_ptr<Node>& root`, simply deallocates memory


# 1st Part(harder part): setting up the binary tree
  You will convert an expression into a binary tree such that if you were to do an inorder traversal of the tree, the program would spit back the exact same expression you entered. 

For example, if you were to enter "1x2+3", you program should come up with the tree below:
```
                     +
                   /   \ 
                  x     3
                /   \
               1     2
```
You will implement 2 functions:  
(1) `shared_ptr<Node> insert_op(shared_ptr<Node> root, char op)`
  Assuming 'op' is an operator, you will allocate a new node, and I'll leave it to you to figure out where your new node needs to be inserted(**Hint**: draw out a tree, and see what happens when you add a new operator node). This function must return the root of the tree(so if you decide to impelement recursively you'd most probably need a helper function).
  
(2) `shared_ptr<Node> insert_num(shared_ptr<Node> root, char num)`
  Assuming 'num' is a number character, you will allocate a new node, and you will figure out how you should insert the new node into the tree(**Hint**: draw out a tree, and see what happens when you add a new number node). This function must return the root of the tree(so if you decide to impelement recursively you'd most probably need a helper function).

In main.cpp, the program will prompt you to enter an expression. If you impelemented part 1 correctly, the program should spit out the exact same expression you entered. 

# Assumptions:
- assume that `expression` has at least 1 token(so the empty string is illegal)
- assume that `expression` can have only SINGLE DIGIT numbers or operators
- assume that `expression` will have NO spaces
- assume that `expression` will have NO parenthesis(unless you want an extra challenge ;))
- assume that `expression` will have the proper amount of operands and operators(so an infix expression like "1+2x" is illegal)
- assume that `expression` will have no unary minus/unary plus (so an infix expression like "1x-2" is illegal)
- assume that all operators are left associative
- assume that all operators can consist of only `+`, `-`, `x`, `/`, and `^`.

# 2nd Part(easier part): postfix evaluation algorithm
  Once you have the proper tree setup, you now need to implement the postfix evaluation algorithm. 
  
Here is the algorithm(taken from GeeksForGeeks):
```
  1) Create a stack to store operands (or values).
  2) Scan the given expression and do following for every scanned element.
     a) If the element is a number, push it into the stack
     b) If the element is a operator, pop operands for the operator from stack. Evaluate the operator and push the result back to the stack
  3) When the expression is ended, the number in the stack is the final answer
```
So, suppose we have the expression "12x3+". By the algorithm, we push '1' to the stack. Then, we push '2' to the stack. Then, when we encounter 'x', we pop 2 from stack and pop 1 from stack. Multiply 1x2 to get result 2. Push 2 to stack. Then, push 3 to stack. Then, we when we encounter '+', pop 3 from stack and pop 2 from stack. Add 2+3 to get result 5. Push 5 to stack. 

You are tasked to impelement one function:
`void evaluate_helper(shared_ptr<Node> root, stack<int>& tokens)`
(**Hint**: what kind of traversal would you need for POSTfix expression?)

# side note:
If you want, you can also take a look at my Rubix files... but they're not even close to complete. The idea was to make a Rubix cube, randomly scramble it, and then try to solve it using the A* algorithm. However, it is too time consuming for me to do for an extra credit assignment, so I leave it to you if you want to impelement it as a future homework assignment. 

Welcome to my github page! :)
