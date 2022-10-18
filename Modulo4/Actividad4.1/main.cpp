
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

bool getIntersection(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    Point p1 = Point(x1,y1);
    Point q1 = Point(x2,y2);
    Point p2 = Point(x3,y3);
    Point q2 = Point(x4,y4);
    cout << "P1: " << p1.x << " " << p1.y << endl;
    cout << "Q1: " << q1.x << " " << q1.y << endl;
    cout << "P2: " << p2.x << " " << p2.y << endl;
    cout << "Q2: " << q2.x << " " << q2.y << endl;
    return intersect(p1, q1, p2, q2);
}

int main() {
    //Point p1 = { 0, 0 }, q1 = { 4, 4 };
    //Point p2 = { 1, 2 }, q2 = { 10, 2};
    //Point p1 = { 0, 6 }, q1 = { 6, 0 };
    //Point p2 = { 0, 0 }, q2 = { 5, 5};

    int n;
    cin >> n;

    int point[8];
    bool result[n];

    cout << "---Cases---" << endl;
    for(int i=0; i<n; i++) {
        cout << "Case " << i << endl;
        for(int j=0; j<8; j++) {
            cin >> point[j];
        }
        result[i] = getIntersection(point[0], point[1], point[2], point[3], point[4], point[5], point[6], point[7]);
        cout << endl;
    }

    cout << endl;


    cout << boolalpha << "---RESULTS---" << endl;
    for(int i=0; i<n; i++) {
        cout << result[i] << endl;
    }
    cout << endl;


    return 0;
}
