#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

struct Point
{
    double x, y;

    Point() {}

    Point(Point p1, Point p2)
    {
        x = p2.x - p1.x;
        y = p2.y - p1.y;
    }
} P[200002];

typedef Point Vector;
int T, N;
Point base;
vector<Point> hull;

bool operator==(Point& p1, Point& p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

int ccw(Vector v1, Vector v2)
{
    double result = v1.x * v2.y - v2.x * v1.y;
    if(result > 0) return 1;
    else if(result < 0) return -1;
    else return 0;
}

double dist(Point p1, Point p2)
{
    return pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
}

bool comp1(Point p1, Point p2)
{
    Vector v1(base, p1), v2(base, p2);
    int dir = ccw(v1, v2);

    return dir == 0 ? dist(base, p1) > dist(base, p2) : dir > 0;
}

bool comp2(Point p1, Point p2)
{
    return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
}

int main()
{
    hull.clear();

    cin >> N;
    for(int i = 1; i <= N; i++) cin >> P[i].x >> P[i].y;

    sort(P + 1, P + N + 1, comp2);
    base = P[1];
    sort(P + 2, P + N + 1, comp1);

    for(int i = 1; i <= N + 1; i++)
    {
        while(hull.size() > 2)
        {
            int idx = hull.size(), dir;
            Vector v1(hull[idx - 2], hull[idx - 1]), v2(hull[idx - 2], P[(i - 1) % N + 1]);
            dir = ccw(v1, v2);

            if(dir > 0) break;
            hull.pop_back();
        }

        if(i < N + 1) hull.push_back(P[i]);
    }

    // for(Point p : hull) cout << p.x << ' ' << p.y << '\n';

    cout << hull.size() << '\n';
}
