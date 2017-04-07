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

    while((opt = getopt(argc, argv, "c:p:h")) != -1) {
        switch(opt) {
            case 'c':
                ip = optarg;   
                break;
            case 'p':
                port = strtol(optarg, NULL, 10); 
                break;
            case 'h':
                printf("mpd-notif is a notification client for mpd\n
                        Options :\n
                        -c <IP> : set mpd servr IP
                        -p <PORT> : set port");
        }

    }

    if(ip == NULL) {
        ip = malloc(sizeof(char) * 10);
        strcpy(ip, DEFAULTIP);
        ipset = 1;
    }

    if(port == 0) {
        port = DEFAULTPORT;
    }

    int res = mainMpdNotifLoop(ip, port);
    if(ipset) {
        free(ip);
    }
    return res;
}
