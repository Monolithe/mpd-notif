/***********************************************************
Name ....... : mpd-notif
Role ...... : 

Author .... : Monolithe
Version ... : 0.3
Licence ... : GPL

Compilation : gcc -std=c99 -Wall -lmpdclient -o mpd-notif main.c mpd.c
************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "mpd.h"

int main(int argc, char *argv[]) {
    return mainMpdNotifLoop();
}
