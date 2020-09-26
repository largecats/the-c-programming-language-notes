#include <stdio.h>
#include <string.h>
// #include "syscalls.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"
#include "../../../helper_functions.h"
#include <time.h>

#define MAX_PATH 1024

void dirwalk(char *, void (*fcn) (char *));

/* fsize: print the name of the file "name" */
void fsize(char *name) {
    struct stat stbuf;
    struct tm info;
    char format[] = "%Y-%m-%d %H:%M:%S";

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & __S_IFMT) == __S_IFDIR) { /* if name is directory, walk it */
        printf("name %s is a directory\n", name);
        dirwalk(name, fsize);
    }
    char accessTime[100];
    info = *localtime(&stbuf.st_atime);
    strftime(accessTime, sizeof(accessTime), format, &info);
    char modifyTime[100];
    info = *localtime(&stbuf.st_mtime);
    strftime(modifyTime, sizeof(modifyTime), format, &info);
    char changeTime[100];
    info = *localtime(&stbuf.st_ctime);
    strftime(changeTime, sizeof(changeTime), format, &info);
    printf("File: %s\nDevice: %d\nInode number: %8ld\nMode bits: %d\nNumber of links: %d\nOwner userid: %d\nOwnder gorupid: %d\nSize: %ld\nAccess: %s\nLModify: %s\nChange: %s\n", 
        name, stbuf.st_dev, stbuf.st_ino, stbuf.st_mode, stbuf.st_nlink, stbuf.st_uid, stbuf.st_gid, stbuf.st_size, accessTime, modifyTime, changeTime);
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