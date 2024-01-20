#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <rhash.h>
#include <errno.h>
#include <ctype.h>

#ifdef LIBREADLINE
#include <readline/readline.h>
#endif

// #1 командной строки — имя алгоритма хеша.
// #2 либо имя файла, либо строка (строка начинается с «"», файл — нет)
// result - hasf строки или файла
// должны поддерживаться как минимум MD5, SHA1 и TTH,
// если имя хеша начиналось с большой буквы, то в шестнадцатеричном виде,
// а если с маленькой — то в Base64 (в примерах есть Base32).
// stderr
// getline
// ctrl + D
// Модифицировать rhasher так, чтобы при сборке можно было использовать и getline(),
// и readline в зависимости от некоторого #define-а

int read(char **str){
#ifndef LIBREADLINE
    size_t str_size = 0;
    int n = getline(str, &str_size, stdin);
    if (n == -1){
        if(errno){
            fprintf(stderr, "Some error occured: %s\n", strerror(errno));
            free(*str);
            return -1;
        } else {
            printf("\n");
        }
    }
    return 0;
#else
    *str = readline(">> ");
    if(*str == NULL){
        printf("\n");
    }
    return 0;
#endif
}

void hash(char *str){
    unsigned hash_type;
    char *hash_type_str = strtok(str, " ");
    if(hash_type_str == NULL){
        fprintf(stderr, "Two arguments are required\n");
        return;
    } else if (!strcasecmp(hash_type_str, "md5")){
        hash_type = RHASH_MD5;
    } else if (!strcasecmp(hash_type_str, "sha1")){
        hash_type = RHASH_SHA1;
    } else if (!strcasecmp(hash_type_str, "tth")){
        hash_type = RHASH_TTH;
    } else {
        fprintf(stderr, "Unknown hash\n");
        return;
    }

    char *arg = strtok(NULL, "\n");
    unsigned char hashed_str[64];
    if(arg[0] == '"'){
        int res = rhash_file(hash_type, arg, hashed_str);
        if(res == -1){
            fprintf(stderr, "Some error occured: %s\n", strerror(errno));
            return;
        }
    } else {
        int res = rhash_msg(hash_type, &arg[1], strlen(&arg[1]), hashed_str);
        if(res == -1){
            fprintf(stderr, "Some error occured: %s\n", strerror(errno));
            return;
        }
    }

    char result[150];
    int format = isupper(hash_type_str[0]) ? RHPR_HEX : RHPR_BASE64;
    rhash_print_bytes(result, hashed_str, rhash_get_digest_size(hash_type), format);
    printf("%s\n", result);
}

int main(int argc, char *argv[]) {
    rhash_library_init();
    char *str = NULL;
    while(1){
        int n = read(&str);
        if(n != -1){
            hash(str);
        }
    }
    return 0;
}