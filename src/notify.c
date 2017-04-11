/***********************************************************
Name ...... : mpd-notif/notify.c
Role ...... : Show mpd notifications 

Author .... : Monolithe
Version ... : 0.9
Licence ... : GPL
************************************************************/

#include "notify.h"


int printMpdNotif(const char *string) {
    notify_init("mpd-notif");

    if(!notify_is_initted()) {
        return -1;
    }

    NotifyNotification *notif = NULL;

    notif = notify_notification_new(string, NULL, NULL);
    
    GError *err = NULL;

    notify_notification_show(notif, &err);
    
    if(err != NULL) {
        fprintf(stderr, "%s\n", err->message);
        g_error_free(err);
        notify_uninit();
        return -2;
    }    

    notify_uninit();
    return 0;
}
