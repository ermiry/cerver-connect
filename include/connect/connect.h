#ifndef _CERVER_CONNECT_H_
#define _CERVER_CONNECT_H_

#include "cengine/types/types.h"
#include "cengine/cerver/client.h"
#include "cengine/ui/notification.h"

extern NotiCenter *main_noti_center;

extern void cerver_connect_quit (void);

extern void cerver_connect_die (const char *error);

extern int cerver_connect_init (void);

extern int cerver_connect_end (void);

extern Client *client;
extern Connection *main_connection;

extern u8 cerver_connect_to_cerver (const char *ip, u16 port);

extern void cerver_disconnect_from_cerver (void);

#endif