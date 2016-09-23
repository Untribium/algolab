#include<stdio.h>

void do_case() {
    int n;
    scanf("%i", &n);

    double sum = 0;

    for(; n; n--) {
        double d;
        scanf("%lf", &d);

        sum += d;
    }

    printf("%lf\n", sum);
}

int main() {

    int t;
    scanf("%i", &t);

    for(; t; t--){
        do_case();
    }

    return 0;
}
