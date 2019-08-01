#include <stdio.h>

#include "cengine/cengine.h"
#include "cengine/manager/manager.h"

#include "cengine/ui/notification.h"

#include "cengine/utils/utils.h"
#include "cengine/utils/log.h"

#include "ermiry.h"
#include "states/login.h"

int main (void) {

    cengine_set_quit (ermiry_quit);
    cengine_assets_set_path ("./assets/");

    running = !ermiry_init () ? true : false;

    if (ermiry_init_ui ()) {
        cengine_log_msg (stderr, LOG_ERROR, LOG_NO_TYPE, "Failed to init ermriy UI!");
        running = false;
    }

    // if (!ermiry_cerver_connect ()) {
    //     ui_notification_create_and_display (main_noti_center, NOTI_TYPE_INFO, 3, false,
    //         "Connected to cerver!", "Connected to ermiry cerver");
    // }

    // else {
    //     ui_notification_create_and_display (main_noti_center, NOTI_TYPE_ERROR, 5, false,
    //         "Connection Error!", "Failed to connect to ermiry cerver!");
    // }

    login_state = login_state_new ();
    manager = manager_new (login_state);

    cengine_start (30);

    return ermiry_end ();

}