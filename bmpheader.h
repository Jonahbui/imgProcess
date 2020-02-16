// bmpfile.h
#ifndef _BMPHEADER_H_
#define _BMPHEADER_H_

#include <stdint.h>

#pragma pack(1)

typedef struct
{
    uint16_t type;              // Magic identifier
    uint32_t size;              // File size in bytes
    uint16_t reserved1;         // Not used
    uint16_t reserved2;         // Not used
    uint32_t offset;            // --
    uint32_t headerSize;        // Header size in bytes
    uint32_t width;             // Width of image
    uint32_t height;            // Height of image
    uint16_t planes;            // Number of color planes
    uint16_t bits;              // Bits per pixel
    uint32_t compression;       // Compression type
    uint32_t imageSize;         // Image size in bytes
    uint32_t xResolution;       // Pixels per meter
    uint32_t yResolution;       // Pixels per meter
    uint32_t nColors;           // Number of colors
    uint32_t importantColors;   // Important colors
}BMP_Header;
#endif
