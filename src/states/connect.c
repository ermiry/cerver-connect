#include <stdlib.h>

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

#include "connect/connect.h"
#include "connect/validation.h"

State *connect_state = NULL;

static void connect_update (void);

static void connect_to_cerver (void *ptr);

TextBox *connect_text = NULL;
InputField *ip_input = NULL;
InputField *port_input = NULL;
InputField *username_input = NULL;
InputField *password_input = NULL;
Button *connect_button = NULL;

static u8 connect_init (void) {

    connect_state->update = connect_update;

    Font *font = ui_font_get_by_name ("roboto");

    connect_text = ui_textbox_create (10, 10, 0, 0);
    ui_textbox_set_text (connect_text, "Connect to your cerver", 
        font, 64, RGBA_WHITE);

    ip_input = ui_input_field_create (100, 100, 200, 60);
    ui_input_field_set_placeholder_text (ip_input, "Cerver IP",
        font, 32, RGBA_WHITE);
    ui_input_field_set_text (ip_input, "", font, 32, RGBA_WHITE, false);
    ui_input_field_set_selected (ip_input, RGBA_BLUE);
    port_input = ui_input_field_create (100, 200, 200, 60);
    ui_input_field_set_placeholder_text (port_input, "Cerver Port", 
        font, 32, RGBA_WHITE);
    ui_input_field_set_text (port_input, "", font, 32, RGBA_WHITE, false);
    ui_input_field_set_selected (port_input, RGBA_BLUE);

    username_input = ui_input_field_create (100, 300, 200, 60);
    ui_input_field_set_placeholder_text (username_input, "Username", 
        font, 32, RGBA_WHITE);
    ui_input_field_set_text (username_input, "", font, 32, RGBA_WHITE, false);
    ui_input_field_set_selected (username_input, RGBA_BLUE);
    password_input = ui_input_field_create (100, 400, 200, 60);
    ui_input_field_set_placeholder_text (password_input, "Password",
        font, 32, RGBA_WHITE);
    ui_input_field_set_text (password_input, "", font, 32, RGBA_WHITE, true);
    ui_input_field_set_selected (password_input, RGBA_BLUE);

    connect_button = ui_button_create (100, 500, 300, 100);
    ui_button_set_text (connect_button, "Connect", font, 64, RGBA_WHITE);
    ui_button_set_sprite (connect_button, BUTTON_STATE_MOUSE_OUT, "./assets/ui/blue_button04.png");
    ui_button_set_sprite (connect_button, BUTTON_STATE_MOUSE_DOWN, "./assets/ui/blue_button05.png");
    ui_button_set_bg_color (connect_button, RGBA_GREEN);
    ui_button_set_action (connect_button, connect_to_cerver, NULL);

}

static void connect_update (void) {

    game_object_update_all ();
    
}

// destroy all game data
static u8 connect_end (void) {


}

static void connect_on_enter (void) { connect_init (); }

static void connect_on_exit (void) { connect_end (); }

State *connect_state_new (void) {

    State *new_connect_state = (State *) malloc (sizeof (State));
    if (new_connect_state) {
        // new_game_state->state = IN_GAME;

        new_connect_state->update = NULL;

        new_connect_state->onEnter = connect_on_enter;
        new_connect_state->onExit = connect_on_exit;
    }

}

static void connect_to_cerver (void *ptr) {

    String *ip = ui_input_field_get_input (ip_input);

    // check for valid ip
    if (validation_check_value (ip_regex, ip->str)) {
        // check for valid port
        String *port = ui_input_field_get_input (port_input);
        if (port->len > 0) {
            int portnum = atoi (port->str);
            if (!cerver_connect_to_cerver (ip->str, portnum)) {
                // set notification
                ui_notification_create_and_display (main_noti_center, NOTI_TYPE_SUCCESS, 5, false, 
                    "Connected!", "Connected to cerver!");

                // exit connect state and enter game state
            }
        }

        else {
            // set port error message
        }
    }

    else {
        // set ip error message
    }

}