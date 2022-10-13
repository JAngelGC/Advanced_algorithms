
#include <iostream>
#include <string>

using namespace std;

struct Point {
    int x;
    int y;

    Point(int pX, int pY) {
        x = pX;
        y = pY;
    }

    void compare(int p2, int q2) {
        // comparation
    }
};

string orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) {
        return "Collinear";
    }
    else if (val > 0) {
        return "Clock";
    }
    else {
        return "Counter";
    }
}


bool intersect(Point p1, Point q1, Point p2, Point q2) {
    
    string o1 = orientation(p1, q1, p2);
    string o2 = orientation(p1, q1, q2);
    string o3 = orientation(p2, q2, p1);
    string o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) {
        return true;
    }
    else {
        return false;
    }
}


int main() {
    //Point p1 = { 0, 0 }, q1 = { 4, 4 };
    //Point p2 = { 1, 2 }, q2 = { 10, 2};
    Point p1 = { 0, 6 }, q1 = { 6, 0 };
    Point p2 = { 0, 0 }, q2 = { 5, 5};

    cout << intersect(p1 ,q1, p2, q2) << endl;



    return 0;
}
