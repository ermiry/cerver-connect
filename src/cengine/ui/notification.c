#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "cengine/types/types.h"
#include "cengine/types/string.h"

#include "cengine/collections/dlist.h"

#include "cengine/renderer.h"
#include "cengine/timer.h"

#include "cengine/ui/ui.h"
#include "cengine/ui/font.h"
#include "cengine/ui/notification.h"
#include "cengine/ui/components/text.h"

#pragma region Notification

static Notification *ui_notification_new (void) {

    Notification *noti = (Notification *) malloc (sizeof (Notification));
    if (noti) {
        memset (noti, 0, sizeof (Notification));

        noti->timestamp = NULL;
        noti->timestamp_text = NULL;

        noti->title = NULL;
        noti->msg = NULL;

        noti->life = timer_new ();
    }

    return noti;

}

void ui_notification_delete (void *noti_ptr) {

    if (noti_ptr) {
        Notification *noti = (Notification *) noti_ptr;

        ui_text_component_delete (noti->timestamp_text);

        ui_text_component_delete (noti->title);
        ui_text_component_delete (noti->msg);

        timer_destroy (noti->life);

        free (noti);
    }

}

// set notification bg color based on its type
static void ui_notification_get_color (Notification *noti) {

    if (noti) {
        switch (noti->type) {
            case NOTI_TYPE_INFO: {
                RGBA_Color color = { 34, 167, 240, 1 };
                noti->bgcolor = color;
            } break;
            case NOTI_TYPE_SUCCESS: {
                RGBA_Color color = { 38, 166, 91, 1 };
                noti->bgcolor = color;
            } break;
            case NOTI_TYPE_WARNING: {
                RGBA_Color color = { 247, 202, 24, 1 };
                noti->bgcolor = color;
            } break;
            case NOTI_TYPE_ERROR: {
                RGBA_Color color = { 150, 40, 27, 1 };
                noti->bgcolor = color; 
            } break;

            case NOTI_TYPE_UNDEFINED:
            case NOTI_TYPE_CUSTOM:
            default: {
                RGBA_Color color = { 149, 165, 166, 1 };
                noti->bgcolor = color;
            } break;
        }
    }

}

// sets the timestamp to be displayed in the notification
void ui_notification_set_timestmap (Notification *noti, struct tm *timestamp) {

    if (noti) {
        if (timestamp) {
            noti->timestamp = timestamp;

            // update the notification's timestamp text
            if (noti->timestamp_text) ui_text_component_delete (noti->timestamp_text);

            noti->timestamp_text = ui_text_component_new ();
            if (noti->timestamp_text) {
                String *time_str = timer_time_to_string (noti->timestamp);
                ui_text_component_init (noti->timestamp_text,
                    ui_font_get_default (), NOTI_TIMESTAMP_DEFAULT_SIZE, RGBA_WHITE, 
                    time_str->str);
                str_delete (time_str);
            }
        }
    }

}

// sets the notification's timestamp display options
void ui_notification_set_timestamp_options (Notification *noti, 
    Font *font, u32 size, RGBA_Color color) {

    if (noti) {
        if (noti->timestamp_text) {
            noti->timestamp_text->font = font;
            noti->timestamp_text->size = size;
            noti->timestamp_text->text_color = color;
        }
    }

}

// sets the color to be used in the notification's timestamp
void ui_notification_set_timestamp_color (Notification *noti, RGBA_Color color) {

    if (noti) {
        if (noti->timestamp_text) {
            noti->timestamp_text->text_color = color;
        }
    }

}

// sets the font to be used in the notification's timestamp
void ui_notification_set_timestamp_font (Notification *noti, Font *font) {

    if (noti) {
        if (noti->timestamp_text) {
            noti->timestamp_text->font = font;
        }
    }

}

// sets the title of the notification with some options
void ui_notification_set_title (Notification *noti, const char *text, 
    Font *font, u32 size, RGBA_Color color) {

    if (noti) {
        if (noti->title) ui_text_component_delete (noti->title);

        noti->title = ui_text_component_new ();
        if (noti->title) {
            ui_text_component_init (noti->title,
                font, size, color, text);
        }
    }

}

// sets some options for the notification's title
void ui_notification_set_title_options (Notification *noti, 
    Font *font, u32 size, RGBA_Color color) {

    if (noti) {
        if (noti->title) {
            noti->title->font = font;
            noti->title->size = size;
            noti->title->text_color = color;
        }
    }

}

// sets the color of the notification's title
void ui_notification_set_title_color (Notification *noti, RGBA_Color color) {

    if (noti) {
        if (noti->title) noti->title->text_color = color;
    } 

}

// sets the font to be used in the notification's title
void ui_notification_set_title_font (Notification *noti, Font *font) {

    if (noti) {
        if (noti->title) noti->title->font = font;
    }

}

// sets the msg of the notification with some options
void ui_notification_set_msg (Notification *noti, const char *text, 
    Font *font, u32 size, RGBA_Color color) {

    if (noti) {
        if (noti->msg) ui_text_component_delete (noti->msg);

        noti->msg = ui_text_component_new ();
        if (noti->msg) {
            ui_text_component_init (noti->msg,
                font, size, color, text);
        }
    }

}

// sets some options for the notification's msg
void ui_notification_set_msg_options (Notification *noti, 
    Font *font, u32 size, RGBA_Color color) {

    if (noti) {
        if (noti->msg) {
            noti->msg->font = font;
            noti->msg->size = size;
            noti->msg->text_color = color;
        }
    }

}

// sets the color of the notification's message
void ui_notification_set_msg_color (Notification *noti, RGBA_Color color) {

    if (noti) {
        if (noti->msg) noti->msg->text_color = color;
    }

}

// sets the font to be used in the notification's msg
void ui_notification_set_msg_font (Notification *noti, Font *font) {

    if (noti) {
        if (noti->msg) noti->msg->font = font;
    }

}

// sets a custom background color for the notification
void ui_notification_set_bg_color (Notification *noti, RGBA_Color color) {

    if (noti) noti->bgcolor = color;

}

// creates a new notification
// type: default types have already created designs, select custom to pass your own
// lifetime: secs to display
// display_timestamp: option to display the timestamp of the notification
// title: the title of the notification (NULL for empty)
// msg: the message to be displayed (NULL for empty)
// uses the first set font for the texts with default values for sizes
Notification *ui_notification_create (NotificationType type, float lifetime, bool display_timestamp,
    const char *title, const char *msg) {

    Notification *noti = ui_notification_new ();
    if (noti) {
        noti->type = type;
        ui_notification_get_color (noti);
        noti->lifetime = lifetime;

        Font *default_font = ui_font_get_default ();

        if (display_timestamp) {
            // get the current local time the notification has been created
            noti->timestamp = timer_get_local_time ();

            noti->timestamp_text = ui_text_component_new ();
            if (noti->timestamp_text) {
                String *time_str = timer_time_to_string (noti->timestamp);
                ui_text_component_init (noti->timestamp_text, default_font,
                    NOTI_TIMESTAMP_DEFAULT_SIZE, RGBA_WHITE, 
                    time_str->str);
                str_delete (time_str);
            }
        }

        if (title) {
            noti->title = ui_text_component_new ();
            if (noti->title) {
                ui_text_component_init (noti->title, default_font, 
                    NOTI_TITLE_DEFAULT_SIZE, RGBA_WHITE, title);
            } 
        } 

        if (msg) {
            noti->msg = ui_text_component_new ();
            if (noti->msg) {
                ui_text_component_init (noti->msg, default_font, 
                    NOTI_MSG_DEFAULT_SIZE, RGBA_WHITE, msg);
            }
        }
    }

    return noti;

}

// updates the position of the notification;s elements
static void ui_notification_update_pos (Notification *noti) {

    if (noti) {
        u32 y_pos = noti->bgrect.y;

        if (noti->timestamp_text) {
            noti->timestamp_text->rect.y = noti->bgrect.y;
            y_pos += noti->timestamp_text->rect.h;
        }

        if (noti->title) {
            noti->title->rect.y = noti->timestamp_text ? 
                y_pos : noti->bgrect.y;
                y_pos += noti->title->rect.h;
        } 

        if (noti->msg) {
            noti->msg->rect.y = y_pos;
        } 
    }

}

// prepare the notification to be displayed in an upper notification center
static void ui_notification_prepare_upper (NotiCenter *noti_center, Notification *noti) {

    if (noti) {
        // prepare notification layout
        noti->bgrect.w = noti_center->bgrect.w - 10;
        noti->bgrect.x = noti_center->bgrect.x + 5;
        noti->bgrect.y = noti_center->bgrect.y + 5;

        if (noti->timestamp_text) {
            ui_text_component_draw (noti->timestamp_text);

            noti->timestamp_text->rect.x = noti->bgrect.x;
            noti->timestamp_text->rect.y = noti->bgrect.y;

            noti->bgrect.h += noti->timestamp_text->rect.h;
        }

        if (noti->title) {
            ui_text_component_draw (noti->title);

            noti->title->rect.x = noti->bgrect.x;
            noti->title->rect.y = noti->timestamp_text ? noti->bgrect.y + (noti->bgrect.h) : noti->bgrect.y;

            noti->bgrect.h += noti->title->rect.h;
        } 

        if (noti->msg) {
            ui_text_component_draw (noti->msg);

            noti->msg->rect.x = noti->bgrect.x;
            noti->msg->rect.y = noti->title ? noti->bgrect.y + (noti->bgrect.h) : noti->bgrect.y;

            noti->bgrect.h += noti->msg->rect.h;
        } 
    }

}

// prepare the notification to be displayed in a bottom notification center
static void ui_notification_prepare_bottom (NotiCenter *noti_center, Notification *noti) {

    if (noti) {
        // prepare notification layout
        noti->bgrect.w = noti_center->bgrect.w - 10;
        noti->bgrect.x = noti_center->bgrect.x + 5;
        noti->bgrect.y = noti_center->bgrect.y + 5;

        if (noti->timestamp_text) {
            ui_text_component_draw (noti->timestamp_text);

            noti->timestamp_text->rect.x = noti->bgrect.x;
            noti->timestamp_text->rect.y = noti->bgrect.y + 5;

            noti->bgrect.h += noti->timestamp_text->rect.h;
        }

        if (noti->title) {
            ui_text_component_draw (noti->title);

            noti->title->rect.x = noti->bgrect.x;
            noti->title->rect.y = noti->timestamp_text ? noti->bgrect.y + (noti->bgrect.h) : noti->bgrect.y;

            noti->bgrect.h += noti->title->rect.h;
        } 

        if (noti->msg) {
            ui_text_component_draw (noti->msg);

            noti->msg->rect.x = noti->bgrect.x;
            noti->msg->rect.y = noti->title ? noti->bgrect.y + (noti->bgrect.h) : noti->bgrect.y;

            noti->bgrect.h += noti->msg->rect.h;
        } 
    }

}

// adds the notification to the notification center where you want to display it
// and displays the notification for x seconds (lifetime)
void ui_notification_display (NotiCenter *noti_center, Notification *notification) {

    if (noti_center && notification) {
        // prepare the notification to be displayed in the notification center
        noti_center->bottom ? ui_notification_prepare_bottom (noti_center, notification) : ui_notification_prepare_upper (noti_center, notification);

        // add the notification to the notification center for display
        dlist_insert_after (noti_center->notifications, dlist_end (noti_center->notifications), notification);
    }

}

// creates the notification with the passed values and default options by notification type
// and then displays it in the notification center
void ui_notification_create_and_display (NotiCenter *noti_center, NotificationType type, 
    float lifetime, bool display_timestamp,
    const char *title, const char *msg) {

    if (noti_center) {
        // create the notification
        Notification *noti = ui_notification_create (type, lifetime, display_timestamp, title, msg);
        if (noti) ui_notification_display (noti_center, noti);
    }

}

// draws the notification to the screen
static void ui_notification_draw (Notification *noti) {

    if (noti) {
        render_basic_filled_rect (&noti->bgrect, noti->bgcolor);

        if (noti->timestamp) ui_text_component_render (noti->timestamp_text);
        if (noti->title) ui_text_component_render (noti->title);
        if (noti->msg) ui_text_component_render (noti->msg);
    }

}

#pragma endregion

#pragma region NotiCenter

static NotiCenter *ui_noti_center_new (void) {

    NotiCenter *noti_center = (NotiCenter *) malloc (sizeof (NotiCenter));
    if (noti_center) {
        memset (noti_center, 0, sizeof (NotiCenter));
        noti_center->notifications = dlist_init (ui_notification_delete, NULL);
        noti_center->active_notifications = dlist_init (ui_notification_delete, NULL);
    }

    return noti_center;

}

void ui_noti_center_delete (void *noti_center_ptr) {

    if (noti_center_ptr) {
        NotiCenter *noti_center = (NotiCenter *) noti_center_ptr;
        dlist_destroy (noti_center->notifications);
        dlist_destroy (noti_center->active_notifications);
        free (noti_center);
    }

}

// adjust noti center postion values
static void ui_noti_center_update_pos (NotiCenter *noti_center) {

    if (noti_center) {
        u32 screen_width = main_renderer->window_size.width;
        u32 screen_height = main_renderer->window_size.height;

        switch (noti_center->ui_pos) {
            case UI_POS_MIDDLE_CENTER: break;

            case UI_POS_UPPER_CENTER: {
                noti_center->bgrect.x = (screen_width / 2) - (noti_center->bgrect.w / 2);
                noti_center->bgrect.y = 0;
                noti_center->bottom = false;
            } break;
            case UI_POS_RIGHT_UPPER_CORNER: break;
            case UI_POS_RIGHT_CENTER: break;
            case UI_POS_RIGHT_BOTTOM_CORNER: break;
            case UI_POS_BOTTOM_CENTER: break;
            case UI_POS_LEFT_BOTTOM_CORNER: {
                noti_center->bgrect.x = 0;
                noti_center->bgrect.y = screen_height - noti_center->bgrect.h;
                noti_center->bottom = true;
            } break;
            case UI_POS_LEFT_CENTER: break;
            case UI_POS_LEFT_UPPER_CORNER: break;

            default: break;
        }
    }

}

// creates a new notification center
// max_display: max number of notifications to display at once
// position: where do you want the notification center to be
NotiCenter *ui_noti_center_create (u8 max_display, UIPosition pos) {

    NotiCenter *noti_center = NULL;

    UIElement *ui_element = ui_element_new (UI_NOTI_CENTER);

    if (ui_element) {
        noti_center = ui_noti_center_new ();
        if (noti_center) {
            noti_center->max_display = max_display;
            noti_center->ui_pos = pos;

            noti_center->bgrect.w = NOTI_CENTER_DEFAULT_WIDTH;
            noti_center->bgrect.h = NOTI_CENTER_DEFAULT_HEIGHT;

            // adjust noti center postion values
            ui_noti_center_update_pos (noti_center);

            ui_element->element = noti_center;
        }

        else ui_element_delete (ui_element);
    }

    return noti_center;

}

// sets the notification center position in the screen
void ui_noti_center_set_position (NotiCenter *noti_center, UIPosition pos) {

    if (noti_center) {
        noti_center->ui_pos = pos;
        ui_noti_center_update_pos (noti_center);
    }

}

// sets the notification center dimensions
void ui_noti_center_set_dimensions (NotiCenter *noti_center, u32 width, u32 height) {

    if (noti_center) {
        noti_center->bgrect.w = width;
        noti_center->bgrect.h = height;

        ui_noti_center_update_pos (noti_center);
    }

}

// sets the notification center background color
void ui_noti_center_set_bg_color (NotiCenter *noti_center, RGBA_Color color) {

    if (noti_center) noti_center->bgcolor = color;

}

// draws the notification center
void ui_noti_center_draw (NotiCenter *noti_center) {

    if (noti_center) {
        render_basic_outline_rect (&noti_center->bgrect, RGBA_WHITE);

        if (noti_center->active_notifications->size < noti_center->max_display) {
            if (noti_center->notifications->size > 0) {
                Notification *noti = NULL;
                for (ListElement *le = dlist_start (noti_center->notifications); le; le = le->next) {
                    noti = (Notification *) le->data;
                    
                    // check for available space in the notification center UI
                    u32 new_height = noti_center->used_height + noti->bgrect.h;
                    if (new_height <= noti_center->bgrect.h) {
                        // adjust notification position values
                        noti->bgrect.y = noti_center->used_height;
                        ui_notification_update_pos (noti);
                        
                        noti_center->used_height += noti->bgrect.h;

                        // push the notification to the active ones
                        void *noti_data = dlist_remove_element (noti_center->notifications, le);
                        dlist_insert_after (noti_center->active_notifications, 
                            dlist_end (noti_center->active_notifications), noti_data);
                        timer_start (((Notification *) noti_data)->life);
                        
                        if (noti_center->active_notifications->size >= noti_center->max_display) break;
                    }
                }
            }
        }

        // render & update the active notifications
        if (noti_center->active_notifications->size > 0) {
            Notification *noti = NULL;
            for (ListElement *le = dlist_start (noti_center->active_notifications); le; le = le->next) {
                noti = (Notification *) le->data;
                ui_notification_draw (noti);

                // check for lifetime
                if ((timer_get_ticks (noti->life) / 1000) >= noti->lifetime) 
                    dlist_remove_element (noti_center->active_notifications, le);
            }       
        }
    }

}

#pragma endregion