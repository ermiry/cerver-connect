#include <SDL2/SDL_rect.h>

#include "cengine/types/types.h"

#include "cengine/renderer.h"

#include "cengine/ui/position.h"
#include "cengine/ui/components/transform.h"

void ui_position_update (void *transform_ptr, SDL_Rect *ref_rect) {

    if (transform_ptr) {
        UITransform *transform = (UITransform *) transform_ptr;

        SDL_Rect rect = { 0 };

        if (ref_rect) {
            rect.x = ref_rect->x;
            rect.y = ref_rect->y;
            rect.w = ref_rect->w;
            rect.h = ref_rect->h;
        }

        else {
            rect.w = main_renderer->window_size.width;
            rect.h = main_renderer->window_size.height;
        }

        switch (transform->pos) {
            case UI_POS_FREE: break;

            case UI_POS_MIDDLE_CENTER: {
                transform->rect.x = ((rect.w / 2) - (transform->rect.w / 2)) + rect.x;
                transform->rect.y = ((rect.h / 2) - (transform->rect.h / 2)) + rect.y;
            } break;

            case UI_POS_UPPER_CENTER: {
                transform->rect.x = ((rect.w / 2) - (transform->rect.w / 2)) + rect.x;
                transform->rect.y = rect.y;
            } break;

            case UI_POS_RIGHT_UPPER_CORNER: {
                transform->rect.x = (rect.w - transform->rect.w) + rect.x;
                transform->rect.y = rect.y;
            } break;

            case UI_POS_RIGHT_CENTER: {
                transform->rect.x = (rect.w - transform->rect.w) + rect.x;
                transform->rect.y = ((rect.h / 2) - (transform->rect.h / 2)) + rect.y;
            } break;

            case UI_POS_RIGHT_BOTTOM_CORNER: {
                transform->rect.x = (rect.w - transform->rect.w) + rect.x;
                transform->rect.y = (rect.h - transform->rect.h) + rect.y;
            } break;

            case UI_POS_BOTTOM_CENTER: {
                transform->rect.x = ((rect.w / 2) - (transform->rect.w / 2)) + rect.x;
                transform->rect.y = (rect.h - transform->rect.h) + rect.y;
            } break;

            case UI_POS_LEFT_BOTTOM_CORNER: {
                transform->rect.x = rect.x;
                transform->rect.y = (rect.h - transform->rect.h) + rect.y;
            } break;

            case UI_POS_LEFT_CENTER: {
                transform->rect.x = rect.x;
                transform->rect.y = ((rect.h / 2) - (transform->rect.h / 2)) + rect.y;
            } break;

            case UI_POS_LEFT_UPPER_CORNER: {
                transform->rect.x = rect.x;
                transform->rect.y = rect.y;
            } break;

            default: break;
        }
    }

}