#ifndef _CERVER_CONNECT_H_
#define _CERVER_CONNECT_H_

#include "cengine/types/types.h"
#include "cengine/cerver/client.h"
#include "cengine/ui/notification.h"

extern NotiCenter *main_noti_center;

extern void connect_quit (void);

extern void connect_die (const char *error);

extern int connect_init (void);

extern int connect_end (void);

extern Client *client;
extern Connection *main_connection;

extern u8 connect_cerver_connect (const char *ip, u16 port);

extern void connect_cerver_disconnect (void);

#endif