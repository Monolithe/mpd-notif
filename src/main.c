#include <mpd/client.h>
#include <mpd/connection.h>
#include <mpd/status.h>
#include <mpd/entity.h>
#include <mpd/search.h>
#include <mpd/tag.h>
#include <mpd/message.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int handle_error(struct mpd_connection *c) {
    assert(mpd_connection_get_error(c) != MPD_ERROR_SUCCESS);
    fprintf(stderr, "%s\n", mpd_connection_get_error_message(c));
    mpd_connection_free(c);
    return EXIT_FAILURE;
}

static const char *getLabel(const struct mpd_song *song, enum mpd_tag_type type) {
    unsigned i = 0;
    const char *value;
    value = mpd_song_get_tag(song, type, 0);
    return value;
}

static void print_song_info(const struct mpd_song *song) {
    const char *artist;
    const char *title;
    artist = getLabel(song, MPD_TAG_ARTIST);
    title = getLabel(song, MPD_TAG_TITLE);
    printf("%s : %s\n", artist, title);
}

int main(int argc, char *argv[]) {
    struct mpd_connection *conn;
    struct mpd_song *song;
    struct mpd_status *status;

    conn = mpd_connection_new("127.0.0.1", 6600, 0);

    if(mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS) {
        return handle_error(conn);
    }

    
    
    while(1) {
        enum mpd_idle idle = mpd_run_idle(conn);
        
        if(idle == 0 && mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS)
            return handle_error(conn);
        

        for(unsigned j = 0; ; ++j) {
            enum mpd_idle i = 1 << j;
            const char *name = mpd_idle_name(i);
        
            if(name == NULL)
                break;
        
            if (idle & i && strcmp(name, "player") == 0) {
                printf("%s\n", name);
                mpd_command_list_begin(conn, true);
                mpd_send_current_song(conn);
                mpd_command_list_end(conn);
                song = mpd_recv_song(conn);
                mpd_response_next(conn);
                print_song_info(song);
                mpd_response_finish(conn);
            }
        }
    }
    
    if(mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS || !mpd_response_finish(conn)) {
        mpd_song_free(song);
        mpd_status_free(status);
        return handle_error(conn);
    }

    mpd_song_free(song);
    mpd_status_free(status);
    mpd_connection_free(conn);
    
    return 0;
}
