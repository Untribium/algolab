#include<stdio.h>

#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

void do_case() {
    
}

int main() {
    int t;
    scanf("%i", &t);

    while(t--) {
        do_case();
    }
}
