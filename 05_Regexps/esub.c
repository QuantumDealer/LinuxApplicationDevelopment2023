#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define MAX 10

int main(int argc, char *argv[]) {
    char *buf;
    size_t len = 0;
    int chars;
    regex_t regex;
    regmatch_t bags[MAX];

    if(argc != 4){
        printf("Not enough argumets\n");
        exit(1);
    }
    
    int rc;
    if ((rc = regcomp(&regex, argv[1], REG_EXTENDED))) {
        char err_buf[100]; 
        regerror(rc, &regex, err_buf, 100);
        fprintf(stderr, "%s\n", err_buf);
        exit(1);
    }

    int max_sub = 0;
    for(int i = 0; argv[2][i] && argv[2][i+1]; ++i)
        if (argv[2][i] == '\\' && argv[2][i+1] > '0' && argv[2][i+1] <= '9')
            max_sub = (max_sub > argv[2][i+1] -'0') ? max_sub : (argv[2][i+1] - '0');
    if (max_sub > regex.re_nsub) {
        fprintf(stderr, "Invalid substitution: unsufficient capture groups in regex: %d\n", max_sub);
        exit(1);
    }

    int re;
    if (re = regexec(&regex, argv[3], MAX, bags, REG_EXTENDED)) {
        char err_buf[100]; 
        regerror(rc, &regex, err_buf, 100);
        fprintf(stderr, "%s\n", err_buf);
        exit(1);
    }

    printf("%.*s", bags[0].rm_so, argv[3]);

    int i;
    for(i = 0; argv[2][i] && argv[2][i+1]; ++i) {
        if (argv[2][i] == '\\' && argv[2][i+1] > '0' && argv[2][i+1] <= '9') {
            printf("%.*s", bags[argv[2][i+1] - '0'].rm_eo - bags[argv[2][i+1] - '0'].rm_so, argv[3] + bags[argv[2][i+1] - '0'].rm_so);
            i++;
        } else if (argv[2][i] == '\\' && argv[2][i+1] == '\\') {
            printf("\\"); i++;
        } else {
            printf("%c", argv[2][i]);
        }
    }
    if (argv[2][i]) {
        printf("%c", argv[2][i]);
    }
    printf("%s\n", argv[3] + bags[0].rm_eo);

    regfree(&regex);

    return 0;
}