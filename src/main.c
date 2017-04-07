/***********************************************************
Name ...... : mpd-notif
Role ...... : 

Author .... : Monolithe
Version ... : 0.5
Licence ... : GPL

Compilation : gcc -std=c99 -Wall -lmpdclient -o mpd-notif main.c mpd.c
************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "mpd.h"

int main(int argc, char *argv[]) {
    int opt;
    char *ip = NULL;
    int port = 0;
    int ipset = 0;

    while((opt = getopt(argc, argv, "c:p:")) != -1) {
        switch(opt) {
            case 'c':
                ip = optarg;   
                break;
            case 'p':
                port = strtol(optarg, NULL, 10); 
                break;
        }

    }

    if(ip == NULL) {
        ip = malloc(sizeof(char) * 10);
        strcpy(ip, "127.0.0.1");
        ipset = 1;
    }

    if(port == 0) {
        port = 6600;
    }

    int res = mainMpdNotifLoop(ip, port);
    if(ipset) {
        free(ip);
    }
    return res;
}
