#ifndef RUBIX_H
#define RUBIX_H

#include <memory>
using namespace std;

enum class Color{GREEN = 'G', BLUE = 'B', ORANGE = 'O', RED = 'R', WHITE = 'W', YELLOW = 'Y'};

struct Face {
    Face(Color color) {
        left  = nullptr;
        right = nullptr;
        above = nullptr;
        below = nullptr;
        for (size_t i = 0; i < 3; ++i) 
            for (size_t j = 0; j < 3; ++j)
                this->colors[i][j] = color;
    }
    // may need copy contrusctor
    Color colors[3][3];
    shared_ptr<Face> left, right, up, bottom;
};


class RubixCube {
public:
    RubixCube();
    // may need copy constructor, operator=, and destructor
    int calc_heuristic() const;
    void rotate_cw(char face);
    void rotate_ccw(char face);
    Color get_front() const;

private:
    shared_ptr<Face> front;
};

#endif