#include "BlockuinoPixelFigure1x1.h"

// Define BLACK color for convenience
static const uint32_t BLACK = 0;

/**
 * Constructor implementation
 */
BlockuinoPixelFigure1x1::BlockuinoPixelFigure1x1(const String colorsStr[1], int startIndex, int pSize)
{
    panelSize = pSize;
    figureSize = 1;
    position = startIndex;
    color = parseHexColor(colorsStr[0]);
}

/**
 * Draw the 1x1 figure onto the NeoPixel strip.
 */
void BlockuinoPixelFigure1x1::draw() {
        // Set the pixel color if within bounds
    if (position >= 0 && position < PixelUtility::getInstance().getStrip().numPixels()) {
        PixelUtility::getInstance().getStrip().setPixelColor(PixelUtility::getInstance().pixel_matrixPixel(position), color);
    }
}

/**
 * Check if a specific pixel is occupied.
 */
bool BlockuinoPixelFigure1x1::isPixelOccupied(int pixelIndex) const {
    return (pixelIndex == position) && (color != BLACK);
}