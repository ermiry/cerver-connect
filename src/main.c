#include "cengine/cengine.h"
#include "cengine/manager/manager.h"

#include "connect/connect.h"
#include "states/login.h"
#include "states/game.h"

int main (void) {

    cengine_set_quit (connect_quit);
    cengine_assets_set_path ("./assets/");

    running = !connect_init () ? true : false;

    // login_state = login_state_new ();
    // manager = manager_new (login_state);
    game_state = game_state_new ();
    manager = manager_new (game_state);

    cengine_start (30);

    return connect_end ();

}