/***********************************************************
Name ...... : mpd-notif
Role ...... : 

Author .... : Monolithe
Version ... : 0.9
Licence ... : GPL

Compilation : gcc -std=c99 -Wall -lmpdclient `pkg-config --cflags --libs libnotify` -o mpd-notif main.c mpd.c notify.c
************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "mpd.h"


void showHelp() {
    printf("mpd-notif is a notification client for mpd\nusage : mpd-notif [-c IP] [-p PORT]\nOptions :\n-c <IP> : set mpd server IP\n-p <PORT> : set port\n-h : show this help\n");
}

int main(int argc, char *argv[]) {
    int opt;
    char *ip = NULL;
    int port = 0;
    int ipset = 0;
    int help = 0;

    while((opt = getopt(argc, argv, "c:p:h")) != -1) {
        switch(opt) {
            case 'c':
                ip = optarg;   
                break;
            case 'p':
                port = strtol(optarg, NULL, 10); 
                break;
            case 'h':
                showHelp();
                help = 1;
                break;
        }

    }

    if(help) {
        return 0;
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
