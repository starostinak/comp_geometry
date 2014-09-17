#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

struct Point {
    Point (int x, int y) : x(x), y(y) { }
    bool operator == (Point const & p) const {
        return x == p.x && y == p.y;
    }
    long long int x;
    long long int y;
};

struct Polygon {
    std::vector <Point> verticles;

    long long int coeff(Point const & from, Point const & to, Point const & p) const {
        // std::cout << (std::max(to.x, from.x) - p.x) << " " << abs(to.y - from.y) << " " << abs((to.x - from.x)) << " " <<  (std::max(to.y, from.y) - p.y) << std::endl;
        return (std::max(to.x, from.x) - p.x) * abs(to.y - from.y) - abs(to.x - from.x) * (std::max(to.y, from.y) - p.y);
    }

    bool was_under(long long int y, int ind) const {
        int before = ind;
        int size = (int)verticles.size();
        while (verticles[before].y == y) {
            before = (before - 1 + size) % size;
        }
        return verticles[before].y < y;
    }

    bool is_inside(Point const & p) const {
        if (std::find(verticles.begin(), verticles.end(), p) != verticles.end()) {
            return true;
        }
        int intersections = 0;
        int size = int(verticles.size());
        for (int i = 0; i < size; ++i) {
            Point from = verticles[i];
            Point to = verticles[(i + 1) % size];
            if (to.y == p.y) {
                if (to.y == from.y && (to.x - p.x) * (from.x - p.x) <= 0) {
                    return true;
                }
            } else if (from.y == p.y && to.y != p.y) {
                bool before_was_under = was_under(p.y, i);
                if (from.x >= p.x && before_was_under ^ (to.y < p.y)) {
                    ++intersections;
                }
                continue;
            } else if (((from.y - p.y) * (to.y - p.y)) <= 0) {
                long long int c = coeff(from, to, p);
                if (c > 0) {
                    ++intersections;
                } else if (c == 0) {
                    return true;
                }
            }
        }
        return (intersections % 2);
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
    for (int i = 0; i != num_points; ++i) {
        std::cin.getline(tmp, 256);
        Point p = parse_point(tmp);
        points.push_back(p);
    }

    /*
    poly.verticles = {Point(-2, -2), Point(4, 2), Point(5, 8), Point(6, 5), Point(7, 9), Point(3, 9)};
    std::vector <Point> points = {Point(5, 5), Point(-3, 5), Point(0, 8), Point(4, 6), Point(0, 9), Point(5, 9), Point(1, 0), Point(4, 5)};
    poly.verticles = {Point(0, 0), Point(2, 0), Point(2, 1), Point(4, 1), Point(4, 0), Point(6, 0), Point(6, -2), Point(8, -2), Point(8, 0), Point(10, 0), Point(10, 2)
, Point(0, 2)};
    std::vector <Point> points = {Point(3, 0), Point(5, 0), Point(7, 0), Point(12, 0)};

    Polygon poly;
    poly.verticles = {Point(-99999, -99999), Point(2, -2), Point(99999, 99999)};
    std::vector <Point> points = {Point(1, -1), Point(3, -1)};
    */

    for (int i = 0; i != points.size(); ++i) {
        if (poly.is_inside(points[i])) {
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
    }

    return 0;
}
