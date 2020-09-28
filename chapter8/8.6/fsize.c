#include <stdio.h>
#include <string.h>
// #include "syscalls.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"
#include "../../helper_functions.h"

#define MAX_PATH 1024

void dirwalk(char *, void (*fcn) (char *));

/* fsize: print the name of the file "name" */
void fsize(char *name) {
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & __S_IFMT) == __S_IFDIR) { /* if name is directory, walk it */
        // printf("name %s is a directory\n", name);
        dirwalk(name, fsize);
    }
    printf("%8ld %s\n", stbuf.st_size, name);
}

/* dirwalk: apply fcn to all files in dir recursively */
void dirwalk(char *dir, void (*fcn)(char *)) {
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    // print_variable(dfd->fd); /* 3 */
    while ((dp = readdir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0) {
            continue; /* skip self and parent directory */
        }
        if (strlen(dir) + strlen(dp->name)+2 > sizeof(name)) {
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
        }
        else {
            sprintf(name, "%s/%s", dir, dp->name); /* save full directory to name */
            (*fcn)(name); /* and apply fcn to it */
        }
    }
    closedir(dfd);
}