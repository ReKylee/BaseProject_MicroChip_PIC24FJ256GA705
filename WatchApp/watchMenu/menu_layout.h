/*
 * Shared menu layout constants.
 */

#ifndef MENU_LAYOUT_H
#define MENU_LAYOUT_H

#ifndef MENU_ICON_SIZE
#define MENU_ICON_SIZE 16
#endif

#define MENU_CENTER_X 47
#define MENU_CENTER_Y 52
#define MENU_RADIUS 32
#define MENU_INNER_RADIUS (MENU_RADIUS - (MENU_ICON_SIZE/2) - 2)
#define MENU_RING_RADIUS (MENU_ICON_SIZE/2 + 3)
#define MENU_EDIT_RING_RADIUS 30
#define MENU_EDIT_LABEL_RADIUS 34
#define MENU_EDIT_TICK_RADIUS 2
#define MENU_EDIT_TICK_ORBIT_RADIUS 24
#define MENU_BITMAP_W 32
#define MENU_ICON_ROWS 16
#define MENU_HEADER_Y 1
#define MENU_HEADER_H 10
#define MENU_TIME_Y 1
#define MENU_TITLE_X 2
#define MENU_TITLE_Y 1

// Geometry reference for SEC_POINTS scaling
#define MENU_GEOM_CENTER_X 47
#define MENU_GEOM_CENTER_Y 47
#define MENU_GEOM_RADIUS 38

#endif // MENU_LAYOUT_H
