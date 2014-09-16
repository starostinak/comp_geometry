#include <iostream>
#include <vector>
#include <cstdlib>

struct Point {
    Point (int x, int y) : x(x), y(y) { }
    int x;
    int y;
};

struct Polygon {
    std::vector <Point> verticles;

    bool is_intersect(Point const & from, Point const & to, Point const & p) const {
        return ((to.x - p.x) * (to.y - from.y) - (to.x - from.x) * (to.y - p.y) > 0);
    }

    bool is_odd_edge(int y, int ind) const {
        int before = ind;
        int size = (int)verticles.size();
        while (verticles[before].y == y) {
            before = (before - 1 + size) % size;
        }
        int after = ind;
        while (verticles[after].y == y) {
            after = (after + 1) % size;
        }
        return ((after - y) * (before - y) < 0);
    }

    bool is_inside(Point const & p) const {
        int intersections = 0;
        int size = int(verticles.size());
        for (int i = 0; i < size; ++i) {
            Point from = verticles[i];
            Point to = verticles[(i + 1) % size];
            if (from.y == to.y && to.y == p.y) {
                if (is_odd_edge(p.y, i)) {
                    ++intersections;
                } 
                while (verticles[i].y == p.y && i != size) {
                    ++i;
                }
                if (from.y == to.y && i != size) {
                    --i;
                }
            } else if (from.y == p.y) {
                if (verticles[(i - 1 + size) % size].y != p.y && is_odd_edge(p.y, i)) {
                    ++intersections;
                }
            } else if (to.y == p.y) {
                continue;
            } else if (((from.y - p.y) * (to.y - p.y)) <= 0 &&
                    !is_intersect(from, p, to)) {
                ++intersections;
            }
        }
        return (intersections % 2 == 0);
    }
};

Point parse_point(std::string const & str) {
    size_t comma = str.find(',');
    int x = std::atoi(str.substr(1, comma).c_str());
    int y = std::atoi(str.substr(comma + 1).c_str());
    // std::cout << x << ' ' << y << std::endl;
    return Point(x, y);
}

int main() {
    /*
    char tmp[256];
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
    std::cout << num_points << std::endl;
    for (int i = 0; i != num_vert; ++i) {
        std::cin.getline(tmp, 256);
        Point p = parse_point(tmp);
        points.push_back(p);
    }
    */

    Polygon poly;
    poly.verticles = {Point(-3, -2), Point(4, 2), Point(5, 8), Point(6, 5), Point(7, 9), Point(3, 9)};
    std::vector <Point> points = {Point(5, 5), Point(-3, 5), Point(0, 8), Point(4, 6), Point(0, 9), Point(5, 9)};

    for (int i = 0; i != points.size(); ++i) {
        if (poly.is_inside(points[i])) {
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
    }

    return 0;
}
