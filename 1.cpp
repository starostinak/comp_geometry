#include <iostream>
#include <vector>

struct Point {
    int x;
    int y;
};

bool is_left_turn(Point const & a, Point const & b, Point const & c) {
    int ax = b.x - a.x;
    int ay = b.y - a.y;
    int bx = c.x - b.x;
    int by = c.y - b.y;
    return (ax * by - ay * bx) > 0;
}

struct Polygon {
    std::vector <Point> verticles;

    bool is_odd_edge(int y, int ind) const {
        int before = ind;
        while (verticles[ind].y == y) {
            before = (before - 1) % verticles.size();
        }
        int after = ind;
        while (verticles[ind].y == y) {
            after = (after + 1) % verticles.size();
        }
        return ((after - y) * (before - y) < 0);
    }

    bool is_inside(Point const & p) const {
        int intersections = 0;
        int size = int(verticles.size());
        for (int i = 0; i != size; ++i) {
            Point from = verticles[i];
            Point to = verticles[(i + 1) % size];
            if (from.y == to.y && from.y == p.y) {
                if (is_odd_edge(p.y, i)) {
                    ++intersections;
                } 
                while (verticles[i].y == p.y && i != size) {
                    ++i;
                }
                if (i != size) {
                    --i;
                }
            } else if (from.y == p.y) {
                if (verticles[(i - 1) % size].y != p.y) {
                    ++intersections;
                }
            } else if (to.y == p.y) {
                if (verticles[(i + 1) % size].y != p.y) {
                    ++intersections;
                } 
            } else if ((from.y - p.y) * (to.y - p.y) <= 0 &&
                    !is_left_turn(from, p, to)) {
                ++intersections;
            }
        }
        return (intersections % 2 == 0);
    }
};

int main() {
    int num_vert = 0;
    std::cin >> num_vert;
    char tmp[256];
    for (int i = 0; i != num_vert; ++i) {
        std::cin.getline(tmp, 256);
        std::cout << tmp << std::endl;
    }
}
