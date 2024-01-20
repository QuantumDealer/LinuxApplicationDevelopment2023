#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if(argc != 3){
        printf("Error occured: Not enough arguments\n");
        exit(1);
    }

    char *infile_name = argv[1];
    char *outfile_name = argv[2];

    FILE *infile = fopen(infile_name, "r");
    if(infile == NULL){
        printf("Error occured: Could not open infile\n");
        exit(2);
    }

    FILE *outfile = fopen(outfile_name, "w");
    if(outfile == NULL){
        printf("Error occured: Could not open outfile\n");
        exit(3);
    }

    char c;
    while((c = fgetc(infile)) != EOF){
        fputc(c, outfile);
        if (ferror(outfile)){
            printf("Error occured: Could not write to outfile\n");
            exit(4);
        }
    }

    if(fclose(outfile) == -1){
        printf("Error occured: Could not close outfile\n");
        exit(5);
    }

    if(fclose(infile) == -1){
        printf("Error occured: Could not close infile\n");
        exit(6);
    }

    return 0;
}