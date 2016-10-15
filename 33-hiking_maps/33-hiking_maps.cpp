#include<stdio.h>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

bool debug = false;

struct Leg {
    Leg(IK::Point_2 p_a, IK::Point_2 p_b) {
        a = p_a;
        b = p_b;
    }
    IK::Point_2 a;
    IK::Point_2 b;
};

struct Map {
    IK::Point_2 q0;
    IK::Point_2 q1;
    IK::Point_2 q2;
    IK::Point_2 q3;
    IK::Point_2 q4;
    IK::Point_2 q5;
    vector<int> covers;
};

void swap(IK::Point_2* a, IK::Point_2* b) {
    IK::Point_2 tmp = *a;
    *a = *b;
    *b = tmp;
}

bool contains(const Map& m, const IK::Point_2& p) {
    return !CGAL::right_turn(m.q0, m.q1, p) && !CGAL::right_turn(m.q2, m.q3, p) && !CGAL::right_turn(m.q4, m.q5, p);
}

bool covers(const Map& m, const Leg& l) {
    return contains(m, l.a) && contains(m, l.b);
}

int m, n;

vector<Leg> legs;
vector<Map> maps;

bool check(int c) {
    int count = 0;
    vector<int> covered(legs.size(), 0);

    for(int i = 0; i < maps.size(); ++i) {
        for(int j : maps[i].covers) {
            covered[j]++;
            if(covered[j] == 1) {
                count++;
            }
        }

        if(i-c >= 0) {
            for(int j : maps[i-c].covers) {
                covered[j]--;
                if(covered[j] == 0) {
                    count--;
                }
            }
        }

        if(count == legs.size()) {
            return true;
        }
    }

    return false;
}

void do_case() {
    scanf("%i %i", &m, &n);

    legs.clear();

    if(debug) printf("read point #0\n");

    int old_x, old_y;
    scanf("%i %i", &old_x, &old_y);

    for(int i = 1; i < m; ++i) {

        if(debug) printf("read point #%i\n", i);

        int x, y;
        scanf("%i %i", &x, &y);

        legs.push_back(Leg(IK::Point_2(old_x, old_y), IK::Point_2(x, y)));
    }

    maps.clear();

    for(int i = 0; i < n; ++i) {

        if(debug) printf("read map #%i\n", i);

        int x0, y0, x1, y1;
        int x2, y2, x3, y3;
        int x4, y4, x5, y5;

        if(debug) printf("- scan coords\n");

        scanf("%i %i %i %i", &x0, &y0, &x1, &y1);
        scanf("%i %i %i %i", &x2, &y2, &x3, &y3);
        scanf("%i %i %i %i", &x4, &y4, &x5, &y5);

        if(debug) printf("- create points...");

        Map m;
        m.q0 = IK::Point_2(x0, y0);
        m.q1 = IK::Point_2(x1, y1);
        m.q2 = IK::Point_2(x2, y2);
        m.q3 = IK::Point_2(x3, y3);
        m.q4 = IK::Point_2(x4, y4);
        m.q5 = IK::Point_2(x5, y5);

        if(debug) printf("done\n");

        if(debug) printf("- fix edge direction\n");

        // fix directions, can't be collinear since no qx is a vertex
        if(CGAL::right_turn(m.q0, m.q1, m.q2)) {
            if(debug) printf("-- swap e1\n");
            swap(&m.q0, &m.q1);
        }

        if(CGAL::right_turn(m.q2, m.q3, m.q4)) {
            if(debug) printf("-- swap e2\n");
            swap(&m.q2, &m.q3);
        }

        if(CGAL::right_turn(m.q4, m.q5, m.q0)) {
            if(debug) printf("-- swap e3\n");
            swap(&m.q4, &m.q5);
        }

        if(debug) printf("- (%f, %f) -> (%f, %f), (%f, %f) -> (%f, %f), (%f, %f) -> (%f, %f)\n", m.q0.x(), m.q0.y(), m.q1.x(), m.q1.y(), m.q2.x(), m.q2.y(), m.q3.x(), m.q3.y(), m.q4.x(), m.q4.y(), m.q5.x(), m.q5.y());

        maps.push_back(m);
    }

    if(debug) printf("- calculate coverage\n");

    for(int i = 0; i < maps.size(); ++i) {
        for(int j = 0; j < legs.size(); ++j) {
            if(covers(maps[i], legs[j])) {
                maps[i].covers.push_back(j);

                if(debug) printf("-- map #%i covers leg #%i\n", i, j);
            }
        }
    }

    if(debug) printf("- binary search\n");

    // binary search for min number of maps

    int c_min = 1, c_max = maps.size();

    while(c_min != c_max) {
        int a = (c_min+c_max)/2;

        if(check(a)) {
            c_max = a;
        }
        else {
            c_min = a+1;
        }
    }

    printf("%i\n", c_min);
}

int main() {
    int c;
    scanf("%i", &c);

    while(c--) {
        do_case();
    }

    return 0;
}
