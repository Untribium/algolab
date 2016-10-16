#include<stdio.h>
#include<limits.h>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

bool debug = false;

struct Leg {
    Leg(int ax, int ay, int bx, int by, int i) {
        a = IK::Point_2(ax, ay);
        b = IK::Point_2(bx, by);
        index = i;
    }
    IK::Point_2 a;
    IK::Point_2 b;
    int index;
};

struct Map {
    Map(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5) {
        q0 = IK::Point_2(x0, y0);
        q1 = IK::Point_2(x1, y1);
        q2 = IK::Point_2(x2, y2);
        q3 = IK::Point_2(x3, y3);
        q4 = IK::Point_2(x4, y4);
        q5 = IK::Point_2(x5, y5);
    }
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

        legs.push_back(Leg(old_x, old_y, x, y, i-1));
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

        if(debug) printf("- create map\n");

        Map m(x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);

        if(debug) printf("- fix edge direction\n");

        // fix directions, can't be collinear since no qx is a vertex
        if(CGAL::right_turn(m.q0, m.q1, m.q2)) {
            if(debug) printf("- - swap #1\n");
            swap(&m.q0, &m.q1);
        }

        if(CGAL::right_turn(m.q2, m.q3, m.q4)) {
            if(debug) printf("- - swap #2\n");
            swap(&m.q2, &m.q3);
        }

        if(CGAL::right_turn(m.q4, m.q5, m.q0)) {
            if(debug) printf("- - swap #3\n");
            swap(&m.q4, &m.q5);
        }

        if(debug) printf("- (%f, %f) -> (%f, %f), (%f, %f) -> (%f, %f), (%f, %f) -> (%f, %f)\n", m.q0.x(), m.q0.y(), m.q1.x(), m.q1.y(), m.q2.x(), m.q2.y(), m.q3.x(), m.q3.y(), m.q4.x(), m.q4.y(), m.q5.x(), m.q5.y());

        maps.push_back(m);
    }

    if(debug) printf("- calculate coverage\n");

    for(Map& map : maps) {
        for(Leg leg : legs) {
            if(covers(map, leg)) {
                map.covers.push_back(leg.index);
            }
        }
    }

    // vector<bool> cov(legs.size(), false);
    //
    // for(Map m : maps) {
    //     for(int i : m.covers) {
    //         cov[i] = true;
    //     }
    // }
    //
    // for(bool b : cov) {
    //     if(!b) {
    //         printf("fail\n");
    //     }
    // }

    if(debug) printf("- sliding window\n");

    int l = 0, r = 0, count = 0; // left, right, count
    int min_cost = INT_MAX; // min #maps

    vector<int> covered(legs.size(), 0);

    while(r < maps.size()) {
        for(int j : maps[r].covers) {
            covered[j]++;
            if(covered[j] == 1) {
                count++;
            }
        }

        while(l < r) {
            bool obs = true; // obsolete
            for(int j : maps[l].covers) {
                if(covered[j] < 2) {
                    obs = false;
                    break;
                }
            }

            if(obs) {
                for(int j : maps[l].covers) {
                    covered[j]--;
                }
                l++;
            }
            else {
                break;
            }
        }

        if(count == legs.size()) {
            min_cost = min(min_cost, r-l+1);
        }

        r++;
    }

    printf("%i\n", min_cost);
}

int main() {
    int c;
    scanf("%i", &c);

    while(c--) {
        do_case();
    }

    return 0;
}
