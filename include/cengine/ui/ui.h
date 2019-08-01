#ifndef _CENGINE_UI_H_
#define _CENGINE_UI_H_

#include <SDL2/SDL.h>

#include "cengine/types/types.h"

/*** Common HEX colors ***/

#define HEX_NO_COLOR        0x00000000
#define HEX_WHITE           0xFFFFFFFF
#define HEX_BLACK           0x000000FF

#define HEX_FULL_RED        0xFF0000FF
#define HEX_FULL_GREEN      0x00FF00FF
#define HEX_FULL_BLUE       0x0000FFFF

#define HEX_YELLOW          0xFFD32AFF
#define HEX_SAPPHIRE        0x1E3799FF

#define HEX_SILVER          0xBDC3C7FF

/*** Common RGBA Colors ***/

typedef SDL_Color RGBA_Color;

extern RGBA_Color RGBA_NO_COLOR;
extern RGBA_Color RGBA_WHITE;
extern RGBA_Color RGBA_BLACK;
extern RGBA_Color RGBA_RED;
extern RGBA_Color RGBA_GREEN;
extern RGBA_Color RGBA_BLUE;

/*** UI Positions */

typedef enum UIPosition {

    UI_POS_MIDDLE_CENTER = 0,

    UI_POS_UPPER_CENTER,
    UI_POS_RIGHT_UPPER_CORNER,
    UI_POS_RIGHT_CENTER,
    UI_POS_RIGHT_BOTTOM_CORNER,
    UI_POS_BOTTOM_CENTER,
    UI_POS_LEFT_BOTTOM_CORNER,
    UI_POS_LEFT_CENTER,
    UI_POS_LEFT_UPPER_CORNER

} UIPosition;

/*** UI Elements ***/

typedef enum UIElementType {

    UI_TEXTBOX,
    UI_IMAGE,
    UI_BUTTON,
    UI_INPUT,
    UI_CHECK,
    UI_NOTI_CENTER

} UIElementType;

#define DEFAULT_MAX_UI_ELEMENTS     10

typedef struct UIElement {

    i32 id;
    UIElementType type;
    void *element;

} UIElement;

// ui element constructor
extern UIElement *ui_element_new (UIElementType type);
extern void ui_element_delete (UIElement *ui_element);

typedef SDL_Rect UIRect;

extern UIRect ui_rect_create (u32 x, u32 y, u32 w, u32 h);
extern UIRect ui_rect_union (UIRect a, UIRect b);
extern UIRect ui_rect_render (SDL_Texture *srcTexture, UIRect *srcRect, u32 x, u32 y);

extern RGBA_Color ui_rgba_color_create (u8 r, u8 g, u8 b, u8 a);

/*** Public ui funcs ***/

// renders all the current active ui to the screen
extern void ui_render (void);

// initializes cengine's ui capabilities
extern u8 ui_init (void);

// sets the location of cengine's default ui assets
extern void ui_default_assets_set_path (const char *pathname);

// loads cengine's default ui assets
extern u8 ui_default_assets_load (void);

// destroys any cengine ui element left and deallocates memory
extern u8 ui_destroy (void);

#endif