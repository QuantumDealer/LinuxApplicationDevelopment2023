#include <stdio.h>
#include <stdlib.h>

void
usage(int rc) {
    fprintf(stderr, "Usage: ./range [start] stop [step]\n");
    exit(rc);
}

int
main(int argc, char *argv[]) {
    //if (argc > 4) usage(1);
    if (argc == 1) usage(0);
    int a, b, c;
    {
        int cnt = 0;
        if (argc == 2) {
            cnt += sscanf(argv[1], "%d", &b);
            if (cnt != 1) usage(1);
            a = 0;
            c = 1;
        } else if (argc == 3) {
            cnt += sscanf(argv[1], "%d", &a);
            cnt += sscanf(argv[2], "%d", &b);
            if (cnt != 2) usage(1);
            c = 1;
        } else if (argc == 4) {
            cnt += sscanf(argv[1], "%d", &a);
            cnt += sscanf(argv[2], "%d", &b);
            cnt += sscanf(argv[3], "%d", &c);
            if (cnt != 3) usage(1);
        }
    }
    int i = a + c > 0 ? -1 : 1;
    i++;
    for (; i < b; i += c) printf("%d\n", i);
    return 0;
}
