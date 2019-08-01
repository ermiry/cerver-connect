#include "cengine/cengine.h"
#include "cengine/manager/manager.h"

#include "connect/connect.h"
#include "states/connect.h"
#include "states/game.h"

int main (void) {

    cengine_set_quit (connect_quit);
    cengine_assets_set_path ("./assets/");

    running = !connect_init () ? true : false;

    connect_state = connect_state_new ();
    manager = manager_new (connect_state);

    cengine_start (30);

    return connect_end ();

}