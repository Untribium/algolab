#include<iostream>
#include<math.h>
#include<vector>
#include<CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_exact_constructions_kernel K;

typedef K::Ray_2 R2;
typedef K::Point_2 P2;
typedef K::Segment_2 S2;
typedef K::Direction_2 D2;

double floor_to_double(const K::FT& x) {
    double a = std::floor(to_double(x));
    while(a > x) a -= 1;
    while(a+1 <= x) a += 1;
    return a;
}

int main() {

    ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

    while(true) {
        int N;
        cin >> N;

        if(!N) break;

        long long px, py, qx, qy;
        cin >> px >> py >> qx >> qy;

        P2 p(px, py);
        R2 r(p, P2(qx, qy));
        S2 c(p, P2(0, 0));

        bool h = false;
        K::FT rd;
        P2 rp;

        vector<S2> segs(N);

        while(N--) {
            long long ax, ay, bx, by;
            cin >> ax >> ay >> bx >> by;

            segs[N] = S2(P2(ax, ay), P2(bx, by));
        }

        random_shuffle(segs.begin(), segs.end());

        for(S2 s : segs) {
            if(!h && do_intersect(r, s) || h && do_intersect(c, s)) {

                P2 i;

                if(r.direction() == s.direction()) {
                    i = s.source();
                } else if (r.direction() == -s.direction()) {
                    i = s.target();
                } else {
                    auto tmp = intersection(r, s);
                    i = *boost::get<P2>(&*tmp);
                }

                if(!h || squared_distance(p, i) < rd) {
                    h = true;
                    rp = i;
                    rd = squared_distance(p, rp);
                    c = S2(p, rp);
                }
            }
        }

        if(!h) {
            cout << "no" << endl;
        } else {
            cout << floor_to_double(rp.x()) << " " << floor_to_double(rp.y())<< endl;
        }
    }

    return 0;
}
