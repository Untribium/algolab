#include<stdio.h>
#include<algorithm>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Exact_predicates_exact_constructions_kernel.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Exact_predicates_exact_constructions_kernel K;

typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

bool debug = false;

struct City {
    City() {}
    City(int x, int y) {
        pos = IK::Point_2(x, y);
    }
    IK::Point_2 pos;
    double distance;
};


bool operator<(const City& c1, const City& c2) {
    return c1.distance < c2.distance;
}

double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a-1 >= x) a -= 1;
    while (a < x) a += 1;
    return a;
}

int n;

vector<City> cities;
City their;

K::FT min_r;

K::FT bounding_radius(int begin, int end) {
    int l = end-begin;
    K::Point_2 points[l];

    for(int i = 0; i < l; ++i) {
        points[i] = K::Point_2(cities[begin+i].pos.x(), cities[begin+i].pos.y());
    }

    Min_circle mc(points, points+l, true);

    return mc.circle().squared_radius();
}

// check if old antenna can cover up to index a
bool check(int a) {

    if(debug) printf("check(%i)?\n", a);

    if(a < n-1) {

        K::FT cur_r = bounding_radius(a+1, cities.size());
        if(debug) printf("bounding radius (a=%i): %.2lf\n", a, CGAL::to_double(cur_r));

        if(cur_r <= cities[a].distance) {
            min_r = (cities[a].distance < min_r) ? cities[a].distance : min_r;
            return true;
        }
        else {
            min_r = (cur_r < min_r) ? cur_r : min_r;
            return false;
        }

    }
    else {
        min_r = (cities[a-1].distance < min_r) ? cities[a].distance : min_r;
        return true;
    }

}

void do_case() {
    scanf("%i", &n);

    cities.clear();

    for(int i = 0; i < n; ++i) {
        int x, y;
        scanf("%i %i", &x, &y);

        cities.push_back(City(x, y));
    }

    their = cities[0];

    for(int i = 0; i < n; ++i) {
        cities[i].distance = CGAL::squared_distance(their.pos, cities[i].pos);
    }

    sort(cities.begin(), cities.end());

    // bin search
    int min_i = 0, max_i = cities.size()-1, a;
    min_r = 1000000000000000000;

    while(min_i != max_i) {
        a = (min_i+max_i)/2;
        if(check(a)) {
            if(debug) printf("check(%i): true\n", a);
            max_i = a;
        }
        else {
            if(debug) printf("check(%i): false\n", a);
            min_i = a+1;
        }
    }

    printf("%.0lf\n", ceil_to_double(min_r));

}


int main() {
    int t;
    scanf("%i", &t);

    while(t--) {
        do_case();
    }
}
