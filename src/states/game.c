#include "cengine/types/types.h"
#include "cengine/types/string.h"

#include "cengine/renderer.h"
#include "cengine/textures.h"
#include "cengine/animation.h"
#include "cengine/game/go.h"
#include "cengine/game/camera.h"
#include "cengine/manager/manager.h"
#include "cengine/collections/dlist.h"

#include "cengine/utils/utils.h"

State *game_state = NULL;

static void game_update (void);

static u8 game_init (void) {

    game_state->update = game_update;

}

// destroy all game data
static u8 game_end (void) {



}

static void game_on_enter (void) { game_init (); }

static void game_on_exit (void) { game_end (); }

static void game_update (void) {

    game_object_update_all ();

    // update the camera
    // camera_update (main_camera);
    
}

State *game_state_new (void) {

    State *new_game_state = (State *) malloc (sizeof (State));
    if (new_game_state) {
        // new_game_state->state = IN_GAME;

        new_game_state->update = NULL;

        new_game_state->on_enter = game_on_enter;
        new_game_state->on_exit = game_on_exit;
    }

}