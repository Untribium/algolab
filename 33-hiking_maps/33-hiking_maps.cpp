#include<stdio.h>
#include<limits.h>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

bool debug = false;

struct Leg {
    Leg(int i, int ax, int ay, int bx, int by) {
        index = i;
        a = IK::Point_2(ax, ay);
        b = IK::Point_2(bx, by);
    }
    IK::Point_2 a;
    IK::Point_2 b;
    int index;
};

struct Map {
    Map(int i, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5) {
        index = i;
        q0 = IK::Point_2(x0, y0);
        q1 = IK::Point_2(x1, y1);
        q2 = IK::Point_2(x2, y2);
        q3 = IK::Point_2(x3, y3);
        q4 = IK::Point_2(x4, y4);
        q5 = IK::Point_2(x5, y5);
    }
    int index;
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

// Point is within triangle if it lies to the left of all edges (given proper orientation of all edges, see line 107)
// !right_turn to handle collinearity
bool contains(const Map& m, const IK::Point_2& p) {
    return !CGAL::right_turn(m.q0, m.q1, p) && !CGAL::right_turn(m.q2, m.q3, p) && !CGAL::right_turn(m.q4, m.q5, p);
}

// Map contains Leg if both endpoints are contained by the map
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

        legs.push_back(Leg(i-1, old_x, old_y, x, y));
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

        Map m(i, x0, y0, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);

        if(debug) printf("- fix edge direction\n");

        // fix orientations
        // the entire triangle must be to the left, therefore pick any point and check
        // can't be collinear since no qx is a vertex
        // resulting triangle is always indexed counterclockwisely
        if(CGAL::right_turn(m.q0, m.q1, m.q2)) {
            if(debug) printf("--- swap #1\n");
            swap(&m.q0, &m.q1);
        }

        if(CGAL::right_turn(m.q2, m.q3, m.q4)) {
            if(debug) printf("--- swap #2\n");
            swap(&m.q2, &m.q3);
        }

        if(CGAL::right_turn(m.q4, m.q5, m.q0)) {
            if(debug) printf("--- swap #3\n");
            swap(&m.q4, &m.q5);
        }

        if(debug) printf("- (%.0f, %.0f) -> (%.0f, %.0f), (%.0f, %.0f) -> (%.0f, %.0f), (%.0f, %.0f) -> (%.0f, %.0f)\n", m.q0.x(), m.q0.y(), m.q1.x(), m.q1.y(), m.q2.x(), m.q2.y(), m.q3.x(), m.q3.y(), m.q4.x(), m.q4.y(), m.q5.x(), m.q5.y());

        maps.push_back(m);
    }

    if(debug) printf("- calculate coverage\n");

    // calculate coverage for all maps and legs
    for(Map& map : maps) {
        for(Leg leg : legs) {
            if(covers(map, leg)) {
                map.covers.push_back(leg.index);
                if(debug) printf("--- map #%i covers leg #%i\n", map.index, leg.index);
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

    int l = 0, r = 0, count = 0; // left, right, count of covered (distinct) legs
    int min_cost = INT_MAX; // min #maps

    vector<int> covered(legs.size(), 0); // how many maps in the current window cover a certain leg

    // move right pointer through all maps
    while(r < maps.size()) {
        // add rightmost map, increase covered-counter
        for(int j : maps[r].covers) {
            covered[j]++;
            // if leg wasn't covered before, increase count
            if(covered[j] == 1) {
                count++;
            }
        }

        // move left pointer if leftmost map is no longer required for complete coverage
        while(l < r) {
            bool obs = true; // obsolete
            for(int j : maps[l].covers) {
                // if maps[l] is the only map in the window covering legs[j] then abort
                if(covered[j] == 1) {
                    obs = false;
                    break;
                }
            }

            // remove leftmost map if obsolete, adjust covered-counter
            if(obs) {
                for(int j : maps[l].covers) {
                    covered[j]--;
                }
                // move left pointer
                l++;
            }
            else {
                break;
            }
        }

        // if all legs are covered...
        if(count == legs.size()) {
            // ...see if cost is now smaller than current min
            min_cost = min(min_cost, r-l+1);
        }

        // move right pointer
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
