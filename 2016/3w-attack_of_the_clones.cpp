#include<stdio.h>
#include<vector>
#include<algorithm>

using namespace std;

struct Jedi {
    Jedi(int p_a, int p_b, int p_d) {
        a = p_a;
        b = p_b;
        d = p_d;
    }
    int a;
    int b;
    int d;
};

bool operator<(const Jedi& j1, const Jedi& j2) {
    return j1.b < j2.b;
}

struct Endpoint {
    Endpoint(int p_s, bool p_left) {
        s = p_s;
        left = p_left;
    }
    int s;
    bool left;
};

bool operator<(const Endpoint& e1, const Endpoint& e2) {
    return (e1.s == e2.s) ? e1.left : e1.s < e2.s;
}

vector<Jedi> input;
vector<Jedi> jedis; // jedis
vector<Jedi> starts; // starting points
vector<Endpoint> endpoints; // endpoints of intervals

int m, n;

int distance(int a, int b) {
    return (b-a+m)%m;
}

int schedule(int a, int b, int count) {

    int i;
    while(i < jedis.size() && jedis[i].b < b) { ++i; }

    i %= jedis.size();

    for(int k = i; k < i+jedis.size(); ++k) {

        Jedi j = jedis[k%jedis.size()];

        if(j.d < distance(b, j.b) && distance(a, b) < distance(j.b, b)) {
            count++;
            b = j.b;
        }
    }

    return count;
}

void do_case() {
    scanf("%i %i", &n, &m);

    int count = 0;
    int l = 0;

    input.clear();
    jedis.clear();
    starts.clear();
    endpoints.clear();

    for(int i = 0; i < n; ++i) {
        int a, b;
        scanf("%i %i", &a, &b);

        // subtract 1 to allow % computations
        a -= 1;
        b -= 1;

        input.push_back(Jedi(a, b, distance(a, b)));

        // add endpoints of intervals for linear collision count
        endpoints.push_back(Endpoint(a, true));
        endpoints.push_back(Endpoint(b, false));

        // if distance from a to b is >= b, then current jedi protects segment 0
        if(distance(a, b) >= b) {
            count++;
        }
    }

    sort(endpoints.begin(), endpoints.end());

    // search segment k where count of collisions is minimal
    int min_segment = 0;
    int min_count = count;

    for(int k = 0; k < endpoints.size(); ++k) {

        if(endpoints[k].left) {
            count++;
        }
        else {
            count--;
            if(count < min_count) {
                min_count = count;
                min_segment = endpoints[k].s;
            }
        }
    }

    sort(input.begin(), input.end());

    for(int i = 0; i < n; ++i) {

        if(input[i].d >= distance(min_segment, input[i].b)) {
            starts.push_back(input[i]);
        }
        else {
            jedis.push_back(input[i]);
        }
    }

    if(jedis.size() > 0) {

        // no jedi protects segment l, initial count = 0
        int max_jedis = schedule(min_segment, min_segment, 0);

        // one jedi protects segment l
        for(int i = 0; i < starts.size(); ++i) {

            max_jedis = max(max_jedis, schedule(starts[i].a, starts[i].b, 1));
        }

        printf("%i\n", max_jedis);
    }
    else {
        printf("%i\n", 1);
    }

}

int main() {
    int t;
    scanf("%i", &t);

    while(t--) {
        do_case();
    }

    return 0;
}
