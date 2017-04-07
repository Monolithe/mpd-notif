#ifndef MPD_H
#define MPD_H

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

#define DEFAULTIP "127.0.0.1"
#define DEFAULTPORT 6600

const char *getLabel(const struct mpd_song*, enum mpd_tag_type);
void printInfos(struct mpd_connection*);
int mainMpdNotifLoop(char *, int);

#endif
