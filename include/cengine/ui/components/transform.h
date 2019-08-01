#ifndef _CENGINE_UI_COMPONENT_TRANSFORM_
#define _CENGINE_UI_COMPONENT_TRANSFORM_

#include "cengine/ui/ui.h"

typedef struct UITransform {

    UIRect rect;
    int x_scale, y_scale;

} UITransform;

extern UITransform *ui_transform_component_new (void);

extern void ui_transform_component_delete (void *transform_ptr);

extern void ui_transform_component_set_values (UITransform *transform,
    int x, int y, int w, int h);

extern void ui_transform_component_set_scale (UITransform *transform, int x_scale, int y_scale);

extern UITransform *ui_transform_component_create (int x, int y, int w, int h);

#endif