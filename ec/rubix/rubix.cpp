#include "rubix.h"








////////////////////////////////////////////////////////////

// THIS IS NOT PART OF THE CHALLENGE PROBLEM! DO NOT ENTER... :)

////////////////////////////////////////////////////////////













RubixCube::RubixCube() : front(make_shared<Face>(Color::GREEN)) {
    shared_ptr<Face> temp = front;
    // allocate data in rightwards direction
    for (size_t i = 0; i < 3; ++i) {
        temp->right = make_shared<Face>();
        temp = temp->right;
    }
    // connect left face to front face
    temp->right = front;
    // now connect the leftward direction
    temp = front;
    for (size_t i = 0; i < 4; ++i) {
        temp->right->left = temp;
        temp = temp->right;
    }
    // connect upwards direction
    front->up = make_shared<Face>();
    front->up->left = front->left;
    front->left = front->up->left;
    front->up->right = front->right;
    front->right = front->up->right;
    front->up->up = front->right->right;
    front->right->right = front->up->up;
    // basically copy/pasted code, this should be a function instead
    front->bottom = make_shared<Face>();
    front->bottom->left = front->left;
    front->left = front->bottom->left;
    front->bottom->right = front->right;
    front->right = front->bottom->right;
    front - bottom->bottom = front->right->right;
    front->right->right = front->bottom->bottom;

    /*
    // allocate up face
    front->up = make_shared<Face>(Color::WHITE);
    front->up->bottom = front;
    // allocate bottom face
    front->bottom = make_shared<Face>(Color::YELLOW);
    front->bottom->up = front;
    // allocate left face
    front->left = make_shared<Face>(Color::ORANGE);
    front->left->right = front;
    // allocate right face
    front->right = make_shared<Face>(Color::RED);
    front->right->left = front;
    // allocate back face
    front->right->right = make_shared<Face>(Color::BLUE);
    front->right->right->left = front->right;
    // connect the left and back faces
    front->left->left = front->right->right;
    front->right->right->right = front->left;
    // connect the up face to left, right, and back faces
    front->up->left = front->left;
    front->left = front->up->left;
    front->up->right = front->right;
    front->right = front->up->right;
    front->up->up = front->right->right;
    front->right->right = front->up->up;
    // basically copy/pasted code, this should be a function instead
    front->bottom->left = front->left;
    front->left = front->bottom->left;
    front->bottom->right = front->right;
    front->right = front->bottom->right;
    front-bottom->bottom = front->right->right;
    front->right->right = front->bottom->bottom;
    */
}

void RubixCube::rotate_cw(char face) {
    shared_ptr<Face> temp;
    switch (face) {
    case 'F':
        temp = this->front;
        break;
    case 'B':
        temp = this->front->right->right;
        break;
    case 'L':
        temp = this->front->left;
        break;
    case 'R':
        temp = this->front->right;
        break;
    case 'U':
        temp = this->front->up;
        break;
    default:
        temp = this->front->bottom;
    }

    // temp->colors rotate it clockwise
}
