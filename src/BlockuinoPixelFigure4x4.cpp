#include "BlockuinoPixelFigure4x4.h"

// Define BLACK color for convenience
static const uint32_t BLACK = 0;

/**
 * Constructor implementation
 */
BlockuinoPixelFigure4x4::BlockuinoPixelFigure4x4(const String colorsStr[16], int startIndex, int pSize)
{
    panelSize = pSize;
    figureSize = 4;
    position = startIndex;

    // Parse the figure data into colors array
    for (int i = 0; i < 16; i++) {
        colors[i] = parseHexColor(colorsStr[i]);
    }
}

/**
 * Draw the 4x4 figure onto the NeoPixel strip.
 */
void BlockuinoPixelFigure4x4::draw() {
    // Clear previous drawing is handled by the user

    // Convert position to row and column
    int rowStart = position / panelSize;
    int colStart = position % panelSize;

    // Iterate through the 4x4 figure
    for (int r = 0; r < figureSize; r++) {
        for (int c = 0; c < figureSize; c++) {
            int rotatedRow, rotatedCol;

            // Apply rotation based on the direction
            switch (direction) {
                case 'N': // No rotation
                    rotatedRow = r;
                    rotatedCol = c;
                    break;
                case 'E': // 90 degrees clockwise
                    rotatedRow = figureSize - 1 - c;
                    rotatedCol = r;
                    break;
                case 'S': // 180 degrees
                    rotatedRow = figureSize - 1 - r;
                    rotatedCol = figureSize - 1 - c;
                    break;
                case 'W': // 90 degrees counter-clockwise
                    rotatedRow = c;
                    rotatedCol = figureSize - 1 - r;
                    break;
                default:
                    rotatedRow = r;
                    rotatedCol = c;
            }

            int figureIndex = rotatedRow * figureSize + rotatedCol;
            uint32_t currentColor = colors[figureIndex];

            // If color is not BLACK, draw it
            if (currentColor != BLACK) {
                int currentRow = rowStart + r;
                int currentCol = colStart + c;

                // Ensure within bounds
                if (currentRow >= 0 && currentRow < panelSize &&
                    currentCol >= 0 && currentCol < panelSize) {
                    int idx = currentRow * panelSize + currentCol;
                    if (idx >= 0 && idx < PixelUtility::getInstance().getStrip().numPixels()) {
                        PixelUtility::getInstance().getStrip().setPixelColor(PixelUtility::getInstance().pixel_matrixPixel(idx), currentColor);
                    }
                }
            }
        }
    }
}


/**
 * Check if a specific pixel is occupied.
 */
bool BlockuinoPixelFigure4x4::isPixelOccupied(int pixelIndex) const {
    for (int r = 0; r < figureSize; r++) {
        for (int c = 0; c < figureSize; c++) {
            int rotatedRow, rotatedCol;

            // Apply rotation based on the direction
            switch (direction) {
                case 'N': // No rotation
                    rotatedRow = r;
                    rotatedCol = c;
                    break;
                case 'E': // 90 degrees clockwise
                    rotatedRow = c;
                    rotatedCol = figureSize - 1 - r;
                    break;
                case 'S': // 180 degrees
                    rotatedRow = figureSize - 1 - r;
                    rotatedCol = figureSize - 1 - c;
                    break;
                case 'W': // 90 degrees counter-clockwise
                    rotatedRow = figureSize - 1 - c;
                    rotatedCol = r;
                    break;
                default:
                    rotatedRow = r;
                    rotatedCol = c;
            }

            int absRow = (position / panelSize) + rotatedRow;
            int absCol = (position % panelSize) + rotatedCol;
            int absIndex = absRow * panelSize + absCol;

            // Check if the current figure position matches the pixel index
            if (absIndex == pixelIndex && colors[r * figureSize + c] != BLACK) {
                return true;
            }
        }
    }
    return false;
}