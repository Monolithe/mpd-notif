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

#include "mpd.h"

int main(int argc, char *argv[]) {
    return mainMpdNotifLoop();
}
