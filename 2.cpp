#include <iostream>
#include <vector>
#include <list>

struct Point {
    Point(int x, int y) : x(x), y(y) { }
    int x;
    int y;
};

enum turn_t {
    LEFT, RIGHT, COLLINEAR
};

turn_t get_turn(Point a, Point b, Point c) {
    std::int64_t det = ((std::int64_t)(c.y - a.y)) * (b.x - a.x) - ((std::int64_t)(c.x - a.x)) * (b.y - a.y);
    if (det < 0) {
        return RIGHT;
    } else if (det == 0) {
        return COLLINEAR;
    } 
    return LEFT;
}

enum chain_t {
    UP, DOWN, LEFTMOST, RIGHTMOST
};

struct Polygon {
    struct chained_point {
        chained_point(chain_t chain, size_t ind) : chain(chain), ind(ind) { }
        chain_t chain;
        size_t ind;
    };

    struct Triangle {
        Triangle(size_t a_ind, size_t b_ind, size_t c_ind) :
            a_ind(a_ind), b_ind(b_ind), c_ind(c_ind) { }
        size_t a_ind;
        size_t b_ind;
        size_t c_ind;
    };

    std::vector <Point> verticles;

    size_t get_leftmost_verticle() {
        int x = 1000000;
        size_t res = 0;
        for (size_t i = 0; i != verticles.size(); ++i) {
            if (verticles[i].x < x) {
                res = i;
                x = verticles[i].x;
            }
        }
        return res;
    }

    size_t next_vertex(size_t i) {
        return (i + 1) % verticles.size();
    }

    size_t prev_vertex(size_t i) {
        return (i + verticles.size() - 1) % verticles.size();
    }

    void sort_points(std::vector <chained_point> & sorted_points) {
        size_t leftmost = get_leftmost_verticle();
        sorted_points.push_back(chained_point(LEFTMOST, leftmost));
        size_t up_ind = prev_vertex(leftmost);
        size_t down_ind = next_vertex(leftmost);
        while (up_ind != down_ind) {
            if (verticles[up_ind].x <= verticles[down_ind].x) {
                sorted_points.push_back(chained_point(UP, up_ind));
                up_ind = prev_vertex(up_ind);
            } else {
                sorted_points.push_back(chained_point(DOWN, down_ind));
                down_ind = next_vertex(down_ind);
            }
        }
        sorted_points.push_back(chained_point(RIGHTMOST, up_ind));
    }

    void triangulate(std::vector <Triangle> & triangulation) {
        std::vector <chained_point> sorted_points;
        sort_points(sorted_points);
        std::list <chained_point> stack;
        for (size_t i = 0; i != sorted_points.size(); ++i) {
            if (stack.size() < 2) {
                stack.push_back(sorted_points[i]);
            } else {
                if (stack.back().chain == sorted_points[i].chain) {
                    chained_point a = sorted_points[i];
                    while (stack.size() >= 2) {
                        chained_point b = stack.back();
                        stack.pop_back();
                        chained_point c = stack.back();
                        stack.pop_back();
                        turn_t turn = get_turn(verticles[a.ind], verticles[b.ind], verticles[c.ind]);
                        if ((turn == LEFT && a.chain == UP) || (turn == RIGHT && a.chain == DOWN)) {
                            if (a.chain == UP) {
                                triangulation.push_back(Triangle(a.ind, b.ind, c.ind));
                            } else {
                                triangulation.push_back(Triangle(a.ind, c.ind, b.ind));
                            }
                            stack.push_back(c);
                        } else {
                            stack.push_back(c);
                            stack.push_back(b);
                            break;
                        }
                    }
                    stack.push_back(a);
                } else {
                    chained_point a = sorted_points[i];
                    chained_point b = stack.back();
                    chained_point c = chained_point(UP, 0);
                    size_t new_leftmost = b.ind;
                    stack.pop_back();
                    while(!stack.empty()) {
                        c = stack.back();
                        stack.pop_back();
                        if (b.chain == UP) {
                            triangulation.push_back(Triangle(a.ind, b.ind, c.ind));
                        } else {
                            triangulation.push_back(Triangle(a.ind, c.ind, b.ind));
                        }
                        b = c;
                    }
                    stack.push_back(chained_point(LEFTMOST, new_leftmost));
                    stack.push_back(sorted_points[i]);
                }
            }
        }
    }
};

Point parse_point(std::string const & str) {
    size_t comma = str.find(',');
    int x = std::atoi(&(str.c_str()[1]));
    int y = std::atoi(&(str.c_str()[comma + 1]));
    return Point(x, y);
}

bool operator <(Polygon::Triangle const & t1, Polygon::Triangle const & t2) {
    if (t1.a_ind != t2.a_ind) {
        return t1.a_ind < t2.a_ind;
    }
    if (t1.b_ind != t2.b_ind) {
        return t1.b_ind < t2.b_ind;
    }
    return t1.c_ind <= t2.c_ind;
}

void print_triangle(Polygon::Triangle & t) {
    std::cout << "(" << t.a_ind << ", " << t.b_ind << ", " << t.c_ind << ")" << std::endl;
}

void print_triangulation(std::vector <Polygon::Triangle> const & triangulation) {
    for (auto it = triangulation.begin(); it != triangulation.end(); ++it) {
        Polygon::Triangle t1 = *it;
        Polygon::Triangle t2 = Polygon::Triangle(t1.c_ind, t1.a_ind, t1.b_ind);
        Polygon::Triangle t3 = Polygon::Triangle(t1.b_ind, t1.c_ind, t1.a_ind);
        if (t1 < t2) {
            if (t1 < t3) {
                print_triangle(t1);
            } else {
                print_triangle(t3);
            }
        } else {
            if (t2 < t3) {
                print_triangle(t2);
            } else {
                print_triangle(t3);
            }
        }
    }
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

    /*
    Polygon poly;
    poly.verticles = {Point(0, 0), Point(2, -1), Point(3, -1), Point(4, -2),
                      Point(5, 0), Point(7, 1), Point(6, 2), Point(1, 1)};
    poly.verticles = {Point(4, 0), Point(5, 10), Point(0, 0), Point(2, 1), Point(3, -1), Point(3, 1) };
    */

    std::vector <Polygon::Triangle> triangulation;
    poly.triangulate(triangulation);
    print_triangulation(triangulation);
    return 0;
}
