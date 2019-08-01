#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <signal.h>

#include "cengine/types/types.h"

#include "cengine/cengine.h"
#include "cengine/manager/manager.h"
#include "cengine/cerver/client.h"

#include "cengine/ui/ui.h"
#include "cengine/ui/font.h"
#include "cengine/ui/notification.h"

#include "cengine/utils/utils.h"
#include "cengine/utils/log.h"

#include "connect/connect.h"
#include "connect/validation.h"

void cerver_disconnect_from_cerver (void);

NotiCenter *main_noti_center = NULL;

#pragma region public

void cerver_connect_quit (void) { running = false; }

static void cerver_connect_quit_signal (int dummy) { running = false; }

void cerver_connect_die (const char *error) {

    cengine_log_msg (stderr, LOG_ERROR, LOG_NO_TYPE, error);
    cerver_connect_quit ();

};

static u8 cerver_connect_init_ui (void) {

    u8 errors = 0;

    ui_default_assets_set_path (c_string_create ("%sui/default/", cengine_assets_path->str));
    errors = ui_default_assets_load ();

    Font *main_font = ui_font_create ("roboto", "./assets/fonts/Roboto-Regular.ttf");
    if (main_font) {
        ui_font_set_sizes (main_font, 4, 20, 32, 64, 200);
        ui_font_load (main_font, TTF_STYLE_NORMAL);
    } 

    else {
        cengine_log_msg (stderr, LOG_ERROR, LOG_NO_TYPE, "Failed to load main font!");
        errors = 1;
    } 

    main_noti_center = ui_noti_center_create (3, UI_POS_UPPER_CENTER);
    if (!main_noti_center) errors = 1;

    return errors;

}

int cerver_connect_init (void) {

    int errors = 0;

    // register to some signals
    signal (SIGINT, cerver_connect_quit_signal);
    signal (SIGSEGV, cerver_connect_quit_signal);

    // main_settings = settings_load ();

    WindowSize window_size = { 1920, 1080 };
    errors = cengine_init ("Cerver Connect", window_size, false);

    errors = cerver_connect_init_ui ();

    errors = validation_init ();

    return errors;

}

int cerver_connect_end (void) {

    cerver_disconnect_from_cerver ();

    validation_end ();

    manager->curr_state->onExit ();
    manager_delete (manager);

    cengine_end ();

    return 0;

}

#pragma endregion

#pragma region connection

Client *client = NULL;
Connection *main_connection = NULL;

u8 cerver_connect_to_cerver (const char *ip, u16 port) {

    u8 retval = 1;

    if (ip) {
        client = client_create ();
        if (client) {
            client_connection_create (client, "main", 
                ip, port, PROTOCOL_TCP, false);
            main_connection = client_connection_get_by_name (client, "main");
            retval = client_connection_start (client, main_connection);
        }
    }

    return retval;

}

void cerver_disconnect_from_cerver (void) {

    client_connection_end (client, main_connection);
    client_teardown (client);

}

#pragma endregion