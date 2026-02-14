#ifndef ICON_ASSET_H
#define ICON_ASSET_H

#include <stdint.h>

typedef struct {
    const uint8_t* pixels;
    const uint16_t* palette;
} IconAsset_t;

#endif // ICON_ASSET_H
