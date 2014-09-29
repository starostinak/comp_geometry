#include <iostream>

struct Point {
    int x;
    int y;
}

enum turn_t {
    LEFT, RIGHT, COLLINEAR
};

turn_t get_turn(Point a, Point b, Point c) {
    long long int prod = (long long int(c.x - a.x)) * (b.y - a.y) - (long long int(c.y - a.y)) * (b.x - a.x);
    if (prod < 0) {
        return RIGHT;
    } else if (prod == 0) {
        return COLLINEAR;
    } 
    return LEFT;
}

struct 

struct Polygon {
    typedef std::vector <Point>::iterator point_iterator;
    std::vector <Point> verticles;

    point_iterator get_leftmost_verticle() {
        int y = 1000000;
        point_iterator res = verticles.end();
            if (it->y < y) {
        }
    }


};

Point parse_point(std::string const & str) {
    size_t comma = str.find(',');
    int x = std::atoi(str.substr(1, comma).c_str());
    int y = std::atoi(str.substr(comma + 1).c_str());
    return Point(x, y);
}

int main() {
    std::cin.getline(tmp, 256);
    int num_vert = std::atoi(tmp);
    Polygon poly;
    for (int i = 0; i != num_vert; ++i) {
        std::cin.getline(tmp, 256);
        Point p = parse_point(tmp);
        poly.verticles.push_back(p);
    }

    std::vector <Point> points;
    std::cin.getline(tmp, 256);
    int num_points = std::atoi(tmp);
    for (int i = 0; i != num_points; ++i) {
        std::cin.getline(tmp, 256);
        Point p = parse_point(tmp);
        points.push_back(p);
    }
}
