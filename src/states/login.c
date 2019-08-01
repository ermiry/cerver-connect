#include "cengine/types/types.h"
#include "cengine/types/string.h"

#include "cengine/renderer.h"
#include "cengine/textures.h"
#include "cengine/animation.h"

#include "cengine/manager/manager.h"

#include "cengine/ui/ui.h"
#include "cengine/ui/font.h"
#include "cengine/ui/textbox.h"
#include "cengine/ui/inputfield.h"
#include "cengine/ui/button.h"
#include "cengine/ui/image.h"

#include "cengine/collections/dlist.h"

#include "cengine/utils/utils.h"

State *login_state = NULL;

static void login_update (void);

static u8 login_init (void) {

    login_state->update = login_update;

    Button *submit_button = ui_button_create (500, 500, 300, 100);
    ui_button_set_text (submit_button, "Submit", ui_font_get_by_name ("roboto"), 64, RGBA_WHITE);
    ui_button_set_sprite (submit_button, BUTTON_STATE_MOUSE_OUT, "./assets/ui/blue_button04.png");
    ui_button_set_sprite (submit_button, BUTTON_STATE_MOUSE_DOWN, "./assets/ui/blue_button05.png");
    ui_button_set_bg_color (submit_button, RGBA_GREEN);

    TextBox *login_text = ui_textbox_create (0, 0, 300, 100);
    ui_textbox_set_text (login_text, "Login", ui_font_get_by_name ("roboto"), 200, RGBA_WHITE);

    InputField *username_text = ui_input_field_create (500, 200, 200, 100);
    ui_input_field_set_placeholder_text (username_text, "Username", 
        ui_font_get_by_name ("roboto"), 32, RGBA_WHITE);
    ui_input_field_set_text (username_text, "", 
        ui_font_get_by_name ("roboto"), 32, RGBA_WHITE, true);
    ui_input_field_set_selected (username_text, RGBA_BLUE);

}

static void login_update (void) {

    game_object_update_all ();

    // update the camera
    // camera_update (main_camera);
    
}

// destroy all game data
static u8 login_end (void) {


}

static void login_onEnter (void) { login_init (); }

static void login_onExit (void) { login_end (); }

State *login_state_new (void) {

    State *new_login_state = (State *) malloc (sizeof (State));
    if (new_login_state) {
        // new_game_state->state = IN_GAME;

        new_login_state->update = NULL;

        new_login_state->onEnter = login_onEnter;
        new_login_state->onExit = login_onExit;
    }

}