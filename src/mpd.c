/**********************************************************************************************
Name ....... : mpd-notif/mpd.c
Role ...... : Connect to the mpd server, wait for a "player" idle and print current's song name 

Author .... : Monolithe
Version ... : 0.9
Licence ... : GPL

***********************************************************************************************/

#include "mpd.h"

static int handleError(struct mpd_connection *c) {
    assert(mpd_connection_get_error(c) != MPD_ERROR_SUCCESS);
    fprintf(stderr, "%s\n", mpd_connection_get_error_message(c));
    mpd_connection_free(c);
    return EXIT_FAILURE;
}


const char *getLabel(const struct mpd_song *song, enum mpd_tag_type type) {
    const char *value;
    value = mpd_song_get_tag(song, type, 0);
    return value;
}

char *getSongInfo(const struct mpd_song *song) {
    const char *artist;
    const char *title;
    artist = getLabel(song, MPD_TAG_ARTIST);
    title = getLabel(song, MPD_TAG_TITLE);
    
    int size = strlen(artist) + strlen(title) + 3;
    char *res = calloc(size, size * sizeof(char));

    
    strcat(res, artist);
    strcat(res, " : ");
    strcat(res, title);
    
    return res;
}

void printInfos(struct mpd_connection *c) {
    struct mpd_song *song;
    
    mpd_command_list_begin(c, true);
    mpd_send_current_song(c);
    mpd_command_list_end(c);
    
    song = mpd_recv_song(c);
    
    mpd_response_next(c);

    char *songInfo = getSongInfo(song);
    printMpdNotif(songInfo);
    free(songInfo);
    
    mpd_response_finish(c);
    mpd_song_free(song);
}

int mainMpdNotifLoop(char *ip, int port) {
    int success = 0;
    printf("Connect to %s:%d...\n", ip, port);
    struct mpd_connection *conn;

    conn = mpd_connection_new(ip, port, 0);

    if(mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS) {
        return handleError(conn);
    }
    else {
        success = 1;
    }

    printf("Success !\n");

    while(mpd_connection_get_error(conn) == MPD_ERROR_SUCCESS) { // main loop, run while there's no errors

        enum mpd_idle idle = mpd_run_idle(conn);

        if(idle == 0 && mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS)
            return handleError(conn);

        for(unsigned j = 0; ; ++j) {
            enum mpd_idle i = 1 << j; // note : I have no idea wtf is this line doing
            const char *name = mpd_idle_name(i);

            if(name == NULL) 
                break;

            if(idle & i && strcmp(name, "player") == 0) {
                mpd_send_status(conn);
                struct mpd_status *status = mpd_recv_status(conn);
                
                if(mpd_status_get_error(status) != NULL) {
                    printf("error : %s\n", mpd_status_get_error(status));
                }

                if(mpd_status_get_state(status) == MPD_STATE_PLAY || mpd_status_get_state(status) == MPD_STATE_PAUSE) {
                    printInfos(conn);
                }
                mpd_status_free(status);
            }
        }
    }

    if(mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS || !mpd_response_finish(conn)) {
        return handleError(conn);
    }

    if(success) {
        mpd_connection_free(conn);
    }

    return 0;
}
