#include<stdio.h>
#include<algorithm>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Exact_predicates_exact_constructions_kernel.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Exact_predicates_exact_constructions_kernel K;

typedef  CGAL::Min_circle_2_traits_2<K> Traits;
typedef  CGAL::Min_circle_2<Traits> Min_circle;

bool debug = false;

struct City {
    City() {}
    City(int x, int y) {
        pos = IK::Point_2(x, y);
    }
    IK::Point_2 pos;
    IK::FT distance;
};


bool operator<(const City& c1, const City& c2) {
    return c1.distance < c2.distance;
}

double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

int n;

vector<City> cities;
City their;

K::FT cur_dist;

K::FT bounding_radius(int begin, int end) {
    int l = end-begin;
    K::Point_2 points[l];

    for(int i = 0; i < l; ++i) {
        points[i] = K::Point_2(cities[i].pos.x(), cities[i].pos.y());
    }

    Min_circle mc(points, points+l, true);

    return mc.circle().squared_radius();
}

bool check(int a) {
    // City last_city = cities[a];
    // IK::FT last_distance = last_city.distance;

    //while(a < cities.size() && cities[a].distance == last_distance) { a++; }
    a++;

    if(a<n) {

        cur_dist = bounding_radius(a, cities.size());

        if(cur_dist <= squared_distance(K::Point_2(their.pos.x(), their.pos.y()), K::Point_2(cities[a-1].pos.x(), cities[a-1].pos.y()))) {
            return true;
        }
        else {
            return false;
        }

    }
    else {
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
    int min_r = 1, max_r = cities.size(), a;

    while(min_r != max_r) {
        a = (min_r+max_r)/2;
        if(check(a)) {
            max_r = a;
        }
        else {
            min_r = a+1;
        }
    }

    if(bounding_radius() > bounding_radius(min_r+1))
    // check special case where last point was wrongly taken

    printf("%i\n", min_r);

}


int main() {
    int t;
    scanf("%i", &t);

    while(t--) {
        do_case();
    }
}
